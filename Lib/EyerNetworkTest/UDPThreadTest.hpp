#ifndef EYERLIB_UDPTHREADTEST_HPP
#define EYERLIB_UDPTHREADTEST_HPP

#include <gtest/gtest.h>
#include <string.h>
#include <stdio.h>

#include "EyerCore/EyerCore.hpp"
#include "EyerNetwork/EyerNetwork.hpp"

TEST(EyerNetwork, EyerNetworkUDPThread)
{
    printf("=======================UDP=======================\n");
    Eyer::EyerUDPThread udpThread(5060);
    udpThread.Start();

    for(int i=0;i<60 * 2;i++){
        printf("wait\n");
        Eyer::EyerTime::EyerSleepMilliseconds(1000);
    }

    udpThread.Stop();
}
#endif //EYERLIB_UDPTHREADTEST_HPP
