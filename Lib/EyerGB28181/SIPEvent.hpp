#ifndef EYERLIB_SIPEVENT_HPP
#define EYERLIB_SIPEVENT_HPP

#include "SIPEventType.hpp"

namespace Eyer
{
    class SIPEvent {
    public:
        SIPEvent();
        virtual ~SIPEvent();

        virtual SIPEventType GetEventType() = 0;
    };
}

#endif //EYERLIB_SIPEVENT_HPP
