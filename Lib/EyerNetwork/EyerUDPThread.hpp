#ifndef EYERLIB_EYERUDPTHREAD_HPP
#define EYERLIB_EYERUDPTHREAD_HPP

#include "EyerThread/EyerThread.hpp"
#include "EyerUDPCallback.hpp"
#include "EyerCore/EyerCore.hpp"
#include "UDPMessage.hpp"

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
        EyerUDPThread(int _port, EyerUDPCallback * _udpCallback);
        ~EyerUDPThread();

        virtual void Run();

        int Send(EyerBuffer & buffer, EyerSockaddr & sockaddr);

    private:
        int port = 5060;
        int sockfd;

        EyerUDPCallback * udpCallback = nullptr;

        EyerLockQueue<UDPMessage> sendQueue;
    };
}

#endif //EYERLIB_EYERUDPTHREAD_HPP
