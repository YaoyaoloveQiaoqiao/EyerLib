#include <gtest/gtest.h>

#include "EyerAV/EyerAV.hpp"

TEST(EyerAVTool, EyerAVTool){
    Eyer::EyerYUVLen yuvLen;
    Eyer::EyerAVTool::GetYUVLen(100, 100, yuvLen, Eyer::EyerAVPixelFormat::Eyer_AV_PIX_FMT_YUV422P);
    printf("y:%d , u: %d, v: %d\n", yuvLen.yLen, yuvLen.uLen, yuvLen.vLen);
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
