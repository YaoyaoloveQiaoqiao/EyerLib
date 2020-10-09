#ifndef EYERLIB_EYERSLICEBASE_H
#define EYERLIB_EYERSLICEBASE_H

#include "EyerNALU.hpp"
#include "EyerAVCCommon.hpp"
#include "EyerBitStream.hpp"
#include "EyerVUI.hpp"
#include "EyerField.hpp"
#include "EyerNAL.hpp"
#include "EyerSPS.hpp"
#include "EyerPPS.hpp"

namespace Eyer{
    class EyerSLICEBase : public EyerNAL {
    public:
        EyerSLICEBase(EyerNALU & _nalu, EyerSPS & _sps, EyerPPS & _pps);
        ~EyerSLICEBase();

        virtual NaluType GetNalType() = 0;

    public:
        EyerSPS sps;
        EyerPPS pps;

        int idr_flag;
        int idr_pic_id;
        int nal_reference_idc;                       //!< nal_reference_idc from NAL unit

        int                 first_mb_in_slice;   //!< MUST be set by NAL even in case of ei_flag == 1
        int                 slice_type;    //!< slice type
        int                 pic_parameter_set_id;   //!<the ID of the picture parameter set the

        int colour_plane_id;               //!< colour_plane_id of the current coded slice
        unsigned int        frame_num;   //frame_num for this frame
        unsigned int        field_pic_flag;

        byte                bottom_field_flag;
    };
}



#endif //EYERLIB_EYERSLICEBASE_H
