/* In the name of Allah */
/**
 * @file time.c
 * @copyright (C) 1399 Hossein Sabzehmeidani
 * @license GNU General Public License (GPLv3+)
 */

#include "lahzeh.h"

#ifdef ENABLE_TIME_C
/*****************************************************************************/
/**
 * Current Time
 *
 * @since 1.0.0
 */
int
time_current (struct locale l, struct time *t)
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

    t->hour = t_info->tm_hour;
    t->minute = t_info->tm_min;
    t->second = t_info->tm_sec;
    strftime (t->timezone, LEN_TIMEZONE3 + 1, "%z", t_info);

    //debug_printf("[Current Time] %02i:%02i:%02i  %s\n", t->hour, t->minute, t->second, t->timezone);

    return (t->hour * 10000) + (t->minute * 100) + t->second;
}

#endif /* ENABLE_TIME_C */
