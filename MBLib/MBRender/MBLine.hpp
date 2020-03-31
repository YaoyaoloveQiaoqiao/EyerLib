#ifndef	EYER_LIB_REDNER_LINE_AV_H
#define	EYER_LIB_REDNER_LINE_AV_H

#include "MBCore/MBCore.hpp"

namespace MB
{
    class MBLine
    {
    private:
        MBVec2 point1;
        MBVec2 point2;
    public:
        MBLine();
        ~MBLine();
    };
}

#endif