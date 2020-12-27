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

        // ===================== Syntax Start =====================
        rootSyntax.Put(true, "pic_parameter_set_id",        pic_parameter_set_id);
        rootSyntax.Put(true, "seq_parameter_set_id",        seq_parameter_set_id);
        rootSyntax.Put(true, "entropy_coding_mode_flag",    entropy_coding_mode_flag);
        rootSyntax.Put(true, "pic_order_present_flag",      pic_order_present_flag);
        rootSyntax.Put(true, "num_slice_groups_minus1",     num_slice_groups_minus1);
        // ===================== Syntax End =====================


        if(num_slice_groups_minus1 > 0) {
            slice_group_map_type = bs.bs_read_ue();
            if(slice_group_map_type == 0) {
                for(int i_group = 0; i_group <= num_slice_groups_minus1; i_group++){
                    run_length_minus1[i_group] = bs.bs_read_ue();
                }
            }
            else if(slice_group_map_type == 2) {
                for(int i_group = 0; i_group < num_slice_groups_minus1; i_group++) {
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
            else if(slice_group_map_type == 6) {
                pic_size_in_map_units_minus1 = bs.bs_read_ue();
                for( int i = 0; i <= pic_size_in_map_units_minus1; i++ ) {
                    int v = intlog2( num_slice_groups_minus1 + 1 );
                    slice_group_id[i] = bs.bs_read_u(v);
                }
            }
        }
        // ===================== Syntax Start =====================
        EyerSyntax if_num_slice_groups_minus1_Syntax(true, "if(num_slice_groups_minus1 > 0)", rootSyntax.GetLevel() + 1);
        {
            bool isNumSlice = num_slice_groups_minus1 > 0;
            if_num_slice_groups_minus1_Syntax.Put(isNumSlice, "slice_group_map_type", slice_group_map_type);
            EyerSyntax if_slice_group_map_type_Syntax(isNumSlice, "if(slice_group_map_type == 0)", if_num_slice_groups_minus1_Syntax.GetLevel() + 1);
            {
                EyerSyntax for_num_slice_groups_minus1(isNumSlice && (slice_group_map_type == 0), "for(int i_group = 0; i_group <= num_slice_groups_minus1; i_group++)", if_slice_group_map_type_Syntax.GetLevel() + 1);
                {
                    for(int i_group = 0; i_group <= num_slice_groups_minus1; i_group++){
                        for_num_slice_groups_minus1.Put(isNumSlice && (slice_group_map_type == 0), EyerString() + "run_length_minus1[" + EyerString::Number(i_group) + "]", run_length_minus1[i_group]);
                    }
                }
                if_slice_group_map_type_Syntax.Put(for_num_slice_groups_minus1);
            }
            if_num_slice_groups_minus1_Syntax.Put(if_slice_group_map_type_Syntax);

            EyerSyntax elseif_slice_group_map_type_Syntax(isNumSlice, "else if(slice_group_map_type == 2)", if_num_slice_groups_minus1_Syntax.GetLevel() + 1);
            {
                EyerSyntax for_num_slice_groups_minus1(isNumSlice && (slice_group_map_type == 2), "for(int i_group = 0; i_group < num_slice_groups_minus1; i_group++)", if_slice_group_map_type_Syntax.GetLevel() + 1);
                {
                    for(int i_group = 0; i_group < num_slice_groups_minus1; i_group++){
                        for_num_slice_groups_minus1.Put(isNumSlice && (slice_group_map_type == 2), EyerString() + "top_left[" + EyerString::Number(i_group) + "]", top_left[i_group]);
                        for_num_slice_groups_minus1.Put(isNumSlice && (slice_group_map_type == 2), EyerString() + "bottom_right[" + EyerString::Number(i_group) + "]", bottom_right[i_group]);
                    }
                }
                elseif_slice_group_map_type_Syntax.Put(for_num_slice_groups_minus1);
            }
            if_num_slice_groups_minus1_Syntax.Put(elseif_slice_group_map_type_Syntax);

            EyerString elseif_slice_group_map_type2_Str =   "else if(slice_group_map_type == 3 ||\n"
                                                            "        slice_group_map_type == 4 ||\n"
                                                            "        slice_group_map_type == 5)";
            EyerSyntax elseif_slice_group_map_type2_Syntax(isNumSlice, elseif_slice_group_map_type2_Str, if_num_slice_groups_minus1_Syntax.GetLevel() + 1);
            {
                bool elseif2 = (slice_group_map_type == 3 || slice_group_map_type == 4 || slice_group_map_type == 5);
                elseif_slice_group_map_type2_Syntax.Put(isNumSlice && elseif2, "slice_group_change_direction_flag", slice_group_change_direction_flag);
                elseif_slice_group_map_type2_Syntax.Put(isNumSlice && elseif2, "slice_group_change_rate_minus1", slice_group_change_rate_minus1);
            }
            if_num_slice_groups_minus1_Syntax.Put(elseif_slice_group_map_type2_Syntax);



            EyerSyntax elseif_slice_group_map_type3_Syntax(isNumSlice, "slice_group_map_type == 6", if_num_slice_groups_minus1_Syntax.GetLevel() + 1);
            {
                bool elseif3 = (slice_group_map_type == 6);
                elseif_slice_group_map_type3_Syntax.Put(isNumSlice && elseif3, "pic_size_in_map_units_minus1", pic_size_in_map_units_minus1);
                EyerSyntax for_pic_size_in_map_units_minus1(isNumSlice && elseif3, "for(int i=0; i<=pic_size_in_map_units_minus1; i++)", elseif_slice_group_map_type3_Syntax.GetLevel() + 1);
                {
                    for(int i_group = 0; i_group < pic_size_in_map_units_minus1; i_group++){
                        for_pic_size_in_map_units_minus1.Put(isNumSlice && elseif3, EyerString() + "slice_group_id[" + EyerString::Number(i_group) + "]", slice_group_id[i_group]);
                    }
                }
                elseif_slice_group_map_type3_Syntax.Put(for_pic_size_in_map_units_minus1);
            }
            if_num_slice_groups_minus1_Syntax.Put(elseif_slice_group_map_type3_Syntax);
        }
        rootSyntax.Put(if_num_slice_groups_minus1_Syntax);
        // ===================== Syntax End =====================

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

        // ===================== Syntax Start =====================
        rootSyntax.Put(true, "num_ref_idx_l0_active_minus1",            num_ref_idx_l0_active_minus1);
        rootSyntax.Put(true, "num_ref_idx_l1_active_minus1",            num_ref_idx_l1_active_minus1);
        rootSyntax.Put(true, "weighted_pred_flag",                      weighted_pred_flag);
        rootSyntax.Put(true, "weighted_bipred_idc",                     weighted_bipred_idc);
        rootSyntax.Put(true, "pic_init_qp_minus26",                     pic_init_qp_minus26);
        rootSyntax.Put(true, "pic_init_qs_minus26",                     pic_init_qs_minus26);
        rootSyntax.Put(true, "chroma_qp_index_offset",                  chroma_qp_index_offset);
        rootSyntax.Put(true, "deblocking_filter_control_present_flag",  deblocking_filter_control_present_flag);
        rootSyntax.Put(true, "constrained_intra_pred_flag",             constrained_intra_pred_flag);
        rootSyntax.Put(true, "redundant_pic_cnt_present_flag",          redundant_pic_cnt_present_flag);
        // ===================== Syntax End =====================

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