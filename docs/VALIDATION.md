# Gregorian Calendar — validation plan

**Evidence status:** no standalone CI, installer, published package, installed-system test or successful migration has been established in this repository. These are acceptance criteria, not completed test results.

## Required checks

- [ ] Migrate only the `gregorian` provider implementation and required shared API dependencies, retaining historical provenance.
- [ ] Build one loadable ELF `.so` named exactly `Gregorian Calendar.so` with portable target ABI.
- [ ] Validate versioned metadata (stable ID, kind, name) and all executable calendar provider entry points.
- [ ] Compare date fields, localized rendering, period boundaries and next/previous navigation against existing Common tests and independent calendar references.
- [ ] Confirm identical domain rejection for fields, formatting and navigation; numerical extremes fail without overflow, hangs or output mutation.
- [ ] Confirm missing/invalid resource is unavailable without fallback and without breaking other installed resources.
- [ ] Test the installed compiled bytes, not merely a separately rebuilt test copy.
- [ ] Test reproducibility, debug-symbol separation, clean installation, upgrades, rollback and removal.
- [ ] Verify the package owns only `/System/Resources/Calendars/Gregorian Calendar.so` plus its own nonconflicting metadata/documentation, and does not conflict with the former combined package.
- [ ] Run integration tests with Calendar, Files and System Settings where supported.

## Historical/model-specific regression

**Expected implemented model:** Resource-owned proleptic Gregorian arithmetic across the representable civil-date domain; locale-sensitive formatting remains ICU/CLDR-backed.

**Do not overclaim:** Before local adoption is proleptic; country-specific changeover is not modeled.

Inspect the upstream calendar regression suite at [test-calendars.c](https://github.com/Infiltrator-Projects/Libraries/blob/main/resources/temporal/tests/test-calendars.c) and the chronology/model matrix in [Calendar docs](https://github.com/Infiltrator-Projects/Calendar/blob/main/docs/MODELS.md). Individual accepted reference cases must be recorded with expected fields, formatting, operations and supported/unsupported date boundaries when the tests are migrated.

## Evidence policy

Check a box only with a reproducible commit, test run, environment and result. Upstream qualification of the combined package is not proof of this future standalone repository's packaging or release.
