#ifndef	EYER_LIB_AV_TEST_ENCODER_H
#define	EYER_LIB_AV_TEST_ENCODER_H

#include <gtest/gtest.h>
#include "MBAV/MBAV.hpp"

#include "Path.hpp"

#include <math.h>

TEST(MBAVCodec, audio_re_encoder){
    MB::MBAVReader audioReader("/home/redknot/Videos/A/1403_20_4431.aac");

    int ret = audioReader.Open();
    if(ret){
        return;
    }

    MB::MBAVStream audioStream;
    ret = audioReader.GetStream(audioStream, 0);
    if(ret){
        return;
    }

    MB::MBAVDecoder audioDecoder;
    audioDecoder.Init(&audioStream);

    MB::MBAVEncoder encoder;
    MB::EncoderParam audioParam;
    audioParam.codecId = MB::CodecId::CODEC_ID_AAC;
    ret = encoder.Init(&audioParam);
    if(ret){
        printf("Open Encoder Error\n");
        return;
    }

    MB::MBAVWriter writer("/home/redknot/Videos/miaomiao.aac");
    int streamId = writer.AddStream(&encoder);

    writer.Open();

    while(1){
        MB::MBAVPacket readPacket;
        ret = audioReader.Read(&readPacket);
        if(ret){
            break;
        }

        audioDecoder.SendPacket(&readPacket);

        while(1){
            MB::MBAVFrame frame;
            ret = audioDecoder.RecvFrame(&frame);
            if(ret){
                break;
            }

            encoder.SendFrame(&frame);

            MB::MBAVPacket encoderPacket;

            while(1){
                ret = encoder.RecvPacket(&encoderPacket);
                if(ret){
                    break;
                }

                encoderPacket.SetStreamId(streamId);
                writer.WritePacket(&encoderPacket);
            }
        }
    }

    writer.Close();

    audioReader.Close();
}

/*
TEST(MBAVCodec, audio_encoder){
    MB::MBAVEncoder encoder;

    MB::EncoderParam audioParam;
    audioParam.codecId = MB::CodecId::CODEC_ID_AAC;

    int ret = encoder.Init(&audioParam);
    if(ret){
        printf("Open Encoder Error\n");

        return;
    }

    MB::MBAVWriter writer("/home/redknot/Videos/miaomiao.aac");
    int streamId = writer.AddStream(&encoder);

    writer.Open();
    
    for(int i=0;i<1000;i++){
        int bufferSize = encoder.GetBufferSize();
        printf("Buffer Size:%d\n", bufferSize);

        float * buf = (float *)malloc(bufferSize);

        for(int j=0;j<bufferSize / 4;j++){
            buf[j] = sin(j * 0.01f * 1.0f) * 100.0f + 128.0f;
        }

        MB::MBAVFrame frame;
        frame.SetPTS(i * 100);
        frame.SetData((unsigned char *)buf, bufferSize);

        encoder.SendFrame(&frame);
        while(1){
            MB::MBAVPacket packet;
            ret = encoder.RecvPacket(&packet);
            if(ret){
                break;
            }

            printf("Encoder Success DTS:%lld=====PTS:%lld\n", packet.GetDTS(), packet.GetPTS());
            packet.SetStreamId(streamId);

            writer.WritePacket(&packet);
        }

        free(buf);
    }    

    writer.Close();
}
*/

#endif
