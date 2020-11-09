#include <gtest/gtest.h>

#include "EyerAV/EyerAV.hpp"
#include "EyerDASH/EyerDASH.hpp"

TEST(A, ATest){
    Eyer::EyerDASHReader * dashReader = new Eyer::EyerDASHReader("http://redknot.cn/DASH/xiaomai_dash.mpd");

    for(int i=0;i<10;i++){
        dashReader->CreateStream(i % 3 + 1);
        Eyer::EyerAVReader reader("rtmp://redknot.cn:1935/demo/aaa", dashReader);
        int ret = reader.Open();
        if(ret){
            printf("Open Fail ret: %d\n", ret);
            return;
        }

        int streamCount = reader.GetStreamCount();
        printf("Stream Count: %d\n", streamCount);

        int packetIndex = 0;
        while(1){
            Eyer::EyerAVPacket packet;
            ret = reader.Read(&packet);
            if(ret){
                break;
            }
            // printf("Packet: %lld, Stream Id: %d\n", packet.GetPTS(), packet.GetStreamId());

            packetIndex++;
            if(packetIndex == 20){
                dashReader->SwitchStream(3);
            }
        }

        printf("End\n");

        reader.Close();
    }
}

int main(int argc,char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
