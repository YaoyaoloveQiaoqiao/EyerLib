#include "EyerMP4Box_edts.hpp"

namespace Eyer
{
    EyerMP4Box_edts::EyerMP4Box_edts(const EyerBuffer & _buffer) : EyerMP4Box(_buffer)
    {

    }

    EyerMP4Box_edts::~EyerMP4Box_edts()
    {

    }

    BoxType EyerMP4Box_edts::GetType()
    {
        return BoxType::EDTS;
    }

    int EyerMP4Box_edts::PrintInfo()
    {
        printf("========EDTS========\n");
        return 0;
    }
}