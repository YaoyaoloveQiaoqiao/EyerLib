#include "EyerPPS.hpp"

namespace Eyer
{
    EyerPPS::EyerPPS()
    {

    }

    EyerPPS::~EyerPPS()
    {

    }

    int EyerPPS::Parse()
    {
        EyerNALU::Parse();

        EyerBitStream bs(naluData.GetRBSPBuffer());

        pic_parameter_set_id        = bs.bs_read_ue();
        seq_parameter_set_id        = bs.bs_read_ue();
        entropy_coding_mode_flag    = bs.bs_read_u1();
        pic_order_present_flag      = bs.bs_read_u1();
        num_slice_groups_minus1     = bs.bs_read_ue();


        if(num_slice_groups_minus1 > 0) {
            slice_group_map_type = bs.bs_read_ue();
            if(slice_group_map_type == 0) {
                for( int i_group = 0; i_group <= num_slice_groups_minus1; i_group++ ){
                    run_length_minus1[i_group] = bs.bs_read_ue();
                }
            }
            else if( slice_group_map_type == 2 ) {
                for( int i_group = 0; i_group < num_slice_groups_minus1; i_group++ ) {
                    top_left[ i_group ]     = bs.bs_read_ue();
                    bottom_right[ i_group ] = bs.bs_read_ue();
                }
            }
            else if( slice_group_map_type == 3 ||
                     slice_group_map_type == 4 ||
                     slice_group_map_type == 5 )
            {
                slice_group_change_direction_flag = bs.bs_read_u1();
                slice_group_change_rate_minus1 = bs.bs_read_ue();
            }
            else if( slice_group_map_type == 6 ) {
                pic_size_in_map_units_minus1 = bs.bs_read_ue();
                for( int i = 0; i <= pic_size_in_map_units_minus1; i++ ) {
                    int v = intlog2( num_slice_groups_minus1 + 1 );
                    slice_group_id[i] = bs.bs_read_u(v);
                }
            }
        }

        num_ref_idx_l0_active_minus1            = bs.bs_read_ue();
        num_ref_idx_l1_active_minus1            = bs.bs_read_ue();
        weighted_pred_flag                      = bs.bs_read_u1();
        weighted_bipred_idc                     = bs.bs_read_u(2);
        pic_init_qp_minus26                     = bs.bs_read_se();
        pic_init_qs_minus26                     = bs.bs_read_se();
        chroma_qp_index_offset                  = bs.bs_read_se();
        deblocking_filter_control_present_flag  = bs.bs_read_u1();
        constrained_intra_pred_flag             = bs.bs_read_u1();
        redundant_pic_cnt_present_flag          = bs.bs_read_u1();

        // TODO more_rbsp_data
        if(bs.more_data()) {
            transform_8x8_mode_flag             = bs.bs_read_u1();
            pic_scaling_matrix_present_flag     = bs.bs_read_u1();
            if(pic_scaling_matrix_present_flag) {
                // TODO
            }
        }

        valid = true;

        return 0;
    }
}