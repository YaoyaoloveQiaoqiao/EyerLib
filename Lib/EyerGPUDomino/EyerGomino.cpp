#include "EyerGPUDomino.hpp"

namespace Eyer
{
    EyerGomino::EyerGomino(EyerString _name)
    {
        name = _name;
    }

    EyerGomino::EyerGomino(EyerGomino & gomino)
    {
        *this = gomino;
    }

    EyerGomino::~EyerGomino()
    {
        ClearAll();
    }

    EyerGomino & EyerGomino::operator = (EyerGomino & gomino)
    {
        ClearAll();

        name = gomino.name;

        return *this;
    }

    int EyerGomino::ClearAll()
    {
        return 0;
    }

    EyerGomino & EyerGomino::operator << (EyerGomino & gomino)
    {
        return *this;
    }
}