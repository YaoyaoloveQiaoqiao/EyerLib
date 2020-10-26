#ifndef EYERLIB_EYERVUI_HPP
#define EYERLIB_EYERVUI_HPP

#include "EyerBitStream.hpp"

namespace Eyer{
    class EyerVUI {
    public:
        EyerVUI();
        ~EyerVUI();
    public:
        Boolean      aspect_ratio_info_present_flag;                   // u(1)
        unsigned int aspect_ratio_idc;                                 // u(8)
        unsigned short sar_width;                                      // u(16)
        unsigned short sar_height;                                     // u(16)

        Boolean      overscan_info_present_flag;                       // u(1)
        Boolean      overscan_appropriate_flag;                        // u(1)
        Boolean      video_signal_type_present_flag;                   // u(1)

        unsigned int video_format;                                     // u(3)
        Boolean      video_full_range_flag;                            // u(1)
        Boolean      colour_description_present_flag;                  // u(1)

        unsigned int colour_primaries;                                 // u(8)
        unsigned int transfer_characteristics;                         // u(8)
        unsigned int matrix_coefficients;                              // u(8)

        Boolean      chroma_location_info_present_flag;                // u(1)

        unsigned int  chroma_sample_loc_type_top_field;                // ue(v)
        unsigned int  chroma_sample_loc_type_bottom_field;             // ue(v)

        Boolean      timing_info_present_flag;                         // u(1)

        unsigned int num_units_in_tick;                                // u(32)
        unsigned int time_scale;                                       // u(32)
        Boolean      fixed_frame_rate_flag;                            // u(1)

        Boolean      nal_hrd_parameters_present_flag;                  // u(1)
        Boolean      vcl_hrd_parameters_present_flag;                  // u(1)

        Boolean      low_delay_hrd_flag;                               // u(1)

        Boolean      pic_struct_present_flag;                          // u(1)
        Boolean      bitstream_restriction_flag;                       // u(1)

        Boolean      motion_vectors_over_pic_boundaries_flag;          // u(1)
        unsigned int max_bytes_per_pic_denom;                          // ue(v)
        unsigned int max_bits_per_mb_denom;                            // ue(v)
        unsigned int log2_max_mv_length_vertical;                      // ue(v)
        unsigned int log2_max_mv_length_horizontal;                    // ue(v)
        unsigned int num_reorder_frames;                               // ue(v)
        unsigned int max_dec_frame_buffering;                          // ue(v)
    };
}

#endif //EYERLIB_EYERVUI_HPP
