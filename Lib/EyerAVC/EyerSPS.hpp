#ifndef EYERLIB_EYERSPS_HPP
#define EYERLIB_EYERSPS_HPP

#include "EyerNALU.hpp"
#include "EyerAVCCommon.hpp"

namespace Eyer{
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

    class EyerSPS {
    public:
        EyerSPS(EyerNALU & _nalu);
        ~EyerSPS();

        int PrintInfo();

    private:
        EyerNALU nalu;

        unsigned int profile_idc;                                       // u(8)
        Boolean   constrained_set0_flag;                                // u(1)
        Boolean   constrained_set1_flag;                                // u(1)
        Boolean   constrained_set2_flag;                                // u(1)
        Boolean   constrained_set3_flag;                                // u(1)
        Boolean   constrained_set4_flag;                                // u(1)
        Boolean   constrained_set5_flag;                                // u(1)
        unsigned  int level_idc;                                        // u(8)
        unsigned  int seq_parameter_set_id;                             // ue(v)
    };
}

#endif //EYERLIB_EYERSPS_HPP
