#ifndef EYERLIB_EYERSLICEHEADER_HPP
#define EYERLIB_EYERSLICEHEADER_HPP

#include "EyerBitStream.hpp"
#include "SLICEType.hpp"
#include "EyerSPS.hpp"
#include "EyerPPS.hpp"

namespace Eyer
{
    typedef struct
    {
        int first_mb_in_slice;
        int slice_type;
        int pic_parameter_set_id;
        int colour_plane_id;
        int frame_num;
        int field_pic_flag;
        int bottom_field_flag;
        int idr_pic_id;
        int pic_order_cnt_lsb;
        int delta_pic_order_cnt_bottom;
        int delta_pic_order_cnt[ 2 ];
        int redundant_pic_cnt;
        int direct_spatial_mv_pred_flag;
        int num_ref_idx_active_override_flag;
        int num_ref_idx_l0_active_minus1;
        int num_ref_idx_l1_active_minus1;
        int cabac_init_idc;
        int slice_qp_delta;
        int sp_for_switch_flag;
        int slice_qs_delta;
        int disable_deblocking_filter_idc;
        int slice_alpha_c0_offset_div2;
        int slice_beta_offset_div2;
        int slice_group_change_cycle;

        struct
        {
            int luma_log2_weight_denom;
            int chroma_log2_weight_denom;
            int luma_weight_l0_flag[64];
            int luma_weight_l0[64];
            int luma_offset_l0[64];
            int chroma_weight_l0_flag[64];
            int chroma_weight_l0[64][2];
            int chroma_offset_l0[64][2];
            int luma_weight_l1_flag[64];
            int luma_weight_l1[64];
            int luma_offset_l1[64];
            int chroma_weight_l1_flag[64];
            int chroma_weight_l1[64][2];
            int chroma_offset_l1[64][2];
        } pwt;

        struct
        {
            int ref_pic_list_reordering_flag_l0;
            struct
            {
                int reordering_of_pic_nums_idc[64];
                int abs_diff_pic_num_minus1[64];
                int long_term_pic_num[64];
            } reorder_l0;
            int ref_pic_list_reordering_flag_l1;
            struct
            {
                int reordering_of_pic_nums_idc[64];
                int abs_diff_pic_num_minus1[64];
                int long_term_pic_num[64];
            } reorder_l1;
        } rplr;

        struct
        {
            int no_output_of_prior_pics_flag;
            int long_term_reference_flag;
            int adaptive_ref_pic_marking_mode_flag;
            int memory_management_control_operation[64];
            int difference_of_pic_nums_minus1[64];
            int long_term_pic_num[64];
            int long_term_frame_idx[64];
            int max_long_term_frame_idx_plus1[64];
        } drpm;

    } SliceHeaderData;


    class EyerSLICEHeader {
    public:
        EyerSLICEHeader();
        ~EyerSLICEHeader();

        SLICEType GetSLICEType();

        int Parse(EyerBitStream & bs, EyerFieldList & fieldList, EyerSPS & _sps, EyerPPS & _pps, EyerNALUData & _naluData);

    public:
        SliceHeaderData sh;
    private:
        EyerSPS sps;
        EyerPPS pps;
        EyerNALUData naluData;

        SLICEType sliceType;

        int ParseHeadPartA(EyerBitStream & bs, EyerFieldList & fieldList);
        int ParseHeadPartB(EyerBitStream & bs, EyerFieldList & fieldList);

        int ReadRefPicListReordering    (EyerBitStream & bs, EyerFieldList & fieldList);
        int ReadPredWeightTable         (EyerBitStream & bs, EyerFieldList & fieldList);
        int ReadDecRefPicMarking        (EyerBitStream & bs, EyerFieldList & fieldList);

        int intlog2(int x);
    };
}

#endif //EYERLIB_EYERSLICEHEADER_HPP
