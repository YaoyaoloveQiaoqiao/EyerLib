#include <stdio.h>
#include <gtest/gtest.h>
#include "EyerYUV/EyerYUV.hpp"
#include "EyerCore/EyerCore.hpp"
#include "EyerAV/EyerAV.hpp"

int writeYuv2File(Eyer::EyerAVFrame * frame, FILE * f){
    if(frame->GetPixFormat() != Eyer::EyerAVPixelFormat::Eyer_AV_PIX_FMT_YUV420P){
        return -1;
    }

    Eyer::EyerYUVLen yuvLen;
    Eyer::EyerAVTool::GetYUVLen(*frame, yuvLen);

    // EyerLog("y: %d, u: %d, v: %d\n", yuvLen.yLen, yuvLen.uLen, yuvLen.vLen);

    unsigned char * y = (unsigned char *)malloc(yuvLen.yLen);
    unsigned char * u = (unsigned char *)malloc(yuvLen.uLen);
    unsigned char * v = (unsigned char *)malloc(yuvLen.vLen);

    // 420
    fwrite(y, yuvLen.yLen, 1, f);
    fwrite(u, yuvLen.uLen, 1, f);
    fwrite(v, yuvLen.vLen, 1, f);

    frame->GetYData(y);
    frame->GetUData(u);
    frame->GetVData(v);

    free(y);
    free(u);
    free(v);

    return 0;
}

TEST(YUV, Reader){
    Eyer::EyerAVReader reader("./demo_video.mp4");
    int ret = reader.Open();
    if(ret){
        EyerLog("Open Error\n");
    }

    int videoStreamIndex = reader.GetVideoStreamIndex();

    Eyer::EyerAVStream videoStream;
    reader.GetStream(videoStream, videoStreamIndex);

    Eyer::EyerAVDecoder decoder;
    decoder.Init(&videoStream);


    char yuv420p_file_path[128];
    sprintf(yuv420p_file_path, "/home/redknot/YUV/yuv_%s_%d_%d.yuv", "420p", videoStream.GetWidth(), videoStream.GetHeight());
    FILE * yuv420p_file = fopen(yuv420p_file_path, "wb");

    while(1){
        Eyer::EyerAVPacket pkt;
        int ret = reader.Read(&pkt);
        if(ret){
            break;
        }
        if(pkt.GetStreamId() != videoStreamIndex){
            continue;
        }

        ret = decoder.SendPacket(&pkt);
        if(ret){
            break;
        }

        while(1){
            Eyer::EyerAVFrame frame;
            ret = decoder.RecvFrame(&frame);
            if(ret){
                break;
            }

            writeYuv2File(&frame, yuv420p_file);
        }
    }

    decoder.SendPacket(nullptr);
    while(1){
        Eyer::EyerAVFrame frame;
        ret = decoder.RecvFrame(&frame);
        if(ret){
            break;
        }
        writeYuv2File(&frame, yuv420p_file);
    }

    fclose(yuv420p_file);

    reader.Close();
}

int main(int argc,char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
