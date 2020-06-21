/* In the name of Allah */
/**
 * @file option.c
 * @copyright (C) 1399 Hossein Sabzehmeidani
 * @license GNU General Public License (GPLv3+)
 */

#include "lahzeh.h"

#ifdef ENABLE_OPTION_C
/*****************************************************************************/
/**
 * Command Line Options
 *
 * @since 1.0.0
 */
void
command_line_options (int argc,
                      char *argv[],
                      struct locale l,
                      struct date d,
                      struct time t)
{
    struct date d_sh = d;
    struct date d_lh = d;
    struct date d_gc = d;

    date_convert ("GC", "SH", &d_sh);
    date_convert ("GC", "LH", &d_lh);

    if (argc == 1)
    {
        printf ("Usage: %s [OPTION]...\n", APP_NAME);
        printf ("\n");
        printf ("Try \"%s --help\" for more options.\n", APP_NAME);
    }

    else
    {
        for (int i = 1; i < argc; i++)
        {
            if (strcmp (argv[i], "-t") == 0 || strcmp (argv[i], "--time") == 0)
            {
                printf (BLD"[ %02i:%02i:%02i  %s ]\n"RST,
                        t.hour,
                        t.minute,
                        t.second,
                        t.timezone);
            }

            else if (strcmp (argv[i], "-d") == 0
                    || strcmp (argv[i], "--date") == 0)
            {
                char *str_sh = date_return (l, d_sh, "SH", dformat);
                char *str_lh = date_return (l, d_lh, "LH", dformat);
                char *str_gc = date_return (l, d_gc, "GC", dformat);
                printf (BLD"[ %s | %s | %s ]\n"RST, str_sh, str_lh, str_gc);
                if (date_event == 1)
                {
                    event (l, d_lh, "LH");
                    event (l, d_sh, "SH");
                    event (l, d_gc, "GC");
                }
                if (strcmp (str_sh, "****-**-**") != 0)
                {
                    free (str_sh);
                }
                if (strcmp (str_lh, "****-**-**") != 0)
                {
                    free (str_lh);
                }
                if (strcmp (str_gc, "****-**-**") != 0)
                {
                    free (str_gc);
                }
            }

            else if (strcmp (argv[i], "-sh") == 0)
            {
                struct date d_check =
                { 1, 1, 1, 5 };
                if (argc > i + 3)
                {
                    d_check.year = atoi (argv[i + 1]);
                    d_check.month = atoi (argv[i + 2]);
                    d_check.day = atoi (argv[i + 3]);
                }
                solar_hijri_check (&d_check);
                struct date date_sh = d_check;
                struct date date_lh = d_check;
                struct date date_gc = d_check;
                date_convert ("SH", "LH", &date_lh);
                date_convert ("SH", "GC", &date_gc);
                date_sh.week = date_lh.week;
                char *string_sh = date_return (l, date_sh, "SH", dformat);
                char *string_lh = date_return (l, date_lh, "LH", dformat);
                char *string_gc = date_return (l, date_gc, "GC", dformat);
                printf (BLD"[> %s <| %s | %s ]\n"RST,
                        string_sh,
                        string_lh,
                        string_gc);
                if (date_event == 1)
                {
                    event (l, date_lh, "LH");
                    event (l, date_sh, "SH");
                    event (l, date_gc, "GC");
                }
                if (strcmp (string_sh, "****-**-**") != 0)
                {
                    free (string_sh);
                }
                if (strcmp (string_lh, "****-**-**") != 0)
                {
                    free (string_lh);
                }
                if (strcmp (string_gc, "****-**-**") != 0)
                {
                    free (string_gc);
                }
                i += 3;
            }

            else if (strcmp (argv[i], "-lh") == 0)
            {
                struct date d_check =
                { 1, 1, 1, 5 };
                if (argc > i + 3)
                {
                    d_check.year = atoi (argv[i + 1]);
                    d_check.month = atoi (argv[i + 2]);
                    d_check.day = atoi (argv[i + 3]);
                }
                lunar_hijri_check (&d_check);
                struct date date_sh = d_check;
                struct date date_lh = d_check;
                struct date date_gc = d_check;
                date_convert ("LH", "SH", &date_sh);
                date_convert ("LH", "GC", &date_gc);
                date_lh.week = date_sh.week;
                char *string_sh = date_return (l, date_sh, "SH", dformat);
                char *string_lh = date_return (l, date_lh, "LH", dformat);
                char *string_gc = date_return (l, date_gc, "GC", dformat);
                printf (BLD"[ %s |> %s <| %s ]\n"RST,
                        string_sh,
                        string_lh,
                        string_gc);
                if (date_event == 1)
                {
                    event (l, date_lh, "LH");
                    event (l, date_sh, "SH");
                    event (l, date_gc, "GC");
                }
                if (strcmp (string_sh, "****-**-**") != 0)
                {
                    free (string_sh);
                }
                if (strcmp (string_lh, "****-**-**") != 0)
                {
                    free (string_lh);
                }
                if (strcmp (string_gc, "****-**-**") != 0)
                {
                    free (string_gc);
                }
                i += 3;
            }

            else if (strcmp (argv[i], "-gc") == 0)
            {
                struct date d_check =
                { 1, 1, 1, 1 };
                if (argc > i + 3)
                {
                    d_check.year = atoi (argv[i + 1]);
                    d_check.month = atoi (argv[i + 2]);
                    d_check.day = atoi (argv[i + 3]);
                }
                gregorian_christmas_check (&d_check);
                struct date date_sh = d_check;
                struct date date_lh = d_check;
                struct date date_gc = d_check;
                date_convert ("GC", "SH", &date_sh);
                date_convert ("GC", "LH", &date_lh);
                date_gc.week = date_sh.week;
                char *string_sh = date_return (l, date_sh, "SH", dformat);
                char *string_lh = date_return (l, date_lh, "LH", dformat);
                char *string_gc = date_return (l, date_gc, "GC", dformat);
                printf (BLD"[ %s | %s |> %s <]\n"RST,
                        string_sh,
                        string_lh,
                        string_gc);
                if (date_event == 1)
                {
                    event (l, date_lh, "LH");
                    event (l, date_sh, "SH");
                    event (l, date_gc, "GC");
                }
                if (strcmp (string_sh, "****-**-**") != 0)
                {
                    free (string_sh);
                }
                if (strcmp (string_lh, "****-**-**") != 0)
                {
                    free (string_lh);
                }
                if (strcmp (string_gc, "****-**-**") != 0)
                {
                    free (string_gc);
                }
                i += 3;
            }

            else if (strcmp (argv[i], "-v") == 0
                    || strcmp (argv[i], "--version") == 0)
            {
                printf ("%s %s\n", APP_NAME, APP_VERSION);
                break;
            }

            else if (strcmp (argv[i], "-h") == 0
                    || strcmp (argv[i], "--help") == 0)
            {
                option_help ();
                break;
            }

            else if (strcmp (argv[i], "-c") == 0
                    || strcmp (argv[i], "--config") == 0
                    || strcmp (argv[i], "-p") == 0
                    || strcmp (argv[i], "--path") == 0
                    || strcmp (argv[i], "--dformat") == 0
                    || strcmp (argv[i], "--country") == 0
                    || strcmp (argv[i], "--language") == 0
                    || strcmp (argv[i], "--charset") == 0
                    || strcmp (argv[i], "--timezone") == 0)
            {
                i++;
            }

            else if (strcmp (argv[i], "-e") == 0
                    || strcmp (argv[i], "--event") == 0)
            {
            }

            else
            {
                printf ("Try \"%s --help\" for more options.\n",
                APP_NAME);
                break;
            }
        }
    }
}
/*****************************************************************************/
/**
 * Help Option
 *
 * @since 1.0.0
 */
void
option_help (void)
{
    printf (BLD"In the name of Allah\n"RST);
    printf ("\n");

    printf ("%s %s, is a \"Solar & Lunar Hijri\" and \"Gregorian Christmas\" calendar.\n",
            APP_NAME,
            APP_VERSION);
    printf ("\n");

    printf ("Usage: %s [OPTION]...\n", APP_NAME);
    printf ("\n");

    printf ("Startup:\n");
    printf ("  -v,  --version      display version\n");
    printf ("  -h,  --help         print this help\n");
    printf ("\n");

    printf ("General:\n");
    printf ("  -t,  --time         display time now\n");
    printf ("  -d,  --date         display date now\n");
    printf ("  -e,  --event        display date event\n");
    printf ("\n");

    printf ("Conversion:\n");
    printf ("  -sh YYYY MM DD      convert \"Solar Hijri\" date to \"LH & GC\"\n");
    printf ("                          -sh 1400 01 01\n");
    printf ("  -lh YYYY MM DD      convert \"Lunar Hijri\" date to \"SH & GC\"\n");
    printf ("                          -lh 1440 01 01\n");
    printf ("  -gc YYYY MM DD      convert \"Gregorian Christmas\" date to \"SH & LH\"\n");
    printf ("                          -gc 2020 01 01\n");
    printf ("\n");

    printf ("Configuration:\n");
    printf ("  -c,  --config FILE  specify config file\n");
    printf ("                          /.../%s/res/config-startup-file\n",
    APP_NAME);
    printf ("  -p,  --path FOLDER  specify path folder\n");
    printf ("                          /.../%s/\n", APP_NAME);
    printf ("  --dformat  ***      specify date format\n");
    printf ("                          \"YY-M-D\", \"YY/M/D\", \"YY.M.D\"\n");
    printf ("                          \"YYYY-MM-DD\", \"YYYY/MM/DD\", \"YYYY.MM.DD\"\n");
    printf ("                          \"WWW YY-M-D\", \"WWW YY/M/D\", \"WWW YY.M.D\"\n");
    printf ("                          \"WWWW YYYY-MM-DD\", \"WWWW YYYY/MM/DD\",\"WWWW YYYY.MM.DD\"\n");
    printf ("                          \"WWW D MMM YY\", \"WWW DD MMM YYYY\", \"WWWW DD MMMM YYYY\"\n");
    printf ("  --country  **       specify country\n");
    printf ("                          IR, IQ, CN, RU, US\n");
    printf ("  --language **       specify language\n");
    printf ("                          fa, ar, zh, ru, en\n");
    printf ("  --charset  ***      specify charset\n");
    printf ("                          UTF-8\n");
    printf ("  --timezone ***      specify timezone\n");
    printf ("                          Etc/GMT\n");
    printf ("                          Asia/Tehran, Asia/Baghdad\n");
    printf ("                          Asia/Shanghai, Europe/Moscow, America/New_York\n");
    printf ("\n");

    printf (
    BLD"Please Open issues (bugs, questions, discussions) at <http://Sabzehmeidani.ir>\n"RST);
    printf (
    BLD"Copyright (C) 1399 Hossein Sabzehmeidani <H.Sabzehmeidani@chmail.ir>\n"RST);
    printf (BLD"License GNU General Public License (GPLv3+)\n"RST);
}

#endif /* ENABLE_OPTION_C */
