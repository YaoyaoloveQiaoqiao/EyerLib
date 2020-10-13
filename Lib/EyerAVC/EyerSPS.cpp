#include "EyerSPS.hpp"
#include "EyerBitStream.hpp"
#include "EyerAVC_VLC.hpp"
#include "EyerCore/EyerLog.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

namespace Eyer
{
    NaluType EyerSPS::GetNalType()
    {
        return NaluType::NALU_TYPE_SPS;
    }

    EyerSPS::EyerSPS() : EyerNAL()
    {
        valid = Boolean::FALSE;
    }

    EyerSPS::EyerSPS(EyerNALU & _nalu) : EyerNAL()
    {
        nalu = _nalu;

        nalu.ToSODB();

        EyerBitStream bitStream(nalu.buf + 1, nalu.len - 1);
        bitStream.code_len = nalu.len - 1;
        bitStream.bitstream_length = nalu.len - 1;
        bitStream.ei_flag = 0;
        bitStream.read_len = 0;
        bitStream.frame_bitoffset = 0;

        int usedBits = 0;

        profile_idc = EyerAVC_VLC::read_u_v(8, "SPS: profile_idc", &bitStream, &usedBits);
        fieldList.push_back(new EyerField("profile_idc", profile_idc));

        if ((profile_idc != BASELINE       ) &&
            (profile_idc != MAIN           ) &&
            (profile_idc != EXTENDED       ) &&
            (profile_idc != FREXT_HP       ) &&
            (profile_idc != FREXT_Hi10P    ) &&
            (profile_idc != FREXT_Hi422    ) &&
            (profile_idc != FREXT_Hi444    ) &&
            (profile_idc != FREXT_CAVLC444 ))
        {
            EyerLog("Invalid Profile IDC (%d) encountered. \n", profile_idc);
            return;
        }

        int reserved_zero;

        constrained_set0_flag                  = EyerAVC_VLC::read_u_1  (   "SPS: constrained_set0_flag"                 , &bitStream, &usedBits);
        constrained_set1_flag                  = EyerAVC_VLC::read_u_1  (   "SPS: constrained_set1_flag"                 , &bitStream, &usedBits);
        constrained_set2_flag                  = EyerAVC_VLC::read_u_1  (   "SPS: constrained_set2_flag"                 , &bitStream, &usedBits);
        constrained_set3_flag                  = EyerAVC_VLC::read_u_1  (   "SPS: constrained_set3_flag"                 , &bitStream, &usedBits);
        constrained_set4_flag                  = EyerAVC_VLC::read_u_1  (   "SPS: constrained_set4_flag"                 , &bitStream, &usedBits);
        constrained_set5_flag                  = EyerAVC_VLC::read_u_1  (   "SPS: constrained_set5_flag"                 , &bitStream, &usedBits);

        fieldList.push_back(new EyerField("constrained_set0_flag", constrained_set0_flag));
        fieldList.push_back(new EyerField("constrained_set1_flag", constrained_set1_flag));
        fieldList.push_back(new EyerField("constrained_set2_flag", constrained_set2_flag));
        fieldList.push_back(new EyerField("constrained_set3_flag", constrained_set3_flag));
        fieldList.push_back(new EyerField("constrained_set4_flag", constrained_set4_flag));
        fieldList.push_back(new EyerField("constrained_set5_flag", constrained_set5_flag));

        reserved_zero                          = EyerAVC_VLC::read_u_v  (2, "SPS: reserved_zero_2bits"          , &bitStream, &usedBits);
        fieldList.push_back(new EyerField("reserved_zero_2bits", reserved_zero));

        level_idc                              = EyerAVC_VLC::read_u_v  (8, "SPS: level_idc"                    , &bitStream, &usedBits);
        fieldList.push_back(new EyerField("level_idc", level_idc));

        seq_parameter_set_id                   = EyerAVC_VLC::read_ue_v ("SPS: seq_parameter_set_id"                     , &bitStream, &usedBits);
        fieldList.push_back(new EyerField("seq_parameter_set_id", seq_parameter_set_id));


        // Fidelity Range Extensions stuff
        chroma_format_idc = 1;

        if((profile_idc == FREXT_HP   ) ||
           (profile_idc == FREXT_Hi10P) ||
           (profile_idc == FREXT_Hi422) ||
           (profile_idc == FREXT_Hi444) ||
           (profile_idc == FREXT_CAVLC444))
        {
            chroma_format_idc                       = EyerAVC_VLC::read_ue_v ("SPS: chroma_format_idc"                       , &bitStream, &usedBits);
            fieldList.push_back(new EyerField("chroma_format_idc", chroma_format_idc, nullptr, 1));

            if(chroma_format_idc == YUV444){
                separate_colour_plane_flag          = EyerAVC_VLC::read_u_1  ("SPS: separate_colour_plane_flag"              , &bitStream, &usedBits);
                fieldList.push_back(new EyerField("separate_colour_plane_flag", separate_colour_plane_flag, nullptr, 2));
            }

            bit_depth_luma_minus8                   = EyerAVC_VLC::read_ue_v ("SPS: bit_depth_luma_minus8"                   , &bitStream, &usedBits);
            bit_depth_chroma_minus8                 = EyerAVC_VLC::read_ue_v ("SPS: bit_depth_chroma_minus8"                 , &bitStream, &usedBits);
            lossless_qpprime_flag                   = EyerAVC_VLC::read_u_1  ("SPS: lossless_qpprime_y_zero_flag"            , &bitStream, &usedBits);
            seq_scaling_matrix_present_flag         = EyerAVC_VLC::read_u_1  ("SPS: seq_scaling_matrix_present_flag"         , &bitStream, &usedBits);

            fieldList.push_back(new EyerField("bit_depth_luma_minus8", bit_depth_luma_minus8, nullptr, 1));
            fieldList.push_back(new EyerField("bit_depth_chroma_minus8", bit_depth_chroma_minus8, nullptr, 1));
            fieldList.push_back(new EyerField("lossless_qpprime_flag", lossless_qpprime_flag, nullptr, 1));
            fieldList.push_back(new EyerField("seq_scaling_matrix_present_flag", seq_scaling_matrix_present_flag, nullptr, 1));

            if(seq_scaling_matrix_present_flag) {
                int scalingList = (chroma_format_idc != YUV444) ? 8 : 12;
                // EyerLog("scalingList: %d\n", scalingList);
                for(int i=0;i<scalingList;i++){
                    seq_scaling_list_present_flag[i]= EyerAVC_VLC::read_u_1  ("SPS: seq_scaling_list_present_flag"        , &bitStream, &usedBits);
                    if(seq_scaling_list_present_flag[i]){
                        if(i < 6){
                            ScalingList(ScalingList4x4[i], 16, &UseDefaultScalingMatrix4x4Flag[i], &bitStream, &usedBits);
                        }
                        else{
                            ScalingList(ScalingList8x8[i - 6], 64, &UseDefaultScalingMatrix8x8Flag[i - 6], &bitStream, &usedBits);
                        }
                    }
                }
            }
        }

        log2_max_frame_num_minus4                   = EyerAVC_VLC::read_ue_v ("SPS: log2_max_frame_num_minus4"                          , &bitStream, &usedBits);
        pic_order_cnt_type                          = EyerAVC_VLC::read_ue_v ("SPS: pic_order_cnt_type"                                 , &bitStream, &usedBits);

        fieldList.push_back(new EyerField("log2_max_frame_num_minus4", log2_max_frame_num_minus4));
        fieldList.push_back(new EyerField("pic_order_cnt_type", pic_order_cnt_type));

        if(pic_order_cnt_type == 0){
            log2_max_pic_order_cnt_lsb_minus4       = EyerAVC_VLC::read_ue_v ("SPS: log2_max_pic_order_cnt_lsb_minus4"                  , &bitStream, &usedBits);
            fieldList.push_back(new EyerField("log2_max_pic_order_cnt_lsb_minus4", log2_max_pic_order_cnt_lsb_minus4, nullptr, 1));
        }
        else if(pic_order_cnt_type == 1){
            delta_pic_order_always_zero_flag        = EyerAVC_VLC::read_u_1  ("SPS: delta_pic_order_always_zero_flag"                   , &bitStream, &usedBits);
            offset_for_non_ref_pic                  = EyerAVC_VLC::read_se_v ("SPS: offset_for_non_ref_pic"                             , &bitStream, &usedBits);
            offset_for_top_to_bottom_field          = EyerAVC_VLC::read_se_v ("SPS: offset_for_top_to_bottom_field"                     , &bitStream, &usedBits);
            num_ref_frames_in_pic_order_cnt_cycle   = EyerAVC_VLC::read_ue_v ("SPS: num_ref_frames_in_pic_order_cnt_cycle"              , &bitStream, &usedBits);

            fieldList.push_back(new EyerField("delta_pic_order_always_zero_flag", delta_pic_order_always_zero_flag, nullptr, 1));
            fieldList.push_back(new EyerField("offset_for_non_ref_pic", offset_for_non_ref_pic, nullptr, 1));
            fieldList.push_back(new EyerField("offset_for_top_to_bottom_field", offset_for_top_to_bottom_field, nullptr, 1));
            fieldList.push_back(new EyerField("num_ref_frames_in_pic_order_cnt_cycle", num_ref_frames_in_pic_order_cnt_cycle, nullptr, 1));

            for(int i=0;i<num_ref_frames_in_pic_order_cnt_cycle;i++){
                offset_for_ref_frame[i]             = EyerAVC_VLC::read_se_v ("SPS: offset_for_ref_frame[i]"                            , &bitStream, &usedBits);
            }
        }

        num_ref_frames                              = EyerAVC_VLC::read_ue_v ("SPS: num_ref_frames"                                     , &bitStream, &usedBits);
        gaps_in_frame_num_value_allowed_flag        = EyerAVC_VLC::read_u_1  ("SPS: gaps_in_frame_num_value_allowed_flag"               , &bitStream, &usedBits);

        fieldList.push_back(new EyerField("num_ref_frames", num_ref_frames));
        fieldList.push_back(new EyerField("gaps_in_frame_num_value_allowed_flag", gaps_in_frame_num_value_allowed_flag));





        /////////////////////////////////////////////
        pic_width_in_mbs_minus1                     = EyerAVC_VLC::read_ue_v ("SPS: pic_width_in_mbs_minus1"                                    , &bitStream, &usedBits);
        pic_height_in_map_units_minus1              = EyerAVC_VLC::read_ue_v ("SPS: pic_height_in_map_units_minus1"                             , &bitStream, &usedBits);

        frame_mbs_only_flag                         = EyerAVC_VLC::read_u_1  ("SPS: frame_mbs_only_flag"                                        , &bitStream, &usedBits);

        if(!frame_mbs_only_flag){
            mb_adaptive_frame_field_flag            = EyerAVC_VLC::read_u_1  ("SPS: mb_adaptive_frame_field_flag"                               , &bitStream, &usedBits);
        }

        direct_8x8_inference_flag                   = EyerAVC_VLC::read_u_1  ("SPS: direct_8x8_inference_flag"                                  , &bitStream, &usedBits);
        frame_cropping_flag                         = EyerAVC_VLC::read_u_1  ("SPS: frame_cropping_flag"                                        , &bitStream, &usedBits);

        if (frame_cropping_flag){
            frame_crop_left_offset                  = EyerAVC_VLC::read_ue_v ("SPS: frame_crop_left_offset"                                     , &bitStream, &usedBits);
            frame_crop_right_offset                 = EyerAVC_VLC::read_ue_v ("SPS: frame_crop_right_offset"                                    , &bitStream, &usedBits);
            frame_crop_top_offset                   = EyerAVC_VLC::read_ue_v ("SPS: frame_crop_top_offset"                                      , &bitStream, &usedBits);
            frame_crop_bottom_offset                = EyerAVC_VLC::read_ue_v ("SPS: frame_crop_bottom_offset"                                   , &bitStream, &usedBits);
        }

        EyerVec2 wh;
        GetWH(wh);

        fieldList.push_back(new EyerField("pic_width_in_mbs_minus1", pic_width_in_mbs_minus1, EyerString::Number((int)wh.x()), 0));
        fieldList.push_back(new EyerField("pic_height_in_map_units_minus1", pic_height_in_map_units_minus1, EyerString::Number((int)wh.y()), 0));
        fieldList.push_back(new EyerField("frame_mbs_only_flag", frame_mbs_only_flag));
        if(frame_mbs_only_flag){
            fieldList.push_back(new EyerField("mb_adaptive_frame_field_flag", mb_adaptive_frame_field_flag, nullptr, 1));
        }

        fieldList.push_back(new EyerField("direct_8x8_inference_flag", direct_8x8_inference_flag));
        fieldList.push_back(new EyerField("frame_cropping_flag", frame_cropping_flag));
        if (frame_cropping_flag){
            fieldList.push_back(new EyerField("frame_crop_left_offset", frame_crop_left_offset, nullptr, 1));
            fieldList.push_back(new EyerField("frame_crop_right_offset", frame_crop_right_offset, nullptr, 1));
            fieldList.push_back(new EyerField("frame_crop_top_offset", frame_crop_top_offset, nullptr, 1));
            fieldList.push_back(new EyerField("frame_crop_bottom_offset", frame_crop_bottom_offset, nullptr, 1));
        }

        /////////////////////////////////////////////






        vui_parameters_present_flag                 = EyerAVC_VLC::read_u_1  ("SPS: vui_parameters_present_flag"                            , &bitStream, &usedBits);
        fieldList.push_back(new EyerField("vui_parameters_present_flag", vui_parameters_present_flag));

        if(vui_parameters_present_flag){
            LoadVUI(&bitStream, &usedBits);
        }

        valid = Boolean::TRUE;
    }

    EyerSPS::~EyerSPS()
    {
    }

    int EyerSPS::GetWH(EyerVec2 & wh)
    {
        int width = (pic_width_in_mbs_minus1 + 1) * 16;
        int height = (2 - frame_mbs_only_flag) * (pic_height_in_map_units_minus1 + 1) * 16;

        int crop_unit_x = 1;
        int crop_unit_y = 2 - frame_mbs_only_flag;//monochrome or 4:4:4
        if (chroma_format_idc == 1) {//4:2:0
            crop_unit_x = 2;
            crop_unit_y = 2 * (2 - frame_mbs_only_flag);
        }
        else if (chroma_format_idc == 2) {//4:2:2
            crop_unit_x = 2;
            crop_unit_y = 2 - frame_mbs_only_flag;
        }

        width -= crop_unit_x * (frame_crop_left_offset + frame_crop_right_offset);
        height -= crop_unit_y * (frame_crop_top_offset + frame_crop_bottom_offset);

        wh.SetX(width);
        wh.SetY(height);

        return 0;
    }

    int EyerSPS::LoadVUI(EyerBitStream * bitstream, int * used_bits)
    {
        fieldList.push_back(new EyerField("vui_parameters[]"));

        vui.matrix_coefficients = 2;

        vui.aspect_ratio_info_present_flag      = EyerAVC_VLC::read_u_1  ("VUI: aspect_ratio_info_present_flag", bitstream, used_bits);
        fieldList.push_back(new EyerField("aspect_ratio_info_present_flag", vui.aspect_ratio_info_present_flag, nullptr, 1));

        if(vui.aspect_ratio_info_present_flag){
            vui.aspect_ratio_idc                = EyerAVC_VLC::read_u_v  ( 8, "VUI: aspect_ratio_idc"              , bitstream, used_bits);
            fieldList.push_back(new EyerField("aspect_ratio_idc", vui.aspect_ratio_idc, nullptr, 2));

            if (255 == vui.aspect_ratio_idc){
                vui.sar_width                   = (unsigned short) EyerAVC_VLC::read_u_v  (16, "VUI: sar_width"                     , bitstream, used_bits);
                vui.sar_height                  = (unsigned short) EyerAVC_VLC::read_u_v  (16, "VUI: sar_height"                    , bitstream, used_bits);
            }
        }

        vui.overscan_info_present_flag          = EyerAVC_VLC::read_u_1  ("VUI: overscan_info_present_flag"        , bitstream, used_bits);
        fieldList.push_back(new EyerField("overscan_info_present_flag", vui.overscan_info_present_flag, nullptr, 1));
        if (vui.overscan_info_present_flag) {
            vui.overscan_appropriate_flag       = EyerAVC_VLC::read_u_1  ("VUI: overscan_appropriate_flag"         , bitstream, used_bits);
            fieldList.push_back(new EyerField("overscan_appropriate_flag", vui.overscan_appropriate_flag, nullptr, 2));
        }

        vui.video_signal_type_present_flag      = EyerAVC_VLC::read_u_1  ("VUI: video_signal_type_present_flag"    , bitstream, used_bits);
        fieldList.push_back(new EyerField("video_signal_type_present_flag", vui.video_signal_type_present_flag, nullptr, 1));

        if (vui.video_signal_type_present_flag) {
            vui.video_format                    = EyerAVC_VLC::read_u_v  ( 3,"VUI: video_format"                               , bitstream, used_bits);
            vui.video_full_range_flag           = EyerAVC_VLC::read_u_1  (   "VUI: video_full_range_flag"                               , bitstream, used_bits);
            vui.colour_description_present_flag = EyerAVC_VLC::read_u_1  (   "VUI: color_description_present_flag"                      , bitstream, used_bits);

            fieldList.push_back(new EyerField("video_format", vui.video_format, nullptr, 2));
            fieldList.push_back(new EyerField("video_full_range_flag", vui.video_full_range_flag, nullptr, 2));
            fieldList.push_back(new EyerField("colour_description_present_flag", vui.colour_description_present_flag, nullptr, 2));

            if(vui.colour_description_present_flag) {
                vui.colour_primaries              = EyerAVC_VLC::read_u_v  ( 8,"VUI: colour_primaries"                                              , bitstream, used_bits);
                vui.transfer_characteristics      = EyerAVC_VLC::read_u_v  ( 8,"VUI: transfer_characteristics"                                      , bitstream, used_bits);
                vui.matrix_coefficients           = EyerAVC_VLC::read_u_v  ( 8,"VUI: matrix_coefficients"                        , bitstream, used_bits);
            }
        }

        vui.chroma_location_info_present_flag     = EyerAVC_VLC::read_u_1  (   "VUI: chroma_loc_info_present_flag"                        , bitstream, used_bits);
        fieldList.push_back(new EyerField("chroma_location_info_present_flag", vui.chroma_location_info_present_flag, nullptr, 1));

        if(vui.chroma_location_info_present_flag) {
            vui.chroma_sample_loc_type_top_field     = EyerAVC_VLC::read_ue_v  ( "VUI: chroma_sample_loc_type_top_field"                            , bitstream, used_bits);
            vui.chroma_sample_loc_type_bottom_field  = EyerAVC_VLC::read_ue_v  ( "VUI: chroma_sample_loc_type_bottom_field"                         , bitstream, used_bits);

            fieldList.push_back(new EyerField("chroma_sample_loc_type_top_field", vui.chroma_sample_loc_type_top_field, nullptr, 2));
            fieldList.push_back(new EyerField("chroma_sample_loc_type_bottom_field", vui.chroma_sample_loc_type_bottom_field, nullptr, 2));
        }

        vui.timing_info_present_flag          = EyerAVC_VLC::read_u_1  ("VUI: timing_info_present_flag"           , bitstream, used_bits);
        fieldList.push_back(new EyerField("timing_info_present_flag", vui.timing_info_present_flag, nullptr, 1));

        if (vui.timing_info_present_flag) {
            vui.num_units_in_tick               = EyerAVC_VLC::read_u_v  (32,"VUI: num_units_in_tick"               , bitstream, used_bits);
            vui.time_scale                      = EyerAVC_VLC::read_u_v  (32,"VUI: time_scale"                      , bitstream, used_bits);
            vui.fixed_frame_rate_flag           = EyerAVC_VLC::read_u_1  (   "VUI: fixed_frame_rate_flag"                    , bitstream, used_bits);
        }

        vui.nal_hrd_parameters_present_flag     = EyerAVC_VLC::read_u_1  ("VUI: nal_hrd_parameters_present_flag"             , bitstream, used_bits);
        fieldList.push_back(new EyerField("nal_hrd_parameters_present_flag", vui.nal_hrd_parameters_present_flag, nullptr, 1));
        if (vui.nal_hrd_parameters_present_flag){
            // TODO ReadHRDParameters
        }
        vui.vcl_hrd_parameters_present_flag   = EyerAVC_VLC::read_u_1  ("VUI: vcl_hrd_parameters_present_flag"               , bitstream, used_bits);
        fieldList.push_back(new EyerField("vcl_hrd_parameters_present_flag", vui.vcl_hrd_parameters_present_flag, nullptr, 1));
        if (vui.vcl_hrd_parameters_present_flag) {
            // TODO ReadHRDParameters
        }

        if (vui.nal_hrd_parameters_present_flag || vui.vcl_hrd_parameters_present_flag) {
            vui.low_delay_hrd_flag             =  EyerAVC_VLC::read_u_1  ("VUI: low_delay_hrd_flag"                 , bitstream, used_bits);
        }

        vui.pic_struct_present_flag            =  EyerAVC_VLC::read_u_1  ("VUI: pic_struct_present_flag   "         , bitstream, used_bits);
        vui.bitstream_restriction_flag         =  EyerAVC_VLC::read_u_1  ("VUI: bitstream_restriction_flag"         , bitstream, used_bits);

        fieldList.push_back(new EyerField("pic_struct_present_flag", vui.pic_struct_present_flag, nullptr, 1));
        fieldList.push_back(new EyerField("bitstream_restriction_flag", vui.bitstream_restriction_flag, nullptr,1));

        if (vui.bitstream_restriction_flag){
            vui.motion_vectors_over_pic_boundaries_flag =  EyerAVC_VLC::read_u_1  ("VUI: motion_vectors_over_pic_boundaries_flag", bitstream, used_bits);
            vui.max_bytes_per_pic_denom                 =  EyerAVC_VLC::read_ue_v ("VUI: max_bytes_per_pic_denom"                , bitstream, used_bits);
            vui.max_bits_per_mb_denom                   =  EyerAVC_VLC::read_ue_v ("VUI: max_bits_per_mb_denom"                  , bitstream, used_bits);
            vui.log2_max_mv_length_horizontal           =  EyerAVC_VLC::read_ue_v ("VUI: log2_max_mv_length_horizontal"          , bitstream, used_bits);
            vui.log2_max_mv_length_vertical             =  EyerAVC_VLC::read_ue_v ("VUI: log2_max_mv_length_vertical"            , bitstream, used_bits);
            vui.num_reorder_frames                      =  EyerAVC_VLC::read_ue_v ("VUI: num_reorder_frames"                     , bitstream, used_bits);
            vui.max_dec_frame_buffering                 =  EyerAVC_VLC::read_ue_v ("VUI: max_dec_frame_buffering"                , bitstream, used_bits);

            fieldList.push_back(new EyerField("motion_vectors_over_pic_boundaries_flag", vui.motion_vectors_over_pic_boundaries_flag, nullptr, 2));
            fieldList.push_back(new EyerField("max_bytes_per_pic_denom", vui.max_bytes_per_pic_denom, nullptr, 2));
            fieldList.push_back(new EyerField("max_bits_per_mb_denom", vui.max_bits_per_mb_denom, nullptr, 2));
            fieldList.push_back(new EyerField("log2_max_mv_length_horizontal", vui.log2_max_mv_length_horizontal, nullptr, 2));
            fieldList.push_back(new EyerField("log2_max_mv_length_vertical", vui.log2_max_mv_length_vertical, nullptr, 2));
            fieldList.push_back(new EyerField("num_reorder_frames", vui.num_reorder_frames, nullptr, 2));
            fieldList.push_back(new EyerField("max_dec_frame_buffering", vui.max_dec_frame_buffering, nullptr, 2));
        }

        return 0;
    }
}
