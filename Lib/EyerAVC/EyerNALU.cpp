#include "EyerNALU.hpp"
#include "EyerAVCCommon.hpp"
#include <stdlib.h>
#include <string.h>

namespace Eyer {

    EyerNALU::EyerNALU(int buffersize)
    {
        max_size = buffersize;
        buf = (unsigned char * )malloc(buffersize);
        memset(buf, 0, max_size);
    }

    EyerNALU::~EyerNALU()
    {
        if(buf != nullptr){
            free(buf);
            buf = nullptr;
        }
    }

    int EyerNALU::ToRBSP()
    {
        len = EyerAVCCommon::EBSPtoRBSP(buf, len, 1);
        return 0;
    }
}