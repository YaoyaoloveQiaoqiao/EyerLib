#ifndef EYERLIB_EYERNALUDATA_HPP
#define EYERLIB_EYERNALUDATA_HPP

#include "EyerCore/EyerCore.hpp"
#include "NALRefIdc.hpp"
#include "NALUType.hpp"

namespace Eyer
{
    class EyerNALUData {
    public:
        EyerNALUData();
        ~EyerNALUData();

        int SetData(EyerBuffer & naluBuffer, int startCodeLen);

        NALUType & GetNALUType();

        EyerBuffer & GetNaluBuffer();
        EyerBuffer & GetRBSPBuffer();
        EyerBuffer & GetSODBBuffer();

    public:
        EyerBuffer naluBuffer;
        EyerBuffer rbspBuffer;
        EyerBuffer sodbBuffer;

        int startCodeLen = 0;

        int       forbidden_bit              = 0;//!< should be always FALSE
        NALRefIdc nal_ref_idc                = NALRefIdc::NALU_PRIORITY_DISPOSABLE;
        NALUType  nal_unit_type              = NALUType::NALU_TYPE_SEI;

        int EBSPtoRBSP(unsigned char * streamBuffer, int end_bytepos, int begin_bytepos);
        int RBSPtoSODB(unsigned char * streamBuffer, int last_byte_pos);
    };
}

#endif //EYERLIB_EYERNALUDATA_HPP
