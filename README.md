# Gregorian Calendar

**Resource:** `Calendar-Gregorian` · **Kind:** Calendar · **Stable ID:** `gregorian` · **Compiled file:** `Gregorian Calendar.so`

Gregorian civil arithmetic. This project represents one independently installable InfiltratorOS calendar resource. The calendar converts and presents dates according to its own rules; it is not a standalone desktop app.

## Implementation contract

- **Model:** Resource-owned proleptic Gregorian arithmetic across the representable civil-date domain; locale-sensitive formatting remains ICU/CLDR-backed.
- **Historical scope:** Before local adoption is proleptic; country-specific changeover is not modeled
- **Resource identity:** `gregorian` in validated versioned module metadata; the human-readable filename is not the identity.
- **Install location:** `/System/Resources/Calendars/Gregorian Calendar.so` (case-sensitive).
- **Consumers:** InfiltratorOS Calendar, Files, System Settings and other clients through Common's temporal-resource API.

## Current project status

**Source copied and build verified.** This repository contains the implementation of `gregorian`, the supporting code it needs, a one-provider `Makefile` and focused regression fixtures. The copy is based on Common 1.19.78 at `8d60662114e3`; the original Common source remains unchanged.

Run `make` to produce `build/Gregorian Calendar.so` and `make check` to run this provider's checks. No Common checkout or Common archive is required. The current combined Common package and its installation ownership remain in place; this copy does not introduce an independent installer or release.

See [source provenance and build details](SOURCE.md), [source manifest](SOURCE-MANIFEST.json) and [recorded validation](VALIDATION-RESULTS.json).

## Documents

- [Model and fidelity](docs/MODEL.md)
- [Architecture and ownership](docs/ARCHITECTURE.md)
- [Validation requirements](docs/VALIDATION.md)
- [Migration roadmap](docs/ROADMAP.md)
- [Documentation index](docs/README.md)

## Authoritative references

- [Common temporal resource source](https://github.com/Infiltrator-Projects/Libraries/tree/main/resources/temporal)
- [Resource build definition](https://github.com/Infiltrator-Projects/Libraries/blob/main/resources/temporal/Makefile)
- [Chronology and time model contracts](https://github.com/Infiltrator-Projects/Calendar/blob/main/docs/MODELS.md)
- [Historical fidelity audit](https://github.com/Infiltrator-Projects/Libraries/blob/main/docs/TEMPORAL_HISTORICAL_FIDELITY.md)
- [Runtime provider contract](https://github.com/Infiltrator-Projects/Libraries/blob/main/docs/TEMPORAL_PROVIDERS.md)

## Independent forensic audit

See [audit findings](docs/FORENSIC-AUDIT.md) for corrections, numerical-model limits and unresolved authority disagreements. A successful build is not a historical-accuracy certificate.
