#include "EyerNALU.hpp"
#include "EyerAVCCommon.hpp"
#include <stdlib.h>
#include <string.h>

namespace Eyer {

    EyerNALU::EyerNALU(int buffersize)
    {
        printf("NALU: %d\n", buffersize);
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

    EyerNALU::EyerNALU(const EyerNALU & _nalu) : EyerNALU(MAX_NALU_SIZE)
    {
        *this = _nalu;
    }

    EyerNALU & EyerNALU::operator = (const EyerNALU & _nalu)
    {
        len = _nalu.len;
        memcpy(buf, _nalu.buf, len);

        return *this;
    }

    int EyerNALU::ToRBSP()
    {
        len = EyerAVCCommon::EBSPtoRBSP(buf, len, 1);
        return 0;
    }

    int EyerNALU::ToSODB()
    {
        len = EyerAVCCommon::RBSPtoSODB(buf, len - 1);
        return 0;
    }
}