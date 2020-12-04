#ifndef EYERLIB_SIPSERVER_HPP
#define EYERLIB_SIPSERVER_HPP

#include "SIPServerMainThread.hpp"
#include "SIPServerContext.hpp"
#include "EyerCore/EyerCore.hpp"

namespace Eyer
{
    class SIPServer {
    public:
        SIPServer(int _port = 5060);
        ~SIPServer();

        int Start();
        int Stop();

        int StartStream(
                EyerString & streamServerIp,
                int streamServerPort,
                EyerString & deviceId,
                EyerString & channelId);

        int StopStream();

    private:
        int port = 5060;
        SIPServerMainThread * mainThread = nullptr;
        SIPServerContext context;
    };
}

#endif //EYERLIB_SIPSERVER_HPP
