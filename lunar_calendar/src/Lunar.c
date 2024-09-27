/******************************************************************************
* Included headers
******************************************************************************/

//#include <bits/getopt_ext.h>
#include <sys/types.h>
#include <getopt.h>
#include <time.h>
#include <stdint.h>
#include <stdio.h>
//#include <time.h>
#include <errno.h>
#include <unistd.h>
#include <getopt.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
/******************************************************************************
* Local definitions
******************************************************************************/

#define PI acos(-1.0)
#define deg PI/180
#define TAG __func__,__LINE__

#define USAGE_HEADER     _("\nUsage:\n")
#define USAGE_OPTIONS    _("\nOptions:\n")
#define USAGE_FUNCTIONS  _("\nFunctions:\n")
#define USAGE_COMMANDS   _("\nCommands:\n")
#define USAGE_ARGUMENTS   _("\nArguments:\n")
#define USAGE_COLUMNS    _("\nAvailable output columns:\n")
#define USAGE_DEFAULT_COLUMNS _("\nDefault columns:\n")
#define USAGE_SEPARATOR    "\n"

#define USAGE_OPTSTR_HELP     _("display this help")
#define USAGE_OPTSTR_VERSION  _("display version")


#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"
#define KYEL "\x1B[33m"
#define KBLU "\x1B[34m"
#define KMAG "\x1B[35m"
#define KCYN "\x1B[36m"
#define KWHT "\x1B[37m"

enum {
    SUNDAY = 0,
    MONDAY,
    TUESDAY,
    WEDNESDAY,
    THURSDAY,
    FRIDAY,
    SATURDAY,
    DAY_IN_WEEK,
    NONEDAY
};

enum {
    JANUARY = 1,
    FEBRUARY,
    MARS,
    APRIL,
    MAY,
    JUNE,
    JULY,
    AUGUST,
    SEPTEMBER,
    OCTOBER,
    NOVEMBER,
    DECEMBER
};

typedef struct _LunarDate {
    int day;
    int month;
    int year;
    int leap_month;
    char can[16];
    char chi[16];
    char tiet_khi[16];
} LunarDate;

enum Can {
    Giap = 0, At, Binh, Dinh, Mau, Ky, Canh, Tan, Nham, Quy
};

enum Chi {
    Ti = 0, Suu, Dan, Mao, Thin, Ty, Ngo, Mui, Than, Dau, Tuat, Hoi
};

enum Zodiac {
    Aries = 0, Taurus, Gemini, Cancer, Leo, Virgo, Libra, Scorpio, Sagittarius, Capricorn, Aquarius, Pisces
};

#define JULIAN_DATE_1900 2415021


/******************************************************************************
* function prototypes
******************************************************************************/
int convert_georgian_to_julius(int y, int m, int d);
struct tm convert_julian_to_georgian(int julian_day);
int get_new_moon_day(int timeZone, int k);
int get_lunar_month_november(int yyyy, int timeZone);
int get_sun_longtitude(int jdn, int timeZone);
int get_leap_month_offset(int nov, int timeZone);
const char* zodiac_sign(int dd, int mm);
void convert_solar_to_lunar(int dd, int mm, int yyyy, int timeZone, LunarDate *lunar_date);
void convert_lunar_to_solar(int lunar_dd, int lunar_mm, int lunar_yyyy, int timeZone);
const char* get_tiet_khi(float angle);

const char* print_week_day(int wday);
const char* get_month_name(int mon);

int get_length_month(int month, int year);
int get_length_lunar_month(int month, int year);

void print_month(int month, int year, int timeZone);
const char* print_chi(int chi);
const char* print_can(int can);
static void __attribute__((__noreturn__)) usage(void);


int main(int argc, char **argv)
{
    //printf("[%s][%s] \n", __DATE__, __TIME__);
    int ch = 0;
    char date[9];
    char month[7];
    int isCustomTime = 0;
    int printMonth = 0;
    int dd, mm, yyyy;
    int is_full = 0;
    LunarDate lunar_date;
    time_t t = time(NULL);
    struct tm tm = {0};

    static const struct option longopts[] = {
        {"date", required_argument, NULL, 'd'},
        {"month", required_argument, NULL, 'm'},
        {"all", no_argument, NULL, 'a'},
        {"version", no_argument, NULL, 'V'},
        {NULL, 0, NULL, 0}
    };

    while ((ch = getopt_long(argc, argv, "ad:m::", longopts, NULL)) != -1)
    {
        switch (ch)
        {
        case 'd':
            if (optarg)
            {
                memset(date, 0, sizeof(date));
                strncpy(date, optarg, sizeof(date) - 1);
                date[8] = '\0';
                isCustomTime = 1;
                if (strlen(date) < 8) {
                    printf("Please give time format ddmmyyyy\n");
                    return -1;
                }
            }
            else
            {
                printf("no optarg\n");
                // TODO: print usage
                usage();
            }
            break;
        case 'm':
            printMonth = 1;
            if (optarg == NULL && optind < argc && NULL != argv[optind] && argv[optind][0] != '-') {
                optarg = argv[optind++];
            }
            if (optarg) {
                strncpy(month, optarg, sizeof(month) - 1);

                if (strlen(month) > 6 || strlen(month) < 6) {
                    printf("Please give the month\n");
                    return -1;
                }
                char buf[8];
                mm = atoi(strncpy(buf, month, 2));
                yyyy = atoi(strncpy(buf, month + 2, 4));
            } else {
                tm = *localtime(&t);
                mm = tm.tm_mon + 1;
                yyyy = tm.tm_year + 1900;
                //
            }
            break;
        case 'a':
            is_full = 1;
            break;
        default:
            printf("default case\n");
            break;
        }
    }

    if (isCustomTime)
    {
        char buf[8];
        dd = atoi(strncpy(buf, date, 2));
        mm = atoi(strncpy(buf, date + 2, 2));
        yyyy = atoi(strncpy(buf, date + 4, 4));
        tm.tm_year = yyyy - 1900;
        tm.tm_mon = mm - 1;
        tm.tm_mday = dd;
        mktime(&tm);
        printf(KGRN "time: (%s) %s %d-%02d-%02d %02d:%02d:%02d (%d)%s\n", zodiac_sign(tm.tm_mday, tm.tm_mon+1), print_week_day(tm.tm_wday), tm.tm_year + 1900,
                tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, tm.tm_yday + 1, KNRM);
        //get_new_moon_day(convert_georgian_to_julius(tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday), 0);
        convert_solar_to_lunar(tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, 7, &lunar_date);
        printf(KRED "lunar day %d lunar month %d lunar year %d%s\n", lunar_date.day, lunar_date.month, lunar_date.year, KNRM);
    }
    else if (printMonth) {
        print_month(mm, yyyy, 7);
    }
    else
    {
        //time_t t = time(NULL);
        tm = *localtime(&t);
        dd = tm.tm_mday;
        mm = tm.tm_mon + 1;
        yyyy = tm.tm_year + 1900;
        printf(KGRN "time: (%s) %s %d-%02d-%02d %02d:%02d:%02d (%d)%s\n", zodiac_sign(tm.tm_mday, tm.tm_mon+1), print_week_day(tm.tm_wday), tm.tm_year + 1900,
                tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, tm.tm_yday + 1, KNRM);
        //get_new_moon_day(convert_georgian_to_julius(tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday), 0);
        convert_solar_to_lunar(tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, 7, &lunar_date);
        printf(KRED "lunar day %d lunar month %d lunar year %d%s\n", lunar_date.day, lunar_date.month, lunar_date.year, KNRM);
        if (is_full) {
            int jdn = convert_georgian_to_julius(yyyy, mm, dd);
            //printf(KBLU "[%s][%d] jdn: %d %s\n", TAG, jdn, KNRM);
            printf(KYEL "Day %s %s, Month %s %s Year %s %s%s\n", print_can((jdn+9) %10),print_chi((jdn+1)%12),
                    print_can((lunar_date.year*12+lunar_date.month+3)%10),print_chi((lunar_date.month+1)%12),
                    print_can((lunar_date.year + 6) % 10), print_chi((lunar_date.year + 8)%12), KNRM);
        }
       // printf(KYEL "Day %s %s, Month %s %s Year %s %s%s\n", print_can((jdn+9) %10),print_chi((jdn+1)%12),
       //         print_can((lunarYear*12+lunarMonth+3)%10),print_chi((lunarMonth+1)%12),
       //         print_can((lunarYear + 6) % 10), print_chi((lunarYear + 8)%12), KNRM);
    }
    //printf("[%s][%d] %d/%d/%d\n", TAG,dd,mm,yyyy);
    //printf(KGRN "time: (%s) %s %d-%02d-%02d %02d:%02d:%02d (%d)%s\n", zodiac_sign(tm.tm_mday, tm.tm_mon+1), print_week_day(tm.tm_wday), tm.tm_year + 1900,
    //        tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, tm.tm_yday + 1, KNRM);

    //printf("[%s][%d] julian date: %d\n", TAG, convert_georgian_to_julius(tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday));
    //struct tm revert_tm = convert_julian_to_georgian(convert_georgian_to_julius(tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday));
    //printf("[%s][%d] convert time: %d-%02d-%02d\n", TAG, revert_tm.tm_year, revert_tm.tm_mon, revert_tm.tm_mday);

    //get_new_moon_day(convert_georgian_to_julius(tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday), 0);
    /*
    for(int _mm = 1; _mm <= 12; _mm++)
    {
        for(int _dd = 1;_dd <= 31; _dd++)
        {
            printf(KBLU "[%s][%d] %02d/%02d/%d%s\n",TAG, _dd, _mm, 2021, KNRM);
            convert_solar_to_lunar(_dd, _mm, 2021, 0);
        }
    }
    */
    //convert_solar_to_lunar(tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, 7);


    return 0;
}

long get_julius_day(int jdn)
{

    return 0;
}

struct tm convert_julian_to_georgian(int jdn)
{
    int a,b,c,d,e,m,dd,mm,yyyy;
    if (jdn > 2299160)
    {
        a = jdn + 32044;
        b = (4*a+3)/146097;
        c = a - (b*146097)/4;
    }
    else
    {
        b = 0;
        c = jdn + 32082;
    }
    d = (4*c + 3)/1461;
    e = c - (1461*d)/4;
    m = (5*e + 2)/153;
    dd = e - (153*m+2)/5 + 1;
    mm = m + 3 - 12*(m/10);
    yyyy = b*100 + d - 4800 + m/10;
    //time_t t = time(NULL);
    struct tm tm = {0};
    tm.tm_year = yyyy - 1900;
    tm.tm_mon = mm - 1;
    tm.tm_mday = dd;
    mktime(&tm);
    return tm;
}

float get_solar_longtitude(int jdn)
{
    float T = (jdn - 2451545.0)/(float)36525;
    // solar longtitude (deg)
    float L0  = 280.46645 + 36000.76983*T + 0.0003032*T*T;
    //printf("[%s][%d] %f + %f = %f\n", TAG, 36000.76983*T, 0.0003032*T*T, L0);
    // solar mean anomaly (deg)
    float M = 357.52910 + 35999.05030*T - 0.0001559*T*T - 0.00000048*T*T*T;
    // eccentricity of Earth's orbit
    //float e = 0.016708617 - 0.000042037*T - 0.0000001236*T*T;
    // sun's equation of center (deg)
    float C = (1.9146 - 0.004817*T - 0.000014*T*T)*sin(M * deg/2) +
        (0.019993 - 0.000101*T)*sin(2*M*deg/2) + 0.00029*sin(3*M*deg/2);
    // solar true longtitude (deg)
    //printf("[%s][%d] T: %f L0: %f M: %f C: %f\n", TAG, T, L0, M, C);
    float theta =  L0 + C;
    float lambda = theta - 0.00569 - 0.00478 * sin((125.04 - 1934.136*T)*deg);
    //printf("[%s][%d] theta %f lambda %f\n", TAG, theta, lambda);
    lambda = lambda - 360*(int)(lambda/360);
    //printf("[%s][%d] %f\n", TAG, lambda);
    return lambda;
}

int convert_georgian_to_julius(int y, int m, int d)
{
    //printf("[%s][%d] %d/%d/%d\n", TAG, d, m, y);
    int a = (m-14)/12;
    return (1461*(y+4800 + a))/4 + (367*(m-2-12*a))/12 - (3*(y+4900+a)/100)/4 + d -32075;
}

const char* print_week_day(int wday)
{
    switch (wday)
    {
        case 1:
            return "Monday";
        case 2:
            return "Tuesday";
        case 3:
            return "Wednesday";
        case 4:
            return "Thursday";
        case 5:
            return "Friday";
        case 6:
            return "Saturday";
        case 0:
            return "Sunday";
        default:
            return "Day";
    }
}

const char* print_can(int can)
{
    switch (can)
    {
        case 0:
            return "Giap";
        case 1:
            return "At";
        case 2:
            return "Binh";
        case 3:
            return "Dinh";
        case 4:
            return "Mau";
        case 5:
            return "Ky";
        case 6:
            return "Canh";
        case 7:
            return "Tan";
        case 8:
            return "Nham";
        case 9:
            return "Quy";
        default:
            return "";
    }
}

const char* print_chi(int chi)
{
    switch (chi)
    {
        case 0:
            return "Ti";
        case 1:
            return "Suu";
        case 2:
            return "Dan";
        case 3:
            return "Mao";
        case 4:
            return "Thin";
        case 5:
            return "Ty";
        case 6:
            return "Ngo";
        case 7:
            return "Mui";
        case 8:
            return "Than";
        case 9:
            return "Dau";
        case 10:
            return "Tuat";
        case 11:
            return "Hoi";
        default:
            return "";
    }
}

int get_new_moon_day(int timeZone, int k)
{
    /*
    int day_since_new = day - 2451549;
    float new_moon = (float)day_since_new / 29.53;
    int day_in_cycle = (new_moon - floor(new_moon)) * 29.53 + 0.5;
    */
    //printf("[%s][%d] sol.1: %d\n", __func__, __LINE__, day_in_cycle);

    float T = (float)k / 1236.85;
    float Jd1 = 2415020.75933 + 29.53058868*k + 0.0001178*T*T - 0.000000155*T*T*T + 0.00033*sin((166.56 + 132.87*T-0.009173*T*T)*deg); // Mean new moon
    float M = 359.2242 + 29.10535608*k - 0.0000333*T*T + 0.0000347*T*T*T; // Sun's mean anomaly
    float Mpr = 306.0253 + 385.81691806*k + 0.0107306*T*T + 0.00001236*T*T*T; // Moon's mean anomaly
    float F = 21.296 + 390.67050646*k - 0.0016528*T*T - 0.00000239*T*T*T; // Moon's argument of latitude
    float C1 = (0.1734 - 0.000393*T)*sin(M*deg) + 0.0021*sin(2*deg*M)
        - 0.4068*sin(Mpr*deg) + 0.0161*sin(deg*2*Mpr) - 0.0004*sin(deg*3*Mpr)
        + 0.0104*sin(deg*2*F) - 0.0051*sin(deg*(M+Mpr))
        - 0.0074*sin(deg*(M-Mpr)) + 0.0004*sin(deg*(2*F+M))
        - 0.0004*sin(deg*(2*F-M)) - 0.0006*sin(deg*(2*F+Mpr))
        + 0.0010*sin(deg*(2*F-Mpr)) + 0.0005*sin(deg*(2*Mpr+M));

    float deltat;
    if (T < -11)
    {
        //printf("[%s][%d]\n", TAG);
        deltat = 0.001 + 0.000839*T + 0.0002261*T*T - 0.00000845*T*T*T - 0.000000081*T*T*T*T;
    }
    else
    {
        deltat = -0.000278 + 0.000265*T + 0.000262*T*T;
    }

    float JdNew = Jd1 + C1 - deltat;

    //printf("[%s][%d] sol.2: %f\n", TAG,  JdNew + 0.5);

    //struct tm nov_tm = convert_julian_to_georgian((int)(JdNew + 0.5));
    //printf("[%s][%d] %02d/%02d/%d\n", TAG, nov_tm.tm_mday, nov_tm.tm_mon + 1, nov_tm.tm_year + 1900);
    return (int)(JdNew + 0.5 + (float)timeZone/24);
}

int get_lunar_month_november(int yyyy, int timeZone)
{
    int off = convert_georgian_to_julius(yyyy, 12, 31) - JULIAN_DATE_1900;
    int k = off / 29.530588853;
    //printf("[%s][%d] year: %d off: %d\n", TAG, yyyy, k);
    int jd = get_new_moon_day(0, k);
    if (get_sun_longtitude(jd, timeZone) >= 9)
    {
        jd = get_new_moon_day(0, k-1);
    }
    //printf("[%s][%d] %d\n", TAG, jd);
    return jd;
}

int get_sun_longtitude(int jdn, int timeZone)
{
    float T = (jdn - 2451545) / 36525;
    float M = 357.52910 + 359999.05030*T - 0.00001559*T*T - 0.00000048*T*T*T; // mean anomaly, degree
    float L0 = 280.46645 + 36000.76983*T + 0.0003032*T*T; //mean longitude, degree
    float DL = (1.914600 - 0.004817*T - 0.000014*T*T)*sin(deg*M)
        + (0.019993 - 0.000101*T)*sin(deg*2*M) + 0.000290*sin(deg*3*M);
    float L = (L0 + DL)*deg;
    L = L - PI*2*(int)(L/(PI*2));
    //printf("[%s][%d] %d\n", TAG, (int)(L/PI * 6));
    return (int)(L/PI *6);
}

int get_leap_month_offset(int nov, int timeZone)
{
    int k = (int)((nov - 2415021.076998695) / 29.530588853 + 0.5);
    int last = 0, i = 1;
    int arc = get_sun_longtitude(get_new_moon_day(k, timeZone), timeZone);
    do {
        last = arc;
        i++;
        arc = get_sun_longtitude(get_new_moon_day((k+i), timeZone), timeZone);
    } while ( arc != last && i < 14);
    //printf("[%s][%d] i:%d\n", TAG, i);
    return i-1;
}

void convert_solar_to_lunar(int dd, int mm, int yyyy, int timeZone, LunarDate *lunar_date)
{
    //printf("[%s][%d] %02d/%02d/%d\n", TAG, dd, mm, yyyy);
    int lunarYear, lunarMonth, lunarDay;
    int diff, leapMonDiff;
    int jdn = convert_georgian_to_julius(yyyy, mm, dd);
    int  k = (int)((jdn - 2415021.076998695)/ 29.530588853);
    timeZone = 7;
    int monthStart = get_new_moon_day(timeZone, k+1);
    int nextMonthStart = 0;
    //printf("[%s][%d] month start 1: %d\n",TAG, monthStart);
    if (monthStart > jdn)
    {
        nextMonthStart = monthStart;
        monthStart = get_new_moon_day(timeZone, k);
    }
    else
    {
        nextMonthStart = get_new_moon_day(timeZone, k + 2);
    }
    //printf("[%s][%d] month start 2: %d\n",TAG, monthStart);
    int a11 = get_lunar_month_november(yyyy, timeZone);
    int b11 = a11;
    if (a11 >= monthStart)
    {
        lunarYear = yyyy;
        a11 = get_lunar_month_november(yyyy - 1, timeZone);
    }
    else
    {
        lunarYear = yyyy + 1;
        b11 = get_lunar_month_november(yyyy + 1, timeZone);
    }
    //printf("[%s][%d] a11[%d] b11[%d]\n", TAG, a11, b11);
    //nextMonthStart = get_new_moon_day(jdn, k+2);
    //printf("[%s][%d] next month (%d)\n", TAG, nextMonthStart);
    if (jdn < nextMonthStart) {
        lunarDay = jdn - monthStart + 1;
    } else {
        lunarDay = 1;
    }
    //printf("[%s][%d] jdn (%d) \tmonthStart (%d) \tlunarDay(%d)\n",TAG, jdn, monthStart, lunarDay);
    diff = (monthStart - a11)/29;
    int lunarLeap = 0;
    lunarMonth = diff + 11;
    //printf("[%s][%d] diff (%d) lunar month (%d) \n", TAG, diff, lunarMonth);

    if ((b11 - a11) > 365)
    {
        leapMonDiff = get_leap_month_offset(a11, timeZone);
        //printf("[%s][%d] leapMonDiff (%d) diff (%d)\n", TAG, leapMonDiff, diff);
        if (diff >= leapMonDiff)
        {
            lunarMonth = diff + 10;
            if (diff == leapMonDiff)
            {
                lunarLeap = 1;
            }
        }
    } else {

    }

    //printf("[%s][%d] lunarLeap (%d) lunarMonth %d\n", TAG, lunarLeap, lunarMonth);
    if (lunarMonth > 12)
    {
        lunarMonth = lunarMonth - 12;
    }
    if (lunarMonth >= 11 && diff < 4)
    {
        lunarYear--;
    }

    //printf(KBLU "(%s) ", get_tiet_khi(get_solar_longtitude(jdn)), KNRM);
    //printf("[%s][%d] jdn: %d\t k: %d\t monthStart: %d \n", TAG, jdn, k, monthStart);
    //printf(KRED "[%s][%d]  lunar day %d lunar month %d leap(%d) lunar year %d%s\n", TAG, lunarDay, lunarMonth, lunarLeap, lunarYear, KNRM);
    //printf(KYEL "Day %s %s, Month %s %s Year %s %s%s\n", print_can((jdn+9) %10),print_chi((jdn+1)%12),
    //        print_can((lunarYear*12+lunarMonth+3)%10),print_chi((lunarMonth+1)%12),
    //        print_can((lunarYear + 6) % 10), print_chi((lunarYear + 8)%12), KNRM);
    lunar_date->day = lunarDay;
    lunar_date->month = lunarMonth;
    lunar_date->year = lunarYear;
    lunar_date->leap_month = lunarLeap;
    //strncpy(lunar_date->can, print_can((jdn+9) % 10));
    //strncpy(lunar_date->chi, print_can((jdn+1) % 12));
    strncpy(lunar_date->tiet_khi, get_tiet_khi(get_solar_longtitude(jdn)), 16);
}

const char* zodiac_sign(int dd, int mm)
{
    switch (mm)
    {
        case 1:
            return (dd < 20) ? "Capricorn ♑" : "Aquarius ♒";
        case 2:
            return (dd < 19) ? "Aquarius ♒" : "Pisces ♓";
        case 3:
            return (dd < 21) ? "Pisces ♓" : "Aries ♈";
        case 4:
            return (dd < 20) ? "Aries ♈" : "Taurus ♉";
        case 5:
            return (dd < 21) ? "Taurus ♉" : "Gemini ♊";
        case 6:
            return (dd < 21) ? "Gemini ♊" : "Cancer ♋";
        case 7:
            return (dd < 23) ? "Cancer ♋" : "Leo ♌";
        case 8:
            return (dd < 23) ? "Leo ♌" : "Virgo ♍";
        case 9:
            return (dd < 23) ? "Virgo ♍" : "Libra ♎";
        case 10:
            return (dd < 23) ? "Libra ♎" : "Scorpius ♏";
        case 11:
            return (dd < 22) ? "Scorpius ♏" : "Sagittarius ♐";
        case 12:
            return (dd < 22) ? "Sagittarius ♐" : "Capricorn ♑";
        default:
            return "";
    }
}

const char* get_tiet_khi(float angle)
{
    if (angle > 345.0) return "Kinh Trap";
    else if (angle > 330.0)    return "Vu Thuy";
    else if (angle > 315.0)  return "Lap Xuan";
    else if (angle > 300.0)  return "Dai Han";
    else if (angle > 285.0)  return "Tieu Han";
    else if (angle > 270.0)  return "Dong Chi";
    else if (angle > 255.0)  return "Dai Tuyet";
    else if (angle > 240.0)  return "Tieu Tuyet";
    else if (angle > 225.0)  return "Lap Dong";
    else if (angle > 210.0)  return "Suong Giang";
    else if (angle > 195.0)  return "Han Lo";
    else if (angle > 180.0)  return "Thu Phan";
    else if (angle > 165.0)  return "Bach Lo";
    else if (angle > 150.0)  return "Xu Thu";
    else if (angle > 135.0)  return "Lap Thu";
    else if (angle > 120.0)  return "Dai Thu";
    else if (angle > 105.0)  return "Tieu Thu";
    else if (angle > 90.0)  return "Ha Chi";
    else if (angle > 75.0)  return "Mang Chung";
    else if (angle > 60.0)  return "Tieu Man";
    else if (angle > 45.0)  return "Lap Ha";
    else if (angle > 30.0)  return "Coc Vu";
    else if (angle > 15.0)  return "Thanh Minh";
    else if (angle > 0.0)  return "Xuan Phan";
    else return "";
}

const char* get_month_name(int mon) {
    if (mon == 1) return "January";
    else if (mon == 2) return "February";
    else if (mon == 3) return "Mars";
    else if (mon == 4) return "April";
    else if (mon == 5) return "May";
    else if (mon == 6) return "June";
    else if (mon == 7) return "July";
    else if (mon == 8) return "August";
    else if (mon == 9) return "September";
    else if (mon == 10) return "October";
    else if (mon == 11) return "November";
    else if (mon == 12) return "December";
    else return "";
}

void convert_lunar_to_solar(int lunar_dd, int lunar_mm, int lunar_yyyy, int timeZone) {
    int a11 = 0;
    int b11 = 0;
    if (lunar_mm < 11) {
        a11 = get_lunar_month_november(lunar_yyyy - 1, timeZone);
        b11 = get_lunar_month_november(lunar_yyyy, timeZone);
    } else {
        a11 = get_lunar_month_november(lunar_yyyy, timeZone);
        b11 = get_lunar_month_november(lunar_yyyy + 1, timeZone);
    }
    //int k = (int)(0.5 + (a11 - 2415021.076998695)/29.530588853);
    if (b11 -a11 > 365) {

    }
}

/* https://stackoverflow.com/questions/46704484/last-day-of-a-given-month */
int get_length_month(int month, int year) {
    if (month < 1 || month > 12) return 0;
    if (month == 4 || month == 6 || month == 9 || month == 11) return 30;
    else if (month == 2) return ((((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0)) ? 29 : 28);
    return 31;
}

int get_length_lunar_month(int month, int year) {
    int jdn = convert_georgian_to_julius(year, month, 1);
    int  k = (int)((jdn - 2415021.076998695)/ 29.530588853);
    int timeZone = 7;
    int currMonthStart = get_new_moon_day(timeZone, k);
    int monthStart = get_new_moon_day(timeZone, k+1);
    if (monthStart < jdn)
    {
        monthStart = get_new_moon_day(timeZone, k + 2);
    }
    //printf(KBLU "[%s](%d) jdn(%d) next monthStart(%d) %d%s\n", TAG, currMonthStart, monthStart, (monthStart - currMonthStart), KNRM);
    return (monthStart - currMonthStart);
}

/* https://stackoverflow.com/questions/64054639/how-to-properly-print-month-calendar-on-terminal */
void print_month(int month, int year, int timeZone) {
    int count = 1;

    struct tm tm = {0};
    tm.tm_year = year - 1900;
    tm.tm_mon = month - 1;
    tm.tm_mday = 1;
    mktime(&tm);
    int wday = tm.tm_wday;
    int len_mon = get_length_month(month, year);
    struct tm last_day = {0};
    last_day.tm_year = year - 1900;
    last_day.tm_mon = month - 1;
    last_day.tm_mday = len_mon;
    mktime(&last_day);
    int last_wday = last_day.tm_wday;
    //printf(KBLU "[%s](%d) weekday start month %d %s%s\n", TAG, wday, print_week_day(wday), KNRM);
    //printf(KBLU "[%s](%d) weekday end month %d %s%s\n", TAG, last_wday, print_week_day(last_wday), KNRM);
    if (wday == 0) wday = 7;
    if (last_wday == 0) last_wday = 7;
    LunarDate first;
    LunarDate last;
    convert_solar_to_lunar(1, month, year, timeZone, &first);
    //printf("lunar date first(%d) lunar month (%d) lunar year (%d)\n", first.day, first.month, first.year);
    convert_solar_to_lunar(len_mon, month, year, timeZone, &last);
    //printf("lunar date last(%d) lunar month (%d) lunar year (%d)\n", last.day, last.month, last.year);
    int lunar_mon_len = get_length_lunar_month(month, year);
    int curr_lunar = first.day;

    printf(KYEL "Month : %s/%d%s\n", get_month_name(month), year, KNRM);
    printf(KGRN "|  Mon   |  Tue   |  Wed   |  Thu   |  Fri   |  Sat   |  Sun   |%s\n", KNRM);
    printf("|--------------------------------------------------------------|\n");
    for(int i = 0; i < wday - 1; i++, count++) {
        printf("|%8s", "");
    }
    for(int i = 1; i <= len_mon; i++, count++) {
        printf("| %2d(%2d) ", i, curr_lunar++);
        if (count % 7 == 0) printf("|\n");
        if (curr_lunar > lunar_mon_len) curr_lunar = 1;
    }
    if (last_wday != 7) printf("|\n");
}

static void __attribute__((__noreturn__)) usage(void)
{
    FILE *out = stdout;
    //fputs(USAGE_HEADER, out);
    exit(EXIT_SUCCESS);
}
