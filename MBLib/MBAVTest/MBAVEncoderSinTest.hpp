#ifndef	EYER_LIB_AV_TEST_ENCODER_SIN_H
#define	EYER_LIB_AV_TEST_ENCODER_SIN_H

#include <gtest/gtest.h>
#include "MBAV/MBAV.hpp"
#include <math.h>

TEST(MBAVCodec, audio_encoder_sin){
    MB::MBAVWriter writer(sinOutPathStr);

    MB::EncoderParam param;
    param.codecId = MB::CodecId::CODEC_ID_AAC;
    MB::MBAVEncoder encoder;
    encoder.Init(&param);

    int streamIndex = writer.AddStream(&encoder);

    int timeBaseDen = writer.GetStreamTimeBaseDen(streamIndex);
    int timeBaseNum = writer.GetStreamTimeBaseNum(streamIndex);

    printf("Time Base Den:%d\n", timeBaseDen);
    printf("Time Base Num:%d\n", timeBaseNum);


    int bufferSize = encoder.GetBufferSize();
    printf("bufferSize:%d\n", bufferSize);

    writer.Open();

    for(int i=0;i<100;i++){
        MB::MBAVFrame frame;

        int frameSize = encoder.GetFrameSize();
        int size = encoder.GetBufferSize();

        float * d = (float *)malloc(size);
        for(int i=0;i<size / 4;i++){
            d[i] = sin(i * (3.1415926 / 1024.0 * 4.0)) * 0.3f;
        }
        for(int i=0;i<size / 4 / 2;i++){
            d[i] = sin(i * (3.1415926 / 1024.0 * 4.0));
        }

        frame.SetAudioData((unsigned char *)d, size, frameSize, 2, MB::MBAVFormat::EYER_AV_SAMPLE_FMT_FLTP);

        free(d);

        encoder.SendFrame(&frame);

        while (1){
            MB::MBAVPacket pkt;
            int ret = encoder.RecvPacket(&pkt);
            if(ret){
                break;
            }

            // printf("Write Success\n");
            writer.WritePacket(&pkt);
        }
    }


    writer.Close();
}

#endif