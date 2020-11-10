#include <gtest/gtest.h>

#include "EyerAV/EyerAV.hpp"
#include "EyerDASH/EyerDASH.hpp"

TEST(DASH, DAHSTest){
    Eyer::EyerAVReader reader("http://redknot.cn/DASH2/stream.mpd");
    int ret = reader.Open();
    if(ret){
        printf("Open Fail ret: %d\n", ret);
        return;
    }

    int videoStreamIndex = reader.GetVideoStreamIndex();
    int audioStreamIndex = reader.GetAudioStreamIndex();

    int streamCount = reader.GetStreamCount();
    printf("Stream Count: %d\n", streamCount);

    for(int i = 0; i < streamCount; i++){
        if(videoStreamIndex == i){
            continue;
        }
        if(audioStreamIndex == i){
            continue;
        }
        reader.SetDiscardStream(i);
    }

    while(1){
        Eyer::EyerAVPacket packet;
        ret = reader.Read(&packet);
        if(ret){
            break;
        }
        printf("Packet: %lld, Stream Id: %d\n", packet.GetPTS(), packet.GetStreamId());
    }

    printf("End\n");

    reader.Close();
}

/*
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
 */

int main(int argc,char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
