#include "EyerMP4Box_mdia.hpp"

namespace Eyer
{
    EyerMP4Box_mdia::EyerMP4Box_mdia(const EyerBuffer & _buffer) : EyerMP4Box(_buffer)
    {

    }

    EyerMP4Box_mdia::~EyerMP4Box_mdia()
    {

    }

    BoxType EyerMP4Box_mdia::GetType()
    {

    }

    int EyerMP4Box_mdia::PrintInfo()
    {
        printf("========MDIA========\n");
        return 0;
    }

    bool EyerMP4Box_mdia::HasSub()
    {
        return true;
    }
}
