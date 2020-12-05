#ifndef EYERLIB_SIPCALLBACK_HPP
#define EYERLIB_SIPCALLBACK_HPP

namespace Eyer
{
    class SIPCallback {
    public:
        SIPCallback();
        ~SIPCallback();

        virtual int UserRegister() = 0;
    };
}

#endif //EYERLIB_SIPCALLBACK_HPP
