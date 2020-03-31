//
// Created by lichi on 2020/1/2.
//

#ifndef EYE_LIB_EYERAVDECODERAUDIOTEST_H
#define EYE_LIB_EYERAVDECODERAUDIOTEST_H

#include <gtest/gtest.h>
#include "MBAV/MBAV.hpp"

#include "Path.hpp"

TEST(MBAVDeocder, decoder_audio){
    MB::MBAVReader reader("/Users/lichi/Movies/1403_20_4431.aac");

    reader.Open();

    MB::MBAVStream stream;
    reader.GetStream(stream, 0);

    MB::MBAVDecoder decoder;
    decoder.Init(&stream);

    while(1){
        MB::MBAVPacket pkt;
        int ret = reader.Read(&pkt);
        if(ret){
            break;
        }

        MB::MBAVFrame frame;
        decoder.SendPacket(&pkt);

        while(1){
            ret = decoder.RecvFrame(&frame);
            if(ret){
                break;
            }

            frame.GetInfo();
        }
    }

    reader.Close();
}

#endif //EYE_LIB_EYERAVDECODERAUDIOTEST_H
