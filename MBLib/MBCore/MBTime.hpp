#ifndef	EYER_CORE_TIME_H
#define	EYER_CORE_TIME_H

#include "MBString.hpp"

#ifdef _MSC_VER
#include <winsock2.h>
#else
#include <sys/time.h>
#include <unistd.h>
#endif // _MSC_VER

namespace MB
{
    class MBTime
    {
    public:
        static long long GetTime();
        static MBString TimeFormat();

        static int MBSleep(int time);
    };
}

#endif
