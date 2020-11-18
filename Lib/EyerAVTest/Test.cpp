#include <gtest/gtest.h>

#include "EyerAV/EyerAV.hpp"
#include "EyerDASH/EyerDASH.hpp"

TEST(AVDecoder, AVDecoderTest)
{
    Eyer::EyerAVReader reader("/Users/lichi/annie/xiaomai_h264_ts.ts");
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

    Eyer::EyerAVBitstreamFilter filter(Eyer::EyerAVBitstreamFilterType::hevc_mp4toannexb, videoStream);

    while(1){
        Eyer::EyerAVPacket packet;
        ret = reader.Read(&packet);
        if(ret){
            break;
        }

        if(packet.GetStreamId() != videoStreamIndex){
            continue;
        }

        /*
        filter.SendPacket(&packetA);

        Eyer::EyerAVPacket packet;
        filter.ReceivePacket(&packet);
         */

        // packet = packetA;

        printf("%d %d %d %d %d\n", packet.GetDataPtr()[0], packet.GetDataPtr()[1], packet.GetDataPtr()[2], packet.GetDataPtr()[3], packet.GetDataPtr()[4]);

        videoDecoder.SendPacket(&packet);
        while(1){
            Eyer::EyerAVFrame frame;
            ret = videoDecoder.RecvFrame(&frame);
            if(ret){
                break;
            }
            printf("frame: %lld\n", frame.GetPTS());
        }
    }


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
