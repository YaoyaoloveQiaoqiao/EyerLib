#include "SIPServer.hpp"

namespace Eyer
{
    SIPServer::SIPServer(int _port)
    {
        port = _port;
    }

    SIPServer::~SIPServer()
    {
        Stop();
    }

    int SIPServer::Start()
    {
        Stop();
        mainThread = new SIPServerMainThread(port, &context);
        mainThread->Start();

        return 0;
    }

    int SIPServer::Stop()
    {
        if(mainThread != nullptr){
            mainThread->Stop();
            delete mainThread;
            mainThread = nullptr;
        }
        return 0;
    }


    int StartStream(
            EyerString & streamServerIp,
            int streamServerPort,
            EyerString & deviceId,
            EyerString & channelId)
    {
        // 构建，放入消息队列

        return 0;
    }
}