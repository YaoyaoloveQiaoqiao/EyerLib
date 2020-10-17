#include "EyerMP4Box_trak.hpp"

namespace Eyer
{
    EyerMP4Box_trak::EyerMP4Box_trak(const EyerBuffer & _buffer) : EyerMP4Box(_buffer)
    {
        //// <==========================================>

        //// <==========================================>
    }

    EyerMP4Box_trak::~EyerMP4Box_trak()
    {

    }

    BoxType EyerMP4Box_trak::GetType()
    {
        return BoxType::TRAK;
    }

    int EyerMP4Box_trak::PrintInfo()
    {
        printf("========TRAK========\n");
        return 0;
    }
}