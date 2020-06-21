/* In the name of Allah */
/**
 * @file event.c
 * @copyright (C) 1399 Hossein Sabzehmeidani
 * @license GNU General Public License (GPLv3+)
 */

#include "lahzeh.h"

#ifdef ENABLE_EVENT_C
/*****************************************************************************/
/**
 * Calendar Events
 *
 * @since 1.0.0
 */
void
event (struct locale l, struct date d, char c[LEN_CALENDAR + 1])
{
    char month_open[6], month_close[8];
    sprintf (month_open, "<M%i>", d.month);
    sprintf (month_close, "</M%i>", d.month);

    char day_open[6], day_close[8];
    sprintf (day_open, "<D%i>", d.day);
    sprintf (day_close, "</D%i>", d.day);

    char f[LEN_FILE];
    sprintf (f, "%sres/events/%s/%s.xml", path, l.country, c);

    FILE *fp;
    fp = fopen (f, "r");

    char ch, line[LEN_LINE_MAX] =
    { '\0' };
    int ind = 0, find_month = 0;

    if (fp == NULL)
    {
        debug_printf("[ERROR] Could not open file \"%s\".\n", f);
    }
    else
    {
        ch = fgetc (fp);

        while (ch != EOF)
        {
            if (ch != '\n')
            {
                line[ind++] = ch;
            }
            else
            {
                if (strstr (line, month_open) != NULL)
                {
                    find_month = 1;
                }
                if (strstr (line, month_close) != NULL)
                {
                    find_month = 0;
                    break;
                }

                /* Quds Day Event */
                if (strstr (line, "<D_J>") != NULL && find_month == 1)
                {
                    if (strcmp (c, "LH") == 0 && d.month == 9 && d.day > 29 - 7
                            && d.week == 5)
                    {
                        for (int i = (int) (strstr (line, "<D_J>") - line)
                                + strlen ("<D_J>");
                                i < strlen (line) - strlen ("</D_J>"); i++)
                        {
                            printf ("%c", line[i]);
                        }
                        printf ("\n");
                    }
                }

                /* Day Event */
                if (strstr (line, day_open) != NULL && find_month == 1)
                {
                    for (int i = (int) (strstr (line, day_open) - line)
                            + strlen (day_open);
                            i < strlen (line) - strlen (day_close); i++)
                    {
                        printf ("%c", line[i]);
                    }
                    printf ("\n");
                    find_month = 0;
                    break;
                }

                for (int i = 0; i < LEN_LINE_MAX; i++)
                {
                    line[i] = '\0';
                }
                ind = 0;
            }
            ch = fgetc (fp);
        }

        fclose (fp);
    }
}

#endif /* ENABLE_EVENT_C */
