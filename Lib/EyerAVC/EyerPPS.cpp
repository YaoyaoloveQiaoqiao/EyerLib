#include "EyerPPS.hpp"

namespace Eyer
{
    EyerPPS::EyerPPS()
    {

    }

    EyerPPS::~EyerPPS()
    {

    }

    int EyerPPS::Parse()
    {
        EyerBitStream bs(naluData.GetSODBBuffer());
        return 0;
    }
}