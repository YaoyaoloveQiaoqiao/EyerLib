#include <stdio.h>
#include <gtest/gtest.h>
#include "EyerYUV/EyerYUV.hpp"
#include "EyerCore/EyerCore.hpp"
#include "EyerAV/EyerAV.hpp"

int writeYuv420File(Eyer::EyerAVFrame * frame, FILE * f){
    if(frame->GetPixFormat() != Eyer::EyerAVPixelFormat::Eyer_AV_PIX_FMT_YUV420P){
        return -1;
    }

    Eyer::EyerYUVLen yuvLen;
    Eyer::EyerAVTool::GetYUVLen(*frame, yuvLen);

    unsigned char * y = (unsigned char *)malloc(yuvLen.yLen);
    unsigned char * u = (unsigned char *)malloc(yuvLen.uLen);
    unsigned char * v = (unsigned char *)malloc(yuvLen.vLen);

    frame->GetYData(y);
    frame->GetUData(u);
    frame->GetVData(v);

    fwrite(y, yuvLen.yLen, 1, f);
    fwrite(u, yuvLen.uLen, 1, f);
    fwrite(v, yuvLen.vLen, 1, f);

    free(y);
    free(u);
    free(v);

    return 0;
}

int writeYV12File(Eyer::EyerAVFrame * frame, FILE * f){
    if(frame->GetPixFormat() != Eyer::EyerAVPixelFormat::Eyer_AV_PIX_FMT_YUV420P){
        return -1;
    }

    Eyer::EyerYUVLen yuvLen;
    Eyer::EyerAVTool::GetYUVLen(*frame, yuvLen);

    unsigned char * y = (unsigned char *)malloc(yuvLen.yLen);
    unsigned char * u = (unsigned char *)malloc(yuvLen.uLen);
    unsigned char * v = (unsigned char *)malloc(yuvLen.vLen);

    frame->GetYData(y);
    frame->GetUData(u);
    frame->GetVData(v);

    fwrite(y, yuvLen.yLen, 1, f);
    fwrite(v, yuvLen.vLen, 1, f);
    fwrite(u, yuvLen.uLen, 1, f);

    free(y);
    free(u);
    free(v);

    return 0;
}

int writeNV12File(Eyer::EyerAVFrame * frame, FILE * f){
    if(frame->GetPixFormat() != Eyer::EyerAVPixelFormat::Eyer_AV_PIX_FMT_YUV420P){
        return -1;
    }

    Eyer::EyerYUVLen yuvLen;
    Eyer::EyerAVTool::GetYUVLen(*frame, yuvLen);

    unsigned char * y = (unsigned char *)malloc(yuvLen.yLen);
    unsigned char * u = (unsigned char *)malloc(yuvLen.uLen);
    unsigned char * v = (unsigned char *)malloc(yuvLen.vLen);

    frame->GetYData(y);
    frame->GetUData(u);
    frame->GetVData(v);

    fwrite(y, yuvLen.yLen, 1, f);

    unsigned char * uv = (unsigned char *)malloc(frame->GetHeight() * frame->GetWidth() / 2);

    int index = 0;
    for(int h=0;h<frame->GetHeight() / 2;h++){
        for(int w=0;w<frame->GetWidth() / 2;w++){
            unsigned char uuu = u[h * frame->GetWidth() / 2 + w];
            unsigned char vvv = v[h * frame->GetWidth() / 2 + w];

            uv[index] = uuu;
            index++;
            uv[index] = vvv;
            index++;
        }
    }

    fwrite(uv, frame->GetHeight() * frame->GetWidth() / 2, 1, f);

    free(y);
    free(u);
    free(v);

    free(uv);

    return 0;
}


int writeNV21File(Eyer::EyerAVFrame * frame, FILE * f){
    if(frame->GetPixFormat() != Eyer::EyerAVPixelFormat::Eyer_AV_PIX_FMT_YUV420P){
        return -1;
    }

    Eyer::EyerYUVLen yuvLen;
    Eyer::EyerAVTool::GetYUVLen(*frame, yuvLen);

    unsigned char * y = (unsigned char *)malloc(yuvLen.yLen);
    unsigned char * u = (unsigned char *)malloc(yuvLen.uLen);
    unsigned char * v = (unsigned char *)malloc(yuvLen.vLen);

    frame->GetYData(y);
    frame->GetUData(u);
    frame->GetVData(v);

    fwrite(y, yuvLen.yLen, 1, f);

    unsigned char * uv = (unsigned char *)malloc(frame->GetHeight() * frame->GetWidth() / 2);

    int index = 0;
    for(int h=0;h<frame->GetHeight() / 2;h++){
        for(int w=0;w<frame->GetWidth() / 2;w++){
            unsigned char uuu = u[h * frame->GetWidth() / 2 + w];
            unsigned char vvv = v[h * frame->GetWidth() / 2 + w];

            uv[index] = vvv;
            index++;
            uv[index] = uuu;
            index++;
        }
    }

    fwrite(uv, frame->GetHeight() * frame->GetWidth() / 2, 1, f);

    free(y);
    free(u);
    free(v);

    free(uv);

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

    char yv12_file_path[128];
    sprintf(yv12_file_path, "/home/redknot/YUV/yv12_%s_%d_%d.yuv", "420p", videoStream.GetWidth(), videoStream.GetHeight());
    FILE * yv12_file = fopen(yv12_file_path, "wb");

    char nv12_file_path[128];
    sprintf(nv12_file_path, "/home/redknot/YUV/nv12_%s_%d_%d.yuv", "420p", videoStream.GetWidth(), videoStream.GetHeight());
    FILE * nv12_file = fopen(nv12_file_path, "wb");

    char nv21_file_path[128];
    sprintf(nv21_file_path, "/home/redknot/YUV/nv21_%s_%d_%d.yuv", "420p", videoStream.GetWidth(), videoStream.GetHeight());
    FILE * nv21_file = fopen(nv21_file_path, "wb");

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

            writeYuv420File(&frame, yuv420p_file);
            writeYV12File(&frame, yv12_file);
            writeNV12File(&frame, nv12_file);
            writeNV21File(&frame, nv21_file);
        }
    }

    decoder.SendPacket(nullptr);
    while(1){
        Eyer::EyerAVFrame frame;
        ret = decoder.RecvFrame(&frame);
        if(ret){
            break;
        }
        writeYuv420File(&frame, yuv420p_file);
        writeYV12File(&frame, yv12_file);
        writeNV12File(&frame, nv12_file);
        writeNV21File(&frame, nv21_file);
    }

    fclose(yuv420p_file);
    fclose(yv12_file);
    fclose(nv12_file);
    fclose(nv21_file);

    reader.Close();
}

int main(int argc,char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
