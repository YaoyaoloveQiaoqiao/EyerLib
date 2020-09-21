#include "EyerBitStream.hpp"

#include <stdlib.h>
#include <string.h>

namespace Eyer{
    EyerBitStream::EyerBitStream(byte * stream, int len)
    {
        streamBuffer = (byte *)malloc(len);
        memcpy(streamBuffer, stream, len);
    }

    EyerBitStream::~EyerBitStream()
    {
        if(streamBuffer != nullptr){
            free(streamBuffer);
            streamBuffer = nullptr;
        }
    }
}