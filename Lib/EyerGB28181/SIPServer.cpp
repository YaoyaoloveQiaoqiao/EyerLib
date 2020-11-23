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
        mainThread = new SIPServerMainThread(port);
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
}