#ifndef EYERLIB_SIPEVENTQUEUE_HPP
#define EYERLIB_SIPEVENTQUEUE_HPP

#include "EyerCore/EyerCore.hpp"
#include "SIPEvent.hpp"

namespace Eyer
{
    class SIPEventQueue {
    public:
        SIPEventQueue();
        ~SIPEventQueue();

    private:
        EyerLockQueue<SIPEvent> eventQueue;
    };
}

#endif //EYERLIB_SIPEVENTQUEUE_HPP
