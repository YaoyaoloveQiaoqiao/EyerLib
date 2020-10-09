#include "EyerAVCDecoder.hpp"

#include "EyerAnnexB.hpp"

namespace Eyer
{
    EyerAVCDecoder::EyerAVCDecoder(const EyerString & _path)
    {
        path = _path;
    }

    EyerAVCDecoder::~EyerAVCDecoder()
    {

    }

    int EyerAVCDecoder::DecodeAll()
    {
        return 0;
    }
}