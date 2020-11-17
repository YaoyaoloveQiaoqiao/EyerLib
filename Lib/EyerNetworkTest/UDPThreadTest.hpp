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
    virtual int OnMessageRecv(uint8_t * buffer, int bufferSize)
    {
        printf("=====================================\n");
        printf("buffer:\n %s\n", buffer);

        Eyer::EyerSIPMessgae sipMessgae;
        int ret = sipMessgae.Parse(buffer, bufferSize + 1);
        if(ret){
            return -1;
        }

        Eyer::EyerString method = sipMessgae.GetMethod();
        printf("method: %s\n", method.str);

        Eyer::EyerSIPFrom from;
        sipMessgae.GetFrom(from);
        from.PrintfInfo();

        Eyer::EyerSIPFrom to;
        sipMessgae.GetTo(to);
        to.PrintfInfo();

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
