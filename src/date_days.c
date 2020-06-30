/* In the name of Allah */
/**
 * @file date_days.c
 * @copyright (C) 1399 Hossein Sabzehmeidani
 * @license GNU General Public License (GPLv3+)
 */

#include "lahzeh.h"

#ifdef ENABLE_DATE_DAYS_C
/*****************************************************************************/
/**
 * Convert Date to Days (Solar Hijri)
 *
 * @since 1.0.0
 */
int
solar_hijri_days (struct date d)
{
    int days = d.day;
    int days_of_months[] =
    { 31, 31, 31, 31, 31, 31, 30, 30, 30, 30, 30, 29 };

    if (solar_hijri_leap (d.year))
    {
        days_of_months[11] = 30;
    }

    for (int m = 0; m < d.month - 1; m++)
    {
        days += days_of_months[m];
    }

    for (int y = 1; y < d.year; y++)
    {
        if (solar_hijri_leap (y))
        {
            days += 366;
        }
        else
        {
            days += 365;
        }
    }

    return days;
}
/*****************************************************************************/
/**
 * Convert Date to Days (Lunar Hijri)
 *
 * @since 1.0.0
 */
int
lunar_hijri_days (struct date d)
{
    int days = d.day;
    int days_of_months[] =
    { 30, 29, 30, 29, 30, 29, 30, 29, 30, 29, 30, 29 };

    if (lunar_hijri_leap (d.year))
    {
        days_of_months[11] = 30;
    }

    /* Crescent Lunar Hijri */
    if (strcmp (country_crescent, "IR") == 0)
    {
        struct crescent lhc;
        lunar_hijri_crescent (d.year, &lhc);

        if (d.year >= lhc.year_s && d.year <= lhc.year_e)
        {
            for (int m = 0; m < 12; m++)
            {
                days_of_months[m] = lhc.month[m];
            }
        }
    }

    for (int m = 0; m < d.month - 1; m++)
    {
        days += days_of_months[m];
    }

    for (int y = 1; y < d.year; y++)
    {
        if (lunar_hijri_leap (y))
        {
            days += 355;
        }
        else
        {
            days += 354;
        }
    }

    return days;
}
/*****************************************************************************/
/**
 * Convert Date to Days (Gregorian Christmas)
 *
 * @since 1.0.0
 */
int
gregorian_christmas_days (struct date d)
{
    int days = d.day;
    int days_of_months[] =
    { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    if (gregorian_christmas_leap (d.year))
    {
        days_of_months[1] = 29;
    }

    for (int m = 0; m < d.month - 1; m++)
    {
        days += days_of_months[m];
    }

    for (int y = 1; y < d.year; y++)
    {
        if (gregorian_christmas_leap (y))
        {
            days += 366;
        }
        else
        {
            days += 365;
        }
    }

    return days;
}

#endif /* ENABLE_DATE_DAYS_C */
