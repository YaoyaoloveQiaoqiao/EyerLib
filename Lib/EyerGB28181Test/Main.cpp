#include <gtest/gtest.h>
#include <iostream>

#include "EyerGB28181/EyerGB28181.hpp"
#include "EyerCore/EyerCore.hpp"
#include "EyerRTP/EyerRTP.hpp"

class MySIPCallback : public Eyer::SIPCallback
{
public:
    Eyer::SIPServer * sipServer = nullptr;

    MySIPCallback(Eyer::SIPServer * _sipServer){
        sipServer = _sipServer;
    }

    virtual int UserRegister(Eyer::EyerString deviceId)
    {
        EyerLog("User Register: %s\n", deviceId.str);

        Eyer::EyerString streamServerIp = "192.168.2.106";
        Eyer::EyerString channelId = "1234";

        sipServer->StartStream(
                streamServerIp,
                6000,
                deviceId,
                channelId
                );
        return 0;
    }
};

TEST(GB28181, GB28181SipServer) {
    eye_log_set_level(1);

    Eyer::EyerRTPServer rtpServer;

    Eyer::SIPServer sipServer(5060);
    MySIPCallback sipCallback(&sipServer);
    sipServer.SetCallback(&sipCallback);
    sipServer.Start();

    for(int i=0;i<60 * 2;i++){
        Eyer::EyerTime::EyerSleepMilliseconds(1000);
    }

    sipServer.Stop();
}

int main(int argc,char **argv){
    eyer_log_param(1, 1, 0, 0, 0);

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}