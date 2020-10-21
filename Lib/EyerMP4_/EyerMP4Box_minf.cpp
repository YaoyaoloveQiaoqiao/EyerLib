#include "EyerMP4Box_minf.hpp"

namespace Eyer
{
    EyerMP4Box_minf::EyerMP4Box_minf(const EyerBuffer & _buffer) : EyerMP4Box(_buffer)
    {

    }

    EyerMP4Box_minf::~EyerMP4Box_minf()
    {

    }

    BoxType EyerMP4Box_minf::GetType()
    {
        return BoxType::MINF;
    }

    int EyerMP4Box_minf::PrintInfo()
    {
        printf("========MINF========\n");
        return 0;
    }

    bool EyerMP4Box_minf::HasSub()
    {
        return true;
    }
}