#ifndef EYERLIB_EYERAVCCOMMON_HPP
#define EYERLIB_EYERAVCCOMMON_HPP

#include "EyerCore/EyerCore.hpp"

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

    typedef enum
    {
        P_SLICE = 0,
        B_SLICE = 1,
        I_SLICE = 2,
        SP_SLICE = 3,
        SI_SLICE = 4,
        NUM_SLICE_TYPES = 5
    } SliceType;

    typedef enum {
        NO_PROFILE     =  0,       //!< disable profile checking for experimental coding (enables FRExt, but disables MV)
        FREXT_CAVLC444 = 44,       //!< YUV 4:4:4/14 "CAVLC 4:4:4"
        BASELINE       = 66,       //!< YUV 4:2:0/8  "Baseline"
        MAIN           = 77,       //!< YUV 4:2:0/8  "Main"
        EXTENDED       = 88,       //!< YUV 4:2:0/8  "Extended"
        FREXT_HP       = 100,      //!< YUV 4:2:0/8  "High"
        FREXT_Hi10P    = 110,      //!< YUV 4:2:0/10 "High 10"
        FREXT_Hi422    = 122,      //!< YUV 4:2:2/10 "High 4:2:2"
        FREXT_Hi444    = 244,      //!< YUV 4:4:4/14 "High 4:4:4"
        MVC_HIGH       = 118,      //!< YUV 4:2:0/8  "Multiview High"
        STEREO_HIGH    = 128       //!< YUV 4:2:0/8  "Stereo High"
    } ProfileIDC;

    typedef enum {
        CF_UNKNOWN = -1,     //!< Unknown color format
        YUV400     =  0,     //!< Monochrome
        YUV420     =  1,     //!< 4:2:0
        YUV422     =  2,     //!< 4:2:2
        YUV444     =  3      //!< 4:4:4
    } ColorFormat;

    typedef enum
    {
        // YUV
        PLANE_Y = 0,  // PLANE_Y
        PLANE_U = 1,  // PLANE_Cb
        PLANE_V = 2,  // PLANE_Cr
        // RGB
        PLANE_G = 0,
        PLANE_B = 1,
        PLANE_R = 2
    } ColorPlane;

    enum {
        LIST_0 = 0,
        LIST_1 = 1,
        BI_PRED = 2,
        BI_PRED_L0 = 3,
        BI_PRED_L1 = 4
    };

    class EyerENUMUtil {
    public:
        static EyerString GetSliceTypeStr(const SliceType & sliceType);
    };

    class EyerAVCCommon {
    public:
        static const int ZEROBYTES_SHORTSTARTCODE = 2;
        static int EBSPtoRBSP(unsigned char * streamBuffer, int end_bytepos, int begin_bytepos);
        static int RBSPtoSODB(unsigned char * streamBuffer, int last_byte_pos);
    };
}

#endif //EYERLIB_EYERAVCCOMMON_HPP
