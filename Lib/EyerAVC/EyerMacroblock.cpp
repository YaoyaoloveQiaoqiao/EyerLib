#include "EyerMacroblock.hpp"
#include "EyerBitStream.hpp"

namespace Eyer
{
    EyerMacroblock::EyerMacroblock(int _mbIndex)
    {
        mbIndex = _mbIndex;
    }

    EyerMacroblock::~EyerMacroblock()
    {

    }

    int EyerMacroblock::Parse(EyerBitStream & bs, EyerSPS & _sps, EyerPPS & _pps, EyerSLICEHeader & _sliceHeader)
    {
        sps = _sps;
        pps = _pps;
        sliceHeader = _sliceHeader;

        SLICEType sliceType = sliceHeader.GetSLICEType();

        //TODO
        uint32_t mb_type = 0;
        if(!pps.entropy_coding_mode_flag){
            mb_type = bs.bs_read_ue();
        }
        else {
            // TODO ae(v)
            // mb_type = bs.bs_read_ae();
        }

        mbType = MB_TYPE::Select(sliceType, mb_type);
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
                mb_pred(bs);
            }

            if(mbType.MbPartPredMode() != MB_PART_PRED_MODE::Intra_16x16){
                uint32_t coded_block_pattern = bs.bs_read_me(sps.ChromaArrayType, mbType.MbPartPredMode());
                CodecBlockPatterLuma = coded_block_pattern % 16;
                CodecBlockPatterChroma = coded_block_pattern / 16;
            }

            if(CodecBlockPatterLuma > 0 || CodecBlockPatterChroma > 0 || mbType.MbPartPredMode() == MB_PART_PRED_MODE::Intra_16x16){
                int32_t mb_qp_delta = bs.bs_read_se();
                residual(bs);
            }
        }

        return 0;
    }

    int EyerMacroblock::mb_pred(EyerBitStream & bs){
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
            }

            if(mbType.MbPartPredMode() == MB_PART_PRED_MODE::Intra_8x8){
                uint32_t prev_intra8x8_pred_mode_flag[4];
                memset(prev_intra8x8_pred_mode_flag, 0, 4 * sizeof(uint32_t));
                uint32_t rem_intra8x8_pred_mode_flag[4];
                memset(rem_intra8x8_pred_mode_flag, 0, 4 * sizeof(uint32_t));
                for(int luma8x8BlkIdx=0; luma8x8BlkIdx<4; luma8x8BlkIdx++){
                    prev_intra8x8_pred_mode_flag[luma8x8BlkIdx] = bs.bs_read_u1();
                    if(!prev_intra8x8_pred_mode_flag[luma8x8BlkIdx]){
                        rem_intra8x8_pred_mode_flag[luma8x8BlkIdx] = bs.bs_read_u(3);
                    }
                }
            }

            if(sps.ChromaArrayType == 1 || sps.ChromaArrayType == 2){
                uint32_t intra_chrome_pred_mode = bs.bs_read_ue();
            }
        }
        else{
            // TODO B P
        }
        return 0;
    }

    int EyerMacroblock::residual(EyerBitStream & bs)
    {
        if(CodecBlockPatterLuma){
            int index8x8 = 0;
            int blockX = 0;
            int blockY = 0;
            int blockSubIndexX = 0;
            int blockSubIndexY = 0;
            for(blockY = 0; blockY < 4; blockY += 2){
                for(blockX = 0; blockX < 4; blockX += 2){
                    EyerLog("8x8 Block\n");
                    if(!pps.entropy_coding_mode_flag){
                        //CAVLC
                        for(blockSubIndexY = blockY; blockSubIndexY < blockY + 2; blockSubIndexY ++){
                            for(blockSubIndexX = blockX; blockSubIndexX < blockX + 2; blockSubIndexX ++){
                                index8x8 = 2 * (blockY / 2) + blockX / 2;
                                if(CodecBlockPatterLuma & (1 << index8x8)){
                                    EyerLog("有残差，Block X: %d, Y: %d, Sub X: %d, Sub Y: %d\n", blockX, blockY, blockSubIndexX, blockSubIndexY);
                                    lumaResidual[blockSubIndexY][blockSubIndexX].emptyBlock = true;
                                    get_luma_coeff(blockSubIndexX, blockSubIndexY);
                                }
                                else{
                                    EyerLog("无残差，Block X: %d, Y: %d, Sub X: %d, Sub Y: %d\n", blockX, blockY, blockSubIndexX, blockSubIndexY);
                                    lumaResidual[blockSubIndexY][blockSubIndexX].emptyBlock = false;
                                }
                            }
                        }
                    }
                    else{
                        //CABAC
                    }
                }
            }
        }
        return 0;
    }

    int EyerMacroblock::get_luma_coeff(int x, int y)
    {
        int err;

        // int blockType =
        if(mbType.MbPartPredMode() == MB_PART_PRED_MODE::Intra_16x16 || mbType == MB_TYPE::I_PCM){
            // LUMA_INTRA16x16AC
        }
        else{
            // LUMA
        }

        int max_ceoff_number = 0;
        int numCoeff_vlcIdx = 0, prefixLength = 0, suffixLength = 0, level_prefix = 0, level_suffix = 0;
        int levelSuffixSize = 0, levelCode = 0, i = 0;

        int numberCurrent; //nC

        numberCurrent = GetNumberCurrent(x, y);
        if (numberCurrent < 2){
            numCoeff_vlcIdx = 0;
        }
        else if(numberCurrent < 4){
            numCoeff_vlcIdx = 1;
        }
        else if(numberCurrent < 8){
            numCoeff_vlcIdx = 2;
        }
        else{
            numCoeff_vlcIdx = 3;
        }

        // NumberCeoff
        uint8_t numCoeff = 0;
        uint8_t trailingOnes = 0;

        int token = 0;



        return err;
    }

    int EyerMacroblock::GetNumberCurrent(int x, int y)
    {
        int nC = 0;
        int topIndex = 0;
        int leftIndex = 0;
        int topNum = 0;
        int leftNum = 0;

        bool available_top = false;
        bool available_left = false;

        GetNeighborAvailable(available_top, available_left, topIndex, leftIndex, x, y);

        if(!available_left && !available_top){
            nC = 0;
        }
        else{
            if(available_left){
                // TODO
                topNum;
            }
            if(available_top){
                // TODO
                leftNum;
            }
            nC = topNum + leftNum;
            if(available_left && available_top){
                nC++;
                nC >> 1;
            }
        }

        return nC;
    }

    int EyerMacroblock::GetNeighborAvailable(bool & available_top, bool & available_left, int & topIndex, int & leftIndex, int blockIndexX, int blockIndexY){

        int width_in_mb = sps.pic_width_in_mbs_minus1 + 1;
        int height_in_mb = sps.pic_height_in_map_units_minus1 + 1;

        bool left_egde_mb = (mbIndex % width_in_mb == 0);
        bool top_egde_mb = (mbIndex < width_in_mb);

        if(!top_egde_mb){
            available_top = true;
            topIndex = mbIndex - width_in_mb;
        }
        else{
            if(blockIndexY == 0){
                available_top = false;
            }
            else{
                available_top = true;
                topIndex = mbIndex;
            }
        }

        if(!left_egde_mb){
            available_left = true;
            leftIndex = mbIndex - 1;
        }
        else{
            if(blockIndexX == 0){
                available_left = false;
            }
            else{
                available_left = true;
                leftIndex = mbIndex;
            }
        }

        return 0;
    }
}