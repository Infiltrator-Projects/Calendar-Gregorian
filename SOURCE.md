# Gregorian Calendar — source copy record

This document records the initial extraction of provider `gregorian` from Common 1.19.78. Current builds use the independent provider implementation and the authoritative pinned Common submodule.

## Origin and scope

- **Source:** [Libraries/Common 1.19.78](https://github.com/Infiltrator-Projects/Libraries/tree/8d60662114e3052380f6f88ad3cacd9732ae7131).
- **Source revision:** `8d60662114e3052380f6f88ad3cacd9732ae7131`.
- **Original entry:** `resources/temporal/src/calendars/gregorian.c`.
- **Local entry:** `src/provider.c`.
- **Output:** `Gregorian Calendar.so`.
- **Native resource path:** `/System/Resources/Calendars/Gregorian Calendar.so`.
- **Original Common code:** retained unchanged. The original extraction was a copy, not a removal. Independent packaging now transfers only this installed module through dpkg; Common source remains retained.

Combined source files were selected for this provider and split by keeping its existing operations, data and required helper definitions. Inactive provider branches and unreachable definitions were removed. At the time of extraction, shared helpers were copied locally. That historical arrangement was superseded by the Common submodule and static archive; the current Makefile rejects copied Common headers.

Public Common ABI headers retain compatibility declarations. Those declarations do not install or implement the other providers. The built module exports only its metadata entry and its `calendar` operation-table entry. Existing notices and the original GPL license are retained.

`SOURCE-MANIFEST.json` records original paths, original/copy hashes, selected definitions and the build configuration. Its hashes identify this initial extraction; later local edits legitimately change the copied hashes.

## Build and check

Use C11 and C++20 compilers, GNU Make and pkg-config; initialise the exact Common submodule recorded by the Makefile. The provider uses the GLib and ICU development packages.

```sh
make
make check
```

The build directly creates `build/Gregorian Calendar.so`. The provider uses the host's ICU/CLDR data; the pinned Common submodule supplies the ICU bridge, release and installation tools. See `docs/PACKAGING.md`.

## Recorded checks

- Independent build with strict C11 warnings treated as errors.
- Metadata, stable ID, canonical name, callback ABI and export checks.
- **883** observations matched the original Common-built provider, including applicable conversion, formatting, navigation, timing and invalid-input cases.
- **84** provider-specific regression fixtures are retained under `tests/`.
- Common's existing calendar and clock module suites passed against the complete set of 54 independently built copies: **6 calendar tests and 16 clock tests**.

See `VALIDATION-RESULTS.json` for the tested host and exact source revision. This verifies the copy against the existing implementation; it is not an additional historical-fidelity audit or a cross-platform release qualification.
