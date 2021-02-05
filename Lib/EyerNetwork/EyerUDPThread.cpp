#include "EyerUDPThread.hpp"

#include <osipparser2/osip_parser.h>

namespace Eyer
{
    EyerUDPThread::EyerUDPThread(int _port, EyerUDPCallback * _udpCallback)
    {
        port = _port;
        udpCallback = _udpCallback;
#ifdef _WIN32
        WSADATA wsaData;
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        }
#endif //_WIN32
    }

    EyerUDPThread::~EyerUDPThread()
    {

    }

    void EyerUDPThread::Run()
    {
        sockfd = socket(AF_INET, SOCK_DGRAM, 0);
        if (sockfd < 0) {
            printf("socket(AF_INET, SOCK_DGRAM, 0) Fail\n");
            return;
        }

        struct sockaddr_in addr = {};
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);
        addr.sin_addr.s_addr = inet_addr("0.0.0.0");
        int value = 64 * 1024;
        setsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, (char*)& value, sizeof(value));
        int ret = bind(sockfd, (const struct sockaddr*) & addr, sizeof(addr));
        if (0 > ret) {
            printf("bind() Fail\n");
            return;
        }

        fd_set rfd;
        fd_set wfd;
        timeval timeout;
        timeout.tv_sec = 1;
        timeout.tv_usec = 0;

        UDPMessage * sendingUdpMessage = nullptr;

        while (!stopFlag)
        {
            FD_ZERO(&rfd);
            FD_ZERO(&wfd);
            FD_SET(sockfd, &rfd);
            FD_SET(sockfd, &wfd);

            int nRet = select(sockfd + 1, &rfd, &wfd, NULL, &timeout);
            if (nRet < 0) {
                break;
            }
            else if (nRet == 0) {
                // Time Out
                continue;
            }
            else {
                if (FD_ISSET(sockfd, &rfd)) {
                    // able read
                    int bufferSize = 1024 * 1024;
                    char * buffer = (char *)malloc(bufferSize);
                    memset(buffer, 0, bufferSize);

                    EyerSockaddr sockaddr;
                    socklen_t addrlen = sizeof(struct sockaddr);
                    EyerBuffer bufferS;

                    int retLen = recvfrom(sockfd, buffer, bufferSize, 0, (struct sockaddr *)sockaddr.GetPtr(), &addrlen);

                    bufferS.Append((uint8_t *)buffer, retLen);

                    UDPMessage * udpMessage = new UDPMessage(bufferS, sockaddr);

                    udpCallback->OnMessageRecv(udpMessage);

                    delete udpMessage;


                    free(buffer);
                }
                if (FD_ISSET(sockfd, &wfd)) {
                    // able write
                    if(sendingUdpMessage != nullptr){
                        if(sendingUdpMessage->buffer.GetLen() <= 0){
                            delete sendingUdpMessage;
                            sendingUdpMessage = nullptr;
                        }
                    }
                    if(sendingUdpMessage == nullptr){
                        sendQueue.FrontPop(&sendingUdpMessage);
                    }
                    if(sendingUdpMessage != nullptr){
                        int ret = sendto(sockfd, sendingUdpMessage->buffer.GetPtr(), sendingUdpMessage->buffer.GetLen(), 0, (struct sockaddr *)sendingUdpMessage->sockaddr.GetPtr(), sendingUdpMessage->sockaddr.GetLen());
                        if(ret > 0){
                            EyerBuffer tempBuffer;
                            sendingUdpMessage->buffer.CutOff(tempBuffer, ret);
                        }
                    }
                }
            }
        }
    }

    int EyerUDPThread::Send(EyerBuffer & buffer, EyerSockaddr & sockaddr)
    {
        UDPMessage * udpMessage = new UDPMessage(buffer, sockaddr);
        sendQueue.Push(udpMessage);
        return 0;
    }
}