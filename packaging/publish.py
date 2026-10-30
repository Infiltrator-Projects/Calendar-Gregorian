#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Publish exactly the qualified DEB, native RUN and complete source ZIP."""
import hashlib
import json
import os
from pathlib import Path
import subprocess
import tempfile


def gh(*arguments, optional=False):
    result = subprocess.run(["gh", *arguments], text=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    if optional and result.returncode:
        # Only absent resources are optional; permission/network errors fail.
        if "HTTP 404" in result.stderr or "release not found" in result.stderr.lower():
            return None
    if result.returncode:
        raise RuntimeError(result.stderr)
    return result.stdout


root = Path("release")
contract = json.loads((root / "contract.json").read_text())
source = os.environ["GITHUB_SHA"]
repository = os.environ["GITHUB_REPOSITORY"]
assert contract["commit"] == source
assets = contract["assets"]
assert len(assets) == 3 and {Path(x).suffix for x in assets} == {".deb", ".run", ".zip"}
for name, digest in assets.items():
    assert Path(name).name == name
    assert hashlib.sha256((root / name).read_bytes()).hexdigest() == digest
head = json.loads(gh("api", f"repos/{repository}/git/ref/heads/main"))["object"]["sha"]
if head != source:
    print("Qualified commit was superseded; publication skipped.")
    raise SystemExit(0)
tag = "v" + contract["version"]
identity = gh("api", f"repos/{repository}/git/ref/tags/{tag}", optional=True)
if identity:
    identity = json.loads(identity)["object"]
    assert identity["type"] == "commit", "Released tag does not point to a commit"
    if identity["sha"] != source:
        # An already published VERSION is immutable. A workflow-only maintenance
        # commit must not attempt a second release, but a product/source change
        # without a version bump must still fail closed.
        comparison = json.loads(gh("api", f"repos/{repository}/compare/{identity['sha']}...{source}"))
        files = comparison.get("files", [])
        governance = all(
            entry["filename"].startswith(".github/workflows/")
            or entry["filename"] == "packaging/publish.py"
            for entry in files
        )
        if comparison.get("status") in ("ahead", "identical") and governance and len(files) < 300:
            print("Existing published version and unchanged product inputs; governance-only push skipped.")
            raise SystemExit(0)
        raise AssertionError("Advance VERSION before changing a released product")
existing = gh("release", "view", tag, "--json", "isDraft,targetCommitish", optional=True)
paths = [str(root / x) for x in assets]
if existing:
    existing = json.loads(existing)
    if existing["isDraft"]:
        if not identity:
            assert existing["targetCommitish"] == source
        gh("release", "upload", tag, *paths, "--clobber")
else:
    gh("release", "create", tag, *paths, "--target", source, "--draft",
       "--title", contract["name"] + " " + contract["version"],
       "--notes", "Portable amd64 Debian package, hardware-native source installer (aggressive CPU tuning, LTO and two-pass PGO), and complete source ZIP. Each package installs this provider only.")


def verify():
    remote = json.loads(gh("release", "view", tag, "--json", "assets"))["assets"]
    assert sorted(x["name"] for x in remote) == sorted(assets)
    with tempfile.TemporaryDirectory() as temporary:
        gh("release", "download", tag, "--dir", temporary)
        for name, digest in assets.items():
            assert hashlib.sha256((Path(temporary) / name).read_bytes()).hexdigest() == digest


verify()
if not existing or existing["isDraft"]:
    gh("release", "edit", tag, "--draft=false", "--latest")
verify()
print("Published and byte-verified " + tag + " with exactly three assets.")
