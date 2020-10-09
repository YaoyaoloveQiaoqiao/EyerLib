#include "EyerPPS.hpp"
#include "EyerBitStream.hpp"
#include "EyerAVC_VLC.hpp"

namespace Eyer
{
    NaluType EyerPPS::GetNalType()
    {
        return NaluType::NALU_TYPE_PPS;
    }

    EyerPPS::EyerPPS() : EyerNAL()
    {
        valid = Boolean::FALSE;
    }

    EyerPPS::EyerPPS(EyerNALU & _nalu) : EyerNAL()
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

        pic_parameter_set_id                  = EyerAVC_VLC::read_ue_v ("PPS: pic_parameter_set_id"                   , &bitStream, &usedBits);
        seq_parameter_set_id                  = EyerAVC_VLC::read_ue_v ("PPS: seq_parameter_set_id"                   , &bitStream, &usedBits);
        entropy_coding_mode_flag              = EyerAVC_VLC::read_u_1  ("PPS: entropy_coding_mode_flag"               , &bitStream, &usedBits);

        //! Note: as per JVT-F078 the following bit is unconditional.  If F078 is not accepted, then
        //! one has to fetch the correct SPS to check whether the bit is present (hopefully there is
        //! no consistency problem :-(
        //! The current encoder code handles this in the same way.  When you change this, don't forget
        //! the encoder!  StW, 12/8/02
        bottom_field_pic_order_in_frame_present_flag    = EyerAVC_VLC::read_u_1  ("PPS: bottom_field_pic_order_in_frame_present_flag"                   , &bitStream, &usedBits);
        num_slice_groups_minus1                         = EyerAVC_VLC::read_ue_v ("PPS: num_slice_groups_minus1"                                        , &bitStream, &usedBits);

        fieldList.push_back(new EyerField("pic_parameter_set_id", pic_parameter_set_id));
        fieldList.push_back(new EyerField("seq_parameter_set_id", seq_parameter_set_id));
        fieldList.push_back(new EyerField("entropy_coding_mode_flag", entropy_coding_mode_flag));
        fieldList.push_back(new EyerField("bottom_field_pic_order_in_frame_present_flag", bottom_field_pic_order_in_frame_present_flag));
        fieldList.push_back(new EyerField("num_slice_groups_minus1", num_slice_groups_minus1));

        // FMO stuff begins here
        if (num_slice_groups_minus1 > 0){
            slice_group_map_type                        = EyerAVC_VLC::read_ue_v ("PPS: slice_group_map_type"                , &bitStream, &usedBits);
            fieldList.push_back(new EyerField("slice_group_map_type", slice_group_map_type, nullptr, 1));
            if (slice_group_map_type == 0) {
                for (int i=0; i<=num_slice_groups_minus1; i++) {
                    run_length_minus1[i] = EyerAVC_VLC::read_ue_v("PPS: run_length_minus1 [i]", &bitStream, &usedBits);
                }
            }
            else if (slice_group_map_type == 2){
                for (int i=0; i<num_slice_groups_minus1; i++) {
                    //! JVT-F078: avoid reference of SPS by using ue(v) instead of u(v)
                    top_left[i]                          = EyerAVC_VLC::read_ue_v ("PPS: top_left [i]"                        , &bitStream, &usedBits);
                    bottom_right[i]                      = EyerAVC_VLC::read_ue_v ("PPS: bottom_right [i]"                    , &bitStream, &usedBits);
                }
            }
            else if (slice_group_map_type == 3 ||
                     slice_group_map_type == 4 ||
                     slice_group_map_type == 5) {
                slice_group_change_direction_flag       = EyerAVC_VLC::read_u_1  ("PPS: slice_group_change_direction_flag"              , &bitStream, &usedBits);
                slice_group_change_rate_minus1          = EyerAVC_VLC::read_ue_v ("PPS: slice_group_change_rate_minus1"                 , &bitStream, &usedBits);
            }
            else if (slice_group_map_type == 6){
                // TODO
            }
        }

        num_ref_idx_l0_default_active_minus1    = EyerAVC_VLC::read_ue_v ("PPS: num_ref_idx_l0_default_active_minus1"   , &bitStream, &usedBits);
        num_ref_idx_l1_default_active_minus1    = EyerAVC_VLC::read_ue_v ("PPS: num_ref_idx_l1_default_active_minus1"   , &bitStream, &usedBits);
        weighted_pred_flag                      = EyerAVC_VLC::read_u_1  ("PPS: weighted_pred_flag"                     , &bitStream, &usedBits);
        weighted_bipred_idc                     = EyerAVC_VLC::read_u_v  ( 2, "PPS: weighted_bipred_idc"                , &bitStream, &usedBits);
        pic_init_qp_minus26                     = EyerAVC_VLC::read_se_v ("PPS: pic_init_qp_minus26"                    , &bitStream, &usedBits);
        pic_init_qs_minus26                     = EyerAVC_VLC::read_se_v ("PPS: pic_init_qs_minus26"                    , &bitStream, &usedBits);

        chroma_qp_index_offset                  = EyerAVC_VLC::read_se_v ("PPS: chroma_qp_index_offset"                 , &bitStream, &usedBits);

        deblocking_filter_control_present_flag  = EyerAVC_VLC::read_u_1 ("PPS: deblocking_filter_control_present_flag"  , &bitStream, &usedBits);
        constrained_intra_pred_flag             = EyerAVC_VLC::read_u_1  ("PPS: constrained_intra_pred_flag"            , &bitStream, &usedBits);
        redundant_pic_cnt_present_flag          = EyerAVC_VLC::read_u_1  ("PPS: redundant_pic_cnt_present_flag"         , &bitStream, &usedBits);

        fieldList.push_back(new EyerField("num_ref_idx_l0_default_active_minus1", num_ref_idx_l0_default_active_minus1));
        fieldList.push_back(new EyerField("num_ref_idx_l1_default_active_minus1", num_ref_idx_l1_default_active_minus1));
        fieldList.push_back(new EyerField("weighted_pred_flag", weighted_pred_flag));
        fieldList.push_back(new EyerField("weighted_bipred_idc", weighted_bipred_idc));
        fieldList.push_back(new EyerField("pic_init_qp_minus26", pic_init_qp_minus26));
        fieldList.push_back(new EyerField("pic_init_qs_minus26", pic_init_qs_minus26));
        fieldList.push_back(new EyerField("chroma_qp_index_offset", chroma_qp_index_offset));
        fieldList.push_back(new EyerField("deblocking_filter_control_present_flag", deblocking_filter_control_present_flag));
        fieldList.push_back(new EyerField("constrained_intra_pred_flag", constrained_intra_pred_flag));
        fieldList.push_back(new EyerField("redundant_pic_cnt_present_flag", redundant_pic_cnt_present_flag));

        // TODO more_rbsp_data
        valid = Boolean::TRUE;
    }

    EyerPPS::~EyerPPS()
    {
        for(int i=0;i<fieldList.size();i++){
            delete fieldList[i];
        }
        fieldList.clear();
    }
}
