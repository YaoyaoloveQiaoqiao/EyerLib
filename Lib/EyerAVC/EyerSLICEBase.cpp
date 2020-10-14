#include "EyerSLICEBase.hpp"
#include "EyerAVC_VLC.hpp"

namespace Eyer
{
    EyerSLICEBase::EyerSLICEBase(EyerNALU & _nalu, EyerSPS & _sps, EyerPPS & _pps) : EyerNAL()
    {
        sps = _sps;
        pps = _pps;

        nalu = _nalu;

        nalu.ToSODB();

        int val;
        int len;

        idr_flag = (nalu.nal_unit_type == NALU_TYPE_IDR);
        nal_reference_idc = nalu.nal_reference_idc;

        EyerBitStream bitStream(nalu.buf + 1, nalu.len - 1);
        bitStream.code_len = nalu.len - 1;
        bitStream.bitstream_length = nalu.len - 1;
        bitStream.ei_flag = 0;
        bitStream.read_len = 0;
        bitStream.frame_bitoffset = 0;

        int usedBits = 0;

        first_mb_in_slice = EyerAVC_VLC::read_ue_v ("SH: first_mb_in_slice", &bitStream, &usedBits);
        fieldList.push_back(new EyerField("first_mb_in_slice", first_mb_in_slice));

        int tmp = EyerAVC_VLC::read_ue_v ("SH: slice_type", &bitStream, &usedBits);
        if (tmp > 4) {
            tmp -= 5;
        }

        slice_type = (SliceType) tmp;
        EyerString slice_type_str = EyerENUMUtil::GetSliceTypeStr((SliceType)slice_type);
        fieldList.push_back(new EyerField("slice_type", slice_type, slice_type_str));

        pic_parameter_set_id = EyerAVC_VLC::read_ue_v ("SH: pic_parameter_set_id", &bitStream, &usedBits);
        fieldList.push_back(new EyerField("pic_parameter_set_id", pic_parameter_set_id));



        if(sps.separate_colour_plane_flag){
            colour_plane_id = EyerAVC_VLC::read_u_v (2, "SH: colour_plane_id", &bitStream, &usedBits);
        }
        else {
            colour_plane_id = PLANE_Y;
        }




        ////////////////////////////////

        frame_num = EyerAVC_VLC::read_u_v (sps.log2_max_frame_num_minus4 + 4, "SH: frame_num", &bitStream, &usedBits);
        fieldList.push_back(new EyerField("frame_num", frame_num));

        if (sps.frame_mbs_only_flag) {
            field_pic_flag = 0;
        }
        else{
            field_pic_flag = EyerAVC_VLC::read_u_1("SH: field_pic_flag", &bitStream, &usedBits);
            if (field_pic_flag) {
                bottom_field_flag = (byte) EyerAVC_VLC::read_u_1("SH: bottom_field_flag", &bitStream, &usedBits);
            }
            else {
                bottom_field_flag = FALSE;
            }
        }
        fieldList.push_back(new EyerField("field_pic_flag", field_pic_flag, "", 1));

        mb_aff_frame_flag = (sps.mb_adaptive_frame_field_flag && (field_pic_flag==0));

        if (idr_flag) {
            idr_pic_id = EyerAVC_VLC::read_ue_v("SH: idr_pic_id", &bitStream, &usedBits);
            fieldList.push_back(new EyerField("idr_pic_id", idr_pic_id, "", 1));
        }



        //////////////// pic_order_cnt_type /////////////////////
        if (sps.pic_order_cnt_type == 0) {
            pic_order_cnt_lsb = EyerAVC_VLC::read_u_v(sps.log2_max_pic_order_cnt_lsb_minus4 + 4, "SH: pic_order_cnt_lsb", &bitStream, &usedBits);
            fieldList.push_back(new EyerField("pic_order_cnt_lsb", pic_order_cnt_lsb, "", 1));
            if(pps.bottom_field_pic_order_in_frame_present_flag == 1 && !field_pic_flag){
                delta_pic_order_cnt_bottom = EyerAVC_VLC::read_se_v("SH: delta_pic_order_cnt_bottom", &bitStream, &usedBits);
            }
            else {
                delta_pic_order_cnt_bottom = 0;
            }
        }

        if (sps.pic_order_cnt_type == 1) {
            if (!sps.delta_pic_order_always_zero_flag) {
                delta_pic_order_cnt[ 0 ] = EyerAVC_VLC::read_se_v("SH: delta_pic_order_cnt[0]", &bitStream, &usedBits);
                if(pps.bottom_field_pic_order_in_frame_present_flag  ==  1  &&  !field_pic_flag) {
                    delta_pic_order_cnt[ 1 ] = EyerAVC_VLC::read_se_v("SH: delta_pic_order_cnt[1]", &bitStream, &usedBits);
                }
                else {
                    delta_pic_order_cnt[ 1 ] = 0;  // set to zero if not in stream
                }
            }
            else {
                delta_pic_order_cnt[ 0 ] = 0;
                delta_pic_order_cnt[ 1 ] = 0;
            }
        }

        if (pps.redundant_pic_cnt_present_flag) {
            redundant_pic_cnt = EyerAVC_VLC::read_ue_v ("SH: redundant_pic_cnt", &bitStream, &usedBits);
        }

        if(slice_type == B_SLICE) {
            direct_spatial_mv_pred_flag = EyerAVC_VLC::read_u_1 ("SH: direct_spatial_mv_pred_flag", &bitStream, &usedBits);
        }

        num_ref_idx_active[LIST_0] = pps.num_ref_idx_l0_default_active_minus1 + 1;
        num_ref_idx_active[LIST_1] = pps.num_ref_idx_l1_default_active_minus1 + 1;

        if(slice_type == P_SLICE || slice_type == SP_SLICE || slice_type == B_SLICE) {
            val = EyerAVC_VLC::read_u_1 ("SH: num_ref_idx_override_flag", &bitStream, &usedBits);
            if (val) {
                num_ref_idx_active[LIST_0] = 1 + EyerAVC_VLC::read_ue_v ("SH: num_ref_idx_l0_active_minus1", &bitStream, &usedBits);
                if(slice_type == B_SLICE) {
                    num_ref_idx_active[LIST_1] = 1 + EyerAVC_VLC::read_ue_v ("SH: num_ref_idx_l1_active_minus1", &bitStream, &usedBits);
                }
            }
        }
        if (slice_type != B_SLICE) {
            num_ref_idx_active[LIST_1] = 0;
        }

        ref_pic_list_reordering(&bitStream, &usedBits);

        weighted_pred_flag = (unsigned short) ((slice_type == P_SLICE || slice_type == SP_SLICE)
                                                          ? pps.weighted_pred_flag
                                                          : (slice_type == B_SLICE && pps.weighted_bipred_idc == 1));
        weighted_bipred_idc = (unsigned short) (slice_type == B_SLICE && pps.weighted_bipred_idc > 0);

        if ((pps.weighted_pred_flag && (slice_type == P_SLICE || slice_type == SP_SLICE)) ||
            (pps.weighted_bipred_idc == 1 && (slice_type == B_SLICE))) {
            pred_weight_table(&bitStream, &usedBits);
        }

        if (nal_reference_idc) {
            dec_ref_pic_marking(&bitStream, &usedBits);
        }

        if (pps.entropy_coding_mode_flag && slice_type != I_SLICE && slice_type != SI_SLICE) {
            model_number = EyerAVC_VLC::read_ue_v("SH: cabac_init_idc", &bitStream, &usedBits);
        }
        else {
            model_number = 0;
        }

        val = EyerAVC_VLC::read_se_v("SH: slice_qp_delta", &bitStream, &usedBits);
        slice_qp_delta = val;
        qp = 26 + pps.pic_init_qp_minus26 + val;

        fieldList.push_back(new EyerField("qp", qp));
        fieldList.push_back(new EyerField("slice_qp_delta", slice_qp_delta));

        if(slice_type == SP_SLICE || slice_type == SI_SLICE) {
            if(slice_type == SP_SLICE) {
                sp_switch = EyerAVC_VLC::read_u_1 ("SH: sp_for_switch_flag", &bitStream, &usedBits);
            }
            slice_qs_delta = val = EyerAVC_VLC::read_se_v("SH: slice_qs_delta", &bitStream, &usedBits);
            qs = 26 + pps.pic_init_qs_minus26 + val;

            fieldList.push_back(new EyerField("qs", qs));
            fieldList.push_back(new EyerField("slice_qs_delta", slice_qs_delta));
        }


        if (pps.deblocking_filter_control_present_flag) {
            DFDisableIdc = (short) EyerAVC_VLC::read_ue_v ("SH: disable_deblocking_filter_idc", &bitStream, &usedBits);
            if (DFDisableIdc != 1) {
                DFAlphaC0Offset = (short) (2 * EyerAVC_VLC::read_se_v("SH: slice_alpha_c0_offset_div2", &bitStream, &usedBits));
                DFBetaOffset    = (short) (2 * EyerAVC_VLC::read_se_v("SH: slice_beta_offset_div2", &bitStream, &usedBits));
            }
            else {
                DFAlphaC0Offset = DFBetaOffset = 0;
            }
        }
        else {
            DFDisableIdc = DFAlphaC0Offset = DFBetaOffset = 0;
        }
        fieldList.push_back(new EyerField("disable_deblocking_filter_idc", DFDisableIdc, "", 1));
        fieldList.push_back(new EyerField("slice_alpha_c0_offset_div2", DFAlphaC0Offset, "", 2));
        fieldList.push_back(new EyerField("slice_beta_offset_div2", DFBetaOffset, "", 2));

        /*
        if ( is_HI_intra_only_profile(active_sps->profile_idc, active_sps->constrained_set3_flag) && (p_Inp->intra_profile_deblocking == 0) )
        {
            currSlice->DFDisableIdc =1;
            currSlice->DFAlphaC0Offset = currSlice->DFBetaOffset = 0;
        }
        */

        if (pps.num_slice_groups_minus1 > 0 && pps.slice_group_map_type >= 3 && pps.slice_group_map_type <= 5) {
            len = (sps.pic_height_in_map_units_minus1 + 1) * (sps.pic_width_in_mbs_minus1 + 1) / (pps.slice_group_change_rate_minus1 + 1);
            if (((sps.pic_height_in_map_units_minus1 + 1) * (sps.pic_width_in_mbs_minus1 + 1)) % (pps.slice_group_change_rate_minus1 + 1)) {
                len +=1;
            }

            len = CeilLog2(len + 1);

            slice_group_change_cycle = EyerAVC_VLC::read_u_v (len, "SH: slice_group_change_cycle", &bitStream, &usedBits);
        }

        /*
        p_Vid->PicHeightInMbs = p_Vid->FrameHeightInMbs / ( 1 + currSlice->field_pic_flag );
        p_Vid->PicSizeInMbs   = p_Vid->PicWidthInMbs * p_Vid->PicHeightInMbs;
        p_Vid->FrameSizeInMbs = p_Vid->PicWidthInMbs * p_Vid->FrameHeightInMbs;
        */

        EyerSliceHeader sliceHeader;
        sliceHeader.first_mb_in_slice = first_mb_in_slice;
        sliceHeader.mb_aff_frame_flag = mb_aff_frame_flag;
        sliceHeader.slice_type = slice_type;
        sliceData.Parse(sps, pps, sliceHeader, &bitStream, &usedBits);
    }

    EyerSLICEBase::~EyerSLICEBase()
    {

    }

    int EyerSLICEBase::ref_pic_list_reordering(EyerBitStream * bitStream, int * usedBits)
    {
        fieldList.push_back(new EyerField("ref_pic_list_reordering[]"));

        //TODO Free
        alloc_ref_pic_list_reordering_buffer();

        int val;
        int i;
        if (slice_type != I_SLICE && slice_type != SI_SLICE) {
            val = ref_pic_list_reordering_flag[LIST_0] = EyerAVC_VLC::read_u_1 ("SH: ref_pic_list_reordering_flag_l0", bitStream, usedBits);
            fieldList.push_back(new EyerField("ref_pic_list_reordering_flag[LIST_0]", ref_pic_list_reordering_flag[LIST_0], "", 1));

            if (val){
                i = 0;
                do {
                    val = modification_of_pic_nums_idc[LIST_0][i] = EyerAVC_VLC::read_ue_v("SH: modification_of_pic_nums_idc_l0", bitStream, usedBits);
                    if (val==0 || val==1) {
                        abs_diff_pic_num_minus1[LIST_0][i] = EyerAVC_VLC::read_ue_v("SH: abs_diff_pic_num_minus1_l0", bitStream, usedBits);
                    }
                    else {
                        if (val==2) {
                            long_term_pic_idx[LIST_0][i] = EyerAVC_VLC::read_ue_v("SH: long_term_pic_idx_l0", bitStream, usedBits);
                        }
                    }
                    i++;
                } while(val != 3);
            }
        }

        if (slice_type == B_SLICE) {
            val = ref_pic_list_reordering_flag[LIST_1] = EyerAVC_VLC::read_u_1 ("SH: ref_pic_list_reordering_flag_l1", bitStream, usedBits);
            fieldList.push_back(new EyerField("ref_pic_list_reordering_flag[LIST_1]", ref_pic_list_reordering_flag[LIST_1], "", 1));
            if (val) {
                i = 0;
                do {
                    val = modification_of_pic_nums_idc[LIST_1][i] = EyerAVC_VLC::read_ue_v("SH: modification_of_pic_nums_idc_l1", bitStream, usedBits);
                    if (val==0 || val==1) {
                        abs_diff_pic_num_minus1[LIST_1][i] = EyerAVC_VLC::read_ue_v("SH: abs_diff_pic_num_minus1_l1", bitStream, usedBits);
                    }
                    else {
                        if (val == 2) {
                            long_term_pic_idx[LIST_1][i] = EyerAVC_VLC::read_ue_v("SH: long_term_pic_idx_l1", bitStream, usedBits);
                        }
                    }
                    i++;
                } while (val != 3);
            }
        }

        if(redundant_pic_cnt && (slice_type != I_SLICE) ) {
            redundant_slice_ref_idx = abs_diff_pic_num_minus1[LIST_0][0] + 1;
            fieldList.push_back(new EyerField("redundant_slice_ref_idx", redundant_slice_ref_idx, "", 1));
        }

        return 0;
    }

    int EyerSLICEBase::alloc_ref_pic_list_reordering_buffer()
    {
        if (slice_type != I_SLICE && slice_type != SI_SLICE) {
            int size = num_ref_idx_active[LIST_0] + 1;
            modification_of_pic_nums_idc[LIST_0] = (int *)calloc(size ,sizeof(int));
            abs_diff_pic_num_minus1[LIST_0] = (int *)calloc(size,sizeof(int));
            long_term_pic_idx[LIST_0] = (int *)calloc(size,sizeof(int));
        }
        else {
            modification_of_pic_nums_idc[LIST_0] = NULL;
            abs_diff_pic_num_minus1[LIST_0] = NULL;
            long_term_pic_idx[LIST_0] = NULL;
        }

        if (slice_type == B_SLICE) {
            int size = num_ref_idx_active[LIST_1] + 1;
            modification_of_pic_nums_idc[LIST_1] = (int *)calloc(size,sizeof(int));
            abs_diff_pic_num_minus1[LIST_1] = (int *)calloc(size,sizeof(int));
            long_term_pic_idx[LIST_1] = (int *)calloc(size,sizeof(int));
        }
        else {
            modification_of_pic_nums_idc[LIST_1] = NULL;
            abs_diff_pic_num_minus1[LIST_1] = NULL;
            long_term_pic_idx[LIST_1] = NULL;
        }
        return 0;
    }


    int EyerSLICEBase::dec_ref_pic_marking(EyerBitStream * bitStream, int * usedBits)
    {
        fieldList.push_back(new EyerField("dec_ref_pic_marking[]"));

        int val;

        if (idr_flag) {
            no_output_of_prior_pics_flag = EyerAVC_VLC::read_u_1("SH: no_output_of_prior_pics_flag", bitStream, usedBits);
            long_term_reference_flag = EyerAVC_VLC::read_u_1("SH: long_term_reference_flag", bitStream, usedBits);

            fieldList.push_back(new EyerField("no_output_of_prior_pics_flag", no_output_of_prior_pics_flag, "", 1));
            fieldList.push_back(new EyerField("long_term_reference_flag", long_term_reference_flag, "", 1));
        }
        else{
            adaptive_ref_pic_buffering_flag = EyerAVC_VLC::read_u_1("SH: adaptive_ref_pic_buffering_flag", bitStream, usedBits);
            fieldList.push_back(new EyerField("adaptive_ref_pic_buffering_flag", adaptive_ref_pic_buffering_flag, "", 1));
            if (adaptive_ref_pic_buffering_flag) {
                do {
                    int memory_management_control_operation;
                    val = memory_management_control_operation = EyerAVC_VLC::read_ue_v("SH: memory_management_control_operation", bitStream, usedBits);

                    if ((val == 1)||(val == 3)) {
                        int difference_of_pic_nums_minus1 = EyerAVC_VLC::read_ue_v("SH: difference_of_pic_nums_minus1", bitStream, usedBits);
                    }
                    if (val == 2) {
                        int long_term_pic_num = EyerAVC_VLC::read_ue_v("SH: long_term_pic_num", bitStream, usedBits);
                    }

                    if ((val == 3)||(val == 6)) {
                        int long_term_frame_idx = EyerAVC_VLC::read_ue_v("SH: long_term_frame_idx", bitStream, usedBits);
                    }
                    if (val == 4) {
                        int max_long_term_frame_idx_plus1 = EyerAVC_VLC::read_ue_v("SH: max_long_term_pic_idx_plus1", bitStream, usedBits);
                    }
                }
                while (val != 0);
            }
        }

        return 0;
    }

    int EyerSLICEBase::pred_weight_table(EyerBitStream * bitStream, int * usedBits)
    {
        int i = 0;

        luma_log2_weight_denom = (unsigned short) EyerAVC_VLC::read_ue_v ("SH: luma_log2_weight_denom", bitStream, usedBits);
        wp_round_luma = luma_log2_weight_denom ? 1<<(luma_log2_weight_denom - 1): 0;

        if ( 0 != sps.chroma_format_idc) {
            chroma_log2_weight_denom = (unsigned short) EyerAVC_VLC::read_ue_v ("SH: chroma_log2_weight_denom", bitStream, usedBits);
            wp_round_chroma = chroma_log2_weight_denom ? 1<<(chroma_log2_weight_denom - 1): 0;
        }

        for (i=0; i < num_ref_idx_active[LIST_0]; i++) {
            luma_weight_flag_l0 = EyerAVC_VLC::read_u_1("SH: luma_weight_flag_l0", bitStream, usedBits);
            int a;
            if (luma_weight_flag_l0) {
                a = EyerAVC_VLC::read_se_v ("SH: luma_weight_l0", bitStream, usedBits);
                a = EyerAVC_VLC::read_se_v ("SH: luma_offset_l0", bitStream, usedBits);
            }
            else {
                a = 1 << luma_log2_weight_denom;
                a = 0;
            }

            if (sps.chroma_format_idc != 0) {
                chroma_weight_flag_l0 = EyerAVC_VLC::read_u_1 ("SH: chroma_weight_flag_l0", bitStream, usedBits);
                for (int j=1; j<3; j++) {
                    int a;
                    if (chroma_weight_flag_l0){
                        a = EyerAVC_VLC::read_se_v("SH: chroma_weight_l0", bitStream, usedBits);
                        a = EyerAVC_VLC::read_se_v("SH: chroma_offset_l0", bitStream, usedBits);
                    }
                    else {
                        a = 1 << chroma_log2_weight_denom;
                        a = 0;
                    }
                }
            }
        }

        if ((slice_type == B_SLICE) && pps.weighted_bipred_idc == 1) {
            for (i=0;i<num_ref_idx_active[LIST_1];i++) {
                luma_weight_flag_l1 = EyerAVC_VLC::read_u_1("SH: luma_weight_flag_l1", bitStream, usedBits);

                int a;
                if (luma_weight_flag_l1) {
                    a = EyerAVC_VLC::read_se_v ("SH: luma_weight_l1", bitStream, usedBits);
                    a = EyerAVC_VLC::read_se_v ("SH: luma_offset_l1", bitStream, usedBits);
                }
                else {
                    a = 1<<luma_log2_weight_denom;
                    a = 0;
                }

                if (sps.chroma_format_idc != 0) {
                    chroma_weight_flag_l1 = EyerAVC_VLC::read_u_1 ("SH: chroma_weight_flag_l1", bitStream, usedBits);

                    for (int j=1; j<3; j++) {
                        if (chroma_weight_flag_l1) {
                            a = EyerAVC_VLC::read_se_v("SH: chroma_weight_l1", bitStream, usedBits);
                            a = EyerAVC_VLC::read_se_v("SH: chroma_offset_l1", bitStream, usedBits);
                        }
                        else
                        {
                            a = 1<<chroma_log2_weight_denom;
                            a = 0;
                        }
                    }
                }
            }
        }

        return 0;
    }
}