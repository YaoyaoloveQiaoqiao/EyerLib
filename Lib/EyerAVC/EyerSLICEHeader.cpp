#include "EyerSLICEHeader.hpp"
#include "EyerField.hpp"

namespace Eyer
{
    EyerSLICEHeader::EyerSLICEHeader(EyerSPS & _sps, EyerPPS & _pps, EyerNALUData & _naluData)
    {
        sps = _sps;
        pps = _pps;
        naluData = _naluData;
    }

    EyerSLICEHeader::~EyerSLICEHeader()
    {

    }

    int EyerSLICEHeader::Parse(EyerBitStream & bs, std::vector<EyerField *> & fieldList)
    {
        ParseHeadPartA(bs, fieldList);

        // Select SPS PPS
        if(!sps.isValid()){
            return -1;
        }
        if(!pps.isValid()){
            return -1;
        }

        ParseHeadPartB(bs, fieldList);

        return 0;
    }

    SLICEType EyerSLICEHeader::GetSLICEType()
    {
        return sliceType;
    }

    int EyerSLICEHeader::ParseHeadPartA(EyerBitStream & bs, std::vector<EyerField *> & fieldList)
    {
        sh.first_mb_in_slice           = bs.bs_read_ue();
        sh.slice_type                  = bs.bs_read_ue();
        sh.pic_parameter_set_id        = bs.bs_read_ue();

        sliceType = sh.slice_type;

        fieldList.push_back(new EyerField("first_mb_in_slice",                             sh.first_mb_in_slice));
        fieldList.push_back(new EyerField("slice_type",                                    sh.slice_type));
        fieldList.push_back(new EyerField("pic_parameter_set_id",                          sh.pic_parameter_set_id));

        return 0;
    }

    int EyerSLICEHeader::ParseHeadPartB(EyerBitStream & bs, std::vector<EyerField *> & fieldList)
    {
        sliceType = sh.slice_type;

        if (sps.residual_colour_transform_flag) {
            sh.colour_plane_id = bs.bs_read_u(2);
            fieldList.push_back(new EyerField("colour_plane_id",                           sh.colour_plane_id));
        }

        sh.frame_num = bs.bs_read_u(sps.log2_max_frame_num_minus4 + 4);
        fieldList.push_back(new EyerField("frame_num",      sh.frame_num));

        if(!sps.frame_mbs_only_flag){
            sh.field_pic_flag = bs.bs_read_u1();
            fieldList.push_back(new EyerField("field_pic_flag",             sh.field_pic_flag));
            if(sh.field_pic_flag) {
                sh.bottom_field_flag = bs.bs_read_u1();
                fieldList.push_back(new EyerField("bottom_field_flag",      sh.bottom_field_flag, nullptr, 1));
            }
        }

        if(naluData.GetNALUType() == NALUType::NALU_TYPE_IDR) {
            sh.idr_pic_id = bs.bs_read_ue();
            fieldList.push_back(new EyerField("idr_pic_id",      sh.idr_pic_id));
        }

        if(sps.pic_order_cnt_type == 0){
            sh.pic_order_cnt_lsb = bs.bs_read_u(sps.log2_max_pic_order_cnt_lsb_minus4 + 4);
            fieldList.push_back(new EyerField("pic_order_cnt_lsb", sh.pic_order_cnt_lsb));
            if(pps.pic_order_present_flag && !sh.field_pic_flag ) {
                sh.delta_pic_order_cnt_bottom = bs.bs_read_se();
                fieldList.push_back(new EyerField("delta_pic_order_cnt_bottom", sh.delta_pic_order_cnt_bottom, nullptr, 1));
            }
        }

        if(sps.pic_order_cnt_type == 1 && !sps.delta_pic_order_always_zero_flag) {
            sh.delta_pic_order_cnt[0] = bs.bs_read_se();
            fieldList.push_back(new EyerField("delta_pic_order_cnt[0]", sh.delta_pic_order_cnt[0], nullptr, 1));
            if(pps.pic_order_present_flag && !sh.field_pic_flag) {
                sh.delta_pic_order_cnt[1] = bs.bs_read_se();
                fieldList.push_back(new EyerField("delta_pic_order_cnt[1]", sh.delta_pic_order_cnt[1], nullptr, 1));
            }
        }

        if(pps.redundant_pic_cnt_present_flag) {
            sh.redundant_pic_cnt = bs.bs_read_ue();
            fieldList.push_back(new EyerField("redundant_pic_cnt", sh.redundant_pic_cnt));
        }

        if(sliceType == SLICEType::SLICE_TYPE_B) {
            sh.direct_spatial_mv_pred_flag = bs.bs_read_u1();
            fieldList.push_back(new EyerField("direct_spatial_mv_pred_flag", sh.direct_spatial_mv_pred_flag));
        }

        if(sliceType == SLICEType::SLICE_TYPE_P || sliceType == SLICEType::SLICE_TYPE_SP || sliceType == SLICEType::SLICE_TYPE_B) {
            sh.num_ref_idx_active_override_flag = bs.bs_read_u1();
            fieldList.push_back(new EyerField("num_ref_idx_active_override_flag", sh.num_ref_idx_active_override_flag));
            if(sh.num_ref_idx_active_override_flag) {
                sh.num_ref_idx_l0_active_minus1 = bs.bs_read_ue();
                fieldList.push_back(new EyerField("num_ref_idx_l0_active_minus1", sh.num_ref_idx_l0_active_minus1, nullptr, 1));
                if(sliceType == SLICEType::SLICE_TYPE_B) {
                    sh.num_ref_idx_l1_active_minus1 = bs.bs_read_ue();
                    fieldList.push_back(new EyerField("num_ref_idx_l1_active_minus1", sh.num_ref_idx_l1_active_minus1, nullptr, 1));
                }
            }
        }

        ReadRefPicListReordering(bs, fieldList);

        if( (pps.weighted_pred_flag && (sliceType == SLICEType::SLICE_TYPE_P || sliceType == SLICEType::SLICE_TYPE_SP)) ||
            (pps.weighted_bipred_idc == 1 && sliceType == SLICEType::SLICE_TYPE_B))
        {
            ReadPredWeightTable(bs, fieldList);
        }
        if(naluData.nal_ref_idc != NALRefIdc::NALU_PRIORITY_DISPOSABLE)
        {
            ReadDecRefPicMarking(bs, fieldList);
        }

        if(pps.entropy_coding_mode_flag && sliceType != SLICEType::SLICE_TYPE_I && sliceType != SLICEType::SLICE_TYPE_SI) {
            sh.cabac_init_idc = bs.bs_read_ue();
            fieldList.push_back(new EyerField("cabac_init_idc", sh.cabac_init_idc));
        }
        sh.slice_qp_delta = bs.bs_read_se();
        fieldList.push_back(new EyerField("slice_qp_delta", sh.slice_qp_delta));

        if(sliceType == SLICEType::SLICE_TYPE_SP || sliceType == SLICEType::SLICE_TYPE_SI){
            if(sliceType == SLICEType::SLICE_TYPE_SP){
                sh.sp_for_switch_flag = bs.bs_read_u1();
                fieldList.push_back(new EyerField("sp_for_switch_flag", sh.sp_for_switch_flag));
            }
            sh.slice_qs_delta = bs.bs_read_se();
            fieldList.push_back(new EyerField("slice_qs_delta", sh.slice_qs_delta));
        }

        if(pps.deblocking_filter_control_present_flag) {
            sh.disable_deblocking_filter_idc = bs.bs_read_ue();
            fieldList.push_back(new EyerField("disable_deblocking_filter_idc", sh.disable_deblocking_filter_idc));
            if(sh.disable_deblocking_filter_idc != 1) {
                sh.slice_alpha_c0_offset_div2 = bs.bs_read_se();
                sh.slice_beta_offset_div2 = bs.bs_read_se();
                fieldList.push_back(new EyerField("slice_alpha_c0_offset_div2", sh.slice_alpha_c0_offset_div2, nullptr, 1));
                fieldList.push_back(new EyerField("slice_beta_offset_div2", sh.slice_beta_offset_div2, nullptr, 1));
            }
        }
        if(pps.num_slice_groups_minus1 > 0 && pps.slice_group_map_type >= 3 && pps.slice_group_map_type <= 5) {
            int v = intlog2( pps.pic_size_in_map_units_minus1 +  pps.slice_group_change_rate_minus1 + 1);
            sh.slice_group_change_cycle = bs.bs_read_u(v); // FIXME add 2?
            fieldList.push_back(new EyerField("slice_group_change_cycle", sh.slice_group_change_cycle));
        }

        return 0;
    }

    int EyerSLICEHeader::ReadRefPicListReordering(EyerBitStream & bs, std::vector<EyerField *> & fieldList)
    {
        fieldList.push_back(new EyerField("ref_pic_list_reordering[]"));
        int level = 1;

        SLICEType sliceType = sh.slice_type;
        if(sliceType != SLICEType::SLICE_TYPE_I && sliceType != SLICEType::SLICE_TYPE_SI ){
            sh.rplr.ref_pic_list_reordering_flag_l0 = bs.bs_read_u1();
            fieldList.push_back(new EyerField("ref_pic_list_reordering_flag_l0", sh.rplr.ref_pic_list_reordering_flag_l0, nullptr, level));
            if(sh.rplr.ref_pic_list_reordering_flag_l0) {
                int n = -1;
                do
                {
                    n++;
                    sh.rplr.reorder_l0.reordering_of_pic_nums_idc[n] = bs.bs_read_ue();
                    // fieldList.push_back(new EyerField(EyerString("reorder_l0.reordering_of_pic_nums_idc[") + EyerString::Number(n) + "]", sh.rplr.reorder_l0.reordering_of_pic_nums_idc[n], nullptr, level + 1));
                    if( sh.rplr.reorder_l0.reordering_of_pic_nums_idc[n] == 0 ||
                        sh.rplr.reorder_l0.reordering_of_pic_nums_idc[n] == 1 )
                    {
                        sh.rplr.reorder_l0.abs_diff_pic_num_minus1[n] = bs.bs_read_ue();
                    }
                    else if( sh.rplr.reorder_l0.reordering_of_pic_nums_idc[n] == 2 )
                    {
                        sh.rplr.reorder_l0.long_term_pic_num[n] = bs.bs_read_ue();
                    }
                } while( sh.rplr.reorder_l0.reordering_of_pic_nums_idc[n] != 3 && ! bs.bs_eof() );
            }
        }

        if(sliceType == SLICEType::SLICE_TYPE_B)
        {
            sh.rplr.ref_pic_list_reordering_flag_l1 = bs.bs_read_u1();
            fieldList.push_back(new EyerField("ref_pic_list_reordering_flag_l1", sh.rplr.ref_pic_list_reordering_flag_l1, nullptr, 1));
            if(sh.rplr.ref_pic_list_reordering_flag_l1) {
                int n = -1;
                do
                {
                    n++;
                    sh.rplr.reorder_l1.reordering_of_pic_nums_idc[n] = bs.bs_read_ue();
                    // fieldList.push_back(new EyerField(EyerString("reorder_l1.reordering_of_pic_nums_idc[") + EyerString::Number(n) + "]", sh.rplr.reorder_l1.reordering_of_pic_nums_idc[n], nullptr, level + 1));
                    if(sh.rplr.reorder_l1.reordering_of_pic_nums_idc[n] == 0 || sh.rplr.reorder_l1.reordering_of_pic_nums_idc[n] == 1) {
                        sh.rplr.reorder_l1.abs_diff_pic_num_minus1[n] = bs.bs_read_ue();
                    }
                    else if(sh.rplr.reorder_l1.reordering_of_pic_nums_idc[n] == 2)
                    {
                        sh.rplr.reorder_l1.long_term_pic_num[n] = bs.bs_read_ue();
                    }
                } while( sh.rplr.reorder_l1.reordering_of_pic_nums_idc[n] != 3 && ! bs.bs_eof());
            }
        }

        return 0;
    }

    int EyerSLICEHeader::ReadPredWeightTable(EyerBitStream & bs, std::vector<EyerField *> & fieldList)
    {
        sh.pwt.luma_log2_weight_denom = bs.bs_read_ue();
        if(sps.chroma_format_idc != 0) {
            sh.pwt.chroma_log2_weight_denom = bs.bs_read_ue();
        }
        for(int i = 0; i <= pps.num_ref_idx_l0_active_minus1; i++){
            sh.pwt.luma_weight_l0_flag[i] = bs.bs_read_u1();
            if(sh.pwt.luma_weight_l0_flag[i]) {
                sh.pwt.luma_weight_l0[i] = bs.bs_read_se();
                sh.pwt.luma_offset_l0[i] = bs.bs_read_se();
            }
            if (sps.chroma_format_idc != 0) {
                sh.pwt.chroma_weight_l0_flag[i] = bs.bs_read_u1();
                if(sh.pwt.chroma_weight_l0_flag[i]) {
                    for(int j =0; j < 2; j++ )
                    {
                        sh.pwt.chroma_weight_l0[i][j] = bs.bs_read_se();
                        sh.pwt.chroma_offset_l0[i][j] = bs.bs_read_se();
                    }
                }
            }
        }

        if(sliceType == SLICEType::SLICE_TYPE_B) {
            for(int i = 0; i <= pps.num_ref_idx_l1_active_minus1; i++)
            {
                sh.pwt.luma_weight_l1_flag[i] = bs.bs_read_u1();
                if(sh.pwt.luma_weight_l1_flag[i]) {
                    sh.pwt.luma_weight_l1[i] = bs.bs_read_se();
                    sh.pwt.luma_offset_l1[i] = bs.bs_read_se();
                }
                if(sps.chroma_format_idc != 0) {
                    sh.pwt.chroma_weight_l1_flag[i] = bs.bs_read_u1();
                    if(sh.pwt.chroma_weight_l1_flag[i]) {
                        for(int j = 0; j < 2; j++) {
                            sh.pwt.chroma_weight_l1[i][j] = bs.bs_read_se();
                            sh.pwt.chroma_offset_l1[i][j] = bs.bs_read_se();
                        }
                    }
                }
            }
        }

        return 0;
    }

    int EyerSLICEHeader::ReadDecRefPicMarking(EyerBitStream & bs, std::vector<EyerField *> & fieldList)
    {
        if(naluData.nal_unit_type == NALUType::NALU_TYPE_IDR) {
            sh.drpm.no_output_of_prior_pics_flag    = bs.bs_read_u1();
            sh.drpm.long_term_reference_flag        = bs.bs_read_u1();

            fieldList.push_back(new EyerField("no_output_of_prior_pics_flag", sh.drpm.no_output_of_prior_pics_flag));
            fieldList.push_back(new EyerField("long_term_reference_flag", sh.drpm.long_term_reference_flag));
        }
        else {
            sh.drpm.adaptive_ref_pic_marking_mode_flag = bs.bs_read_u1();
            if(sh.drpm.adaptive_ref_pic_marking_mode_flag) {
                int n = -1;
                do
                {
                    n++;
                    sh.drpm.memory_management_control_operation[n] = bs.bs_read_ue();
                    if( sh.drpm.memory_management_control_operation[n] == 1 ||
                        sh.drpm.memory_management_control_operation[n] == 3 )
                    {
                        sh.drpm.difference_of_pic_nums_minus1[n] = bs.bs_read_ue();
                    }
                    if(sh.drpm.memory_management_control_operation[n] == 2) {
                        sh.drpm.long_term_pic_num[n] = bs.bs_read_ue();
                    }
                    if( sh.drpm.memory_management_control_operation[n] == 3 ||
                        sh.drpm.memory_management_control_operation[n] == 6 )
                    {
                        sh.drpm.long_term_frame_idx[n] = bs.bs_read_ue();
                    }
                    if( sh.drpm.memory_management_control_operation[n] == 4) {
                        sh.drpm.max_long_term_frame_idx_plus1[n] = bs.bs_read_ue();
                    }
                } while(sh.drpm.memory_management_control_operation[n] != 0 && ! bs.bs_eof() );
            }
        }
        return 0;
    }

    int EyerSLICEHeader::intlog2(int x)
    {
        int log = 0;
        if (x < 0) { x = 0; }
        while ((x >> log) > 0)
        {
            log++;
        }
        if (log > 0 && x == 1<<(log-1)) { log--; }
        return log;
    }
}