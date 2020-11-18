#ifndef EYERLIB_UDPTHREADTEST_HPP
#define EYERLIB_UDPTHREADTEST_HPP

#include <gtest/gtest.h>
#include <string.h>
#include <stdio.h>

#include "EyerCore/EyerCore.hpp"
#include "EyerNetwork/EyerNetwork.hpp"
#include "EyerSIP/EyerSIP.hpp"

Eyer::EyerUDPThread * udpThread = nullptr;

class MyEyerUDPCallback : public Eyer::EyerUDPCallback
{
public:
    virtual int OnMessageRecv(Eyer::UDPMessage * udpMessage)
    {
        printf("=====================================\n");
        printf("buffer:\n %s\n", udpMessage->buffer.GetPtr());

        Eyer::EyerSIPMessgae sipMessgae;
        int ret = sipMessgae.Parse(udpMessage->buffer);
        if(ret){
            return -1;
        }

        printf("xxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");

        Eyer::EyerString method = sipMessgae.GetMethod();
        printf("method: %s\n", method.str);

        Eyer::EyerSIPFrom from;
        sipMessgae.GetFrom(from);
        from.PrintfInfo();

        Eyer::EyerSIPFrom to;
        sipMessgae.GetTo(to);
        to.PrintfInfo();

        Eyer::EyerSIPCallID callId;
        sipMessgae.GetCallID(callId);


        printf("xxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
        Eyer::EyerSIPMessgae response;
        response.SetInfo();
        response.SetFrom(from);
        response.SetTo(to);
        response.SetCallID(callId);
        Eyer::EyerBuffer responseBuffer = response.ToBuffer();

        udpMessage->sockaddr.PrintInfo();
        udpThread->Send(responseBuffer, udpMessage->sockaddr);

        printf("=====================================\n");

        return 0;
    }
};

TEST(EyerNetwork, EyerNetworkUDPThread)
{
    printf("=======================UDP=======================\n");
    udpThread = new Eyer::EyerUDPThread(5060, new MyEyerUDPCallback());
    udpThread->Start();

    for(int i=0;i<60 * 2;i++){
        printf("wait\n");
        Eyer::EyerTime::EyerSleepMilliseconds(1000);
    }

    udpThread->Stop();

    if(udpThread != nullptr){
        delete udpThread;
        udpThread = nullptr;
    }
}
#endif //EYERLIB_UDPTHREADTEST_HPP
