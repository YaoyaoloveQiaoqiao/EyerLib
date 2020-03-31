#ifndef	EYER_LIB_AV_TEST_DECODER_H
#define	EYER_LIB_AV_TEST_DECODER_H

#include <gtest/gtest.h>
#include "MBAV/MBAV.hpp"

#include "Path.hpp"

TEST(MBAVFormat4, format4_read_frame){
    MB::MBAVReader reader(pathStr);
    int ret = reader.Open();
    ASSERT_EQ(ret, 0) << "这里应该打开成功";

    std::vector<MB::MBAVDecoder *> decoderList;
    for(int i=0;i<reader.GetStreamCount();i++){
        MB::MBAVStream stream;
        reader.GetStream(stream, i);

        MB::MBAVDecoder * decoder = new MB::MBAVDecoder();
        decoder->Init(&stream);

        decoderList.push_back(decoder);

        printf("Stream Id:%d,Duration:%f\n", i, stream.GetDuration());
    }

    while (1)
    {
        MB::MBAVPacket packet;
        int ret = reader.Read(&packet);
        if(ret){
            break;
        }

        MB::MBAVDecoder * decoder = decoderList[packet.GetStreamId()];
        decoder->SendPacket(&packet);

        while(1){
            MB::MBAVFrame frame;
            ret = decoder->RecvFrame(&frame);
            if(ret){
                break;
            }
        }
    }

    // 清空解码器
    for(int i=0;i<decoderList.size();i++){
        MB::MBAVDecoder * decoder = decoderList[i];

        decoder->SendPacket(nullptr);
        while(1){
            MB::MBAVFrame frame;
            ret = decoder->RecvFrame(&frame);
            if(ret){
                break;
            }

            printf("End Recv Frame Success, Stream Id:%d\n", i);
        }
    }

    for(int i=0;i<decoderList.size();i++){
        MB::MBAVDecoder * decoder = decoderList[i];
        delete decoder;
    }

    decoderList.clear();
    reader.Close();
}


#endif
