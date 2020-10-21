#include "MP4FullBox.hpp"

namespace Eyer
{
    MP4FullBox::MP4FullBox()
    {

    }

    MP4FullBox::~MP4FullBox()
    {

    }

    int MP4FullBox::ParseParam(EyerBuffer & buffer, int offset)
    {
        offset = MP4Box::ParseParam(buffer, offset);

        unsigned char * data = (unsigned char *)malloc(buffer.GetLen());
        buffer.GetBuffer(data);

        memcpy(&version, data + offset, 1);
        flags = 0;

        // printf("full box version: %d\n", version);

        free(data);
        return offset + 4;
    }
}