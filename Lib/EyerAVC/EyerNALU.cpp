#include "EyerNALU.hpp"
#include <stdlib.h>

namespace Eyer {

    EyerNALU::EyerNALU(int buffersize)
    {
        max_size = buffersize;
        buf = (unsigned char * )malloc(buffersize);
    }

    EyerNALU::~EyerNALU()
    {
        if(buf != nullptr){
            free(buf);
            buf = nullptr;
        }
    }
}