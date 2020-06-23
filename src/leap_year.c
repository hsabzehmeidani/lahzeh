/* In the name of Allah */
/**
 * @file leap_year.c
 * @copyright (C) 1399 Hossein Sabzehmeidani
 * @license GNU General Public License (GPLv3+)
 */

#include "lahzeh.h"

#ifdef ENABLE_LEAP_YEAR_C
/*****************************************************************************/
/**
 * Compare Integers
 *
 * @since 1.0.0
 */
int
compare_integers (const void *a, const void *b)
{
    return (*(int*) a - *(int*) b);
}
/*****************************************************************************/
/**
 * Leap Year (Solar Hijri)
 *
 * @since 1.0.0
 */
bool
solar_hijri_leap (int year)
{
    int leap_years[] =
    { 4, 9, 13, 17, 21, 25, 29, 33, 37, 42, 46, 50, 54, 58, 62, 66, 71, 75, 79,
            83, 87, 91, 95, 99, 104, 108, 112, 116, 120, 124, 128, 132, 137,
            141, 145, 149, 153, 157, 161, 165, 170, 174, 178, 182, 186, 190,
            194, 198, 203, 207, 211, 215, 219, 223, 227, 231, 236, 240, 244,
            248, 252, 256, 260, 264, 269, 273, 277, 281, 285, 289, 293, 297,
            302, 306, 310, 314, 318, 322, 326, 331, 335, 339, 343, 347, 351,
            355, 359, 364, 368, 372, 376, 380, 384, 388, 392, 397, 401, 405,
            409, 413, 417, 421, 425, 430, 434, 438, 442, 446, 450, 454, 458,
            463, 467, 471, 475, 479, 483, 487, 491, 496, 500, 504, 508, 512,
            516, 520, 524, 529, 533, 537, 541, 545, 549, 553, 558, 562, 566,
            570, 574, 578, 582, 586, 591, 595, 599, 603, 607, 611, 615, 619,
            624, 628, 632, 636, 640, 644, 648, 652, 656, 661, 665, 669, 673,
            677, 681, 685, 690, 694, 698, 702, 706, 710, 714, 718, 723, 727,
            731, 735, 739, 743, 747, 751, 756, 760, 764, 768, 772, 776, 780,
            784, 789, 793, 797, 801, 805, 809, 813, 817, 822, 826, 830, 834,
            838, 842, 846, 850, 855, 859, 863, 867, 871, 875, 879, 883, 888,
            892, 896, 900, 904, 908, 912, 916, 921, 925, 929, 933, 937, 941,
            945, 949, 954, 958, 962, 966, 970, 974, 978, 983, 987, 991, 995,
            999, 1003, 1007, 1011, 1016, 1020, 1024, 1028, 1032, 1036, 1040,
            1044, 1049, 1053, 1057, 1061, 1065, 1069, 1073, 1077, 1082, 1086,
            1090, 1094, 1098, 1102, 1106, 1110, 1115, 1119, 1123, 1127, 1131,
            1135, 1139, 1143, 1148, 1152, 1156, 1160, 1164, 1168, 1172, 1176,
            1181, 1185, 1189, 1193, 1197, 1201, 1205, 1210, 1214, 1218, 1222,
            1226, 1230, 1234, 1238, 1243, 1247, 1251, 1255, 1259, 1263, 1267,
            1271, 1276, 1280, 1284, 1288, 1292, 1296, 1300, 1304, 1309, 1313,
            1317, 1321, 1325, 1329, 1333, 1337, 1342, 1346, 1350, 1354, 1358,
            1362, 1366, 1370, 1375, 1379, 1383, 1387, 1391, 1395, 1399, 1403,
            1408, 1412, 1416, 1420, 1424, 1428, 1432, 1436, 1441, 1445, 1449,
            1453, 1457, 1461, 1465, 1469, 1474, 1478, 1482, 1486, 1490, 1494,
            1498, 1502, 1507 };
    int len = (int) (sizeof(leap_years) / sizeof(leap_years[0]));
    if (bsearch (&year, leap_years, len, sizeof(int), compare_integers) != NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}
/*****************************************************************************/
/**
 * List of Leap Years (Solar Hijri)
 *
 * @since 1.0.0
 */
int
solar_hijri_leap_list (int year_s, int year_e)
{
    int num = 0;
    for (int y = year_s; y <= year_e; y++)
    {
        if (solar_hijri_leap (y))
        {
            printf ("%i, ", y);
            num++;
        }
    }
    printf ("\n");
    return num;
}
/*****************************************************************************/
/**
 * Leap Year (Lunar Hijri)
 *
 * @since 1.0.0
 */
bool
lunar_hijri_leap (int year)
{
    /* Crescent Lunar Hijri */
    if (strcmp (country_crescent, "IR") == 0)
    {
        struct crescent lhc;
        lunar_hijri_crescent (year, &lhc);

        if (year >= lhc.year_s && year <= lhc.year_e)
        {
            return lunar_hijri_crescent (year, &lhc);
        }
    }

    int leap_years[] =
    { 2, 5, 7, 10, 13, 16, 18, 21, 24, 26, 29 };
    for (int i = 0; i < 11; i++)
    {
        if (year % 30 == leap_years[i])
        {
            return true;
        }
    }
    return false;
}
/*****************************************************************************/
/**
 * List of Leap Years (Lunar Hijri)
 *
 * @since 1.0.0
 */
int
lunar_hijri_leap_list (int year_s, int year_e)
{
    int num = 0;
    for (int y = year_s; y <= year_e; y++)
    {
        if (lunar_hijri_leap (y))
        {
            printf ("%i, ", y);
            num++;
        }
    }
    printf ("\n");
    return num;
}
/*****************************************************************************/
/**
 * Leap Year (Gregorian Christmas)
 *
 * @since 1.0.0
 */
bool
gregorian_christmas_leap (int year)
{
    if (year % 4 != 0)
    {
        return false;
    }
    else if (year % 400 == 0)
    {
        return true;
    }
    else if (year % 100 == 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}
/*****************************************************************************/
/**
 * List of Leap Years (Gregorian Christmas)
 *
 * @since 1.0.0
 */
int
gregorian_christmas_leap_list (int year_s, int year_e)
{
    int num = 0;
    for (int y = year_s; y <= year_e; y++)
    {
        if (gregorian_christmas_leap (y))
        {
            printf ("%i, ", y);
            num++;
        }
    }
    printf ("\n");
    return num;
}

#endif /* ENABLE_LEAP_YEAR_C */
