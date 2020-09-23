#include "EyerSPS.hpp"
#include "EyerBitStream.hpp"
#include "EyerAVC_VLC.hpp"
#include "EyerCore/EyerLog.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

namespace Eyer{
    EyerSPS::EyerSPS(EyerNALU & _nalu)
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

        reserved_zero                          = EyerAVC_VLC::read_u_v  (2, "SPS: reserved_zero_2bits"          , &bitStream, &usedBits);

        level_idc                              = EyerAVC_VLC::read_u_v  (8, "SPS: level_idc"                    , &bitStream, &usedBits);

        seq_parameter_set_id                   = EyerAVC_VLC::read_ue_v ("SPS: seq_parameter_set_id"                     , &bitStream, &usedBits);


        // Fidelity Range Extensions stuff
        chroma_format_idc = 1;

        if((profile_idc == FREXT_HP   ) ||
           (profile_idc == FREXT_Hi10P) ||
           (profile_idc == FREXT_Hi422) ||
           (profile_idc == FREXT_Hi444) ||
           (profile_idc == FREXT_CAVLC444))
        {
            chroma_format_idc                       = EyerAVC_VLC::read_ue_v ("SPS: chroma_format_idc"                       , &bitStream, &usedBits);
            if(chroma_format_idc == YUV444){
                separate_colour_plane_flag          = EyerAVC_VLC::read_u_1  ("SPS: separate_colour_plane_flag"              , &bitStream, &usedBits);
            }

            bit_depth_luma_minus8                   = EyerAVC_VLC::read_ue_v ("SPS: bit_depth_luma_minus8"                   , &bitStream, &usedBits);
            bit_depth_chroma_minus8                 = EyerAVC_VLC::read_ue_v ("SPS: bit_depth_chroma_minus8"                 , &bitStream, &usedBits);

            /*
            if((bit_depth_luma_minus8 + 8 > sizeof(imgpel) * 8) || (bit_depth_chroma_minus8 + 8> sizeof(imgpel) * 8)){
                EyerLog ("Source picture has higher bit depth than imgpel data type. \nPlease recompile with larger data type for imgpel.");
            }
            */

            lossless_qpprime_flag                   = EyerAVC_VLC::read_u_1  ("SPS: lossless_qpprime_y_zero_flag"            , &bitStream, &usedBits);
            seq_scaling_matrix_present_flag         = EyerAVC_VLC::read_u_1  ("SPS: seq_scaling_matrix_present_flag"         , &bitStream, &usedBits);

            if(seq_scaling_matrix_present_flag) {
                int scalingList = (chroma_format_idc != YUV444) ? 8 : 12;
                EyerLog("scalingList: %d\n", scalingList);
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

        if(pic_order_cnt_type == 0){
            log2_max_pic_order_cnt_lsb_minus4       = EyerAVC_VLC::read_ue_v ("SPS: log2_max_pic_order_cnt_lsb_minus4"                  , &bitStream, &usedBits);
        }
        else if(pic_order_cnt_type == 1){
            delta_pic_order_always_zero_flag        = EyerAVC_VLC::read_u_1  ("SPS: delta_pic_order_always_zero_flag"                   , &bitStream, &usedBits);
            offset_for_non_ref_pic                  = EyerAVC_VLC::read_se_v ("SPS: offset_for_non_ref_pic"                             , &bitStream, &usedBits);
            offset_for_top_to_bottom_field          = EyerAVC_VLC::read_se_v ("SPS: offset_for_top_to_bottom_field"                     , &bitStream, &usedBits);
            num_ref_frames_in_pic_order_cnt_cycle   = EyerAVC_VLC::read_ue_v ("SPS: num_ref_frames_in_pic_order_cnt_cycle"              , &bitStream, &usedBits);
            for(int i=0;i<num_ref_frames_in_pic_order_cnt_cycle;i++){
                offset_for_ref_frame[i]             = EyerAVC_VLC::read_se_v ("SPS: offset_for_ref_frame[i]"                            , &bitStream, &usedBits);
            }
        }

        num_ref_frames                              = EyerAVC_VLC::read_ue_v ("SPS: num_ref_frames"                                     , &bitStream, &usedBits);
        gaps_in_frame_num_value_allowed_flag        = EyerAVC_VLC::read_u_1  ("SPS: gaps_in_frame_num_value_allowed_flag"               , &bitStream, &usedBits);
        pic_width_in_mbs_minus1                     = EyerAVC_VLC::read_ue_v ("SPS: pic_width_in_mbs_minus1"                            , &bitStream, &usedBits);
        pic_height_in_map_units_minus1              = EyerAVC_VLC::read_ue_v ("SPS: pic_height_in_map_units_minus1"                     , &bitStream, &usedBits);
        frame_mbs_only_flag                         = EyerAVC_VLC::read_u_1  ("SPS: frame_mbs_only_flag"                                , &bitStream, &usedBits);

        if(frame_mbs_only_flag){
            mb_adaptive_frame_field_flag            = EyerAVC_VLC::read_u_1  ("SPS: mb_adaptive_frame_field_flag"                        , &bitStream, &usedBits);
        }

        direct_8x8_inference_flag                   = EyerAVC_VLC::read_u_1  ("SPS: direct_8x8_inference_flag"                           , &bitStream, &usedBits);
        frame_cropping_flag                         = EyerAVC_VLC::read_u_1  ("SPS: frame_cropping_flag"                                 , &bitStream, &usedBits);

        if (frame_cropping_flag){
            frame_crop_left_offset                  = EyerAVC_VLC::read_ue_v ("SPS: frame_crop_left_offset"                                 , &bitStream, &usedBits);
            frame_crop_right_offset                 = EyerAVC_VLC::read_ue_v ("SPS: frame_crop_right_offset"                                , &bitStream, &usedBits);
            frame_crop_top_offset                   = EyerAVC_VLC::read_ue_v ("SPS: frame_crop_top_offset"                                  , &bitStream, &usedBits);
            frame_crop_bottom_offset                = EyerAVC_VLC::read_ue_v ("SPS: frame_crop_bottom_offset"                               , &bitStream, &usedBits);
        }

        vui_parameters_present_flag                 = EyerAVC_VLC::read_u_1  ("SPS: vui_parameters_present_flag"                            , &bitStream, &usedBits);
    }

    EyerSPS::~EyerSPS()
    {

    }

    int EyerSPS::PrintInfo()
    {
        char profile_idc_str[128];
        GetProfileIDC(profile_idc_str, profile_idc);
        EyerLog("profile_idc: %s\n", profile_idc_str);

        EyerLog("constrained_set0_flag: %d\n", constrained_set0_flag);
        EyerLog("constrained_set1_flag: %d\n", constrained_set1_flag);
        EyerLog("constrained_set2_flag: %d\n", constrained_set2_flag);
        EyerLog("constrained_set3_flag: %d\n", constrained_set3_flag);
        EyerLog("constrained_set4_flag: %d\n", constrained_set4_flag);
        EyerLog("constrained_set5_flag: %d\n", constrained_set5_flag);

        EyerLog("level_idc: %d\n", level_idc);

        EyerLog("seq_parameter_set_id: %d\n", seq_parameter_set_id);

        EyerLog("chroma_format_idc: %d\n", chroma_format_idc);




        EyerLog("bit_depth_luma_minus8: %d\n", bit_depth_luma_minus8);
        EyerLog("bit_depth_chroma_minus8: %d\n", bit_depth_chroma_minus8);

        EyerLog("seq_scaling_matrix_present_flag: %d\n", seq_scaling_matrix_present_flag);

        return 0;
    }

    /*
     * 0   1   2   3
     * 4   5   6   7
     * 8   9   10  11
     * 12  13  14  15
     */
    static const byte ZZ_SCAN[16]  =
    {
            0,  1,  4,  8,  5,  2,  3,  6,  9, 12, 13, 10,  7, 11, 14, 15
    };

    /*
     * 0   1   2   3   4   5   6   7
     * 8   9   10  11  12  13  14  15
     * 16  17  18  19  20  21  22  23
     * 24  25  26  27  28  29  30  31
     * 32  33  34  35  36  37  38  39
     * 40  41  42  43  44  45  46  47
     * 48  49  50  51  52  53  54  55
     * 56  57  58  59  60  61  62  63
     */
    static const byte ZZ_SCAN8[64] =
    {
            0,  1,  8, 16,  9,  2,  3, 10, 17, 24, 32, 25, 18, 11,  4,  5,
            12, 19, 26, 33, 40, 48, 41, 34, 27, 20, 13,  6,  7, 14, 21, 28,
            35, 42, 49, 56, 57, 50, 43, 36, 29, 22, 15, 23, 30, 37, 44, 51,
            58, 59, 52, 45, 38, 31, 39, 46, 53, 60, 61, 54, 47, 55, 62, 63
    };


    void EyerSPS::ScalingList(int * scalingList, int sizeOfScalingList, Boolean * useDefaultScalingMatrix, EyerBitStream * bitstream, int * used_bits)
    {
        int j, scanj;
        int delta_scale, lastScale, nextScale;

        lastScale      = 8;
        nextScale      = 8;

        for(j=0; j<sizeOfScalingList; j++) {
            scanj = (sizeOfScalingList==16) ? ZZ_SCAN[j]:ZZ_SCAN8[j];

            if(nextScale!=0) {
                delta_scale = EyerAVC_VLC::read_se_v ("   : delta_sl   "                           , bitstream, used_bits);
                nextScale = (lastScale + delta_scale + 256) % 256;
                *useDefaultScalingMatrix = (Boolean) (scanj==0 && nextScale==0);
            }

            scalingList[scanj] = (nextScale==0) ? lastScale:nextScale;
            lastScale = scalingList[scanj];
        }
    }

    int EyerSPS::GetProfileIDC(char * str, unsigned int & profileIdc)
    {
        if(profileIdc == ProfileIDC::NO_PROFILE){
            memcpy(str, "NO_PROFILE", strlen("NO_PROFILE") + 1);
        }
        if(profileIdc == ProfileIDC::FREXT_CAVLC444){
            memcpy(str, "FREXT_CAVLC444", strlen("FREXT_CAVLC444") + 1);
        }
        if(profileIdc == ProfileIDC::BASELINE){
            memcpy(str, "BASELINE", strlen("BASELINE") + 1);
        }
        if(profileIdc == ProfileIDC::MAIN){
            memcpy(str, "MAIN", strlen("MAIN") + 1);
        }
        if(profileIdc == ProfileIDC::EXTENDED){
            memcpy(str, "EXTENDED", strlen("EXTENDED") + 1);
        }
        if(profileIdc == ProfileIDC::FREXT_HP){
            memcpy(str, "FREXT_HP", strlen("FREXT_HP") + 1);
        }
        if(profileIdc == ProfileIDC::FREXT_Hi10P){
            memcpy(str, "FREXT_Hi10P", strlen("FREXT_Hi10P") + 1);
        }
        if(profileIdc == ProfileIDC::FREXT_Hi422){
            memcpy(str, "FREXT_Hi422", strlen("FREXT_Hi422") + 1);
        }
        if(profileIdc == ProfileIDC::FREXT_Hi444){
            memcpy(str, "FREXT_Hi444", strlen("FREXT_Hi444") + 1);
        }
        return 0;
    }
}
