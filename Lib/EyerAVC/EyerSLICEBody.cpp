#include "EyerSLICEBody.hpp"
#include "I_MB_TYPE.hpp"
#include "MB_TYPE.hpp"

namespace Eyer
{
    EyerSLICEBody::EyerSLICEBody()
    {

    }

    EyerSLICEBody::~EyerSLICEBody()
    {

    }

    int EyerSLICEBody::Parse(EyerBitStream & bs, EyerFieldList & fieldList, EyerSPS & _sps, EyerPPS & _pps, EyerSLICEHeader & _sliceHeader)
    {
        sps = _sps;
        pps = _pps;
        sliceHeader = _sliceHeader;

        if(!sps.isValid()){
            return -1;
        }
        if(!pps.isValid()){
            return -1;
        }

        if(pps.entropy_coding_mode_flag){
            // 进行对齐操作
            while(!bs.bs_byte_aligned()) {
                /* cabac_alignment_one_bit */
                bs.bs_read_u1();
            }
        }

        int MbaffFrameFlag = sps.mb_adaptive_frame_field_flag && !sliceHeader.sh.field_pic_flag;
        int CurrMbAddr = sliceHeader.sh.first_mb_in_slice * (1 + MbaffFrameFlag);
        int moreDataFlag = 1;
        int prevMbSkipped = 0;

        do{
            if(sliceHeader.GetSLICEType() != SLICEType::SLICE_TYPE_I && sliceHeader.GetSLICEType() != SLICEType::SLICE_TYPE_SI) {
                if (!pps.entropy_coding_mode_flag) {

                }
                else{

                }
            }

            if(moreDataFlag){
                if(MbaffFrameFlag && (CurrMbAddr % 2 == 0 || (CurrMbAddr % 2 == 1 && prevMbSkipped))){
                    uint32_t mb_field_decoding_flag = bs.bs_read_u1();
                }

                macroblock_layer(sliceHeader.GetSLICEType() ,bs);
            }
            if(!pps.entropy_coding_mode_flag){
                moreDataFlag = bs.more_data();
            }
            else {
                if(sliceHeader.GetSLICEType() != SLICEType::SLICE_TYPE_I && sliceHeader.GetSLICEType() != SLICEType::SLICE_TYPE_SI){
                    //TODO prevMbSkipped = mb_skip_flag;
                }
                if(MbaffFrameFlag && CurrMbAddr % 2 == 0){
                    moreDataFlag = 1;
                }
                else {
                    uint32_t end_of_slice_flag = bs.bs_read_ae();
                    moreDataFlag = !end_of_slice_flag;
                }
            }

            //TODO CurrMbAddr = NextMbAddress(CurrMbAddr);

            //TODO DEBUG
            moreDataFlag = 0;
        }
        while (moreDataFlag);

        return 0;
    }

    int EyerSLICEBody::macroblock_layer(SLICEType sliceType, EyerBitStream & bs)
    {
        //TODO
        uint32_t mb_type = 0;
        if(!pps.entropy_coding_mode_flag){
            mb_type = bs.bs_read_ue();
        }
        else {
            // TODO ae(v)
            // mb_type = bs.bs_read_ae();
        }

        MB_TYPE mbType = MB_TYPE::Select(sliceType, mb_type);

        if(MB_TYPE::I_PCM == mbType){
            //TODO PCM
        }
        else{
            int noSubMbPartSizeLessThan8x8Flag = 1;
            if(
                    mbType != MB_TYPE::I_NxN &&
                    mbType.MbPartPredMode() != MB_PART_PRED_MODE::Intra_16x16 &&
                    mbType.MunMbPart() == 4
            ){
                // TODO B P Slice
            }
            else{
                uint8_t transform_size_8x8_flag = 0;
                if(pps.transform_8x8_mode_flag && mbType == MB_TYPE::I_NxN){
                    transform_size_8x8_flag = bs.bs_read_u1();
                }
                mb_pred(mbType, bs);
            }
            if(mbType.MbPartPredMode() != MB_PART_PRED_MODE::Intra_16x16){
                uint32_t coded_block_pattern = bs.bs_read_me(sps.ChromaArrayType, mbType.MbPartPredMode());
            }
        }

        return 0;
    }

    int EyerSLICEBody::mb_pred(MB_TYPE mbType, EyerBitStream & bs){
        if(
                mbType.MbPartPredMode() == MB_PART_PRED_MODE::Intra_4x4 ||
                mbType.MbPartPredMode() == MB_PART_PRED_MODE::Intra_8x8 ||
                mbType.MbPartPredMode() == MB_PART_PRED_MODE::Intra_16x16
        ){
            if(mbType.MbPartPredMode() == MB_PART_PRED_MODE::Intra_4x4){
                uint32_t prev_intra4x4_pred_mode_flag[16];
                memset(prev_intra4x4_pred_mode_flag, 0, 16 * sizeof(uint32_t));
                uint32_t rem_intra4x4_pred_mode_flag[16];
                memset(rem_intra4x4_pred_mode_flag, 0, 16 * sizeof(uint32_t));
                for(int luma4x4BlkIdx=0; luma4x4BlkIdx<16; luma4x4BlkIdx++){
                    prev_intra4x4_pred_mode_flag[luma4x4BlkIdx] = bs.bs_read_u1();
                    if(!prev_intra4x4_pred_mode_flag[luma4x4BlkIdx]){
                        rem_intra4x4_pred_mode_flag[luma4x4BlkIdx] = bs.bs_read_u(3);
                    }
                }

                int a = 14;
                a = prev_intra4x4_pred_mode_flag[0];
            }
        }
        return 0;
    }
}