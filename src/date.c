/* In the name of Allah */
/**
 * @file date.c
 * @copyright (C) 1399 Hossein Sabzehmeidani
 * @license GNU General Public License (GPLv3+)
 */

#include "lahzeh.h"

#ifdef ENABLE_DATE_C
/*****************************************************************************/
/**
 * Current Date
 *
 * @since 1.0.0
 */
int
date_current (struct locale l, struct date *d)
{
    char language[LEN_LOCALE + 1];
    sprintf (language, "LANG=%s_%s.%s", l.language, l.country, l.charset);
    putenv (language);
    sprintf (language, "LANGUAGE=%s_%s.%s", l.language, l.country, l.charset);
    putenv (language);
    sprintf (language, "%s_%s.%s", l.language, l.country, l.charset);
    setlocale (LC_ALL, language);

    char timezone[LEN_TIMEZONE2 + 1];
    sprintf (timezone, "TZ=%s", l.timezone);
    putenv (timezone);

    time_t t_time = time (NULL);
    struct tm *t_info;
    t_info = localtime (&t_time);

    d->year = t_info->tm_year + 1900;
    d->month = t_info->tm_mon + 1;
    d->day = t_info->tm_mday;
    d->week = t_info->tm_wday;

    //debug_printf("[Current Date] %04i-%02i-%02i\n", d->year, d->month, d->day);

    return (d->year * 10000) + (d->month * 100) + d->day;
}
/*****************************************************************************/
/**
 * Convert Date
 *
 * @since 1.0.0
 */
void
date_convert (char c1[LEN_CALENDAR + 1],
              char c2[LEN_CALENDAR + 1],
              struct date *d)
{
    struct date diff_gc_sh =
    { 622, 3, 22, 5 };
    struct date diff_gc_lh =
    { 622, 7, 19, 5 };
    struct date diff_sh_lh =
    { 1, 4, 27, 5 };

    /* Gregorian -> Solar */
    if (strcmp (c1, "GC") == 0 && strcmp (c2, "SH") == 0)
    {
        solar_hijri_date (gregorian_christmas_days (*d)
                          - gregorian_christmas_days (diff_gc_sh) + 1, d);
    }

    /* Solar -> Gregorian */
    else if (strcmp (c1, "SH") == 0 && strcmp (c2, "GC") == 0)
    {
        gregorian_christmas_date (solar_hijri_days (*d)
                                  + gregorian_christmas_days (diff_gc_sh) - 1, d);
    }

    /* Gregorian -> Lunar */
    else if (strcmp (c1, "GC") == 0 && strcmp (c2, "LH") == 0)
    {
        lunar_hijri_date (gregorian_christmas_days (*d)
                          - gregorian_christmas_days (diff_gc_lh) + 1, d);
    }

    /* Lunar -> Gregorian */
    else if (strcmp (c1, "LH") == 0 && strcmp (c2, "GC") == 0)
    {
        gregorian_christmas_date (lunar_hijri_days (*d)
                                  + gregorian_christmas_days (diff_gc_lh) - 1, d);
    }

    /* Solar -> Lunar */
    else if (strcmp (c1, "SH") == 0 && strcmp (c2, "LH") == 0)
    {
        lunar_hijri_date (solar_hijri_days (*d)
                          - solar_hijri_days (diff_sh_lh) + 1, d);
    }

    /* Lunar -> Solar */
    else if (strcmp (c1, "LH") == 0 && strcmp (c2, "SH") == 0)
    {
        solar_hijri_date (lunar_hijri_days (*d)
                          + solar_hijri_days (diff_sh_lh) - 1, d);
    }

    else
    {
        debug_printf("[ERROR] Calendars include: SH, LH, GC.\n");
        d->year = 1;
        d->month = 1;
        d->day = 1;
        d->week = 5;
    }
}
/*****************************************************************************/
/**
 * Return Date
 *
 * @since 1.0.0
 */
char*
date_return (struct locale l,
             struct date d,
             char c[LEN_CALENDAR + 1],
             char f[LEN_FORMAT + 1])
{
    char language[LEN_LOCALE + 1];
    sprintf (language, "LANG=%s_%s.%s", l.language, l.country, l.charset);
    putenv (language);
    sprintf (language, "LANGUAGE=%s_%s.%s", l.language, l.country, l.charset);
    putenv (language);
    sprintf (language, "%s_%s.%s", l.language, l.country, l.charset);
    setlocale (LC_ALL, language);

    char timezone[LEN_TIMEZONE2 + 1];
    sprintf (timezone, "TZ=%s", l.timezone);
    putenv (timezone);

    char folder[LEN_FILE];
    sprintf (folder, "%sres/languages", path);
    bindtextdomain (APP_NAME, folder);
    textdomain (APP_NAME);

    struct mwname mw;

    for (int i = 0; i < 12; i++)
    {
        mw.mon[i] = malloc ((LEN_MNAME_MIN + 1) * sizeof(char));
        if (mw.mon[i] == NULL)
        {
            debug_printf("[ERROR] Could not allocate space for object \"MonName\".\n");
            exit (1);
        }
    }
    for (int i = 0; i < 12; i++)
    {
        mw.month[i] = malloc ((LEN_MNAME_MAX + 1) * sizeof(char));
        if (mw.month[i] == NULL)
        {
            debug_printf("[ERROR] Could not allocate space for object \"MonthName\".\n");
            exit (1);
        }
    }
    for (int i = 0; i < 7; i++)
    {
        mw.wee[i] = malloc ((LEN_WNAME_MIN + 1) * sizeof(char));
        if (mw.wee[i] == NULL)
        {
            debug_printf("[ERROR] Could not allocate space for object \"WeeName\".\n");
            exit (1);
        }
    }
    for (int i = 0; i < 7; i++)
    {
        mw.week[i] = malloc ((LEN_WNAME_MAX + 1) * sizeof(char));
        if (mw.week[i] == NULL)
        {
            debug_printf("[ERROR] Could not allocate space for object \"WeekName\".\n");
            exit (1);
        }
    }

    if (strcmp (c, "SH") == 0)
    {
        strcpy (mw.mon[0], _("Far"));
        strcpy (mw.mon[1], _("Ord"));
        strcpy (mw.mon[2], _("Kho"));
        strcpy (mw.mon[3], _("Tir"));
        strcpy (mw.mon[4], _("Mor"));
        strcpy (mw.mon[5], _("Sha"));
        strcpy (mw.mon[6], _("Meh"));
        strcpy (mw.mon[7], _("Aba"));
        strcpy (mw.mon[8], _("Aza"));
        strcpy (mw.mon[9], _("Dey"));
        strcpy (mw.mon[10], _("Bah"));
        strcpy (mw.mon[11], _("Esf"));

        strcpy (mw.month[0], _("Farvardin"));
        strcpy (mw.month[1], _("Ordibehesht"));
        strcpy (mw.month[2], _("Khordad"));
        strcpy (mw.month[3], _("Tir"));
        strcpy (mw.month[4], _("Mordad"));
        strcpy (mw.month[5], _("Shahrivar"));
        strcpy (mw.month[6], _("Mehr"));
        strcpy (mw.month[7], _("Aban"));
        strcpy (mw.month[8], _("Azar"));
        strcpy (mw.month[9], _("Dey"));
        strcpy (mw.month[10], _("Bahman"));
        strcpy (mw.month[11], _("Esfand"));

        strcpy (mw.wee[0], _("Ye"));
        strcpy (mw.wee[1], _("Do"));
        strcpy (mw.wee[2], _("Se"));
        strcpy (mw.wee[3], _("Ch"));
        strcpy (mw.wee[4], _("Pa"));
        strcpy (mw.wee[5], _("Jo"));
        strcpy (mw.wee[6], _("Sh"));

        strcpy (mw.week[0], _("YekShanbeh"));
        strcpy (mw.week[1], _("DoShanbeh"));
        strcpy (mw.week[2], _("SehShanbeh"));
        strcpy (mw.week[3], _("ChaharShanbeh"));
        strcpy (mw.week[4], _("PanjShanbeh"));
        strcpy (mw.week[5], _("Jomeh"));
        strcpy (mw.week[6], _("Shanbeh"));
    }

    else if (strcmp (c, "LH") == 0)
    {
        strcpy (mw.mon[0], _("Muh"));
        strcpy (mw.mon[1], _("Saf"));
        strcpy (mw.mon[2], _("RaA"));
        strcpy (mw.mon[3], _("RaT"));
        strcpy (mw.mon[4], _("JuA"));
        strcpy (mw.mon[5], _("JuT"));
        strcpy (mw.mon[6], _("Raj"));
        strcpy (mw.mon[7], _("Sha"));
        strcpy (mw.mon[8], _("Ram"));
        strcpy (mw.mon[9], _("Shw"));
        strcpy (mw.mon[10], _("ZiQ"));
        strcpy (mw.mon[11], _("ZiH"));

        strcpy (mw.month[0], _("Muharram"));
        strcpy (mw.month[1], _("Safar"));
        strcpy (mw.month[2], _("Rabi-alAwwal"));
        strcpy (mw.month[3], _("Rabi-athThani"));
        strcpy (mw.month[4], _("Jumada-alAwwal"));
        strcpy (mw.month[5], _("Jumada-athThani"));
        strcpy (mw.month[6], _("Rajab"));
        strcpy (mw.month[7], _("Shaban"));
        strcpy (mw.month[8], _("Ramadan"));
        strcpy (mw.month[9], _("Shawwal"));
        strcpy (mw.month[10], _("Zi-alQadah"));
        strcpy (mw.month[11], _("Zi-alHijjah"));

        strcpy (mw.wee[0], _("Ah"));
        strcpy (mw.wee[1], _("It"));
        strcpy (mw.wee[2], _("Th"));
        strcpy (mw.wee[3], _("Ar"));
        strcpy (mw.wee[4], _("Kh"));
        strcpy (mw.wee[5], _("Ju"));
        strcpy (mw.wee[6], _("Sa"));

        strcpy (mw.week[0], _("alAhad"));
        strcpy (mw.week[1], _("alIthnayn"));
        strcpy (mw.week[2], _("alThulatha"));
        strcpy (mw.week[3], _("alArbia"));
        strcpy (mw.week[4], _("alKhamis"));
        strcpy (mw.week[5], _("alJumah"));
        strcpy (mw.week[6], _("asSabt"));
    }

    else
    {
        strcpy (mw.mon[0], _("Jan"));
        strcpy (mw.mon[1], _("Feb"));
        strcpy (mw.mon[2], _("Mar"));
        strcpy (mw.mon[3], _("Apr"));
        strcpy (mw.mon[4], _("May"));
        strcpy (mw.mon[5], _("Jun"));
        strcpy (mw.mon[6], _("Jul"));
        strcpy (mw.mon[7], _("Aug"));
        strcpy (mw.mon[8], _("Sep"));
        strcpy (mw.mon[9], _("Oct"));
        strcpy (mw.mon[10], _("Nov"));
        strcpy (mw.mon[11], _("Dec"));

        strcpy (mw.month[0], _("January"));
        strcpy (mw.month[1], _("February"));
        strcpy (mw.month[2], _("March"));
        strcpy (mw.month[3], _("April"));
        strcpy (mw.month[4], _("May"));
        strcpy (mw.month[5], _("June"));
        strcpy (mw.month[6], _("July"));
        strcpy (mw.month[7], _("August"));
        strcpy (mw.month[8], _("September"));
        strcpy (mw.month[9], _("October"));
        strcpy (mw.month[10], _("November"));
        strcpy (mw.month[11], _("December"));

        strcpy (mw.wee[0], _("Su"));
        strcpy (mw.wee[1], _("Mo"));
        strcpy (mw.wee[2], _("Tu"));
        strcpy (mw.wee[3], _("We"));
        strcpy (mw.wee[4], _("Th"));
        strcpy (mw.wee[5], _("Fr"));
        strcpy (mw.wee[6], _("Sa"));

        strcpy (mw.week[0], _("Sunday"));
        strcpy (mw.week[1], _("Monday"));
        strcpy (mw.week[2], _("Tuesday"));
        strcpy (mw.week[3], _("Wednesday"));
        strcpy (mw.week[4], _("Thursday"));
        strcpy (mw.week[5], _("Friday"));
        strcpy (mw.week[6], _("Saturday"));
    }

    char *s = malloc (LEN_PRINT * sizeof(char));

    if (s == NULL)
    {
        debug_printf("[ERROR] Could not allocate space for object.\n");
        return "****-**-**";
    }
    else
    {
        char *YYYY = int_to_str ("%04i", d.year, l, c);
        char *YY = int_to_str ("%02i", d.year % 100, l, c);
        char *MM = int_to_str ("%02i", d.month, l, c);
        char *M = int_to_str ("%i", d.month, l, c);
        char *DD = int_to_str ("%02i", d.day, l, c);
        char *D = int_to_str ("%i", d.day, l, c);

        if (strcmp (f, "YY-M-D") == 0)
        {
            sprintf (s, "%s-%s-%s", YY, M, D);
        }
        else if (strcmp (f, "YY/M/D") == 0)
        {
            sprintf (s, "%s/%s/%s", YY, M, D);
        }
        else if (strcmp (f, "YY.M.D") == 0)
        {
            sprintf (s, "%s.%s.%s", YY, M, D);
        }
        else if (strcmp (f, "YY M D") == 0)
        {
            sprintf (s, "%s %s %s", YY, M, D);
        }

        else if (strcmp (f, "YYYY-MM-DD") == 0)
        {
            sprintf (s, "%s-%s-%s", YYYY, MM, DD);
        }
        else if (strcmp (f, "YYYY/MM/DD") == 0)
        {
            sprintf (s, "%s/%s/%s", YYYY, MM, DD);
        }
        else if (strcmp (f, "YYYY.MM.DD") == 0)
        {
            sprintf (s, "%s.%s.%s", YYYY, MM, DD);
        }
        else if (strcmp (f, "YYYY MM DD") == 0)
        {
            sprintf (s, "%s %s %s", YYYY, MM, DD);
        }

        else if (strcmp (f, "WWW YY-M-D") == 0)
        {
            sprintf (s, "%s %s-%s-%s", mw.wee[d.week], YY, M, D);
        }
        else if (strcmp (f, "WWW YY/M/D") == 0)
        {
            sprintf (s, "%s %s/%s/%s", mw.wee[d.week], YY, M, D);
        }
        else if (strcmp (f, "WWW YY.M.D") == 0)
        {
            sprintf (s, "%s %s.%s.%s", mw.wee[d.week], YY, M, D);
        }
        else if (strcmp (f, "WWW YY M D") == 0)
        {
            sprintf (s, "%s %s %s %s", mw.wee[d.week], YY, M, D);
        }

        else if (strcmp (f, "WWWW YYYY-MM-DD") == 0)
        {
            sprintf (s, "%s %s-%s-%s", mw.week[d.week], YYYY, MM, DD);
        }
        else if (strcmp (f, "WWWW YYYY/MM/DD") == 0)
        {
            sprintf (s, "%s %s/%s/%s", mw.week[d.week], YYYY, MM, DD);
        }
        else if (strcmp (f, "WWWW YYYY.MM.DD") == 0)
        {
            sprintf (s, "%s %s.%s.%s", mw.week[d.week], YYYY, MM, DD);
        }
        else if (strcmp (f, "WWWW YYYY MM DD") == 0)
        {
            sprintf (s, "%s %s %s %s", mw.week[d.week], YYYY, MM, DD);
        }

        else if (strcmp (f, "WWW D MMM YY") == 0)
        {
            sprintf (s,
                     "%s %s %s %s",
                     mw.wee[d.week],
                     D,
                     mw.mon[d.month - 1],
                     YY);
        }
        else if (strcmp (f, "WWW DD MMM YYYY") == 0)
        {
            sprintf (s,
                     "%s %s %s %s",
                     mw.wee[d.week],
                     DD,
                     mw.mon[d.month - 1],
                     YYYY);
        }
        else if (strcmp (f, "WWWW DD MMMM YYYY") == 0)
        {
            sprintf (s,
                     "%s %s %s %s",
                     mw.week[d.week],
                     DD,
                     mw.month[d.month - 1],
                     YYYY);
        }

        else
        {
            debug_printf("[ERROR] Format is wrong.\n");
            sprintf (s, "%s%s%s", YYYY, MM, DD);
        }

        if (strcmp (YYYY, "**") != 0)
        {
            free (YYYY);
        }
        if (strcmp (YY, "**") != 0)
        {
            free (YY);
        }
        if (strcmp (MM, "**") != 0)
        {
            free (MM);
        }
        if (strcmp (M, "**") != 0)
        {
            free (M);
        }
        if (strcmp (DD, "**") != 0)
        {
            free (DD);
        }
        if (strcmp (D, "**") != 0)
        {
            free (D);
        }

        for (int i = 0; i < 12; i++)
        {
            free (mw.mon[i]);
        }
        for (int i = 0; i < 12; i++)
        {
            free (mw.month[i]);
        }
        for (int i = 0; i < 7; i++)
        {
            free (mw.wee[i]);
        }
        for (int i = 0; i < 7; i++)
        {
            free (mw.week[i]);
        }

        return s;
    }
}
/*****************************************************************************/
/**
 * Convert Integer to String
 *
 * @since 1.0.0
 */
char*
int_to_str (char t[LEN_TEMPLATE + 1],
            int n,
            struct locale l,
            char c[LEN_CALENDAR + 1])
{
    char *str = malloc ((LEN_Digit + 1) * sizeof(char));

    if (str == NULL)
    {
        debug_printf("[ERROR] Could not allocate space for object.\n");
        return "**";
    }
    else
    {
        sprintf (str, t, n);
        char s[LEN_Digit + 1] =
        { '\0' };
        if ((strcmp (l.language, "fa") == 0 && strcmp (c, "SH") == 0)
                || (strcmp (l.language, "ar") == 0 && strcmp (c, "LH") == 0))
        {
            for (int i = 0; str[i] != '\0'; i++)
            {
                switch (str[i])
                {
                    case '0':
                        strcat (s, "۰");
                        break;
                    case '1':
                        strcat (s, "۱");
                        break;
                    case '2':
                        strcat (s, "۲");
                        break;
                    case '3':
                        strcat (s, "۳");
                        break;
                    case '4':
                        strcat (s, "۴");
                        break;
                    case '5':
                        strcat (s, "۵");
                        break;
                    case '6':
                        strcat (s, "۶");
                        break;
                    case '7':
                        strcat (s, "۷");
                        break;
                    case '8':
                        strcat (s, "۸");
                        break;
                    case '9':
                        strcat (s, "۹");
                        break;
                    case '+':
                        strcat (s, "+");
                        break;
                    case '-':
                        strcat (s, "-");
                        break;
                    default:
                        strcat (s, "؟");
                }
            }
            strcpy (str, s);
        }

        return str;
    }
}

#endif /* ENABLE_DATE_C */
