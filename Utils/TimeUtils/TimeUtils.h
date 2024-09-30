#ifndef TIME_UTILS_H_
#define TIME_UTILS_H_ 

#include <chrono>
#include <time.h>

namespace Utils {

constexpr std::chrono::nanoseconds timespecToDuration(timespec ts)
{
    auto duration = std::chrono::seconds(ts.tv_sec) + std::chrono::nanoseconds(ts.tv_nsec);
    return std::chrono::duration_cast<std::chrono::nanoseconds>(duration);
}

constexpr timespec durationToTimespec(std::chrono::nanoseconds dur)
{
    auto secs = std::chrono::duration_cast<std::chrono::seconds>(dur);
    dur -= secs;
    return timespec(secs.count(), dur.count());
}

constexpr std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds>
timespecToTimePoint(timespec ts)
{
    return std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds>(
            std::chrono::duration_cast<std::chrono::system_clock::duration>(timespecToDuration(ts)));
}


constexpr timespec timepointToTimespec(std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds> tp)
{
    auto secs = std::chrono::time_point_cast<seconds>(tp);
    auto ns = std::chrono::time_point_cast<nanoeconds>(tp)- std::chrono::time_point_cast<nanoseconds>(secs);
    return timespec(secs.time_since_epoch().count(), ns.count());
}

extern "C" {
/*!
 *  print current time in C code
 *  source: https://www.techiedelight.com/print-current-date-and-time-in-c/
 */
void print_current_time()
{
    // variables to store data and time components
    int hours, minutes, seconds, day, month, year;

    // time_t is arthimetic time type
    time_t now;

    // Obtain current time
    // time() returns the current time of the system as a time_t value
    time(&now);
    
    // Convert to local time format and print to stdout
    printf("Today is: %s\n", ctime(&now));

    // localtime converts a time_t value to calendar time and 
    // returns a pointer to a tm structure with its members
    // filled with the corresponding values
    struct tm *local = localtime(&now);

    hours = local->tm_hour;         // get hours since midnight (0-23)
    minutes = local->tm_min;        // get minutes passed after the hour (0-59)
    seconds = local->tm_sec;        // get seconds passed after minute (0-59)

    day = local->tm_mday;           // get day of month (1 to 31)
    month = local->tm_mon + 1;      // get month of year (0 to 11)
    year = local->tm_year + 1900;   // get year since 1900

    // print local time
    if (hours < 12) // before midday
        printf("Time is: %02d:%02d:%02d am\n", hours, minutes, seconds);
    else // after midday
        printf("Time is: %02d:%02d:%02d pm\n", hours - 12, minutes, seconds);

    printf("Date is: %02d/%02d/%d\n", day, month, year);
}

}

#endif // TIME_UTILS_H_
