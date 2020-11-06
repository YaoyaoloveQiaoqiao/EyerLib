#ifndef EYERLIB_EYERPPS_HPP
#define EYERLIB_EYERPPS_HPP

#include "EyerNALUData.hpp"
#include "EyerNALU.hpp"
#include "EyerBitStream.hpp"

namespace Eyer
{
    class EyerPPS : public EyerNALU {
    public:
        EyerPPS();
        ~EyerPPS();

        virtual int Parse();

    public:
        int pic_parameter_set_id = 0;
        int seq_parameter_set_id = 0;
        int entropy_coding_mode_flag = 0;
        int pic_order_present_flag = 0;
        int num_slice_groups_minus1 = 0;
        int slice_group_map_type = 0;
        int run_length_minus1[8]; // up to num_slice_groups_minus1, which is <= 7 in Baseline and Extended, 0 otheriwse
        int top_left[8];
        int bottom_right[8];
        int slice_group_change_direction_flag = 0;
        int slice_group_change_rate_minus1 = 0;
        int pic_size_in_map_units_minus1 = 0;
        int slice_group_id[256]; // FIXME what size?

        int num_ref_idx_l0_active_minus1 = 0;
        int num_ref_idx_l1_active_minus1 = 0;
        int weighted_pred_flag = 0;
        int weighted_bipred_idc = 0;
        int pic_init_qp_minus26 = 0;
        int pic_init_qs_minus26 = 0;
        int chroma_qp_index_offset = 0;
        int deblocking_filter_control_present_flag = 0;
        int constrained_intra_pred_flag = 0;
        int redundant_pic_cnt_present_flag = 0;
    };
}



#endif //EYERLIB_EYERPPS_HPP
