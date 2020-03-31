#include <gtest/gtest.h>

#include "MBAV/MBAV.hpp"
#include "Path.hpp"

#include "MBAVBitmapTest.h"

/*
#include "MBAVDecoderTest.hpp"
#include "MBAVEncoderTest.hpp"
#include "MBAVFrameTest.hpp"
#include "MBAVEncoderSinTest.hpp"
// #include "MBAVDecoderAudioTest.h"

TEST(MBAVPacket, packet){
    for(int i=0;i<100;i++){
        MB::MBAVPacket packet;
    }   
}

TEST(MBAVFormat1, format1){
    MB::MBString path = "";
    MB::MBAVReader reader(path);
    int ret = reader.Open();
    ASSERT_LT(ret, 0) << "这里应该打开失败";
}

TEST(MBAVFormat2, format2_open_success){
    MB::MBString path = pathStr;
    MB::MBAVReader reader(path);
    int ret = reader.Open();
    ASSERT_EQ(ret, 0) << "这里应该打开成功";
    reader.Close();
}

TEST(MBAVFormat3, format3_read_frame){
    MB::MBString path = pathStr;
    MB::MBAVReader reader(path);
    int ret = reader.Open();
    ASSERT_EQ(ret, 0) << "这里应该打开成功";

    while (1)
    {
        MB::MBAVPacket packet;
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

    MB::MBAVWriter writer("/home/redknot/Videos/encoder_mp4.mp4");
    writer.Open();

    MB::MBAVEncoder encoder;
    MB::EncoderParam encoderParam;
    encoderParam.width = width;
    encoderParam.height = height;
    encoderParam.codecId = MB::CodecId::CODEC_ID_H264;
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

        MB::MBAVFrame frame;
        frame.SetPTS(i);
        frame.SetVideoData420P(y, u, v, width, height);

        encoder.SendFrame(&frame);
        while(1){
            MB::MBAVPacket pkt;
            int ret = encoder.RecvPacket(&pkt);
            if(ret){
                break;
            }

            MB::MBAVRational encoderTimebase;
            encoder.GetTimeBase(encoderTimebase);

            MB::MBAVRational streamTimebase;
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
        MB::MBAVPacket pkt;
        int ret = encoder.RecvPacket(&pkt);
        if(ret){
            break;
        }

        MB::MBAVRational encoderTimebase;
        encoder.GetTimeBase(encoderTimebase);

        MB::MBAVRational streamTimebase;
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
