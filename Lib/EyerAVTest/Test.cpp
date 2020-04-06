#include <gtest/gtest.h>

#include "EyerAV/EyerAV.hpp"
#include "Path.hpp"

#include "EyerAVReadePngListTest.hpp"

//#include "EyerAVBitmapTest.h"

/*
#include "EyerAVDecoderTest.hpp"
#include "EyerAVEncoderTest.hpp"
#include "EyerAVFrameTest.hpp"
#include "EyerAVEncoderSinTest.hpp"
// #include "EyerAVDecoderAudioTest.h"

TEST(EyerAVPacket, packet){
    for(int i=0;i<100;i++){
        Eyer::EyerAVPacket packet;
    }   
}

TEST(EyerAVFormat1, format1){
    Eyer::EyerString path = "";
    Eyer::EyerAVReader reader(path);
    int ret = reader.Open();
    ASSERT_LT(ret, 0) << "这里应该打开失败";
}

TEST(EyerAVFormat2, format2_open_success){
    Eyer::EyerString path = pathStr;
    Eyer::EyerAVReader reader(path);
    int ret = reader.Open();
    ASSERT_EQ(ret, 0) << "这里应该打开成功";
    reader.Close();
}

TEST(EyerAVFormat3, format3_read_frame){
    Eyer::EyerString path = pathStr;
    Eyer::EyerAVReader reader(path);
    int ret = reader.Open();
    ASSERT_EQ(ret, 0) << "这里应该打开成功";

    while (1)
    {
        Eyer::EyerAVPacket packet;
        int ret = reader.Read(&packet);
        if(ret){
            break;
        }
    }

    reader.Close();
}
*/


TEST(Encoder, Encoder){
    int width = 1280;
    int height = 720;

    Eyer::EyerAVWriter writer("/home/redknot/Videos/encoder_mp4.mp4");
    writer.Open();

    Eyer::EyerAVEncoder encoder;
    Eyer::EncoderParam encoderParam;
    encoderParam.width = width;
    encoderParam.height = height;
    encoderParam.codecId = Eyer::CodecId::CODEC_ID_H264;
    encoder.Init(&encoderParam);

    int videoStreamIndex = writer.AddStream(&encoder);

    writer.WriteHand();

    for(int i=0;i<60 * 25 * 60;i++){
        unsigned char * y = (unsigned char *)malloc(width * height);
        unsigned char * u = (unsigned char *)malloc(width * height / 4);
        unsigned char * v = (unsigned char *)malloc(width * height / 4);

        memset(y, 0, width * height);
        memset(u, 0, width * height / 4);
        memset(v, 0, width * height / 4);

        Eyer::EyerAVFrame frame;
        frame.SetPTS(i);
        frame.SetVideoData420P(y, u, v, width, height);

        encoder.SendFrame(&frame);
        while(1){
            Eyer::EyerAVPacket pkt;
            int ret = encoder.RecvPacket(&pkt);
            if(ret){
                break;
            }

            Eyer::EyerAVRational encoderTimebase;
            encoder.GetTimeBase(encoderTimebase);

            Eyer::EyerAVRational streamTimebase;
            writer.GetStreamTimeBase(streamTimebase, videoStreamIndex);

            pkt.RescaleTs(encoderTimebase, streamTimebase);

            pkt.SetStreamId(videoStreamIndex);
            writer.WritePacket(&pkt);
        }

        free(y);
        free(u);
        free(v);
    }

    encoder.SendFrame(nullptr);
    while(1){
        Eyer::EyerAVPacket pkt;
        int ret = encoder.RecvPacket(&pkt);
        if(ret){
            break;
        }

        Eyer::EyerAVRational encoderTimebase;
        encoder.GetTimeBase(encoderTimebase);

        Eyer::EyerAVRational streamTimebase;
        writer.GetStreamTimeBase(streamTimebase, videoStreamIndex);

        pkt.RescaleTs(encoderTimebase, streamTimebase);

        pkt.SetStreamId(videoStreamIndex);
        writer.WritePacket(&pkt);
    }

    writer.Close();
}


int main(int argc,char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
