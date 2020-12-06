#ifndef EYERLIB_SIPCALLBACK_HPP
#define EYERLIB_SIPCALLBACK_HPP

#include "EyerCore/EyerCore.hpp"

namespace Eyer
{
    class SIPCallback {
    public:
        SIPCallback();
        ~SIPCallback();

        virtual int UserRegister(EyerString deviceId) = 0;
    };
}

#endif //EYERLIB_SIPCALLBACK_HPP
