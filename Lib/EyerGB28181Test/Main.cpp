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

TEST(GB28181, GB28181SipServer) {
    Eyer::EyerUDPThread udpThread(6000, new MyEyerUDPCallback());
    udpThread.Start();

    Eyer::SIPServer sipServer(5060);
    sipServer.Start();

    for(int i=0;i<60 * 2;i++){
        Eyer::EyerTime::EyerSleepMilliseconds(1000);
    }

    sipServer.Stop();
}

int main(int argc,char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}