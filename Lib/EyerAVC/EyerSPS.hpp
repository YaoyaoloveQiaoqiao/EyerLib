#ifndef EYERLIB_EYERSPS_HPP
#define EYERLIB_EYERSPS_HPP

#include "EyerNALUData.hpp"
#include "EyerNALU.hpp"
#include "EyerBitStream.hpp"

namespace Eyer
{
    class EyerSPSVUI
    {
    public:
        int aspect_ratio_info_present_flag;
        int aspect_ratio_idc;
        int sar_width;
        int sar_height;
        int overscan_info_present_flag;
        int overscan_appropriate_flag;
        int video_signal_type_present_flag;
        int video_format;
        int video_full_range_flag;
        int colour_description_present_flag;
        int colour_primaries;
        int transfer_characteristics;
        int matrix_coefficients;
        int chroma_loc_info_present_flag;
        int chroma_sample_loc_type_top_field;
        int chroma_sample_loc_type_bottom_field;
        int timing_info_present_flag;
        int num_units_in_tick;
        int time_scale;
        int fixed_frame_rate_flag;
        int nal_hrd_parameters_present_flag;
        int vcl_hrd_parameters_present_flag;
        int low_delay_hrd_flag;
        int pic_struct_present_flag;
        int bitstream_restriction_flag;
        int motion_vectors_over_pic_boundaries_flag;
        int max_bytes_per_pic_denom;
        int max_bits_per_mb_denom;
        int log2_max_mv_length_horizontal;
        int log2_max_mv_length_vertical;
        int num_reorder_frames;
        int max_dec_frame_buffering;
    };


    class EyerSPS : public EyerNALU {
    public:
        EyerSPS();
        ~EyerSPS();

        virtual int Parse();

    private:
        int profile_idc;
        int constraint_set0_flag;
        int constraint_set1_flag;
        int constraint_set2_flag;
        int constraint_set3_flag;
        int constraint_set4_flag;
        int constraint_set5_flag;
        int reserved_zero_2bits;
        int level_idc;
        int seq_parameter_set_id;

        int log2_max_frame_num_minus4;
        int pic_order_cnt_type;
        // if(pic_order_cnt_type == 0){
            int log2_max_pic_order_cnt_lsb_minus4;
        // }
        // else if(pic_order_cnt_type == 1){
            int delta_pic_order_always_zero_flag;
            int offset_for_non_ref_pic;
            int offset_for_top_to_bottom_field;
            int num_ref_frames_in_pic_order_cnt_cycle;

            // for(int i=0;i<num_ref_frames_in_pic_order_cnt_cycle;i++){
                int offset_for_ref_frame[256];
            // }
        // }

        int num_ref_frames;
        int gaps_in_frame_num_value_allowed_flag;
        int pic_width_in_mbs_minus1;
        int pic_height_in_map_units_minus1;
        int frame_mbs_only_flag;
        // if(!frame_mbs_only_flag) {
            int mb_adaptive_frame_field_flag;
        // }

        int direct_8x8_inference_flag;
        int frame_cropping_flag;
            int frame_crop_left_offset;
            int frame_crop_right_offset;
            int frame_crop_top_offset;
            int frame_crop_bottom_offset;

        int vui_parameters_present_flag;


        int ReadVuiParameters(EyerBitStream & bs);

        // vui
        EyerSPSVUI vui;
    };
}

#endif //EYERLIB_EYERSPS_HPP
