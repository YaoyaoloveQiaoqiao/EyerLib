#include <gtest/gtest.h>
#include "EyerCore/EyerCore.hpp"
#include "EyerPJSIP/EyerPJSIP.hpp"

TEST(PJSIP, PJSIPServer)
{
    printf("Eyer PJSIP Test Start\n");

    Eyer::PJSIPServer pjsipServer(5060);
    int ret = pjsipServer.Start();
    printf("PJSIPServer Start Ret: %d\n", ret);

    for(int i=0;i<60 * 2;i++){
        Eyer::EyerTime::EyerSleepMilliseconds(1000);
    }

    pjsipServer.Stop();
    printf("Eyer PJSIP Test End\n");
}

int main(int argc,char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
