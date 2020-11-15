#ifndef EYERLIB_EYERUDPTHREAD_HPP
#define EYERLIB_EYERUDPTHREAD_HPP

#include "EyerThread/EyerThread.hpp"

#ifdef _WIN32
#include <WinSock2.h>
#include <ws2tcpip.h>
#else
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>

#endif // _WIN32

namespace Eyer
{
    class EyerUDPThread : public EyerThread{
    public:
        EyerUDPThread(int _port);
        ~EyerUDPThread();

        virtual void Run();

    private:
        int port = 5060;
        int sockfd;
    };
}

#endif //EYERLIB_EYERUDPTHREAD_HPP
