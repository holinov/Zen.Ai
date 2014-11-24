#include <zenai/log.h>
#include <iomanip>

namespace Zen
{
    //!Глобальный мютекс для лога
    std::mutex logMtx;

    namespace Log
    {

        std::string ChannelBase::formattime(const std::tm *timeptr)
        {
#ifndef C_GCC
            std::stringstream buffer;
            buffer << std::put_time(timeptr, "%Y-%m-%d %H:%M:%S");
            return buffer.str();
#else
            static const char wday_name[][4] =
            {
                "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
            };
            static const char mon_name[][4] =
            {
                "Jan", "Feb", "Mar", "Apr", "May", "Jun",
                "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
            };
            static char result[26];
            sprintf(result, "%.3s %.3s%3d %.2d:%.2d:%.2d %d",
                    wday_name[timeptr->tm_wday],
                    mon_name[timeptr->tm_mon],
                    timeptr->tm_mday, timeptr->tm_hour,
                    timeptr->tm_min, timeptr->tm_sec,
                    1900 + timeptr->tm_year);
            return std::string(result);
#endif
        }
    }
}