#include "EyerMP4Box_moov.hpp"

namespace Eyer
{
    EyerMP4Box_moov::EyerMP4Box_moov(const EyerBuffer & _buffer) : EyerMP4Box(_buffer)
    {

    }

    EyerMP4Box_moov::~EyerMP4Box_moov()
    {

    }

    BoxType EyerMP4Box_moov::GetType()
    {
        return BoxType::MOOV;
    }

    int EyerMP4Box_moov::PrintInfo()
    {
        printf("========MOOV========\n");
        return 0;
    }
}
