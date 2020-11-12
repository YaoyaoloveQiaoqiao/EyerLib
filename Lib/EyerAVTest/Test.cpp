#include <gtest/gtest.h>

#include "EyerAV/EyerAV.hpp"
#include "EyerDASH/EyerDASH.hpp"


TEST(DASH, DAHSTest){


    Eyer::EyerAVReader reader("http://redknot.cn/DASH2/stream.mpd");
    int ret = reader.Open();
    if(ret){
        printf("Open Fail ret: %d\n", ret);
        return;
    }



    std::vector<Eyer::EyerAVBitstreamFilter *> filterList;
    std::vector<FILE *> fileList;
    for(int i=0;i<reader.GetStreamCount();i++){
        Eyer::EyerAVStream stream;
        reader.GetStream(stream, i);

        Eyer::EyerAVBitstreamFilter * bitstreamFilter = new Eyer::EyerAVBitstreamFilter(Eyer::EyerAVBitstreamFilterType::h264_mp4toannexb, stream);
        filterList.push_back(bitstreamFilter);

        FILE * f = fopen((Eyer::EyerString("/Users/lichi/a_") + Eyer::EyerString::Number(i) + ".h264").str, "wb");
        fileList.push_back(f);
    }

    int videoStreamIndex = reader.GetVideoStreamIndex();
    int audioStreamIndex = reader.GetAudioStreamIndex();

    videoStreamIndex = 0;
    audioStreamIndex = 4;

    int streamCount = reader.GetStreamCount();
    printf("Stream Count: %d\n", streamCount);

    for(int i = 0; i < streamCount; i++){
        if(videoStreamIndex == i){
            reader.SetUnDiscardStream(i);
            continue;
        }
        if(audioStreamIndex == i){
            reader.SetUnDiscardStream(i);
            continue;
        }
        reader.SetDiscardStream(i);
    }

    int index = 1;
    while(1){
        Eyer::EyerAVPacket packet;
        ret = reader.Read(&packet);
        if(ret){
            break;
        }

        int streamId = packet.GetStreamId();

        // Eyer::EyerTime::EyerSleepMilliseconds(50);
        printf("Packet: %lld, Stream Id: %d\n", packet.GetPTS(), streamId);


        Eyer::EyerAVBitstreamFilter * bitstreamFilter = filterList[streamId];
        bitstreamFilter->SendPacket(&packet);
        while(1){
            Eyer::EyerAVPacket outPacket;
            ret = bitstreamFilter->ReceivePacket(&outPacket);
            if(ret){
                break;
            }

            FILE * f = fileList[streamId];
            fwrite(outPacket.GetDataPtr(), outPacket.GetSize(), 1, f);

            for(int i=0;i<5;i++){
                printf(" %d ", outPacket.GetDataPtr()[i]);
            }
            printf("\n\n");
        }

        index++;
        printf("index: %d\n", index);
        if(index >=1000){
            break;
        }

        /*
        printf("index: %d\n", index);
        if(index % 500 == 0){
            printf("================================================\n");

            videoStreamIndex = 3;
            audioStreamIndex = 4;

            for(int i = 0; i < streamCount; i++){
                if(videoStreamIndex == i){
                    reader.SetUnDiscardStream(i);
                    continue;
                }
                if(audioStreamIndex == i){
                    reader.SetUnDiscardStream(i);
                    continue;
                }
                reader.SetDiscardStream(i);
            }
        }
         */
    }

    printf("End\n");

    reader.Close();

    for(int i=0;i<fileList.size();i++){
        fclose(fileList[i]);
    }
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
