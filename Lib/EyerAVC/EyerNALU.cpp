#include "EyerNALU.hpp"

#include <stdio.h>

namespace Eyer
{
    EyerNALU::EyerNALU()
    {

    }

    EyerNALU::~EyerNALU()
    {

    }

    int EyerNALU::SetData(EyerBuffer & _naluBuffer)
    {
        naluBuffer = _naluBuffer;

        unsigned char * bufPtr = naluBuffer.GetPtr();
        printf("%d %d %d %d %d\n", bufPtr[0], bufPtr[1], bufPtr[2], bufPtr[3], bufPtr[4]);

        return 0;
    }
}