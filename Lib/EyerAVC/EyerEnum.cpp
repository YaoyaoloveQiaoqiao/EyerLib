#include "EyerEnum.hpp"

namespace Eyer
{
    EyerEnum::EyerEnum()
    {

    }

    EyerEnum::EyerEnum(int _val, const EyerString & _name)
    {
        val = _val;
        name = _name;
    }

    EyerEnum::~EyerEnum()
    {

    }

    EyerEnum & EyerEnum::operator = (const EyerEnum & eyerEnum)
    {
        val         = eyerEnum.val;
        name        = eyerEnum.name;
        return *this;
    }

    bool EyerEnum::operator == (const EyerEnum & eyerEnum)
    {
        return val == eyerEnum.val;
    }

    EyerString & EyerEnum::GetName()
    {
        return name;
    }
}