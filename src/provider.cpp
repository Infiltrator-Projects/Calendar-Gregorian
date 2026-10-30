// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 1993-2026 Shannon Smith

/* Native proleptic Gregorian calendar resource. */

#include <infiltratr/arithmetic.h>
#include <infiltratr/core.h>
#include <infiltratr/temporal_calendar.h>

#include <glib.h>
#include <stdint.h>
#include <string.h>

#include "calendar-types.h"
#include "icu-calendar.h"
#include "resource-format.h"
#include "integer-math.h"
#include "julian-day.h"

#if defined(_WIN32)
#define CALENDAR_RESOURCE_EXPORT __declspec(dllexport)
#elif defined(__GNUC__)
#define CALENDAR_RESOURCE_EXPORT __attribute__((visibility("default")))
#else
#define CALENDAR_RESOURCE_EXPORT
#endif

static int64_t
signed_year(const InfiltratrTemporalCalendarFields *fields)
{
    return fields->auxiliary == 0 ?
        infiltratr_i64_subtract_saturating(1, fields->year) :
        fields->year;
}

static void
set_signed_year(int64_t year,
                InfiltratrTemporalCalendarFields *fields)
{
    if (year >= 1)
    {
        fields->year = year;
        fields->auxiliary = 1;
    }
    else
    {
        fields->year = infiltratr_i64_subtract_saturating(1, year);
        fields->auxiliary = 0;
    }
}

static int64_t
fields_to_jdn(const InfiltratrTemporalCalendarFields *fields)
{
    return calendar_gregorian_to_jdn(
        signed_year(fields), fields->month, fields->day);
}

/* The ICU-backed formatter and the arithmetic callbacks share this
 * UTC-noon domain. Reject before narrowing extreme JDNs into civil fields. */
static bool provider_jdn_supported(int64_t jdn)
{
    return jdn >= INT64_C(2440588) - INT64_C(100000000) &&
           jdn <= INT64_C(2440588) + INT64_C(99999999);
}

static bool
provider_fields(const InfiltratrTemporalCalendarProvider *provider,
                int64_t jdn,
                InfiltratrTemporalCalendarFields *fields)
{
    gint year;
    gint month;
    gint day;

    (void)provider;
    if (fields == NULL || !provider_jdn_supported(jdn) ||
        !calendar_gregorian_jdn_representable(jdn))
        return false;

    calendar_jdn_to_gregorian(jdn, &year, &month, &day);
    *fields = InfiltratrTemporalCalendarFields{0, month, day, 0, false};
    set_signed_year(year, fields);
    return true;
}

static bool
provider_format(const InfiltratrTemporalCalendarProvider *provider,
                int64_t jdn,
                InfiltratrTemporalCalendarDatePart part,
                char *buffer,
                size_t capacity,
                size_t *length)
{
    InfiltratrTemporalCalendarFields checked;
    if (!provider_fields(provider, jdn, &checked))
        return false;
    return resource_format_icu(
        CALENDAR_CALENDAR_MODE_GREGORIAN, "gregorian", jdn, part, buffer, capacity, length);
}

static bool
provider_period_start(const InfiltratrTemporalCalendarProvider *provider,
                      int64_t jdn,
                      int64_t *result)
{
    InfiltratrTemporalCalendarFields fields;

    (void)provider;
    if (result == NULL || !provider_fields(provider, jdn, &fields))
        return false;
    fields.day = 1;
    const int64_t candidate = fields_to_jdn(&fields);
    if (!provider_jdn_supported(candidate) ||
        !calendar_gregorian_jdn_representable(candidate)) return false;
    *result = candidate;
    return true;
}

static bool
provider_add_periods(const InfiltratrTemporalCalendarProvider *provider,
                     int64_t jdn,
                     int32_t amount,
                     int64_t *result)
{
    InfiltratrTemporalCalendarFields fields;
    int64_t year;
    int64_t serial;

    (void)provider;
    if (result == NULL || !provider_fields(provider, jdn, &fields))
        return false;

    year = signed_year(&fields);
    serial = infiltratr_i64_add_saturating(
        infiltratr_i64_add_saturating(
            infiltratr_i64_multiply_saturating(year, 12),
            fields.month - 1),
        amount);
    year = calendar_floor_divide(serial, 12);
    fields.month = (int32_t)calendar_positive_modulo(serial, 12) + 1;
    set_signed_year(year, &fields);
    fields.day = MIN(
        fields.day,
        calendar_gregorian_month_length(year, fields.month));
    const int64_t candidate = fields_to_jdn(&fields);
    if (!provider_jdn_supported(candidate) ||
        !calendar_gregorian_jdn_representable(candidate)) return false;
    *result = candidate;
    return true;
}

static bool
provider_add_years(const InfiltratrTemporalCalendarProvider *provider,
                   int64_t jdn,
                   int32_t amount,
                   int64_t *result)
{
    InfiltratrTemporalCalendarFields fields;
    int64_t year;

    (void)provider;
    if (result == NULL || !provider_fields(provider, jdn, &fields))
        return false;

    year = infiltratr_i64_add_saturating(signed_year(&fields), amount);
    set_signed_year(year, &fields);
    fields.day = MIN(
        fields.day,
        calendar_gregorian_month_length(year, fields.month));
    const int64_t candidate = fields_to_jdn(&fields);
    if (!provider_jdn_supported(candidate) ||
        !calendar_gregorian_jdn_representable(candidate)) return false;
    *result = candidate;
    return true;
}

static const InfiltratrTemporalResourceMetadata gregorian_metadata = {
    sizeof(InfiltratrTemporalResourceMetadata), INFILTRATR_TEMPORAL_RESOURCE_METADATA_ABI,
    INFILTRATR_TEMPORAL_RESOURCE_CALENDAR, "gregorian", INFILTRATR_TEMPORAL_DISPLAY_NAME,
    false, false, false
};

static const InfiltratrTemporalCalendarProvider gregorian_provider = {
    sizeof(InfiltratrTemporalCalendarProvider), INFILTRATR_TEMPORAL_CALENDAR_PROVIDER_ABI,
    "gregorian", provider_fields, provider_format, provider_period_start,
    provider_add_periods, provider_add_years
};

extern "C" CALENDAR_RESOURCE_EXPORT const InfiltratrTemporalResourceMetadata *
infiltratr_temporal_resource_metadata_v1(void);
extern "C" CALENDAR_RESOURCE_EXPORT const InfiltratrTemporalCalendarProvider *
infiltratr_temporal_calendar_provider_v1(void);

extern "C" CALENDAR_RESOURCE_EXPORT const InfiltratrTemporalResourceMetadata *
infiltratr_temporal_resource_metadata_v1(void)
{
    return &gregorian_metadata;
}

extern "C" CALENDAR_RESOURCE_EXPORT const InfiltratrTemporalCalendarProvider *
infiltratr_temporal_calendar_provider_v1(void)
{
    return &gregorian_provider;
}
