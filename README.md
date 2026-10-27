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

**Documentation-only repository.** The implementation, tests and combined Debian packaging are still owned by [Libraries/Common](https://github.com/Infiltrator-Projects/Libraries/tree/main/resources/temporal). No independent build, installer, release or successful standalone qualification is claimed here yet. Do not confuse repository creation with migration or release readiness.

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
