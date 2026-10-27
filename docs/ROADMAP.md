# Gregorian Calendar — independent resource roadmap

## Starting point

This is one of 54 new single-resource repositories (31 calendars, 23 clocks). The current implementation is located in [Libraries/Common](https://github.com/Infiltrator-Projects/Libraries/tree/main/resources/temporal), in a 54-resource combined build and package. This repository is documentation-only.

## Migration milestones

- [ ] Establish precise upstream source/test provenance and model-specific scope for `gregorian`.
- [ ] Move authoritative provider implementation into this repository while preserving shared Common mechanisms; do not create competing implementations.
- [ ] Add its independent portable build, source/version metadata and ABI verification.
- [ ] Migrate model-specific, failure-boundary, locale and historical regression tests.
- [ ] Build one canonical `Gregorian Calendar.so` and one independently owned installer/package, with clean uninstall and upgrade.
- [ ] Coordinate Common's package manifest so its existing combined package no longer owns the migrated file.
- [ ] Qualify Debian 12/13 and Ubuntu 24.04-compatible runtime environments, plus actual consumer discovery/formatting/navigation.
- [ ] Publish release artifacts only after reproducibility, installation, integration and regression evidence is recorded.
- [ ] Update documentation to reflect verified code ownership and release status.

## Non-goals of documentation setup

This stage creates no implementation, `.so`, package, release, workflow or installer; it changes no other repository and cannot be counted as functional completion.
