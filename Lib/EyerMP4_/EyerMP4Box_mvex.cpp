#include "EyerMP4Box_mvex.hpp"

namespace Eyer
{
    EyerMP4Box_mvex::EyerMP4Box_mvex() : EyerMP4Box()
    {

    }

    EyerMP4Box_mvex::EyerMP4Box_mvex(const EyerBuffer & _buffer) : EyerMP4Box(_buffer)
    {

    }

    EyerMP4Box_mvex::~EyerMP4Box_mvex()
    {

    }

    BoxType EyerMP4Box_mvex::GetType()
    {
        return BoxType::MVEX;
    }

    int EyerMP4Box_mvex::PrintInfo()
    {
        printf("========MVEX========\n");
        return 0;
    }

    bool EyerMP4Box_mvex::HasSub()
    {
        return true;
    }
}