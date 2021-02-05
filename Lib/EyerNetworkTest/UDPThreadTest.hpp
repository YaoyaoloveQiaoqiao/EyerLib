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
