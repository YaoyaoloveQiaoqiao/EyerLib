#ifndef EYERLIB_EYERSPS_HPP
#define EYERLIB_EYERSPS_HPP

#include "EyerNALU.hpp"
#include "EyerAVCCommon.hpp"
#include "EyerBitStream.hpp"
#include "EyerVUI.hpp"
#include "EyerField.hpp"
#include "EyerNAL.hpp"
#include <vector>

namespace Eyer{

#define MAXnum_ref_frames_in_pic_order_cnt_cycle  256

    typedef enum {
        NO_PROFILE     =  0,       //!< disable profile checking for experimental coding (enables FRExt, but disables MV)
        FREXT_CAVLC444 = 44,       //!< YUV 4:4:4/14 "CAVLC 4:4:4"
        BASELINE       = 66,       //!< YUV 4:2:0/8  "Baseline"
        MAIN           = 77,       //!< YUV 4:2:0/8  "Main"
        EXTENDED       = 88,       //!< YUV 4:2:0/8  "Extended"
        FREXT_HP       = 100,      //!< YUV 4:2:0/8  "High"
        FREXT_Hi10P    = 110,      //!< YUV 4:2:0/10 "High 10"
        FREXT_Hi422    = 122,      //!< YUV 4:2:2/10 "High 4:2:2"
        FREXT_Hi444    = 244,      //!< YUV 4:4:4/14 "High 4:4:4"
        MVC_HIGH       = 118,      //!< YUV 4:2:0/8  "Multiview High"
        STEREO_HIGH    = 128       //!< YUV 4:2:0/8  "Stereo High"
    } ProfileIDC;

    typedef enum {
        CF_UNKNOWN = -1,     //!< Unknown color format
        YUV400     =  0,     //!< Monochrome
        YUV420     =  1,     //!< 4:2:0
        YUV422     =  2,     //!< 4:2:2
        YUV444     =  3      //!< 4:4:4
    } ColorFormat;

    class EyerSPS : public EyerNAL{
    public:
        EyerSPS(EyerNALU & _nalu);
        ~EyerSPS();

        virtual NaluType GetNalType();
    private:
        int LoadVUI(EyerBitStream * bitstream, int * used_bits);

    private:
        unsigned int profile_idc;                                       // u(8)
        Boolean   constrained_set0_flag;                                // u(1)
        Boolean   constrained_set1_flag;                                // u(1)
        Boolean   constrained_set2_flag;                                // u(1)
        Boolean   constrained_set3_flag;                                // u(1)
        Boolean   constrained_set4_flag;                                // u(1)
        Boolean   constrained_set5_flag;                                // u(1)
        unsigned  int level_idc;                                        // u(8)
        unsigned  int seq_parameter_set_id;                             // ue(v)

        unsigned  int chroma_format_idc;                                // ue(v)

        Boolean   seq_scaling_matrix_present_flag;                      // u(1)
        int       seq_scaling_list_present_flag[12];                    // u(1)

        int       ScalingList4x4[6][16];                                // se(v)
        int       ScalingList8x8[6][64];                                // se(v)
        Boolean   UseDefaultScalingMatrix4x4Flag[6];
        Boolean   UseDefaultScalingMatrix8x8Flag[6];


        unsigned int bit_depth_luma_minus8;                             // ue(v)
        unsigned int bit_depth_chroma_minus8;                           // ue(v)

        unsigned int log2_max_frame_num_minus4;                         // ue(v)
        unsigned int pic_order_cnt_type;

        unsigned int log2_max_pic_order_cnt_lsb_minus4;                 // ue(v)


        Boolean delta_pic_order_always_zero_flag;                       // u(1)
        int     offset_for_non_ref_pic;                                 // se(v)
        int     offset_for_top_to_bottom_field;                         // se(v)
        unsigned int num_ref_frames_in_pic_order_cnt_cycle;             // ue(v)

        int   offset_for_ref_frame[MAXnum_ref_frames_in_pic_order_cnt_cycle];   // se(v)

        unsigned int num_ref_frames;                                    // ue(v)
        Boolean   gaps_in_frame_num_value_allowed_flag;                 // u(1)
        unsigned int pic_width_in_mbs_minus1;                           // ue(v)
        unsigned int pic_height_in_map_units_minus1;                    // ue(v)
        Boolean   frame_mbs_only_flag;                                  // u(1)

        Boolean   mb_adaptive_frame_field_flag;                         // u(1)
        Boolean   direct_8x8_inference_flag;                            // u(1)
        Boolean   frame_cropping_flag;                                  // u(1)

        unsigned int frame_crop_left_offset;                            // ue(v)
        unsigned int frame_crop_right_offset;                           // ue(v)
        unsigned int frame_crop_top_offset;                             // ue(v)
        unsigned int frame_crop_bottom_offset;                          // ue(v)

        Boolean   vui_parameters_present_flag;                          // u(1)

        unsigned  int separate_colour_plane_flag;                       // u(1)


        int lossless_qpprime_flag;

        EyerVUI vui;
    };
}

#endif //EYERLIB_EYERSPS_HPP
