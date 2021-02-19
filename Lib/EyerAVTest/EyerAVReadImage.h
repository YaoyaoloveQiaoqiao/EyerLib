#ifndef EYERLIB_EYERAVREADIMAGE_H
#define EYERLIB_EYERAVREADIMAGE_H

#include "EyerAV/EyerAV.hpp"

TEST(EyerAV, ReaderImage)
{


    Eyer::EyerAVReader reader("/Users/yao/Desktop/aaa.jpg");

    int ret = reader.Open();
    int streamCount = reader.GetStreamCount();

    int videoStreamIndex = reader.GetVideoStreamIndex();

    Eyer::EyerAVStream stream;
    reader.GetStream(stream, videoStreamIndex);

    Eyer::EyerAVDecoder decoder;
    ret = decoder.Init(&stream);

    double duration = stream.GetDuration();

    Eyer::EyerAVRational timebase = stream.timebase;

    int width = 0;
    int height = 0;

    FILE * f = fopen("/Users/yao/Desktop/aaa.jpg.test.yuv", "wb");

    while(1) {
        Eyer::EyerAVPacket packet;
        ret = reader.Read(&packet);
        if(ret){
            break;
        }

        decoder.SendPacket(&packet);
        while(1){
            Eyer::EyerAVFrame frame;
            ret = decoder.RecvFrame(&frame);
            if(ret){
                break;
            }

            double t = frame.GetPTS() * 1.0 * timebase.num / timebase.den;
            frame.timePts = t;

            width = frame.GetWidth();
            height = frame.GetHeight();

            Eyer::EyerAVPixelFormat pixelFormat = frame.GetPixFormat();
            if(pixelFormat == Eyer::EyerAVPixelFormat::Eyer_AV_PIX_FMT_YUV420P || pixelFormat == Eyer::EyerAVPixelFormat::Eyer_AV_PIX_FMT_YUVJ420P){
                unsigned char * y = (unsigned char *)malloc(width * height);
                unsigned char * u = (unsigned char *)malloc(width / 2 * height / 2);
                unsigned char * v = (unsigned char *)malloc(width / 2 * height / 2);

                frame.GetYData(y);
                frame.GetUData(u);
                frame.GetVData(v);

                fwrite(y, width * height, 1, f);
                fwrite(u, width / 2 * height / 2, 1, f);
                fwrite(v, width / 2 * height / 2, 1, f);

                free(y);
                free(u);
                free(v);
            }
            else{
            }
        }
    }

    if(f != nullptr){
        fclose(f);
        f = nullptr;
    }

    reader.Close();
}

#endif //EYERLIB_EYERAVREADIMAGE_H
