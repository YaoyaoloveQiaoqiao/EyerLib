#include "MP4BoxMVHD.hpp"

namespace Eyer
{
    MP4BoxMVHD::MP4BoxMVHD() : MP4FullBox()
    {

    }

    MP4BoxMVHD::~MP4BoxMVHD()
    {

    }

    int MP4BoxMVHD::ParseParam(EyerBuffer & buffer, int offset)
    {
        offset = MP4FullBox::ParseParam(buffer, offset);

        unsigned char * data = (unsigned char *)malloc(buffer.GetLen());
        buffer.GetBuffer(data);

        if(version == 1){

        }
        else{

        }

        free(data);

        return 0;
    }
}