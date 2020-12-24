#include "EyerSPS.hpp"

#include "EyerBitStream.hpp"

namespace Eyer
{
    EyerSPS::EyerSPS()
    {

    }

    EyerSPS::~EyerSPS()
    {

    }

    int EyerSPS::Parse()
    {
        EyerNALU::Parse();

        EyerBitStream bs(naluData.GetRBSPBuffer());

        profile_idc = bs.bs_read_u8();
        constraint_set0_flag = bs.bs_read_u1();
        constraint_set1_flag = bs.bs_read_u1();
        constraint_set2_flag = bs.bs_read_u1();
        constraint_set3_flag = bs.bs_read_u1();
        constraint_set4_flag = bs.bs_read_u1();
        constraint_set5_flag = bs.bs_read_u1();
        bs.bs_skip_u(2);
        level_idc = bs.bs_read_u8();
        seq_parameter_set_id = bs.bs_read_ue();

        rootSyntax.PutValid("profile_idc",                      profile_idc);
        rootSyntax.PutValid("constraint_set0_flag",             constraint_set0_flag);
        rootSyntax.PutValid("constraint_set1_flag",             constraint_set1_flag);
        rootSyntax.PutValid("constraint_set2_flag",             constraint_set2_flag);
        rootSyntax.PutValid("constraint_set3_flag",             constraint_set3_flag);
        rootSyntax.PutValid("constraint_set4_flag",             constraint_set4_flag);
        rootSyntax.PutValid("constraint_set5_flag",             constraint_set5_flag);
        rootSyntax.PutValid("reserved_zero_2bits",          0);
        rootSyntax.PutValid("level_idc",                        level_idc);
        rootSyntax.PutValid("seq_parameter_set_id",             seq_parameter_set_id);

        bool isHigh = (profile_idc == 100      || profile_idc == 110       ||
                  profile_idc == 122      || profile_idc == 244       || profile_idc == 44     ||
                  profile_idc == 83       || profile_idc == 86        || profile_idc == 118    ||
                  profile_idc == 128      || profile_idc == 138       || profile_idc == 139    ||
                  profile_idc == 134      || profile_idc == 135);
        if(isHigh)
        {
            chroma_format_idc = bs.bs_read_ue();

            if(chroma_format_idc == 3) {
                separate_colour_plance_flag = bs.bs_read_u1();
            }
            bit_depth_luma_minus8                   = bs.bs_read_ue();
            bit_depth_chroma_minus8                 = bs.bs_read_ue();
            qpprime_y_zero_transform_bypass_flag    = bs.bs_read_u1();
            seq_scaling_matrix_present_flag         = bs.bs_read_u1();

            if(seq_scaling_matrix_present_flag) {
                for(int i=0; i<((chroma_format_idc != 3) ? 8 : 12); i++ ){
                    seq_scaling_list_present_flag[i] = bs.bs_read_u1();
                    if(seq_scaling_list_present_flag[i]){
                        if(i<6) {
                            ReadScalingList(bs, ScalingList4x4[i], 16, &(UseDefaultScalingMatrix4x4Flag[i]));
                        }
                        else {
                            ReadScalingList(bs, ScalingList8x8[i-6], 64, &(UseDefaultScalingMatrix8x8Flag[i-6]));
                        }
                    }
                }
            }
        }

        EyerString if_profile_idc_str = "if( profile_idc == 100 || profile_idc == 110 ||\n"
                                        "    profile_idc == 122 || profile_idc == 244 || profile_idc == 44  ||\n"
                                        "    profile_idc == 83  || profile_idc == 86  || profile_idc == 118 ||\n"
                                        "    profile_idc == 128 || profile_idc == 138 || profile_idc == 139 ||\n"
                                        "    profile_idc == 134 || profile_idc == 135\n"
                                        ")";
        EyerSyntax if_profile_idcSyntax(if_profile_idc_str, rootSyntax.GetLevel() + 1);
        {
            if_profile_idcSyntax.Put(isHigh, "chroma_format_idc", chroma_format_idc);
            bool is_chroma_format_idc_equals_3 = (chroma_format_idc == 3);

            EyerSyntax if_chroma_format_idc_Syntax("if(chroma_format_idc == 3)", if_profile_idcSyntax.GetLevel() + 1);
            {
                if_chroma_format_idc_Syntax.Put(isHigh && is_chroma_format_idc_equals_3, "separate_colour_plance_flag", separate_colour_plance_flag);
            }
            if_profile_idcSyntax.Put(if_chroma_format_idc_Syntax);

            if_profile_idcSyntax.Put(isHigh, "bit_depth_luma_minus8",                   bit_depth_luma_minus8);
            if_profile_idcSyntax.Put(isHigh, "bit_depth_chroma_minus8",                 bit_depth_chroma_minus8);
            if_profile_idcSyntax.Put(isHigh, "qpprime_y_zero_transform_bypass_flag",    qpprime_y_zero_transform_bypass_flag);
            if_profile_idcSyntax.Put(isHigh, "seq_scaling_matrix_present_flag",         seq_scaling_matrix_present_flag);
        }

        rootSyntax.Put(if_profile_idcSyntax);




        if (separate_colour_plance_flag == 0){
            ChromaArrayType = chroma_format_idc;
        }
        else{
            ChromaArrayType = 0;
        }

        if (chroma_format_idc == 1) {
            SubWidthC = 2;
            SubHeightC = 2;
        }
        if (chroma_format_idc == 2) {
            SubWidthC = 2;
            SubHeightC = 1;
        }
        if (chroma_format_idc == 3) {
            SubWidthC = 1;
            SubHeightC = 1;
        }

        log2_max_frame_num_minus4               = bs.bs_read_ue();
        pic_order_cnt_type                      = bs.bs_read_ue();

        if(pic_order_cnt_type == 0) {
            log2_max_pic_order_cnt_lsb_minus4 = bs.bs_read_ue();
        }
        else if(pic_order_cnt_type == 1){
            delta_pic_order_always_zero_flag                = bs.bs_read_u1();
            offset_for_non_ref_pic                          = bs.bs_read_se();
            offset_for_top_to_bottom_field                  = bs.bs_read_se();
            num_ref_frames_in_pic_order_cnt_cycle           = bs.bs_read_ue();

            for(int i=0; i<num_ref_frames_in_pic_order_cnt_cycle; i++) {
                offset_for_ref_frame[i] = bs.bs_read_se();
            }
        }

        num_ref_frames                              = bs.bs_read_ue();
        gaps_in_frame_num_value_allowed_flag        = bs.bs_read_u1();
        pic_width_in_mbs_minus1                     = bs.bs_read_ue();
        pic_height_in_map_units_minus1              = bs.bs_read_ue();
        frame_mbs_only_flag                         = bs.bs_read_u1();

        if(!frame_mbs_only_flag) {
            mb_adaptive_frame_field_flag = bs.bs_read_u1();
        }

        direct_8x8_inference_flag       = bs.bs_read_u1();
        frame_cropping_flag             = bs.bs_read_u1();

        if(frame_cropping_flag) {
            frame_crop_left_offset          = bs.bs_read_ue();
            frame_crop_right_offset         = bs.bs_read_ue();
            frame_crop_top_offset           = bs.bs_read_ue();
            frame_crop_bottom_offset        = bs.bs_read_ue();
        }

        vui_parameters_present_flag         = bs.bs_read_u1();

        if(vui_parameters_present_flag){
            ReadVuiParameters(bs);
        }

        valid = true;

        return 0;
    }

    int EyerSPS::ReadScalingList(EyerBitStream & bs, int * scalingList, int sizeOfScalingList, int * useDefaultScalingMatrixFlag)
    {
        int lastScale = 8;
        int nextScale = 8;
        int delta_scale;
        for( int j = 0; j < sizeOfScalingList; j++ ) {
            if( nextScale != 0 ) {
                if(0) {
                    nextScale = scalingList[ j ];
                    if (useDefaultScalingMatrixFlag[0]) { nextScale = 0; }
                    delta_scale = (nextScale - lastScale) % 256 ;
                }

                delta_scale = bs.bs_read_se();

                if(1) {
                    nextScale = ( lastScale + delta_scale + 256 ) % 256;
                    useDefaultScalingMatrixFlag[0] = ( j == 0 && nextScale == 0 );
                }
            }
            if(1) {
                scalingList[j] = ( nextScale == 0 ) ? lastScale : nextScale;
            }
            lastScale = scalingList[j];
        }
        return 0;
    }

    int EyerSPS::ReadVuiParameters(EyerBitStream & bs)
    {
        int vuilevel = 1;

        int SAR_Extended = 255;
        vui.aspect_ratio_info_present_flag = bs.bs_read_u1();
        if(vui.aspect_ratio_info_present_flag ) {
            vui.aspect_ratio_idc = bs.bs_read_u8();
            if(vui.aspect_ratio_idc == SAR_Extended){
                vui.sar_width      = bs.bs_read_u(16);
                vui.sar_height     = bs.bs_read_u(16);
            }
        }

        vui.overscan_info_present_flag = bs.bs_read_u1();
        if(vui.overscan_info_present_flag) {
            vui.overscan_appropriate_flag = bs.bs_read_u1();
        }

        vui.video_signal_type_present_flag = bs.bs_read_u1();
        if(vui.video_signal_type_present_flag) {
            vui.video_format                            = bs.bs_read_u(3);
            vui.video_full_range_flag                   = bs.bs_read_u1();
            vui.colour_description_present_flag         = bs.bs_read_u1();
            if(vui.colour_description_present_flag) {
                vui.colour_primaries                    = bs.bs_read_u8();
                vui.transfer_characteristics            = bs.bs_read_u8();
                vui.matrix_coefficients                 = bs.bs_read_u8();
            }
        }

        vui.chroma_loc_info_present_flag                = bs.bs_read_u1();
        if(vui.chroma_loc_info_present_flag) {
            vui.chroma_sample_loc_type_top_field        = bs.bs_read_ue();
            vui.chroma_sample_loc_type_bottom_field     = bs.bs_read_ue();
        }

        vui.timing_info_present_flag = bs.bs_read_u1();
        if(vui.timing_info_present_flag) {
            vui.num_units_in_tick                       = bs.bs_read_u(32);
            vui.time_scale                              = bs.bs_read_u(32);
            vui.fixed_frame_rate_flag                   = bs.bs_read_u1();
        }

        vui.nal_hrd_parameters_present_flag = bs.bs_read_u1();
        if(vui.nal_hrd_parameters_present_flag) {
            ReadHrdParameters(vui.hrd_nal, bs);
        }

        vui.vcl_hrd_parameters_present_flag = bs.bs_read_u1();
        if(vui.vcl_hrd_parameters_present_flag) {
            ReadHrdParameters(vui.hrd_vcl, bs);
        }

        if(vui.nal_hrd_parameters_present_flag || vui.vcl_hrd_parameters_present_flag) {
            vui.low_delay_hrd_flag = bs.bs_read_u1();
        }

        vui.pic_struct_present_flag         = bs.bs_read_u1();
        vui.bitstream_restriction_flag      = bs.bs_read_u1();

        if(vui.bitstream_restriction_flag) {
            vui.motion_vectors_over_pic_boundaries_flag     = bs.bs_read_u1();
            vui.max_bytes_per_pic_denom                     = bs.bs_read_ue();
            vui.max_bits_per_mb_denom                       = bs.bs_read_ue();
            vui.log2_max_mv_length_horizontal               = bs.bs_read_ue();
            vui.log2_max_mv_length_vertical                 = bs.bs_read_ue();
            vui.num_reorder_frames                          = bs.bs_read_ue();
            vui.max_dec_frame_buffering                     = bs.bs_read_ue();
        }

        return 0;
    }

    int EyerSPS::ReadHrdParameters(EyerHRD & hrd, EyerBitStream & bs)
    {
        int vuilevel = 2;

        hrd.cpb_cnt_minus1 = bs.bs_read_ue();
        hrd.bit_rate_scale = bs.bs_read_u(4);
        hrd.cpb_size_scale = bs.bs_read_u(4);

        for(int SchedSelIdx = 0; SchedSelIdx <= hrd.cpb_cnt_minus1; SchedSelIdx++) {
            hrd.bit_rate_value_minus1[SchedSelIdx]        = bs.bs_read_ue();
            hrd.cpb_size_value_minus1[SchedSelIdx]        = bs.bs_read_ue();
            hrd.cbr_flag[SchedSelIdx]                     = bs.bs_read_u1();
        }
        hrd.initial_cpb_removal_delay_length_minus1     = bs.bs_read_u(5);
        hrd.cpb_removal_delay_length_minus1             = bs.bs_read_u(5);
        hrd.dpb_output_delay_length_minus1              = bs.bs_read_u(5);
        hrd.time_offset_length                          = bs.bs_read_u(5);

        return 0;
    }
}