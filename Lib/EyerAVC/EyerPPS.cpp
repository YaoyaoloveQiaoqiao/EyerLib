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

        fieldList.push_back(new EyerField("pic_parameter_set_id",                             pic_parameter_set_id));
        fieldList.push_back(new EyerField("seq_parameter_set_id",                             seq_parameter_set_id));
        fieldList.push_back(new EyerField("entropy_coding_mode_flag",                         entropy_coding_mode_flag));
        fieldList.push_back(new EyerField("pic_order_present_flag",                           pic_order_present_flag));
        fieldList.push_back(new EyerField("num_slice_groups_minus1",                          num_slice_groups_minus1));

        if(num_slice_groups_minus1 > 0) {
            slice_group_map_type = bs.bs_read_ue();
            fieldList.push_back(new EyerField("slice_group_map_type", slice_group_map_type, nullptr, 1));
            if(slice_group_map_type == 0) {
                for( int i_group = 0; i_group <= num_slice_groups_minus1; i_group++ ){
                    run_length_minus1[i_group] = bs.bs_read_ue();
                    fieldList.push_back(new EyerField(EyerString("run_length_minus1[") + EyerString::Number(i_group) +"]", run_length_minus1[i_group], nullptr, 2));
                }
            }
            else if( slice_group_map_type == 2 ) {
                for( int i_group = 0; i_group < num_slice_groups_minus1; i_group++ ) {
                    top_left[ i_group ]     = bs.bs_read_ue();
                    bottom_right[ i_group ] = bs.bs_read_ue();
                    fieldList.push_back(new EyerField(EyerString("top_left[") + EyerString::Number(i_group) +"]", top_left[i_group], nullptr, 2));
                    fieldList.push_back(new EyerField(EyerString("bottom_right[") + EyerString::Number(i_group) +"]", bottom_right[i_group], nullptr, 2));
                }
            }
            else if( slice_group_map_type == 3 ||
                     slice_group_map_type == 4 ||
                     slice_group_map_type == 5 )
            {
                slice_group_change_direction_flag = bs.bs_read_u1();
                slice_group_change_rate_minus1 = bs.bs_read_ue();
                fieldList.push_back(new EyerField("slice_group_change_direction_flag", slice_group_change_direction_flag, nullptr, 2));
                fieldList.push_back(new EyerField("slice_group_change_rate_minus1", slice_group_change_rate_minus1, nullptr, 2));
            }
            else if( slice_group_map_type == 6 ) {
                pic_size_in_map_units_minus1 = bs.bs_read_ue();
                fieldList.push_back(new EyerField("pic_size_in_map_units_minus1", pic_size_in_map_units_minus1, nullptr, 2));
                for( int i = 0; i <= pic_size_in_map_units_minus1; i++ ) {
                    int v = intlog2( num_slice_groups_minus1 + 1 );
                    slice_group_id[i] = bs.bs_read_u(v);
                    fieldList.push_back(new EyerField(EyerString("slice_group_id[") + EyerString::Number(i) +"]", slice_group_id[i], nullptr, 3));
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

        fieldList.push_back(new EyerField("num_ref_idx_l0_active_minus1",                           num_ref_idx_l0_active_minus1));
        fieldList.push_back(new EyerField("num_ref_idx_l1_active_minus1",                           num_ref_idx_l1_active_minus1));
        fieldList.push_back(new EyerField("weighted_pred_flag",                                     weighted_pred_flag));
        fieldList.push_back(new EyerField("weighted_bipred_idc",                                    weighted_bipred_idc));
        fieldList.push_back(new EyerField("pic_init_qp_minus26",                                    pic_init_qp_minus26));
        fieldList.push_back(new EyerField("pic_init_qs_minus26",                                    pic_init_qs_minus26));
        fieldList.push_back(new EyerField("chroma_qp_index_offset",                                 chroma_qp_index_offset));
        fieldList.push_back(new EyerField("deblocking_filter_control_present_flag",                 deblocking_filter_control_present_flag));
        fieldList.push_back(new EyerField("constrained_intra_pred_flag",                            constrained_intra_pred_flag));
        fieldList.push_back(new EyerField("redundant_pic_cnt_present_flag",                         redundant_pic_cnt_present_flag));

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