#ifndef EYERLIB_EYERAVCCOMMON_HPP
#define EYERLIB_EYERAVCCOMMON_HPP

namespace Eyer{

    typedef unsigned char byte;

    typedef enum {
        FALSE,
        TRUE
    } Boolean;

    enum NaluType {
        NALU_TYPE_SLICE    = 1,
        NALU_TYPE_DPA      = 2,
        NALU_TYPE_DPB      = 3,
        NALU_TYPE_DPC      = 4,
        NALU_TYPE_IDR      = 5,
        NALU_TYPE_SEI      = 6,
        NALU_TYPE_SPS      = 7,
        NALU_TYPE_PPS      = 8,
        NALU_TYPE_AUD      = 9,
        NALU_TYPE_EOSEQ    = 10,
        NALU_TYPE_EOSTREAM = 11,
        NALU_TYPE_FILL     = 12,
    };

    class EyerAVCCommon {
    public:
        static const int ZEROBYTES_SHORTSTARTCODE = 2;
        static int EBSPtoRBSP(unsigned char * streamBuffer, int end_bytepos, int begin_bytepos);
        static int RBSPtoSODB(unsigned char * streamBuffer, int last_byte_pos);
    };
}

#endif //EYERLIB_EYERAVCCOMMON_HPP
