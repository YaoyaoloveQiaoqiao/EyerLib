#ifndef EYERLIB_EYERANNEXB_HPP
#define EYERLIB_EYERANNEXB_HPP

#include <stdlib.h>
#include <stdio.h>
#include "EyerCore/EyerCore.hpp"

#include "EyerNALU.hpp"

namespace Eyer
{
    class EyerAnnexB {
    public:
        EyerAnnexB(const EyerString & _path);
        ~EyerAnnexB();

        int ReadNALU(EyerNALU & nalu);
    private:
        EyerString path;

        EyerBuffer buffer;

        FILE * file = nullptr;
        bool isEnd = false;

        int ReadFromFile();

        bool CheckStartCode(uint8_t * bufPtr, int bufLen);
    };
}

#endif //EYERLIB_EYERANNEXB_HPP
