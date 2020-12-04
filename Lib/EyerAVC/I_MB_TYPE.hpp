#ifndef EYERLIB_I_MB_TYPE_HPP
#define EYERLIB_I_MB_TYPE_HPP

#include "EyerEnum.hpp"

namespace Eyer
{
    class I_MB_TYPE : public EyerEnum{
    public:
        I_MB_TYPE(int _val, const EyerString & _name);
        I_MB_TYPE(const I_MB_TYPE & mbType);
        I_MB_TYPE(const int & mbType);
        ~I_MB_TYPE();

        I_MB_TYPE & operator = (const I_MB_TYPE & mbType);
        I_MB_TYPE & operator = (const int & mbType);
        bool operator == (const I_MB_TYPE & mbType);

    public:
        static I_MB_TYPE I_NxN;
        static I_MB_TYPE I_PCM;

    };
}

#endif //EYERLIB_I_MB_TYPE_HPP
