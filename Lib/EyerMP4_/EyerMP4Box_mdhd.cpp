#include "EyerMP4Box_mdhd.hpp"

namespace Eyer
{
    EyerMP4Box_mdhd::EyerMP4Box_mdhd(const EyerBuffer & _buffer) : EyerMP4Box(_buffer)
    {
        int dataLen = buffer.GetBuffer();
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
        language = data[0] << 8 | data[1];

        free(dataArr);
    }

    EyerMP4Box_mdhd::~EyerMP4Box_mdhd()
    {

    }

    BoxType EyerMP4Box_mdhd::GetType()
    {
        return BoxType::MDHD;
    }

    int EyerMP4Box_mdhd::PrintInfo()
    {
        printf("========MDHD========\n");
        printf("creation_time: %d, modification_time: %d, timescale: %d, duration: %d, language:%d\n",
               creation_time, modification_time, timescale, duration, language);
        return 0;
    }

    bool EyerMP4Box_mdhd::HasSub()
    {
        return false;
    }
}