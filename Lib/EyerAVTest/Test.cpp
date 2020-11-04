#include <gtest/gtest.h>

#include "EyerAV/EyerAV.hpp"

TEST(A, ATest){
    Eyer::EyerAVReader reader("rtmp://redknot.cn:1935/demo/aaa");
    int ret = reader.Open();
    if(ret){
        printf("Open Fail ret: %d\n", ret);
        return;
    }

    int streamCount = reader.GetStreamCount();
    printf("Stream Count: %d\n", streamCount);

    int videoStreamIndex = reader.GetVideoStreamIndex();
    int audioStreamIndex = reader.GetAudioStreamIndex();


    Eyer::EyerAVStream videoStream;
    reader.GetStream(videoStream, videoStreamIndex);
    Eyer::EyerAVDecoder videoDecoder;
    videoDecoder.Init(&videoStream);

    Eyer::EyerAVStream audioStream;
    reader.GetStream(audioStream, audioStreamIndex);
    Eyer::EyerAVDecoder audioDecoder;
    audioDecoder.Init(&audioStream);

    // Eyer::EyerAVBitstreamFilter::QueryAllBitstreamFilter();

    while (1){
        Eyer::EyerAVPacket packet;
        // Eyer::EyerTime::EyerSleepMilliseconds(10);
        ret = reader.Read(&packet);
        if(ret){
            EyerLog("Ret: %d\n", ret);
            break;
        }

        if(packet.GetStreamId() == videoStreamIndex){
            videoStream.ScalerPacketPTS(packet);

            printf("packet: %f\n", packet.GetSecPTS());

            videoDecoder.SendPacket(&packet);
            while(1){
                Eyer::EyerAVFrame avFrame;
                ret = videoDecoder.RecvFrame(&avFrame);
                if(ret){
                    break;
                }

                // printf("video w:%d, h:%d\n", avFrame.GetWidth(), avFrame.GetHeight());
            }
        }
        if(packet.GetStreamId() == audioStreamIndex){
            audioDecoder.SendPacket(&packet);
            while(1){
                Eyer::EyerAVFrame avFrame;
                ret = audioDecoder.RecvFrame(&avFrame);
                if(ret){
                    break;
                }

                // printf("audio sec: %lld\n", avFrame.GetPTS());
            }
        }

        // EyerLog("Packet: %lld\n", packet.GetPTS());


    }

    reader.Close();
}

int main(int argc,char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
