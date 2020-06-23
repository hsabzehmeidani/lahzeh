/* In the name of Allah */
/**
 * @file lahzeh.c
 * @copyright (C) 1399 Hossein Sabzehmeidani
 * @license GNU General Public License (GPLv3+)
 */

#include "lahzeh.h"

/*****************************************************************************/
/**
 * Main Function
 *
 * @since 1.0.0
 */
int
main (int argc, char *argv[])
{
    date_event = 0;
    strcpy (path, "");
    strcpy (dformat, "WWWW YYYY/MM/DD");
    struct locale l =
    { "IR", "fa", "UTF-8", "Asia/Tehran" };

    config_set (argc, argv, &l);
    strcpy(country_crescent, l.country);

    struct date d;
    date_current (l, &d);

    struct time t;
    time_current (l, &t);

    command_line_options (argc, argv, l, d, t);

    return 0;
}
