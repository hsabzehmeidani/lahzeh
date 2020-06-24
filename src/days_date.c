/* In the name of Allah */
/**
 * @file days_date.c
 * @copyright (C) 1399 Hossein Sabzehmeidani
 * @license GNU General Public License (GPLv3+)
 */

#include "lahzeh.h"

#ifdef ENABLE_DAYS_DATE_C
/*****************************************************************************/
/**
 * Convert Days to Date (Solar Hijri)
 *
 * @since 1.0.0
 */
int
solar_hijri_date (int days, struct date *d)
{
    if (days <= 0)
    {
        days += -1;
    }

    int w = abs (days % 7);
    switch (w)
    {
        case 0:
            d->week = 4; /* PanjShanbeh */
            break;
        case 1:
            d->week = 5; /* Jomeh */
            break;
        case 2:
            d->week = 6; /* Shanbeh */
            break;
        case 3:
            d->week = 0; /* YekShanbeh */
            break;
        case 4:
            d->week = 1; /* DoShanbeh */
            break;
        case 5:
            d->week = 2; /* SehShanbeh */
            break;
        case 6:
            d->week = 3; /* ChaharShanbeh */
            break;
    }

    if (days < 0)
    {
        d->week = (9 - d->week) % 7;
    }

    d->year = 1;
    while ((days >= 365 && !solar_hijri_leap (d->year))
            || (days >= 366 && solar_hijri_leap (d->year)))
    {
        if (solar_hijri_leap (d->year))
        {
            days -= 366;
        }
        else
        {
            days -= 365;
        }
        d->year += 1;
    }

    int days_of_months[] =
    { 31, 31, 31, 31, 31, 31, 30, 30, 30, 30, 30, 29 };

    if (solar_hijri_leap (d->year))
    {
        days_of_months[11] = 30;
    }

    d->month = 0;
    for (int m = 0; m < 11; m++)
    {
        if (days > days_of_months[m])
        {
            d->month += 1;
            days -= days_of_months[m];
        }
        else
        {
            break;
        }
    }
    d->month += 1;

    d->day = days;

    return (d->year * 10000) + (d->month * 100) + d->day;
}
/*****************************************************************************/
/**
 * Convert Days to Date (Lunar Hijri)
 *
 * @since 1.0.0
 */
int
lunar_hijri_date (int days, struct date *d)
{
    if (days <= 0)
    {
        days += -1;
    }

    int w = abs (days % 7);
    switch (w)
    {
        case 0:
            d->week = 4; /* alKhamis */
            break;
        case 1:
            d->week = 5; /* alJumah */
            break;
        case 2:
            d->week = 6; /* asSabt */
            break;
        case 3:
            d->week = 0; /* alAhad */
            break;
        case 4:
            d->week = 1; /* alIthnayn */
            break;
        case 5:
            d->week = 2; /* alThulatha */
            break;
        case 6:
            d->week = 3; /* alArbia */
            break;
    }

    if (days < 0)
    {
        d->week = (9 - d->week) % 7;
    }

    d->year = 1;
    while ((days >= 354 && !lunar_hijri_leap (d->year))
            || (days >= 355 && lunar_hijri_leap (d->year)))
    {
        if (lunar_hijri_leap (d->year))
        {
            days -= 355;
        }
        else
        {
            days -= 354;
        }
        d->year += 1;
    }

    int days_of_months[] =
    { 30, 29, 30, 29, 30, 29, 30, 29, 30, 29, 30, 29 };

    if (lunar_hijri_leap (d->year))
    {
        days_of_months[11] = 30;
    }

    /* Crescent Lunar Hijri */
    if (strcmp (country_crescent, "IR") == 0)
    {
        struct crescent lhc;
        lunar_hijri_crescent (d->year, &lhc);

        if (d->year >= lhc.year_s && d->year <= lhc.year_e)
        {
            for (int m = 0; m < 12; m++)
            {
                days_of_months[m] = lhc.month[m];
            }
        }
    }

    d->month = 0;
    for (int m = 0; m < 11; m++)
    {
        if (days > days_of_months[m])
        {
            d->month += 1;
            days -= days_of_months[m];
        }
        else
        {
            break;
        }
    }
    d->month += 1;

    d->day = days;

    return (d->year * 10000) + (d->month * 100) + d->day;
}
/*****************************************************************************/
/**
 * Convert Days to Date (Gregorian Christmas)
 *
 * @since 1.0.0
 */
int
gregorian_christmas_date (int days, struct date *d)
{
    if (days <= 0)
    {
        days += -1;
    }

    int w = abs (days % 7);
    switch (w)
    {
        case 0:
            d->week = 0; /* Sunday */
            break;
        case 1:
            d->week = 1; /* Monday */
            break;
        case 2:
            d->week = 2; /* Tuesday */
            break;
        case 3:
            d->week = 3; /* Wednesday */
            break;
        case 4:
            d->week = 4; /* Thursday */
            break;
        case 5:
            d->week = 5; /* Friday */
            break;
        case 6:
            d->week = 6; /* Saturday */
            break;
    }

    if (days < 0)
    {
        d->week = (9 - d->week) % 7;
    }

    d->year = 1;
    while ((days >= 365 && !gregorian_christmas_leap (d->year))
            || (days >= 366 && gregorian_christmas_leap (d->year)))
    {
        if (gregorian_christmas_leap (d->year))
        {
            days -= 366;
        }
        else
        {
            days -= 365;
        }
        d->year += 1;
    }

    int days_of_months[] =
    { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    if (gregorian_christmas_leap (d->year))
    {
        days_of_months[1] = 29;
    }

    d->month = 0;
    for (int m = 0; m < 11; m++)
    {
        if (days > days_of_months[m])
        {
            d->month += 1;
            days -= days_of_months[m];
        }
        else
        {
            break;
        }
    }
    d->month += 1;

    d->day = days;

    return (d->year * 10000) + (d->month * 100) + d->day;
}

#endif /* ENABLE_DAYS_DATE_C */
