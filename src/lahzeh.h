/* In the name of Allah */
/**
 * @file lahzeh.h
 * @copyright (C) 1399 Hossein Sabzehmeidani
 * @license GNU General Public License (GPLv3+)
 */

#define APP_NAME    "lahzeh"
#define APP_VERSION "1.0.0"
/* _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_- */
#include <stdio.h>   /* printf(), sprintf() */
#include <stdlib.h>  /* NULL, putenv(), bsearch(), atoi(), abs() */
#include <stdbool.h> /* bool, true, false */
#include <string.h>  /* strcpy(), strcat(), strcmp(), memset() */
#include <locale.h>  /* setlocale() */
#include <time.h>    /* time_t, tm, time(), localtime(), strftime() */
#include <libintl.h> /* bindtextdomain(), textdomain(), gettext() */

#define _(string) gettext(string)
/* _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_- */
//#define DEBUG
#ifdef DEBUG
#define debug_printf printf
#else
#define debug_printf(...);
#endif
/* _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_- */
#define LEN_CALENDAR  2                                                 /* SH, LH, GC */
#define LEN_COUNTRY   2                                                 /* IR */
#define LEN_LANGUAGE  2                                                 /* fa */
#define LEN_CHARSET   5                                                 /* UTF-8 */
#define LEN_LOCALE    LEN_COUNTRY + LEN_LANGUAGE + LEN_CHARSET + 11     /* LANGUAGE=fa_IR.UTF-8 */
#define LEN_TIMEZONE  28                                                /* Asia/Tehran */
#define LEN_TIMEZONE2 LEN_TIMEZONE + 3                                  /* TZ=Asia/Tehran */
#define LEN_TIMEZONE3 5                                                 /* +0430 */
#define LEN_PATH      64
#define LEN_FILE      128
#define LEN_LINE_MIN  64
#define LEN_LINE_MAX  512
#define LEN_Digit     2 * 8                                             /* -days, 1400, ۱۴۰۰ */
#define LEN_MNAME_MIN 2 * 3                                             /* Far, فرو */
#define LEN_MNAME_MAX 2 * 15                                            /* Farvardin, فروردین */
#define LEN_WNAME_MIN 2 * 2                                             /* Jo, جم */
#define LEN_WNAME_MAX 2 * 13                                            /* Jomeh, جمعه */
#define LEN_TEMPLATE  4                                                 /* %i, %02i, %04i */
#define LEN_FORMAT    17                                                /* WWWW DD MMMM YYYY */
#define LEN_PRINT     LEN_WNAME_MAX + 2 * 2 + LEN_MNAME_MAX + 2 * 4 + 3 /* Jomeh 01 Farvardin 1400, جمعه ۰۱ فروردین ۱۴۰۰ */
#define SH_YEAR_MIN   1
#define SH_YEAR_MAX   1500
#define LH_YEAR_MIN   1
#define LH_YEAR_MAX   1500
#define GC_YEAR_MIN   1
#define GC_YEAR_MAX   2100
/* _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_- */
#define RST "\033[0m"  /* RESET */
#define BLD "\033[1m"  /* BOLD */
#define BLK "\033[30m" /* BLACK */
#define RED "\033[31m" /* RED */
#define GRN "\033[32m" /* GREEN */
#define YEL "\033[33m" /* YELLOW */
#define BLU "\033[34m" /* BLUE */
#define MAG "\033[35m" /* MAGENTA */
#define CYN "\033[36m" /* CYAN */
#define WHT "\033[37m" /* WHITE */
/* _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_- */
int date_event;

char path[LEN_PATH];

char dformat[LEN_FORMAT + 1];

struct locale
{
    char country[LEN_COUNTRY + 1];
    char language[LEN_LANGUAGE + 1];
    char charset[LEN_CHARSET + 1];
    char timezone[LEN_TIMEZONE + 1];
};

struct date
{
    int year;
    int month;
    int day;
    int week;
};

struct time
{
    int hour;
    int minute;
    int second;
    char timezone[LEN_TIMEZONE3 + 1];
};

struct mwname
{
    char *mon[12];   /* mon   [12] [LEN_MNAME_MIN + 1] */
    char *month[12]; /* month [12] [LEN_MNAME_MAX + 1] */
    char *wee[7];    /* wee   [7]  [LEN_WNAME_MIN + 1] */
    char *week[7];   /* week  [7]  [LEN_WNAME_MAX + 1] */
};
/* _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_- */
/* The functions in config.c */
#ifndef ENABLE_CONFIG_C
#define ENABLE_CONFIG_C

void
config_set (int argc, char *argv[], struct locale *l);
void
config_load (char f[LEN_FILE], struct locale *l);

#endif
/* _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_- */
/* The functions in date.c */
#ifndef ENABLE_DATE_C
#define ENABLE_DATE_C

int
date_current (struct locale l, struct date *d);
void
date_convert (char c1[LEN_CALENDAR + 1],
              char c2[LEN_CALENDAR + 1],
              struct date *d);
char*
date_return (struct locale l,
             struct date d,
             char c[LEN_CALENDAR + 1],
             char f[LEN_FORMAT + 1]);
char*
int_to_str (char t[LEN_TEMPLATE + 1],
            int n,
            struct locale l,
            char c[LEN_CALENDAR + 1]);

#endif
/* _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_- */
/* The functions in time.c */
#ifndef ENABLE_TIME_C
#define ENABLE_TIME_C

int
time_current (struct locale l, struct time *t);

#endif
/* _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_- */
/* The functions in option.c */
#ifndef ENABLE_OPTION_C
#define ENABLE_OPTION_C

void
command_line_options (int argc,
                      char *argv[],
                      struct locale l,
                      struct date d,
                      struct time t);
void
option_help (void);

#endif
/* _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_- */
/* The functions in leap_year.c */
#ifndef ENABLE_LEAP_YEAR_C
#define ENABLE_LEAP_YEAR_C

int
compare_integers (const void *a, const void *b);

bool
solar_hijri_leap (int year);
int
solar_hijri_leap_list (int year_s, int year_e);

bool
lunar_hijri_leap (int year);
int
lunar_hijri_leap_list (int year_s, int year_e);

bool
gregorian_christmas_leap (int year);
int
gregorian_christmas_leap_list (int year_s, int year_e);

#endif
/* _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_- */
/* The functions in date_days.c */
#ifndef ENABLE_DATE_DAYS_C
#define ENABLE_DATE_DAYS_C

int
solar_hijri_days (struct date d);
int
lunar_hijri_days (struct date d);
int
gregorian_christmas_days (struct date d);

#endif
/* _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_- */
/* The functions in days_date.c */
#ifndef ENABLE_DAYS_DATE_C
#define ENABLE_DAYS_DATE_C

int
solar_hijri_date (int days, struct date *d);
int
lunar_hijri_date (int days, struct date *d);
int
gregorian_christmas_date (int days, struct date *d);

#endif
/* _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_- */
/* The functions in date_check.c */
#ifndef ENABLE_DATE_CHECK_C
#define ENABLE_DATE_CHECK_C

void
solar_hijri_check (struct date *d);
void
lunar_hijri_check (struct date *d);
void
gregorian_christmas_check (struct date *d);

#endif
/* _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_- */
/* The functions in event.c */
#ifndef ENABLE_EVENT_C
#define ENABLE_EVENT_C

void
event (struct locale l, struct date d, char c[LEN_CALENDAR + 1]);

#endif
