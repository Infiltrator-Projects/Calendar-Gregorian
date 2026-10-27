# Gregorian Calendar — model and historical scope

## Identity

- **Stable ID:** `gregorian`
- **Canonical provider name:** Gregorian Calendar
- **Provider kind:** calendar
- **Canonical output:** `Gregorian Calendar.so`

## Existing computational model

Resource-owned proleptic Gregorian arithmetic across the representable civil-date domain; locale-sensitive formatting remains ICU/CLDR-backed.

## Meaning and historical fidelity

**Implemented interpretation:** Gregorian civil arithmetic.

**Scope and limitations:** Before local adoption is proleptic; country-specific changeover is not modeled.

Date calculations and presentation must not be represented as evidence of historical use outside that scope. Where the maintained model does not define a date, the resource must report unsupported rather than returning a plausible alternative chronology.

## Conversion and presentation contract

Dates remain anchored to a canonical civil / Julian-day coordinate independent of the selected presentation resource. The installed calendar provider is responsible for fields, localized formatting, period starts and navigation. All these operations must agree on the supported date domain and reject out-of-range inputs explicitly. Switching presentation must not rewrite absolute timestamps or reorder underlying events.

## Evidence provenance

This description is derived from the existing Common resource definition, Calendar's model matrix and Common's historical-fidelity audit. It is not an independent historical certification.

- [Common temporal resource source](https://github.com/Infiltrator-Projects/Libraries/tree/main/resources/temporal)
- [Resource build definition](https://github.com/Infiltrator-Projects/Libraries/blob/main/resources/temporal/Makefile)
- [Chronology and time model contracts](https://github.com/Infiltrator-Projects/Calendar/blob/main/docs/MODELS.md)
- [Historical fidelity audit](https://github.com/Infiltrator-Projects/Libraries/blob/main/docs/TEMPORAL_HISTORICAL_FIDELITY.md)
- [Runtime provider contract](https://github.com/Infiltrator-Projects/Libraries/blob/main/docs/TEMPORAL_PROVIDERS.md)
