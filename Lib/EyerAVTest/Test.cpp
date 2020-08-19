#include <gtest/gtest.h>

#include "EyerAV/EyerAV.hpp"
#include "Path.hpp"

#include "EyerAVBitmapTest.h"

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

TEST(EyerAVTool, EyerAVTool){
    Eyer::EyerYUVLen yuvLen;
    Eyer::EyerAVTool::GetYUVLen(100, 100, yuvLen, Eyer::EyerAVPixelFormat::Eyer_AV_PIX_FMT_YUV422P);
    printf("y:%d , u: %d, v: %d\n", yuvLen.yLen, yuvLen.uLen, yuvLen.vLen);
}

TEST(Audio, Audio){
    /*
    Eyer::EyerAVReader reader("/home/redknot/Videos/bbb_sunflower_2160p_60fps_normal.mp4");

    reader.Open();

    Eyer::EyerAVStream stream;
    reader.GetStream(stream, 1);

    Eyer::EyerAVDecoder decoder;
    decoder.Init(&stream);

    while(1)
    {
        Eyer::EyerAVPacket pkt;
        int ret = reader.Read(&pkt);
        if(ret){
            break;
        }

        if(pkt.GetStreamId() == 1){
            decoder.SendPacket(&pkt);
            while(1){
                Eyer::EyerAVFrame frame;
                ret = decoder.RecvFrame(&frame);
                if(ret){
                    break;
                }

                int audioSize = frame.GetAudioPackedData(nullptr);

                EyerLog("Audio Size: %d\n", audioSize);

                unsigned char * audioData = (unsigned char *)malloc(audioSize);

                frame.GetAudioPackedData(audioData);

                if(audioData){
                    free(audioData);
                }

                frame.GetInfo();
            }
        }
    }

    reader.Close();
     */
}

TEST(Encoder, Encoder){
    /*
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

    for(int i=0;i<60 * 25 * 1;i++){
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
    */
}

TEST(EyerAVStreamTimebase, EyerAVStreamTimebaseTest){
    Eyer::EyerAVReader reader("/Users/lichi/annie/xinxiaomen.mp4");
    int ret = reader.Open();
    if(ret){
        printf("Open Fail ret: %d\n", ret);
        return;
    }

    int videoStreamIndex = reader.GetVideoStreamIndex();
    int audioStreamIndex = reader.GetAudioStreamIndex();

    if(videoStreamIndex < 0){
        printf("Video Stream is NULL\n");
    }
    if(audioStreamIndex < 0){
        printf("Audio Stream is NULL\n");
    }

    Eyer::EyerAVStream videoStream;
    reader.GetStream(videoStream, videoStreamIndex);
    Eyer::EyerAVStream audioStream;
    reader.GetStream(audioStream, audioStreamIndex);

    int index = 0;
    while (1) {
        Eyer::EyerAVPacket packet;
        ret = reader.Read(&packet);
        if (ret) {
            break;
        }

        if(packet.GetStreamId() == videoStreamIndex){
            videoStream.ScalerPacketPTS(packet);
            double secPts = packet.GetSecPTS();
            printf("Video Sec PTS: %f, index: %d\n", secPts, index);
            index++;
        }
        if(packet.GetStreamId() == audioStreamIndex){
            audioStream.ScalerPacketPTS(packet);
            double secPts = packet.GetSecPTS();
            printf("Audio Sec PTS: %f, index: %d\n", secPts, index);
            index++;
        }
    }
}

TEST(EyerAVBitstreamFilter, EyerAVBitstreamFilter){
    Eyer::EyerAVReader reader("/Users/lichi/annie/xinxiaomen.mp4");
    int ret = reader.Open();
    if(ret){
        printf("Open Fail ret: %d\n", ret);
        return;
    }

    int videoStreamIndex = reader.GetVideoStreamIndex();

    Eyer::EyerAVStream stream;
    reader.GetStream(stream, videoStreamIndex);

    Eyer::EyerAVDecoder decoder;
    decoder.Init(&stream);

    FILE * file = fopen("./xin.h264", "wb");

    Eyer::EyerAVBitstreamFilter::QueryAllBitstreamFilter();

    Eyer::EyerAVBitstreamFilter avBitstreamFilter(Eyer::EyerAVBitstreamFilterType::h264_mp4toannexb, stream);
    while (1){
        Eyer::EyerAVPacket packet;
        ret = reader.Read(&packet);
        if(ret){
            break;
        }

        if(packet.GetStreamId() != videoStreamIndex){
            continue;
        }

        avBitstreamFilter.SendPacket(&packet);
        while(1){
            Eyer::EyerAVPacket outPacket;
            ret = avBitstreamFilter.ReceivePacket(&outPacket);
            if(ret){
                break;
            }

            // printf("dstLen: %d\n", outPacket.GetSize());
            for(int i=0;i<outPacket.GetSize()-4;i++){
                unsigned char * dataPtr = outPacket.GetDataPtr();
                if(dataPtr[i] == 0){
                    if(dataPtr[i + 1] == 0){
                        if(dataPtr[i + 2] == 0){
                            if(dataPtr[i + 3] == 1){
                                // printf("Miao!!!!\n");
                                // printf("nalu type: %d\n", dataPtr[i + 4] & 0x1F);
                            }
                        }
                    }
                }
            }

            // printf("nalu type: %d\n", outPacket.GetDataPtr()[4] & 0x1F);
            // printf("\n\n");

            fwrite(outPacket.GetDataPtr(), outPacket.GetSize(), 1, file);
        }
    }

    fclose(file);

    reader.Close();
}

int main(int argc,char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
