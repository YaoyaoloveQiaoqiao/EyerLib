#ifndef EYERLIB_SIPSERVERCONTEXT_HPP
#define EYERLIB_SIPSERVERCONTEXT_HPP

#include "SIPDeviceManager.hpp"
#include "SIPEventQueue.hpp"
#include "SIPEventThread.hpp"
#include "SIPCallback.hpp"

namespace Eyer
{
    class SIPServerContext {
    public:
        SIPServerContext();
        ~SIPServerContext();

        SIPDeviceManager deviceManager;
        SIPEventQueue eventQueue;

        SIPEventThread * eventThread = nullptr;

        SIPCallback * callback = nullptr;
    };
}

#endif //EYERLIB_SIPSERVERCONTEXT_HPP
