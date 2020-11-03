#include "EyerSLICE.hpp"

namespace Eyer
{
    EyerSLICE::EyerSLICE(EyerSPS & _sps, EyerPPS & _pps)
    {
        sps = _sps;
        pps = _pps;
    }

    EyerSLICE::~EyerSLICE()
    {

    }

    int EyerSLICE::Parse()
    {
        if(!sps.isValid()){
            return -1;
        }
        if(!pps.isValid()){
            return -1;
        }

        EyerNALU::Parse();

        EyerBitStream bs(naluData.GetSODBBuffer());
        ParseHeadPartA(bs);

        // TODO Select SPS PPS

        ParseHeadPartB(bs);

        valid = true;

        return 0;
    }

    int EyerSLICE::ParseHeadPartA(EyerBitStream & bs)
    {
        sh.first_mb_in_slice           = bs.bs_read_ue();
        sh.slice_type                  = bs.bs_read_ue();
        sh.pic_parameter_set_id        = bs.bs_read_ue();

        fieldList.push_back(new EyerField("first_mb_in_slice",                             sh.first_mb_in_slice));
        fieldList.push_back(new EyerField("slice_type",                                    sh.slice_type));
        fieldList.push_back(new EyerField("pic_parameter_set_id",                          sh.pic_parameter_set_id));

        return 0;
    }

    int EyerSLICE::ParseHeadPartB(EyerBitStream & bs)
    {
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

        SLICEType sliceType = sh.slice_type;
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

        ReadRefPicListReordering(bs);

        if( (pps.weighted_pred_flag && (sliceType == SLICEType::SLICE_TYPE_P || sliceType == SLICEType::SLICE_TYPE_SP)) ||
            (pps.weighted_bipred_idc == 1 && sliceType == SLICEType::SLICE_TYPE_B))
        {
            // TODO read_pred_weight_table(h, b);
        }
        if(naluData.nal_ref_idc != NALRefIdc::NALU_PRIORITY_DISPOSABLE)
        {
            // TODO read_dec_ref_pic_marking(h, b);
        }

        return 0;
    }

    int EyerSLICE::ReadRefPicListReordering(EyerBitStream & bs)
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


        if(sliceType != SLICEType::SLICE_TYPE_B)
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
                    if( sh.rplr.reorder_l1.reordering_of_pic_nums_idc[n] == 0 ||
                        sh.rplr.reorder_l1.reordering_of_pic_nums_idc[n] == 1 )
                    {
                        sh.rplr.reorder_l1.abs_diff_pic_num_minus1[ n ] = bs.bs_read_ue();
                    }
                    else if( sh.rplr.reorder_l1.reordering_of_pic_nums_idc[ n ] == 2 )
                    {
                        sh.rplr.reorder_l1.long_term_pic_num[ n ] = bs.bs_read_ue();
                    }
                } while( sh.rplr.reorder_l1.reordering_of_pic_nums_idc[ n ] != 3 && ! bs.bs_eof() );
            }
        }


        return 0;
    }
}