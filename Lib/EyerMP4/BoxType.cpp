#include "BoxType.hpp"

namespace Eyer
{
    BoxType BoxType::UNKNOW     (0, 0, 0, 0, 0);
    BoxType BoxType::FTYP       (1, 'f', 't', 'y', 'p');

    BoxType::BoxType()
    {
        *this = BoxType::UNKNOW;
    }

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

    uint32_t BoxType::GetABCD()
    {
        uint32_t abcd = 0;

        abcd = a << 24 | b << 16 | c << 8 | d;

        return abcd;
    }

    BoxType BoxType::GetType(uint32_t net_type)
    {
        if(net_type == UNKNOW.GetABCD()){
            return UNKNOW;
        }

        if(net_type == FTYP.GetABCD()){
            return FTYP;
        }

        return UNKNOW;
    }
}