#include "NALRefIdc.hpp"

namespace Eyer
{
    NALRefIdc NALRefIdc::NALU_PRIORITY_HIGHEST         (3, "NALU_PRIORITY_HIGHEST");
    NALRefIdc NALRefIdc::NALU_PRIORITY_HIGH            (2, "NALU_PRIORITY_HIGH");
    NALRefIdc NALRefIdc::NALU_PRIORITY_LOW             (1, "NALU_PRIORITY_LOW");
    NALRefIdc NALRefIdc::NALU_PRIORITY_DISPOSABLE      (0, "NALU_PRIORITY_DISPOSABLE");

    NALRefIdc::NALRefIdc(int _val, const EyerString & _name) : EyerEnum(_val, _name)
    {

    }

    NALRefIdc::NALRefIdc(const NALRefIdc & refIdc)
    {
        *this = refIdc;
    }

    NALRefIdc::NALRefIdc(const int & refIdc)
    {
        *this = refIdc;
    }

    NALRefIdc::~NALRefIdc()
    {

    }

    NALRefIdc & NALRefIdc::operator = (const NALRefIdc & refIdc)
    {
        EyerEnum::operator=(refIdc);
        return *this;
    }

    NALRefIdc & NALRefIdc::operator = (const int & refIdc)
    {
        if(refIdc == 0){
            *this = NALU_PRIORITY_DISPOSABLE;
        }
        if(refIdc == 1){
            *this = NALU_PRIORITY_LOW;
        }
        if(refIdc == 2){
            *this = NALU_PRIORITY_HIGH;
        }
        if(refIdc == 3){
            *this = NALU_PRIORITY_HIGHEST;
        }
        return *this;
    }

    bool NALRefIdc::operator == (const NALRefIdc & refIdc)
    {
        return EyerEnum::operator==(refIdc);
    }
}