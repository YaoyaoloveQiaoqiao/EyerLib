#include <gtest/gtest.h>
#include "EyerCore/EyerCore.hpp"
#include "EyerGLWindow/EyerGLWindow.hpp"

#include "EyerAV/EyerAV.hpp"
#include "EyerYUV/EyerYUV.hpp"
#include "Scene.hpp"
#include "EyerGL/GLHeader.h"

int main(int argc,char **argv){
    eyer_log_param(1, 1, 0, 0, 0);

    EyerLog("Hello World\n");

    int width = 1920;
    int height = 1080;

    Eyer::EyerGLWindow window("ColorSpace", width, height);

    window.Open();
    window.SetBGColor(0.0, 0.0, 0.0, 1.0);

    Eyer::Scene scene(width, height);

    scene.Start();


    Eyer::EyerAVEncoder encoder;
    Eyer::EncoderParam param;
    param.width = width;
    param.height = height;
    param.fps = 60;
    param.codecId = Eyer::CodecId::CODEC_ID_H264;
    encoder.Init(&param);

    Eyer::EyerAVRational codecTimebase;
    encoder.GetTimeBase(codecTimebase);

    Eyer::EyerAVWriter writer("./miao.mp4");

    int streamId = writer.AddStream(&encoder);
    writer.Open();
    writer.WriteHand();

    Eyer::EyerAVRational streamTimebase;
    writer.GetStreamTimeBase(streamTimebase, streamId);

    int frameIndex = 0;
    while (!window.ShouldClose()){
        window.Clear();
        scene.Update();

        glFinish();

        unsigned char * data = (unsigned char *)malloc(width * height * 3);
        glReadPixels(0, 0, width, height, GL_BGR, GL_UNSIGNED_BYTE, data);

        unsigned char * y = (unsigned char *)malloc(width * height);
        unsigned char * u = (unsigned char *)malloc(width * height);
        unsigned char * v = (unsigned char *)malloc(width * height);

        Eyer::EyerYUV yuvUtil;
        yuvUtil.RGB2YUV420(width, height, data, y, u, v);

        Eyer::EyerAVFrame frame;
        frame.SetPTS(frameIndex);
        frame.SetVideoData420P(y, u, v, width, height);
        frameIndex++;

        encoder.SendFrame(&frame);

        while(1){
            Eyer::EyerAVPacket packet;
            int ret = encoder.RecvPacket(&packet);
            if(ret){
                break;
            }

            packet.SetStreamId(streamId);
            packet.RescaleTs(codecTimebase, streamTimebase);
            writer.WritePacket(&packet);
        }


        free(data);
        window.Loop();
    }

    encoder.SendFrame(nullptr);
    while(1){
        Eyer::EyerAVPacket packet;
        int ret = encoder.RecvPacket(&packet);
        if(ret){
            break;
        }
        packet.SetStreamId(streamId);
        packet.RescaleTs(codecTimebase, streamTimebase);
        writer.WritePacket(&packet);
    }

    writer.Close();

    window.Close();

    return 0;
}