#include <gtest/gtest.h>

#include "EyerAV/EyerAV.hpp"
#include "EyerDASH/EyerDASH.hpp"

TEST(AVDecoder, AVDecoderTest)
{
    Eyer::EyerAVWriter writer("./demoout.gif");
    writer.Open();

    Eyer::EyerAVEncoder encoder;
    Eyer::EncoderParam param;
    param.codecId = Eyer::CodecId::CODEC_ID_GIF;
    param.width = 1920;
    param.height = 1080;
    param.fps = 30;
    // 初始化编码器
    int ret = encoder.Init(&param);


    int outStreamId = writer.AddStream(&encoder);

    writer.WriteHand();



    Eyer::EyerAVReader reader("./demo.mp4");
    ret = reader.Open();
    if(ret){
        return;
    }

    int videoStream = reader.GetVideoStreamIndex();

    Eyer::EyerAVStream stream;
    reader.GetStream(stream, videoStream);

    Eyer::EyerAVDecoder decoder;
    decoder.Init(&stream);

    while(1){
        Eyer::EyerAVPacket packet;
        ret = reader.Read(&packet);
        if(ret){
            break;
        }

        if(packet.GetStreamId() != videoStream){
            continue;
        }

        ret = decoder.SendPacket(&packet);
        if(ret){
            break;
        }

        while(1){
            Eyer::EyerAVFrame frame;
            ret = decoder.RecvFrame(&frame);
            if(ret){
                break;
            }

            EyerLog("PTS %lld\n", frame.GetPTS());

            // 转颜色空间 YUV->RGB8
            Eyer::EyerAVFrame destFrame;
            frame.Scale(destFrame, frame.GetWidth(), frame.GetHeight(), Eyer::EyerAVPixelFormat::Eyer_AV_PIX_FMT_RGB8);

            encoder.SendFrame(&frame);
            while(1){
                Eyer::EyerAVPacket outPacket;
                ret = encoder.RecvPacket(&outPacket);
                if(ret){
                    break;
                }
                outPacket.SetStreamId(outStreamId);
                writer.WritePacket(&outPacket);
            }
        }
    }

    reader.Close();
    writer.Close();
}

int main(int argc,char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
