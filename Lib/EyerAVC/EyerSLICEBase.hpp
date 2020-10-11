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


    private:
        int ref_pic_list_reordering(EyerBitStream * bitStream, int * usedBits);

        int dec_ref_pic_marking(EyerBitStream * bitStream, int * usedBits);

        int alloc_ref_pic_list_reordering_buffer();

    public:
        EyerSPS sps;
        EyerPPS pps;

        int idr_flag;
        int idr_pic_id;
        int nal_reference_idc;                       //!< nal_reference_idc from NAL unit

        int                 pic_parameter_set_id        = 0;   //!<the ID of the picture parameter set the

        int                 first_mb_in_slice           = 0;   //!< MUST be set by NAL even in case of ei_flag == 1
        int                 slice_type                  = 0;    //!< slice type

        int                 model_number;  //!< cabac model number
        unsigned int        frame_num;   //frame_num for this frame
        unsigned int        field_pic_flag              = 0;

        byte                bottom_field_flag;
        int                 mb_aff_frame_flag;
        int                 direct_spatial_mv_pred_flag;       //!< Indicator for direct mode type (1 for Spatial, 0 for Temporal)
        int                 num_ref_idx_active[2];             //!< number of

        int                 qp;
        int                 slice_qp_delta;
        int                 qs;
        int                 slice_qs_delta;


        //the following is for slice header syntax elements of poc
        // for poc mode 0.
        unsigned int pic_order_cnt_lsb                          = 0;
        int delta_pic_order_cnt_bottom;
        // for poc mode 1.
        int delta_pic_order_cnt[2];





        //weighted prediction
        unsigned short weighted_pred_flag;
        unsigned short weighted_bipred_idc;

        unsigned short luma_log2_weight_denom;
        unsigned short chroma_log2_weight_denom;



        short               DFDisableIdc;     //!< Disable deblocking filter on slice
        short               DFAlphaC0Offset;  //!< Alpha and C0 offset for filtering slice
        short               DFBetaOffset;     //!< Beta offset for filtering slice



        int colour_plane_id;                       //!< colour_plane_id of the current coded slice
        int redundant_pic_cnt;
        int sp_switch;                             //!< 1 for switching sp, 0 for normal sp
        int slice_group_change_cycle;






        int                 ref_pic_list_reordering_flag[2];
        int                 *modification_of_pic_nums_idc[2];
        int                 *abs_diff_pic_num_minus1[2];
        int                 *long_term_pic_idx[2];

        int redundant_slice_ref_idx;     //!< reference index of redundant slice




        int no_output_of_prior_pics_flag;
        int long_term_reference_flag;
    };
}



#endif //EYERLIB_EYERSLICEBASE_H
