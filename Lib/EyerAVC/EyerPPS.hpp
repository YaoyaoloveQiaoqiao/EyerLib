#ifndef EYERLIB_EYERPPS_HPP
#define EYERLIB_EYERPPS_HPP

#include "EyerNALU.hpp"
#include "EyerField.hpp"
#include <vector>

#define MAXnum_slice_groups_minus1  8

namespace Eyer
{
    class EyerPPS {
    public:
        EyerPPS(EyerNALU & _nalu);
        ~EyerPPS();

        int PrintInfo();

    private:
        EyerNALU nalu;

        std::vector<EyerField *> fieldList;

        unsigned int pic_parameter_set_id;                             // ue(v)
        unsigned int seq_parameter_set_id;                             // ue(v)
        Boolean   entropy_coding_mode_flag;                            // u(1)

        // if( pic_order_cnt_type < 2 )  in the sequence parameter set
        Boolean      bottom_field_pic_order_in_frame_present_flag;                           // u(1)
        unsigned int num_slice_groups_minus1;                               // ue(v)
        unsigned int slice_group_map_type;                                  // ue(v)

        // if( slice_group_map_type = = 0 )
        unsigned int run_length_minus1[MAXnum_slice_groups_minus1];         // ue(v)
        // else if( slice_group_map_type = = 2 )
        unsigned int top_left[MAXnum_slice_groups_minus1];                  // ue(v)
        unsigned int bottom_right[MAXnum_slice_groups_minus1];              // ue(v)

        Boolean   slice_group_change_direction_flag;                        // u(1)
        unsigned int slice_group_change_rate_minus1;                        // ue(v)



        int num_ref_idx_l0_default_active_minus1;                     // ue(v)
        int num_ref_idx_l1_default_active_minus1;                     // ue(v)
        Boolean   weighted_pred_flag;                               // u(1)
        unsigned int  weighted_bipred_idc;                              // u(2)
        int       pic_init_qp_minus26;                              // se(v)
        int       pic_init_qs_minus26;                              // se(v)
        int       chroma_qp_index_offset;                           // se(v)

        int       cb_qp_index_offset;                               // se(v)
        int       cr_qp_index_offset;                               // se(v)
        int       second_chroma_qp_index_offset;                    // se(v)

        Boolean   deblocking_filter_control_present_flag;           // u(1)
        Boolean   constrained_intra_pred_flag;                      // u(1)
        Boolean   redundant_pic_cnt_present_flag;                   // u(1)
    };
}

#endif //EYERLIB_EYERPPS_HPP
