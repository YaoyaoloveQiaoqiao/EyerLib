#include "EyerMP4Box_stbl.hpp"

namespace Eyer
{
    EyerMP4Box_stbl::EyerMP4Box_stbl(const EyerBuffer & _buffer) : EyerMP4Box(_buffer)
    {

    }

    EyerMP4Box_stbl::~EyerMP4Box_stbl()
    {

    }

    BoxType EyerMP4Box_stbl::GetType()
    {
        return BoxType::STBL;
    }

    int EyerMP4Box_stbl::PrintInfo()
    {
        printf("========STBL========\n");
        return 0;
    }

    bool EyerMP4Box_stbl::HasSub()
    {
        return true;
    }
}