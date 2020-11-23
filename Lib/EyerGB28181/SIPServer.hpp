#ifndef EYERLIB_SIPSERVER_HPP
#define EYERLIB_SIPSERVER_HPP

#include "SIPServerMainThread.hpp"

namespace Eyer
{
    class SIPServer {
    public:
        SIPServer(int _port = 5060);
        ~SIPServer();

        int Start();
        int Stop();
    private:
        int port = 5060;

        SIPServerMainThread * mainThread = nullptr;
    };
}

#endif //EYERLIB_SIPSERVER_HPP
