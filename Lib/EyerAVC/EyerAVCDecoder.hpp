#ifndef EYERLIB_EYERAVCDECODER_HPP
#define EYERLIB_EYERAVCDECODER_HPP

#include "EyerCore/EyerCore.hpp"
#include "EyerSPS.hpp"
#include "EyerPPS.hpp"

namespace Eyer{
    class EyerAVCDecoder {
    public:
        EyerAVCDecoder(const EyerString & _path);
        ~EyerAVCDecoder();

        int DecodeAll();

    private:
        EyerString path;

        EyerSPS sps;
        EyerPPS pps;

        std::vector<Eyer::EyerNAL *> nalList;
    };
}

#endif //EYERLIB_EYERAVCDECODER_HPP
