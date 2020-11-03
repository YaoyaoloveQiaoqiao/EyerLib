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

    private:
        int pic_parameter_set_id;
        int seq_parameter_set_id;
        int entropy_coding_mode_flag;
        int pic_order_present_flag;
        int num_slice_groups_minus1;
        int slice_group_map_type;
        int run_length_minus1[8]; // up to num_slice_groups_minus1, which is <= 7 in Baseline and Extended, 0 otheriwse
        int top_left[8];
        int bottom_right[8];
        int slice_group_change_direction_flag;
        int slice_group_change_rate_minus1;
        int pic_size_in_map_units_minus1;
        int slice_group_id[256]; // FIXME what size?

        int num_ref_idx_l0_active_minus1;
        int num_ref_idx_l1_active_minus1;
        int weighted_pred_flag;
        int weighted_bipred_idc;
        int pic_init_qp_minus26;
        int pic_init_qs_minus26;
        int chroma_qp_index_offset;
        int deblocking_filter_control_present_flag;
        int constrained_intra_pred_flag;
        int redundant_pic_cnt_present_flag;


        int intlog2(int x);
    };
}



#endif //EYERLIB_EYERPPS_HPP
