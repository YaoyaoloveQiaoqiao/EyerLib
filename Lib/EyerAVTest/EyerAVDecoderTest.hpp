#ifndef	EYER_LIB_AV_TEST_DECODER_H
#define	EYER_LIB_AV_TEST_DECODER_H

#include <gtest/gtest.h>
#include "EyerAV/EyerAV.hpp"

#include "Path.hpp"

TEST(EyerAVFormat4, format4_read_frame){
    Eyer::EyerAVReader reader(pathStr);
    int ret = reader.Open();
    ASSERT_EQ(ret, 0) << "这里应该打开成功";

    std::vector<Eyer::EyerAVDecoder *> decoderList;
    for(int i=0;i<reader.GetStreamCount();i++){
        Eyer::EyerAVStream stream;
        reader.GetStream(stream, i);

        Eyer::EyerAVDecoder * decoder = new Eyer::EyerAVDecoder();
        decoder->Init(&stream);

        decoderList.push_back(decoder);

        printf("Stream Id:%d,Duration:%f\n", i, stream.GetDuration());
    }

    while (1)
    {
        Eyer::EyerAVPacket packet;
        int ret = reader.Read(&packet);
        if(ret) {
            break;
        }

        Eyer::EyerAVDecoder * decoder = decoderList[packet.GetStreamId()];
        decoder->SendPacket(&packet);

        while(1){
            Eyer::EyerAVFrame frame;
            ret = decoder->RecvFrame(&frame);
            if(ret){
                break;
            }
        }
    }

    // 清空解码器
    for(int i=0;i<decoderList.size();i++){
        Eyer::EyerAVDecoder * decoder = decoderList[i];

        decoder->SendPacket(nullptr);
        while(1){
            Eyer::EyerAVFrame frame;
            ret = decoder->RecvFrame(&frame);
            if(ret){
                break;
            }

            printf("End Recv Frame Success, Stream Id:%d\n", i);
        }
    }

    for(int i=0;i<decoderList.size();i++){
        Eyer::EyerAVDecoder * decoder = decoderList[i];
        delete decoder;
    }

    decoderList.clear();
    reader.Close();
}


#endif
