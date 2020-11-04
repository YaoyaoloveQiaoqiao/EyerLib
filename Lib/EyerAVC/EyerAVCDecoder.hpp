#ifndef EYERLIB_EYERAVCDECODER_HPP
#define EYERLIB_EYERAVCDECODER_HPP

#include "EyerCore/EyerCore.hpp"

namespace Eyer
{
    class EyerAVCDecoder {
    public:
        EyerAVCDecoder(const EyerString & _path);
        ~EyerAVCDecoder();

        int Decode();

    private:
        EyerString path;
    };
}

#endif //EYERLIB_EYERAVCDECODER_HPP
