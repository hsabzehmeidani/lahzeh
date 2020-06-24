/* In the name of Allah */
/**
 * @file date_check.c
 * @copyright (C) 1399 Hossein Sabzehmeidani
 * @license GNU General Public License (GPLv3+)
 */

#include "lahzeh.h"

#ifdef ENABLE_DATE_CHECK_C
/*****************************************************************************/
/**
 * Check Date (Solar Hijri)
 *
 * @since 1.0.0
 */
void
solar_hijri_check (struct date *d)
{
    int err = 0;

    if (d->year >= SH_YEAR_MIN && d->year <= SH_YEAR_MAX)
    {
        if (d->month >= 1 && d->month <= 6)
        {
            if (d->day >= 1 && d->day <= 31)
            {
            }
            else
            {
                printf ("[ERROR] D ∈ {1, ..., 31}\n");
                err = 1;
            }
        }
        else if (d->month >= 7 && d->month <= 11)
        {
            if (d->day >= 1 && d->day <= 30)
            {
            }
            else
            {
                printf ("[ERROR] D ∈ {1, ..., 30}\n");
                err = 1;
            }
        }
        else if (d->month == 12)
        {
            if (solar_hijri_leap (d->year))
            {
                if (d->day >= 1 && d->day <= 30)
                {
                }
                else
                {
                    printf ("[ERROR] D ∈ {1, ..., 30}\n");
                    err = 1;
                }
            }
            else
            {
                if (d->day >= 1 && d->day <= 29)
                {
                }
                else
                {
                    printf ("[ERROR] D ∈ {1, ..., 29}\n");
                    err = 1;
                }
            }
        }
        else
        {
            printf ("[ERROR] M ∈ {1, ..., 12}\n");
            err = 1;
        }
    }
    else
    {
        printf ("[ERROR] Y ∈ {%i, ..., %i}\n", SH_YEAR_MIN, SH_YEAR_MAX);
        err = 1;
    }

    if (err == 1)
    {
        d->year = 1;
        d->month = 1;
        d->day = 1;
        d->week = 5;
    }
}
/*****************************************************************************/
/**
 * Check Date (Lunar Hijri)
 *
 * @since 1.0.0
 */
void
lunar_hijri_check (struct date *d)
{
    int err = 0, check = 0;

    /* Crescent Lunar Hijri */
    if (strcmp (country_crescent, "IR") == 0)
    {
        struct crescent lhc;
        lunar_hijri_crescent (d->year, &lhc);

        if (d->year >= lhc.year_s && d->year <= lhc.year_e)
        {
            if (d->month >= 1 && d->month <= 12)
            {
                if (d->day >= 1 && d->day <= lhc.month[d->month - 1])
                {
                }
                else
                {
                    printf ("[ERROR] D ∈ {1, ..., %i}\n", lhc.month[d->month - 1]);
                    err = 1;
                }
            }
            else
            {
                printf ("[ERROR] M ∈ {1, ..., 12}\n");
                err = 1;
            }

            check = 1;
        }
    }

    if (check == 0)
    {
        if (d->year >= LH_YEAR_MIN && d->year <= LH_YEAR_MAX)
        {
            if (d->month == 1 || d->month == 3 || d->month == 5 || d->month == 7
                    || d->month == 9 || d->month == 11)
            {
                if (d->day >= 1 && d->day <= 30)
                {
                }
                else
                {
                    printf ("[ERROR] D ∈ {1, ..., 30}\n");
                    err = 1;
                }
            }
            else if (d->month == 2 || d->month == 4 || d->month == 6
                    || d->month == 8 || d->month == 10)
            {
                if (d->day >= 1 && d->day <= 29)
                {
                }
                else
                {
                    printf ("[ERROR] D ∈ {1, ..., 29}\n");
                    err = 1;
                }
            }
            else if (d->month == 12)
            {
                if (lunar_hijri_leap (d->year))
                {
                    if (d->day >= 1 && d->day <= 30)
                    {
                    }
                    else
                    {
                        printf ("[ERROR] D ∈ {1, ..., 30}\n");
                        err = 1;
                    }
                }
                else
                {
                    if (d->day >= 1 && d->day <= 29)
                    {
                    }
                    else
                    {
                        printf ("[ERROR] D ∈ {1, ..., 29}\n");
                        err = 1;
                    }
                }
            }
            else
            {
                printf ("[ERROR] M ∈ {1, ..., 12}\n");
                err = 1;
            }
        }
        else
        {
            printf ("[ERROR] Y ∈ {%i, ..., %i}\n", LH_YEAR_MIN, LH_YEAR_MAX);
            err = 1;
        }
    }

    if (err == 1)
    {
        d->year = 1;
        d->month = 1;
        d->day = 1;
        d->week = 5;
    }
}
/*****************************************************************************/
/**
 * Check Date (Gregorian Christmas)
 *
 * @since 1.0.0
 */
void
gregorian_christmas_check (struct date *d)
{
    int err = 0;

    if (d->year >= GC_YEAR_MIN && d->year <= GC_YEAR_MAX)
    {
        if (d->month == 1 || d->month == 3 || d->month == 5 || d->month == 7
                || d->month == 8 || d->month == 10 || d->month == 12)
        {
            if (d->day >= 1 && d->day <= 31)
            {
            }
            else
            {
                printf ("[ERROR] D ∈ {1, ..., 31}\n");
                err = 1;
            }
        }
        else if (d->month == 4 || d->month == 6 || d->month == 9
                || d->month == 11)
        {
            if (d->day >= 1 && d->day <= 30)
            {
            }
            else
            {
                printf ("[ERROR] D ∈ {1, ..., 30}\n");
                err = 1;
            }
        }
        else if (d->month == 2)
        {
            if (gregorian_christmas_leap (d->year))
            {
                if (d->day >= 1 && d->day <= 29)
                {
                }
                else
                {
                    printf ("[ERROR] D ∈ {1, ..., 29}\n");
                    err = 1;
                }
            }
            else
            {
                if (d->day >= 1 && d->day <= 28)
                {
                }
                else
                {
                    printf ("[ERROR] D ∈ {1, ..., 28}\n");
                    err = 1;
                }
            }
        }
        else
        {
            printf ("[ERROR] M ∈ {1, ..., 12}\n");
            err = 1;
        }
    }
    else
    {
        printf ("[ERROR] Y ∈ {%i, ..., %i}\n", GC_YEAR_MIN, GC_YEAR_MAX);
        err = 1;
    }

    if (err == 1)
    {
        d->year = 1;
        d->month = 1;
        d->day = 1;
        d->week = 1;
    }
}

#endif /* ENABLE_DATE_CHECK_C */
