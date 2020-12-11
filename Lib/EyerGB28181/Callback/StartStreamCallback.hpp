#ifndef EYERLIB_STARTSTREAMCALLBACK_HPP
#define EYERLIB_STARTSTREAMCALLBACK_HPP

#include "Callback.hpp"

namespace Eyer
{
    class StartStreamCallback : public Callback {
    public:
        virtual int OnStartStream(int status) = 0;
        virtual CallbackType GetType();
    };
}

#endif //EYERLIB_STARTSTREAMCALLBACK_HPP
