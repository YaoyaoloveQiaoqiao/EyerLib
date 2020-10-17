#include "EyerMP4Box_mvhd.hpp"

namespace Eyer
{
    EyerMP4Box_mvhd::EyerMP4Box_mvhd(const EyerBuffer &_buffer) : EyerMP4Box(_buffer)
    {
        //// <==========================================>
        int dataLen = buffer.GetBuffer();
        printf("dataLen: %d\n", dataLen);
        unsigned char * dataArr = (unsigned char *)malloc(dataLen);
        unsigned char * data = dataArr;
        buffer.GetBuffer(data);


        data += 4;
        creation_time = data[0] << 24 | data[1] << 16 | data[2] << 8 | data[3];

        data += 4;
        modification_time = data[0] << 24 | data[1] << 16 | data[2] << 8 | data[3];

        data += 4;
        timescale = data[0] << 24 | data[1] << 16 | data[2] << 8 | data[3];

        data += 4;
        duration = data[0] << 24 | data[1] << 16 | data[2] << 8 | data[3];

        data += 4;
        rate = (data[0] << 8 | data[1]) + (data[2] << 8 | data[3]);

        data += 4;
        volume = data[0] + data[1];

        data += 2;
        data += (MAX_MVHD_RESERVED_LEN + MAX_PRE_DEFINE_LEN + MAX_MATRIX_LEN);
        next_track_id = data[0] << 24 | data[1] << 16 | data[2] << 8 | data[3];

        free(dataArr);
        //// <==========================================>
    }

    EyerMP4Box_mvhd::~EyerMP4Box_mvhd()
    {

    }

    BoxType EyerMP4Box_mvhd::GetType()
    {
        return BoxType::MVHD;
    }

    int EyerMP4Box_mvhd::PrintInfo()
    {
        printf("========MVHD========\n");
        printf("\tcreation_time: %d, modification_time: %d, timescale: %d, duration: %d, rate: %f, volume: %f, next_track_id: %d\n",
               creation_time, modification_time, timescale, duration, rate, volume, next_track_id);
        return 0;
    }
}