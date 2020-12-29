#include "EyerSLICEHeader.hpp"
#include "EyerField.hpp"

namespace Eyer
{
    EyerSLICEHeader::EyerSLICEHeader()
    {

    }

    EyerSLICEHeader::~EyerSLICEHeader()
    {

    }

    int EyerSLICEHeader::Parse(EyerBitStream & bs, EyerSyntax & syntax, EyerSPS & _sps, EyerPPS & _pps, EyerNALUData & _naluData)
    {
        sps = _sps;
        pps = _pps;
        naluData = _naluData;

        ParseHeadPartA(bs, syntax);

        // Select SPS PPS
        if(!sps.isValid()){
            return -1;
        }
        if(!pps.isValid()){
            return -1;
        }

        ParseHeadPartB(bs, syntax);

        return 0;
    }

    SLICEType EyerSLICEHeader::GetSLICEType()
    {
        return sliceType;
    }

    int EyerSLICEHeader::ParseHeadPartA(EyerBitStream & bs, EyerSyntax & syntax)
    {
        sh.first_mb_in_slice           = bs.bs_read_ue();
        sh.slice_type                  = bs.bs_read_ue();
        sh.pic_parameter_set_id        = bs.bs_read_ue();

        syntax.Put(true, "first_mb_in_slice",       sh.first_mb_in_slice);
        syntax.Put(true, "slice_type",              sh.slice_type);
        syntax.Put(true, "pic_parameter_set_id",    sh.pic_parameter_set_id);

        sliceType = sh.slice_type;

        return 0;
    }

    int EyerSLICEHeader::ParseHeadPartB(EyerBitStream & bs, EyerSyntax & syntax)
    {
        sliceType = sh.slice_type;

        if (sps.separate_colour_plance_flag == 1) {
            sh.colour_plane_id = bs.bs_read_u(2);
        }
        // ===================== Syntax Start =====================
        EyerSyntax if_colour_plance_flag_Syntax(true, "if(separate_colour_plance_flag == 1)", syntax.GetLevel() + 1);
        {
            bool is = sps.separate_colour_plance_flag == 1;
            if_colour_plance_flag_Syntax.Put(true && is, "colour_plane_id", sh.colour_plane_id);
        }
        syntax.Put(if_colour_plance_flag_Syntax);
        // ===================== Syntax End =====================

        sh.frame_num = bs.bs_read_u(sps.log2_max_frame_num_minus4 + 4);
        // ===================== Syntax Start =====================
        syntax.Put(true, "frame_num", sh.frame_num);
        // ===================== Syntax End =====================

        if(!sps.frame_mbs_only_flag){
            sh.field_pic_flag = bs.bs_read_u1();
            if(sh.field_pic_flag) {
                sh.bottom_field_flag = bs.bs_read_u1();
            }
        }
        // ===================== Syntax Start =====================
        EyerSyntax if_frame_mbs_only_flag(true, "if(!sps.frame_mbs_only_flag)", syntax.GetLevel() + 1);
        {
            bool isA = !sps.frame_mbs_only_flag;
            if_frame_mbs_only_flag.Put(isA, "field_pic_flag", sh.field_pic_flag);
            EyerSyntax if_field_pic_flag(true && isA, "if(field_pic_flag)", if_frame_mbs_only_flag.GetLevel() + 1);
            {
                bool isB = sh.field_pic_flag;
                if_field_pic_flag.Put(true && isA && isB, "bottom_field_flag", sh.bottom_field_flag);
            }
            if_frame_mbs_only_flag.Put(if_field_pic_flag);
        }
        syntax.Put(if_frame_mbs_only_flag);
        // ===================== Syntax End =====================

        if(naluData.GetNALUType() == NALUType::NALU_TYPE_IDR) {
            sh.idr_pic_id = bs.bs_read_ue();
        }
        // ===================== Syntax Start =====================
        EyerSyntax if_idr(true, "if(naluType == IDR)", syntax.GetLevel() + 1);
        {
            bool is = naluData.GetNALUType() == NALUType::NALU_TYPE_IDR;
            if_idr.Put(is, "idr_pic_id", sh.idr_pic_id);
        }
        syntax.Put(if_idr);
        // ===================== Syntax End =====================

        if(sps.pic_order_cnt_type == 0){
            sh.pic_order_cnt_lsb = bs.bs_read_u(sps.log2_max_pic_order_cnt_lsb_minus4 + 4);
            if(pps.pic_order_present_flag && !sh.field_pic_flag) {
                sh.delta_pic_order_cnt_bottom = bs.bs_read_se();
            }
        }
        // ===================== Syntax Start =====================
        EyerSyntax if_pic_order_cnt_type(true, "if(pic_order_cnt_type == 0)", syntax.GetLevel() + 1);
        {
            bool is = sps.pic_order_cnt_type == 0;
            if_pic_order_cnt_type.Put(is, "pic_order_cnt_lsb", sh.pic_order_cnt_lsb);
            EyerSyntax ifs(is, "pic_order_present_flag && !sh.field_pic_flag", if_pic_order_cnt_type.GetLevel() + 1);
            {
                bool isA = pps.pic_order_present_flag && !sh.field_pic_flag;
                ifs.Put(is && isA, "delta_pic_order_cnt_bottom", sh.delta_pic_order_cnt_bottom);
            }
            if_pic_order_cnt_type.Put(ifs);
        }
        syntax.Put(if_pic_order_cnt_type);
        // ===================== Syntax End =====================

        if(sps.pic_order_cnt_type == 1 && !sps.delta_pic_order_always_zero_flag) {
            sh.delta_pic_order_cnt[0] = bs.bs_read_se();
            if(pps.pic_order_present_flag && !sh.field_pic_flag) {
                sh.delta_pic_order_cnt[1] = bs.bs_read_se();
            }
        }
        // ===================== Syntax Start =====================
        EyerSyntax if_cnt_type(true, "if(sps.pic_order_cnt_type == 1 && !sps.delta_pic_order_always_zero_flag)", syntax.GetLevel() + 1);
        {
            bool isA = sps.pic_order_cnt_type == 1 && !sps.delta_pic_order_always_zero_flag;
            if_cnt_type.Put(isA, "delta_pic_order_cnt[0]", sh.delta_pic_order_cnt[0]);
            EyerSyntax if_a(isA, "if(pic_order_present_flag && !field_pic_flag)", if_cnt_type.GetLevel() + 1);
            {
                bool isB = pps.pic_order_present_flag && !sh.field_pic_flag;
                if_a.Put(isA && isB, "delta_pic_order_cnt[1]", sh.delta_pic_order_cnt[1]);
            }
            if_cnt_type.Put(if_a);
        }
        syntax.Put(if_cnt_type);
        // ===================== Syntax End =====================

        if(pps.redundant_pic_cnt_present_flag) {
            sh.redundant_pic_cnt = bs.bs_read_ue();
        }
        // ===================== Syntax Start =====================
        EyerSyntax if_cnt_present_flag(true, "if(redundant_pic_cnt_present_flag)", syntax.GetLevel() + 1);
        {
            bool isA = pps.redundant_pic_cnt_present_flag;
            if_cnt_present_flag.Put(true && isA, "redundant_pic_cnt", sh.redundant_pic_cnt);
        }
        syntax.Put(if_cnt_present_flag);
        // ===================== Syntax End =====================

        if(sliceType == SLICEType::SLICE_TYPE_B) {
            sh.direct_spatial_mv_pred_flag = bs.bs_read_u1();
        }
        // ===================== Syntax Start =====================
        EyerSyntax if_B_Slice(true, "if(slice_type == B)", syntax.GetLevel() + 1);
        {
            bool isA = sliceType == SLICEType::SLICE_TYPE_B;
            if_B_Slice.Put(true && isA, "direct_spatial_mv_pred_flag", sh.direct_spatial_mv_pred_flag);
        }
        syntax.Put(if_B_Slice);
        // ===================== Syntax End =====================

        if(sliceType == SLICEType::SLICE_TYPE_P || sliceType == SLICEType::SLICE_TYPE_SP || sliceType == SLICEType::SLICE_TYPE_B) {
            sh.num_ref_idx_active_override_flag = bs.bs_read_u1();
            if(sh.num_ref_idx_active_override_flag) {
                sh.num_ref_idx_l0_active_minus1 = bs.bs_read_ue();
                if(sliceType == SLICEType::SLICE_TYPE_B) {
                    sh.num_ref_idx_l1_active_minus1 = bs.bs_read_ue();
                }
            }
        }
        // ===================== Syntax Start =====================
        EyerSyntax id_slice_pb(true, "slice_type == P || slice_type == SP || slice_type == B", syntax.GetLevel() + 1);
        {
            bool isA = sliceType == SLICEType::SLICE_TYPE_P || sliceType == SLICEType::SLICE_TYPE_SP || sliceType == SLICEType::SLICE_TYPE_B;
            id_slice_pb.Put(true && isA, "num_ref_idx_active_override_flag", sh.num_ref_idx_active_override_flag);
            EyerSyntax ifA(true && isA, "if(num_ref_idx_active_override_flag)", id_slice_pb.GetLevel() + 1);
            {
                bool isB = sh.num_ref_idx_active_override_flag;
                ifA.Put(true && isA && isB, "num_ref_idx_l0_active_minus1", sh.num_ref_idx_l0_active_minus1);
                EyerSyntax ifB(true && isA && isB, "sliceType == SLICEType::SLICE_TYPE_B", ifA.GetLevel() + 1);
                {
                    bool isC = sliceType == SLICEType::SLICE_TYPE_B;
                    ifB.Put(true && isA && isB && isC, "num_ref_idx_l1_active_minus1", sh.num_ref_idx_l1_active_minus1);
                }
                ifA.Put(ifB);
            }
            id_slice_pb.Put(ifA);
        }
        syntax.Put(id_slice_pb);
        // ===================== Syntax End =====================

        ReadRefPicListReordering(bs);

        if( (pps.weighted_pred_flag && (sliceType == SLICEType::SLICE_TYPE_P || sliceType == SLICEType::SLICE_TYPE_SP)) ||
            (pps.weighted_bipred_idc == 1 && sliceType == SLICEType::SLICE_TYPE_B))
        {
            ReadPredWeightTable(bs);
        }
        if(naluData.nal_ref_idc != NALRefIdc::NALU_PRIORITY_DISPOSABLE)
        {
            ReadDecRefPicMarking(bs);
        }

        if(pps.entropy_coding_mode_flag && sliceType != SLICEType::SLICE_TYPE_I && sliceType != SLICEType::SLICE_TYPE_SI) {
            sh.cabac_init_idc = bs.bs_read_ue();
        }
        sh.slice_qp_delta = bs.bs_read_se();
        // ===================== Syntax Start =====================
        EyerSyntax entropy_coding_mode_flag(true, "if(entropy_coding_mode_flag && slice_type != I && slice_type != SI)", syntax.GetLevel() + 1);
        {
            bool isA = pps.entropy_coding_mode_flag && sliceType != SLICEType::SLICE_TYPE_I && sliceType != SLICEType::SLICE_TYPE_SI;
            entropy_coding_mode_flag.Put(true && isA, "cabac_init_idc", sh.cabac_init_idc);
        }
        syntax.Put(entropy_coding_mode_flag);
        syntax.Put(true, "slice_qp_delta", sh.slice_qp_delta);
        // ===================== Syntax End =====================


        if(sliceType == SLICEType::SLICE_TYPE_SP || sliceType == SLICEType::SLICE_TYPE_SI){
            if(sliceType == SLICEType::SLICE_TYPE_SP){
                sh.sp_for_switch_flag = bs.bs_read_u1();
            }
            sh.slice_qs_delta = bs.bs_read_se();
        }
        // ===================== Syntax Start =====================
        EyerSyntax if_sp_si(true, "if(slice_type == SP || slice_type == slice_typeSI)", syntax.GetLevel() + 1);
        {
            bool isA = sliceType == SLICEType::SLICE_TYPE_SP || sliceType == SLICEType::SLICE_TYPE_SI;
            EyerSyntax if_sp(true && isA, "if(slice_type == SP)", if_sp_si.GetLevel() + 1);
            {
                bool isB = sliceType == SLICEType::SLICE_TYPE_SP;
                if_sp.Put(true && isA && isB, "sp_for_switch_flag", sh.sp_for_switch_flag);
            }
            if_sp_si.Put(if_sp);
        }
        syntax.Put(if_sp_si);
        // ===================== Syntax End =====================


        if(pps.deblocking_filter_control_present_flag) {
            sh.disable_deblocking_filter_idc = bs.bs_read_ue();
            if(sh.disable_deblocking_filter_idc != 1) {
                sh.slice_alpha_c0_offset_div2 = bs.bs_read_se();
                sh.slice_beta_offset_div2 = bs.bs_read_se();
            }
        }
        // ===================== Syntax Start =====================
        EyerSyntax if_deblocking(true, "if(deblocking_filter_control_present_flag)", syntax.GetLevel() + 1);
        {
            bool isA = pps.deblocking_filter_control_present_flag;
            if_deblocking.Put(true && isA, "disable_deblocking_filter_idc", sh.disable_deblocking_filter_idc);
            EyerSyntax if_deblocking_idc(true && isA, "if(sh.disable_deblocking_filter_idc != 1)", if_deblocking.GetLevel() + 1);
            {
                bool isB = sh.disable_deblocking_filter_idc != 1;
                if_deblocking_idc.Put(true && isA && isB, "slice_alpha_c0_offset_div2", sh.slice_alpha_c0_offset_div2);
                if_deblocking_idc.Put(true && isA && isB, "slice_beta_offset_div2", sh.slice_beta_offset_div2);
            }
            if_deblocking.Put(if_deblocking_idc);
        }
        syntax.Put(if_deblocking);
        // ===================== Syntax End =====================

        if(pps.num_slice_groups_minus1 > 0 && pps.slice_group_map_type >= 3 && pps.slice_group_map_type <= 5) {
            int v = intlog2( pps.pic_size_in_map_units_minus1 +  pps.slice_group_change_rate_minus1 + 1);
            sh.slice_group_change_cycle = bs.bs_read_u(v); // FIXME add 2?
        }
        // ===================== Syntax Start =====================
        EyerSyntax if_miaowu(true, "if(num_slice_groups_minus1 > 0 && slice_group_map_type >= 3 && slice_group_map_type <= 5)", syntax.GetLevel() + 1);
        {
            bool isA = pps.num_slice_groups_minus1 > 0 && pps.slice_group_map_type >= 3 && pps.slice_group_map_type <= 5;
            if_miaowu.Put(true && isA, "slice_group_change_cycle", sh.slice_group_change_cycle);
        }
        syntax.Put(if_miaowu);
        // ===================== Syntax End =====================

        return 0;
    }

    int EyerSLICEHeader::ReadRefPicListReordering(EyerBitStream & bs)
    {
        int level = 1;

        SLICEType sliceType = sh.slice_type;
        if(sliceType != SLICEType::SLICE_TYPE_I && sliceType != SLICEType::SLICE_TYPE_SI ){
            sh.rplr.ref_pic_list_reordering_flag_l0 = bs.bs_read_u1();
            if(sh.rplr.ref_pic_list_reordering_flag_l0) {
                int n = -1;
                do
                {
                    n++;
                    sh.rplr.reorder_l0.reordering_of_pic_nums_idc[n] = bs.bs_read_ue();
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
            if(sh.rplr.ref_pic_list_reordering_flag_l1) {
                int n = -1;
                do
                {
                    n++;
                    sh.rplr.reorder_l1.reordering_of_pic_nums_idc[n] = bs.bs_read_ue();
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

    int EyerSLICEHeader::ReadPredWeightTable(EyerBitStream & bs)
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

    int EyerSLICEHeader::ReadDecRefPicMarking(EyerBitStream & bs)
    {
        if(naluData.nal_unit_type == NALUType::NALU_TYPE_IDR) {
            sh.drpm.no_output_of_prior_pics_flag    = bs.bs_read_u1();
            sh.drpm.long_term_reference_flag        = bs.bs_read_u1();
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