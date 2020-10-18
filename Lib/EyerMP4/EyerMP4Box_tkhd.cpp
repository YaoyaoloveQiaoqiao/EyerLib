#include "EyerMP4Box_tkhd.hpp"

namespace Eyer
{
    EyerMP4Box_tkhd::EyerMP4Box_tkhd(const EyerBuffer & _buffer) : EyerMP4Box(_buffer)
    {
        //// <==========================================>
        int dataLen = buffer.GetBuffer();
        unsigned char * dataArr = (unsigned char *)malloc(dataLen);
        unsigned char * data = dataArr;
        buffer.GetBuffer(data);

        flags = data[1] << 16 | data[2] << 8 | data[3];

        data += 4;
        creation_time = data[0] << 24 | data[1] << 16 | data[2] << 8 | data[3];

        data += 4;
        modification_time = data[0] << 24 | data[1] << 16 | data[2] << 8 | data[3];

        data += 4;
        track_id = data[0] << 24 | data[1] << 16 | data[2] << 8 | data[3];

        data += 4;

        data += 4; /* 4 reserved */
        duration = data[0] << 24 | data[1] << 16 | data[2] << 8 | data[3];

        data += 4;

        data += 8; /* 8 reserved */
        layer = data[0] << 8 | data[1];

        data += 2;
        alternate_group = data[0] << 8 | data[1];

        data += 2;
        volume = data[0] + data[1];

        data += 2;

        data += 2;

        data += 36;
        width = (data[0] << 8 | data[1]) + (data[2] << 8 | data[3]);

        data += 4;
        height = (data[0] << 8 | data[1]) + (data[2] << 8 | data[3]);

        free(dataArr);
        //// <==========================================>
    }

    EyerMP4Box_tkhd::~EyerMP4Box_tkhd()
    {

    }

    BoxType EyerMP4Box_tkhd::GetType()
    {
        return BoxType::TKHD;
    }

    int EyerMP4Box_tkhd::PrintInfo()
    {
        printf("========TKHD========\n");
        printf("flags: %d, creation_time: %d, modification_time: %d, track_id: %d, duration: %d, layer: %d, alternate_group: %d, volume: %f, width: %f, height: %f\n",
               flags, creation_time, modification_time, track_id, duration, layer, alternate_group, volume, width, height);
        return 0;
    }

    bool EyerMP4Box_tkhd::HasSub()
    {
        return false;
    }
}