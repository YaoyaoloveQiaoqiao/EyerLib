#include <gtest/gtest.h>

#include "EyerAV/EyerAV.hpp"
#include "EyerDASH/EyerDASH.hpp"

TEST(AVDecoder, AVDecoderTest)
{
    // Eyer::EyerAVReader reader("/Users/lichi/annie/xiaomai.mp4");
    // Eyer::EyerAVReader reader("/Users/lichi/Downloads/scene_03.mp4");
    Eyer::EyerAVReader reader("/Users/lichi/Desktop/huyou_error.mp4");
    int ret = reader.Open();
    if(ret){
        printf("Open Fail ret: %d\n", ret);
        return;
    }

    Eyer::EyerAVBitstreamFilter::QueryAllBitstreamFilter();


    Eyer::EyerAVStream videoStream;
    int videoStreamIndex = reader.GetVideoStreamIndex();

    reader.GetStream(videoStream, videoStreamIndex);

    Eyer::EyerAVDecoder videoDecoder;
    videoDecoder.Init(&videoStream);

    Eyer::EyerAVBitstreamFilter filter(Eyer::EyerAVBitstreamFilterType::h264_mp4toannexb, videoStream);

    Eyer::AnnexB_to_avcC annexBToAvcC;


    FILE * fff = fopen("/Users/lichi/Desktop/huyou_error.yuv", "wb");

    double maxVideoPts = 0.0;
    while(1){
        Eyer::EyerAVPacket packetA;
        ret = reader.Read(&packetA);
        if(ret){
            break;
        }

        if(packetA.GetStreamId() != videoStreamIndex){
            continue;
        }

        videoStream.ScalerPacketPTS(packetA);
        // printf("packet: %f\n", packetA.GetSecPTS());

        videoDecoder.SendPacket(&packetA);
        while (1){
            Eyer::EyerAVFrame frame;
            ret = videoDecoder.RecvFrame(&frame);
            if(ret){
                break;
            }

            int width = frame.GetWidth();
            int height = frame.GetHeight();

            // printf("w: %d, h: %d\n", width, height);

            /*
            unsigned char * y = (unsigned char *)malloc(width * height);
            unsigned char * u = (unsigned char *)malloc(width * height / 4);
            unsigned char * v = (unsigned char *)malloc(width * height / 4);

            frame.GetYData(y);
            frame.GetUData(u);
            frame.GetVData(v);

            fwrite(y, width * height, 1, fff);
            fwrite(u, width * height / 4, 1, fff);
            fwrite(v, width * height / 4, 1, fff);

            free(y);
            free(u);
            free(v);
             */
        }

        /*
        videoStream.ScalerPacketPTS(packetA);
        if(maxVideoPts <= packetA.GetSecPTS()){
            maxVideoPts = packetA.GetSecPTS();
        }
        // printf("packet: %f\n", maxVideoPts);


        // 转成 AnnexB
        filter.SendPacket(&packetA);

        Eyer::EyerAVPacket packet;
        filter.ReceivePacket(&packet);


        // 转成 avcC

        annexBToAvcC.SendAnnexB(packet.GetDataPtr(), packet.GetSize());
        while(1){
            Eyer::EyerBuffer avccBuffer;
            bool isExtradata;
            ret = annexBToAvcC.RecvAvcC(avccBuffer, isExtradata);
            if(ret){
                break;
            }

            printf("%x %x %x %x %x\n", avccBuffer.GetPtr()[0], avccBuffer.GetPtr()[1], avccBuffer.GetPtr()[2], avccBuffer.GetPtr()[3], avccBuffer.GetPtr()[4]);

            Eyer::EyerAVPacket packetAvcC;
            packetAvcC.SetDataPtr(avccBuffer.GetPtr());
            videoDecoder.SendPacket(&packetAvcC);
            while(1){
                Eyer::EyerAVFrame frame;
                ret = videoDecoder.RecvFrame(&frame);
                if(ret){
                    break;
                }

                printf("PTS: %lld\n", frame.GetPTS());
            }
        }
         */

        // printf("%d %d %d %d %d\n", packet.GetDataPtr()[0], packet.GetDataPtr()[1], packet.GetDataPtr()[2], packet.GetDataPtr()[3], packet.GetDataPtr()[4]);
    }

    fclose(fff);
    reader.Close();
}

/*
TEST(A, ATest){
    Eyer::EyerDASHReader * dashReader = new Eyer::EyerDASHReader("http://redknot.cn/DASH/xiaomai_dash.mpd");

    for(int i=0;i<10;i++){
        dashReader->CreateStream(i % 3 + 1);
        Eyer::EyerAVReader reader("rtmp://redknot.cn:1935/demo/aaa", dashReader);
        int ret = reader.Open();
        if(ret){
            printf("Open Fail ret: %d\n", ret);
            return;
        }

        int streamCount = reader.GetStreamCount();
        printf("Stream Count: %d\n", streamCount);

        int packetIndex = 0;
        while(1){
            Eyer::EyerAVPacket packet;
            ret = reader.Read(&packet);
            if(ret){
                break;
            }
            // printf("Packet: %lld, Stream Id: %d\n", packet.GetPTS(), packet.GetStreamId());

            packetIndex++;
            if(packetIndex == 20){
                dashReader->SwitchStream(3);
            }
        }

        printf("End\n");

        reader.Close();
    }
}
 */

int main(int argc,char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
