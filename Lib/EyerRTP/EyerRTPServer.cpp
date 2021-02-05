#include "EyerRTPServer.hpp"

#include "EyerCore/EyerCore.hpp"

namespace Eyer
{
    EyerRTPServer::EyerRTPServer()
    {
        rtpServerThread = new EyerRTPServerThread();
        rtpServerThread->Start();
    }

    EyerRTPServer::~EyerRTPServer()
    {
        if(rtpServerThread != nullptr){
            delete rtpServerThread;
            rtpServerThread = nullptr;
        }
    }
}