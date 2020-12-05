#include <gtest/gtest.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>

#include "EyerGB28181/EyerGB28181.hpp"
#include "EyerCore/EyerCore.hpp"
#include "EyerNetwork/EyerNetwork.hpp"

class MyEyerUDPCallback : public Eyer::EyerUDPCallback
{
public:
    virtual int OnMessageRecv(Eyer::UDPMessage * udpMessage)
    {
        printf("UDP Len: %d\n", udpMessage->buffer.GetLen());
        return 0;
    }
};

class MySIPCallback : public Eyer::SIPCallback
{
    virtual int UserRegister()
    {
        EyerLog("User Register\n");
        return 0;
    }
};

TEST(GB28181, GB28181SipServer) {
    eyer_log_init();
    eye_log_set_level(1);

    MySIPCallback sipCallback;
    MyEyerUDPCallback eyerUdpCallback;

    Eyer::EyerUDPThread udpThread(6000, &eyerUdpCallback);
    udpThread.Start();

    Eyer::SIPServer sipServer(5060);
    sipServer.SetCallback(&sipCallback);
    sipServer.Start();

    for(int i=0;i<60 * 2;i++){
        Eyer::EyerTime::EyerSleepMilliseconds(1000);
    }

    sipServer.Stop();
    udpThread.Stop();

    eyer_log_uninit();
}

int main(int argc,char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}