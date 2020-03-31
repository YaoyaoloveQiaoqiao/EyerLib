#include "MBGPUDomino.hpp"

namespace MB
{
    MBGomino::MBGomino(MBString _name)
    {
        name = _name;
    }

    MBGomino::MBGomino(MBGomino & gomino)
    {
        *this = gomino;
    }

    MBGomino::~MBGomino()
    {
        ClearAll();
    }

    MBGomino & MBGomino::operator = (MBGomino & gomino)
    {
        ClearAll();

        name = gomino.name;

        return *this;
    }

    int MBGomino::ClearAll()
    {
        return 0;
    }
}