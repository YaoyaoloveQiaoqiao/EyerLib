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
        context.eventThread = new SIPEventThread(&context);
        context.eventThread->Start();

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
        if(context.eventThread != nullptr){
            context.eventThread->Stop();
            delete context.eventThread;
            context.eventThread = nullptr;
        }
        return 0;
    }

    int SIPServer::SetCallback(SIPCallback * callback)
    {
        context.callback = callback;
        return 0;
    }

    int SIPServer::StartStream(
            EyerString & streamServerIp,
            int streamServerPort,
            EyerString & deviceId,
            EyerString & channelId)
    {
        // 构建，放入消息队列

        return 0;
    }

    int SIPServer::StopStream()
    {
        return 0;
    }
}