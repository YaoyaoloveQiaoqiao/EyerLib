#ifndef EYERLIB_STARTSTREAMCALLBACK_HPP
#define EYERLIB_STARTSTREAMCALLBACK_HPP

namespace Eyer
{
    class StartStreamCallback {
    public:
        virtual int OnStartStream(int status);
    };
}

#endif //EYERLIB_STARTSTREAMCALLBACK_HPP
