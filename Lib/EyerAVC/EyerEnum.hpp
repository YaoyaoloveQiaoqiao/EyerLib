#ifndef EYERLIB_EYERENUM_HPP
#define EYERLIB_EYERENUM_HPP

#include "EyerCore/EyerCore.hpp"

namespace Eyer
{
    class EyerEnum {
    public:
        EyerEnum();
        EyerEnum(int _val, const EyerString & _name);
        virtual ~EyerEnum();

        EyerEnum & operator = (const EyerEnum & eyerEnum);
        bool operator == (const EyerEnum & eyerEnum);
        bool operator != (const EyerEnum & eyerEnum);

        EyerString & GetName();
    protected:
        int val = 0;
        EyerString name;
    };
}

#endif //EYERLIB_EYERENUM_HPP
