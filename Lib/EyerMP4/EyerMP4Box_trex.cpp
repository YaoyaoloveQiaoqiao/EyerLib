#include "EyerMP4Box_trex.hpp"

namespace Eyer
{
    EyerMP4Box_trex::EyerMP4Box_trex() : EyerMP4Box()
    {

    }

    EyerMP4Box_trex::EyerMP4Box_trex(const EyerBuffer & _buffer) : EyerMP4Box(_buffer)
    {
        int dataLen = buffer.GetBuffer();
        unsigned char * dataArr = (unsigned char *)malloc(dataLen);
        unsigned char * data = dataArr;
        buffer.GetBuffer(data);


        data += 4;
        track_id                                = data[0] << 24 | data[1] << 16 | data[2] << 8 | data[3];

        data += 4;
        default_sample_description_index        = data[0] << 24 | data[1] << 16 | data[2] << 8 | data[3];

        data += 4;
        default_sample_duration                 = data[0] << 24 | data[1] << 16 | data[2] << 8 | data[3];

        data += 4;
        default_sample_size                     = data[0] << 24 | data[1] << 16 | data[2] << 8 | data[3];

        data += 4;
        default_sample_flags                    = data[0] << 24 | data[1] << 16 | data[2] << 8 | data[3];


        free(dataArr);
    }

    EyerMP4Box_trex::~EyerMP4Box_trex()
    {

    }

    BoxType EyerMP4Box_trex::GetType()
    {
        return BoxType::TREX;
    }

    int EyerMP4Box_trex::PrintInfo()
    {
        printf("========TREX========\n");
        printf("track_id: %d\n", track_id);
        printf("default_sample_description_index: %d\n", default_sample_description_index);
        printf("default_sample_duration: %d\n", default_sample_duration);
        printf("default_sample_size: %d\n", default_sample_size);
        printf("default_sample_flags: %d\n", default_sample_flags);

        return 0;
    }

    bool EyerMP4Box_trex::HasSub()
    {
        return false;
    }
}