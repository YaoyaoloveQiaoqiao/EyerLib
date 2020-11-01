#ifndef EYERLIB_EYERNALU_HPP
#define EYERLIB_EYERNALU_HPP

#include "EyerCore/EyerCore.hpp"

namespace Eyer
{
    class EyerNALU {
    public:
        EyerNALU();
        ~EyerNALU();

        int SetData(EyerBuffer & naluBuffer);
    private:
        EyerBuffer naluBuffer;
    };
}

#endif //EYERLIB_EYERNALU_HPP
