#ifndef EYERLIB_NALUTYPE_HPP
#define EYERLIB_NALUTYPE_HPP

#include "EyerEnum.hpp"

namespace Eyer
{
    class NALUType : public EyerEnum{
    public:
        NALUType(int _val, const EyerString & _name);
        NALUType(const NALUType & naluType);
        NALUType(const int & naluType);
        ~NALUType();


        NALUType & operator = (const NALUType & naluType);
        NALUType & operator = (const int & naluType);
        bool operator == (const NALUType & naluType);
    public:
        static NALUType NALU_TYPE_SLICE;
        static NALUType NALU_TYPE_DPA;
        static NALUType NALU_TYPE_DPB;
        static NALUType NALU_TYPE_DPC;
        static NALUType NALU_TYPE_IDR;
        static NALUType NALU_TYPE_SEI;
        static NALUType NALU_TYPE_SPS;
        static NALUType NALU_TYPE_PPS;
        static NALUType NALU_TYPE_AUD;
        static NALUType NALU_TYPE_EOSEQ;
        static NALUType NALU_TYPE_EOSTREAM;
        static NALUType NALU_TYPE_FILL;
    };
}

#endif //EYERLIB_NALUTYPE_HPP
