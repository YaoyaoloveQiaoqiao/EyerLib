#include "EyerNALU.hpp"
#include "EyerAVCCommon.hpp"
#include <stdlib.h>
#include <string.h>

namespace Eyer {

    EyerNALU::EyerNALU(int buffersize)
    {
        if(buffersize <= 0){
            max_size = 0;
            buf = nullptr;
        }
        else {
            max_size = buffersize;
            buf = (unsigned char * )malloc(max_size);
            memset(buf, 0, max_size);
        }
    }

    EyerNALU::~EyerNALU()
    {
        if(buf != nullptr){
            free(buf);
            buf = nullptr;
        }
    }

    EyerNALU::EyerNALU(const EyerNALU & _nalu) : EyerNALU()
    {
        *this = _nalu;
    }

    EyerNALU & EyerNALU::operator = (const EyerNALU & _nalu)
    {
        if(buf != nullptr){
            free(buf);
            buf = nullptr;
        }

        max_size = _nalu.len;
        len = _nalu.len;
        buf = (unsigned char *)malloc(len);

        memcpy(buf, _nalu.buf, len);

        // len = _nalu.len;
        // memcpy(buf, _nalu.buf, len);

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