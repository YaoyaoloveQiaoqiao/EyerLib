#include <gtest/gtest.h>

#include "EyerAV/EyerAV.hpp"

TEST(A, ATest){
    Eyer::EyerAVReader reader("rtmp://redknot.cn:1935/demo/aaa");
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

    Eyer::EyerAVBitstreamFilter::QueryAllBitstreamFilter();

    Eyer::EyerAVBitstreamFilter avBitstreamFilter(Eyer::EyerAVBitstreamFilterType::h264_mp4toannexb, stream);
    while (1){
        Eyer::EyerAVPacket packet;
        ret = reader.Read(&packet);
        if(ret){
            break;
        }

        EyerLog("Packet: %lld\n", packet.GetPTS());
    }

    reader.Close();
}

int main(int argc,char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
