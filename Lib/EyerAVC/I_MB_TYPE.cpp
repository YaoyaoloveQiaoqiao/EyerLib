#include "I_MB_TYPE.hpp"

namespace Eyer
{
    I_MB_TYPE I_4x4(0,      "I_4x4");
    I_MB_TYPE I_PCM(25,     "I_PCM");

    I_MB_TYPE::I_MB_TYPE(int _val, const EyerString & _name) : EyerEnum(_val, _name)
    {

    }

    I_MB_TYPE::I_MB_TYPE(const I_MB_TYPE & mbType)
    {
        *this = mbType;
    }

    I_MB_TYPE::I_MB_TYPE(const int & mbType)
    {
        *this = mbType;
    }

    I_MB_TYPE::~I_MB_TYPE()
    {

    }

    I_MB_TYPE & I_MB_TYPE::operator = (const I_MB_TYPE & mbType)
    {
        EyerEnum::operator=(mbType);
        return *this;
    }

    I_MB_TYPE & I_MB_TYPE::operator = (const int & mbType)
    {
        if(mbType == 0){
            *this = I_4x4;
        }
        else if(mbType == 25){
            *this = I_PCM;
        }
        return *this;
    }

    bool I_MB_TYPE::operator == (const I_MB_TYPE & mbType)
    {
        return EyerEnum::operator==(mbType);
    }
}