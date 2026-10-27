# Gregorian Calendar — architecture

## Current ownership versus target ownership

**Currently implemented:** [Libraries/Common](https://github.com/Infiltrator-Projects/Libraries/tree/main/resources/temporal) compiles this provider from its `resources/temporal` tree and ships it inside the combined `infiltrator-calendar-resources` package. The new repository currently has Markdown only.

**Intended:** this repository becomes the source, build, test, package and release owner for exactly one calendar provider (`gregorian`), without embedding other calendar implementations. Truly shared APIs, coordinate arithmetic, resource ABI validation and runtime discovery remain in Common.

## Native resource contract

- **Installation path:** `/System/Resources/Calendars/Gregorian Calendar.so`.
- **Identity:** versioned metadata through `infiltratr_temporal_resource_metadata_v1`; stable ID `gregorian`, kind calendar, canonical display name.
- **Executable contract:** validated calendar provider ABI for fields, formatting and navigation; metadata alone is insufficient.
- **Discovery:** Common scans native system resource directories, rejects unsupported objects, symlinks, malformed/wrong-kind modules and duplicate identities according to the documented runtime policy.
- **Consumers:** Calendar, Files, System Settings and the desktop resolve the same installed provider through Common, rather than bundling copies.
- **Trust boundary:** a native `.so` executes in the loading application's process. Only trusted, system-installed resources are within the present contract.

## Build and packaging boundary

The authoritative build currently lives in `Libraries/resources/temporal/Makefile`, with executable contract tests in `Libraries/resources/temporal/tests/test-calendars.c`. Direct compilation must produce the canonical filename without aliases or post-build renames. Portable binaries must not silently inherit the build host's `-march=native` requirements. Shared engine helpers may be linked without pulling in unrelated calendar algorithms.

Independent packaging requires coordinated retirement or splitting of the combined package's ownership of this exact path. Two Debian packages must never claim the same installed resource simultaneously. Retain existing stable IDs and ABI contracts throughout migration.

## Failure boundaries

If this provider is missing or invalid it is unavailable; consumers must not silently substitute another calendar. A fault in this optional provider must not invalidate unrelated providers. No source migration, packaging transition or ABI change is made by these Markdown documents.

- [Common temporal resource source](https://github.com/Infiltrator-Projects/Libraries/tree/main/resources/temporal)
- [Resource build definition](https://github.com/Infiltrator-Projects/Libraries/blob/main/resources/temporal/Makefile)
- [Chronology and time model contracts](https://github.com/Infiltrator-Projects/Calendar/blob/main/docs/MODELS.md)
- [Historical fidelity audit](https://github.com/Infiltrator-Projects/Libraries/blob/main/docs/TEMPORAL_HISTORICAL_FIDELITY.md)
- [Runtime provider contract](https://github.com/Infiltrator-Projects/Libraries/blob/main/docs/TEMPORAL_PROVIDERS.md)
