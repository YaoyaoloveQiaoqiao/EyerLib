#include "BoxType.hpp"
#include <stdio.h>

namespace Eyer
{
    BoxType BoxType::UNKNOW     (0, 'u', 'n', 'k', 'w', false);
    BoxType BoxType::ROOT       (1, 'r', 'o', 'o', 't', true);
    BoxType BoxType::FTYP       (2, 'f', 't', 'y', 'p', false);
    BoxType BoxType::FREE       (3, 'f', 'r', 'e', 'e', false);
    BoxType BoxType::MOOV       (4, 'm', 'o', 'o', 'v', true);
    BoxType BoxType::MDAT       (5, 'm', 'd', 'a', 't', false);
    BoxType BoxType::MVHD       (6, 'm', 'v', 'h', 'd', false);
    BoxType BoxType::TRAK       (7, 't', 'r', 'a', 'k', true);
    BoxType BoxType::TKHD       (8, 't', 'k', 'h', 'd', false);

    BoxType::BoxType()
    {
        *this = BoxType::UNKNOW;
    }

    BoxType::BoxType(int _id, char _a, char _b, char _c, char _d, bool _hasSub)
    {
        id = _id;
        a = _a;
        b = _b;
        c = _c;
        d = _d;
        hasSub = _hasSub;
    }

    BoxType::~BoxType()
    {

    }

    bool BoxType::operator == (const BoxType boxType) const
    {
        return id == boxType.id;
    }

    bool BoxType::operator != (const BoxType boxType) const
    {
        return !(*this == boxType);
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

    uint32_t BoxType::GetABCD()
    {
        uint32_t abcd = 0;

        abcd = d << 24 | c << 16 | b << 8 | a;

        return abcd;
    }

    BoxType BoxType::GetType(uint32_t net_type)
    {
        if(net_type == UNKNOW.GetABCD()){
            return UNKNOW;
        }
        else if(net_type == FTYP.GetABCD()){
            return FTYP;
        }
        else if(net_type == FREE.GetABCD()){
            return FREE;
        }
        else if(net_type == MOOV.GetABCD()){
            return MOOV;
        }
        else if(net_type == MDAT.GetABCD()){
            return MDAT;
        }
        else if(net_type == MVHD.GetABCD()){
            return MVHD;
        }
        else if(net_type == TRAK.GetABCD()){
            return TRAK;
        }
        else if(net_type == TKHD.GetABCD()){
            return TKHD;
        }

        return UNKNOW;
    }

    bool BoxType::HasSub()
    {
        return hasSub;
    }

    int BoxType::PrintInfo()
    {
        printf("%c%c%c%c\n", a, b, c, d);
        return 0;
    }
}