#ifndef EYERLIB_NALREFIDC_HPP
#define EYERLIB_NALREFIDC_HPP

#include "EyerCore/EyerCore.hpp"
#include "EyerEnum.hpp"

namespace Eyer
{
    class NALRefIdc : public EyerEnum{
    public:
        NALRefIdc(int val, const EyerString & _name);
        NALRefIdc(const NALRefIdc & refIdc);
        NALRefIdc(const int & refIdc);
        ~NALRefIdc();

        NALRefIdc & operator = (const NALRefIdc & refIdc);
        NALRefIdc & operator = (const int & refIdc);
        bool operator == (const NALRefIdc & refIdc);
    public:
        static NALRefIdc NALU_PRIORITY_HIGHEST;
        static NALRefIdc NALU_PRIORITY_HIGH;
        static NALRefIdc NALU_PRIORITY_LOW;
        static NALRefIdc NALU_PRIORITY_DISPOSABLE;
    };
}

#endif //EYERLIB_NALREFIDC_HPP
