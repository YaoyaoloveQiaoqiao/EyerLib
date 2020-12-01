#ifndef EYERLIB_SIPSERVERCONTEXT_HPP
#define EYERLIB_SIPSERVERCONTEXT_HPP

#include "SIPDeviceManager.hpp"

namespace Eyer
{
    class SIPServerContext {
    public:
        SIPServerContext();
        ~SIPServerContext();

        SIPDeviceManager deviceManager;
    };
}

#endif //EYERLIB_SIPSERVERCONTEXT_HPP
