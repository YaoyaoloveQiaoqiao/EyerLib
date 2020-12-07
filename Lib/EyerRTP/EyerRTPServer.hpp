#ifndef EYERLIB_EYERRTPSERVER_HPP
#define EYERLIB_EYERRTPSERVER_HPP

#include "EyerRTPServerThread.hpp"

namespace Eyer
{
    class EyerRTPServer {
    public:
        EyerRTPServer();
        ~EyerRTPServer();

    private:
        EyerRTPServerThread * rtpServerThread = nullptr;
    };
}

#endif //EYERLIB_EYERRTPSERVER_HPP
