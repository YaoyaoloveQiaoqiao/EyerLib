#include "EyerUDPThread.hpp"

#include <osipparser2/osip_parser.h>

namespace Eyer
{
    EyerUDPThread::EyerUDPThread(int _port)
    {
        port = _port;
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

        struct sockaddr src_addr;
        socklen_t addrlen = sizeof(struct sockaddr_in);

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

                    int retLen = recvfrom(sockfd, buffer, bufferSize, 0, &src_addr, &addrlen);

                    printf("retLen: %d\n", retLen);
                    printf("%s\n", buffer);
                    fflush(stdout);

                    osip_body_t * body = nullptr;
                    osip_body_init(&body);

                    free(buffer);
                }
                if (FD_ISSET(sockfd, &wfd)) {
                    // able write
                    /*
                    EyerUDPMsg * msg = NULL;
                    sendMsgQueue->Get(msg);
                    if(msg != NULL){
                        RedIPAddr * addr = msg->addr;
                        int sendedLen = 0;
                        while(sendedLen < msg->msg->dataLength){
                            int ret = sendto(sockfd, (char *)msg->msg->data + sendedLen, msg->msg->dataLength - sendedLen, 0, (struct sockaddr *)addr->addr, addr->addrLen);
                            if(ret <= 0){
                                break;
                            }
                            sendedLen += ret;
                        }
                        delete msg;
                    }
                     */
                }
            }
        }
    }
}