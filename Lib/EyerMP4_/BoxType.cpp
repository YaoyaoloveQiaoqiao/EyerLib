#include "EyerMP4Constant.hpp"

namespace Eyer
{
    BoxType::BoxType(int _id, char _a, char _b, char _c, char _d)
    {
        id = _id;
        a = _a;
        b = _b;
        c = _c;
        d = _d;
    }

    BoxType::~BoxType()
    {

    }

    bool BoxType::operator == (const BoxType boxType)
    {
        return id == boxType.id;
    }

    char BoxType::GetA()
    {
        return a;
    }

    char BoxType::GetB()
    {
        return b;
    }

    char BoxType::GetC()
    {
        return c;
    }

    char BoxType::GetD()
    {
        return d;
    }

    BoxType BoxType::UNKNOW     (0, 0, 0, 0, 0);
    BoxType BoxType::FTYP       (1, 'f', 't', 'y', 'p');
    BoxType BoxType::MOOV       (2, 'm', 'o', 'o', 'v');
    BoxType BoxType::MVHD       (3, 'm', 'v', 'h', 'd');
    BoxType BoxType::TRAK       (4, 't', 'r', 'a', 'k');
    BoxType BoxType::TKHD       (5, 't', 'k', 'h', 'd');
    BoxType BoxType::EDTS       (6, 'e', 'd', 't', 's');
    BoxType BoxType::MDHD       (7, 'm', 'd', 'h', 'd');
    BoxType BoxType::HDLR       (8, 'h', 'd', 'l', 'r');
    BoxType BoxType::MDIA       (9, 'm', 'd', 'i', 'a');
    BoxType BoxType::MINF       (10, 'm', 'i', 'n', 'f');
    BoxType BoxType::STBL       (11, 's', 't', 'b', 'l');
    BoxType BoxType::MVEX       (12, 'm', 'v', 'e', 'x');
    BoxType BoxType::TREX       (13, 't', 'r', 'e', 'x');
    BoxType BoxType::MEHD       (14, 'm', 'e', 'h', 'd');
}
