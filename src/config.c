/* In the name of Allah */
/**
 * @file config.c
 * @copyright (C) 1399 Hossein Sabzehmeidani
 * @license GNU General Public License (GPLv3+)
 */

#include "lahzeh.h"

#ifdef ENABLE_CONFIG_C
/*****************************************************************************/
/**
 * Set Configurations from Options
 *
 * @since 1.0.0
 */
void
config_set (int argc, char *argv[], struct locale *l)
{
    for (int i = 1; i < argc; i++)
    {
        if (strcmp (argv[i], "-e") == 0 || strcmp (argv[i], "--event") == 0)
        {
            date_event = 1;
        }

        else if (strcmp (argv[i], "-c") == 0
                || strcmp (argv[i], "--config") == 0)
        {
            i++;
            config_load (argv[i], l);
        }

        else if (strcmp (argv[i], "-p") == 0 || strcmp (argv[i], "--path") == 0)
        {
            i++;
            memset (path, 0, LEN_PATH);
            strcpy (path, argv[i]);
        }

        else if (strcmp (argv[i], "--dformat") == 0)
        {
            i++;
            memset (dformat, 0, LEN_FORMAT + 1);
            strcpy (dformat, argv[i]);
        }

        else if (strcmp (argv[i], "--country") == 0)
        {
            i++;
            memset (l->country, 0, LEN_COUNTRY + 1);
            strcpy (l->country, argv[i]);
        }

        else if (strcmp (argv[i], "--language") == 0)
        {
            i++;
            memset (l->language, 0, LEN_LANGUAGE + 1);
            strcpy (l->language, argv[i]);
        }

        else if (strcmp (argv[i], "--charset") == 0)
        {
            i++;
            memset (l->charset, 0, LEN_CHARSET + 1);
            strcpy (l->charset, argv[i]);
        }

        else if (strcmp (argv[i], "--timezone") == 0)
        {
            i++;
            memset (l->timezone, 0, LEN_TIMEZONE + 1);
            strcpy (l->timezone, argv[i]);
        }
    }
}
/*****************************************************************************/
/**
 * Load Configurations from File
 *
 * @since 1.0.0
 */
void
config_load (char f[LEN_FILE], struct locale *l)
{
    FILE *fp;
    fp = fopen (f, "r");

    char ch, line[LEN_LINE_MIN] =
    { '\0' };
    int ind = 0, j = 0;

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
                if (strstr (line, "path") != NULL)
                {
                    memset (path, 0, LEN_PATH);
                    for (int i = strlen ("path"); i < strlen (line); i++)
                    {
                        if (line[i] != ' ' && line[i] != '=')
                        {
                            path[j++] = line[i];
                        }
                    }
                }

                else if (strstr (line, "dformat") != NULL)
                {
                    memset (dformat, 0, LEN_FORMAT + 1);
                    for (int i = strlen ("dformat"); i < strlen (line); i++)
                    {
                        if (line[i] != ' ' && line[i] != '=')
                        {
                            if (dformat[0] != '\0' && line[i - 1] == ' ')
                            {
                                dformat[j++] = ' ';
                            }
                            dformat[j++] = line[i];
                        }
                    }
                }

                else if (strstr (line, "country") != NULL)
                {
                    memset (l->country, 0, LEN_COUNTRY + 1);
                    for (int i = strlen ("country"); i < strlen (line); i++)
                    {
                        if (line[i] != ' ' && line[i] != '=')
                        {
                            l->country[j++] = line[i];
                        }
                    }
                }

                else if (strstr (line, "language") != NULL)
                {
                    memset (l->language, 0, LEN_LANGUAGE + 1);
                    for (int i = strlen ("language"); i < strlen (line); i++)
                    {
                        if (line[i] != ' ' && line[i] != '=')
                        {
                            l->language[j++] = line[i];
                        }
                    }
                }

                else if (strstr (line, "charset") != NULL)
                {
                    memset (l->charset, 0, LEN_CHARSET + 1);
                    for (int i = strlen ("charset"); i < strlen (line); i++)
                    {
                        if (line[i] != ' ' && line[i] != '=')
                        {
                            l->charset[j++] = line[i];
                        }
                    }
                }

                else if (strstr (line, "timezone") != NULL)
                {
                    memset (l->timezone, 0, LEN_TIMEZONE + 1);
                    for (int i = strlen ("timezone"); i < strlen (line); i++)
                    {
                        if (line[i] != ' ' && line[i] != '=')
                        {
                            l->timezone[j++] = line[i];
                        }
                    }
                }

                j = 0;
                for (int i = 0; i < LEN_LINE_MIN; i++)
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

#endif /* ENABLE_CONFIG_C */
