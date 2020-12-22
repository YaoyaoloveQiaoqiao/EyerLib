#include "EyerMacroblock.hpp"
#include "EyerBitStream.hpp"
#include "EyerCAVLC.hpp"
#include "AVCTable.hpp"

#include <algorithm>
#include <cstdio>
#include <cmath>
#include <iostream>

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
                if(pps.transform_8x8_mode_flag && mbType == MB_TYPE::I_NxN){
                    transform_size_8x8_flag = bs.bs_read_u1();
                }
                MbPred(bs);
            }

            // EyerLog("Byte index: %d, bit offset: %d\n", bs.bits_left, bs.bits_left);

            if(mbType.MbPartPredMode() != MB_PART_PRED_MODE::Intra_16x16){
                uint32_t coded_block_pattern = bs.bs_read_me(sps.ChromaArrayType, mbType.MbPartPredMode());

                CodedBlockPatternLuma = coded_block_pattern % 16;
                CodedBlockPatternChroma = coded_block_pattern / 16;

                EyerLog("CBP: %d\n", coded_block_pattern);
                EyerLog("CodedBlockPatternLuma: %d\n", CodedBlockPatternLuma);
                EyerLog("CodedBlockPatternChroma: %d\n", CodedBlockPatternChroma);
            }

            if(CodedBlockPatternLuma > 0 || CodedBlockPatternChroma > 0 || mbType.MbPartPredMode() == MB_PART_PRED_MODE::Intra_16x16){
                int32_t mb_qp_delta = bs.bs_read_se();
                Residual(bs, 0, 15);
                // _Residual(bs, 0, 15);
            }
        }

        return 0;
    }

    int EyerMacroblock::MbPred(EyerBitStream & bs){
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
                intra_chroma_pred_mode = bs.bs_read_ue();
            }
        }
        else{
            // TODO B P
        }
        return 0;
    }

    int EyerMacroblock::Residual(EyerBitStream & bs, int startIdx, int endIdx)
    {
        ResidualLuma(bs, startIdx, endIdx);

        if(sps.ChromaArrayType == 1 || sps.ChromaArrayType == 2) {
            int NumC8x8 = 4 / (sps.SubWidthC * sps.SubHeightC);

            // 读取 DC 分量
            for (int iCbCr = 0; iCbCr < 2; iCbCr++) {
                if ((CodedBlockPatternChroma & 3) && startIdx == 0) {
                    // residual_block( ChromaDCLevel[ iCbCr ], 0, 4 * NumC8x8 − 1, 4 * NumC8x8 )
                    // ResidualBlockCavlc(bs, blockX, blockY, startIdx, endIdx);
                } else {
                    for (int i = 0; i < 4 * NumC8x8; i++) {
                        // ChromaDCLevel[ iCbCr ][ i ] = 0
                    }
                }
            }

            for (int iCbCr = 0; iCbCr < 2; iCbCr++){
                for(int i8x8 = 0; i8x8 < NumC8x8; i8x8++ ){

                }
            }
        }

        return 0;
    }

    int EyerMacroblock::ResidualLuma (EyerBitStream & bs, int startIdx, int endIdx)
    {
        if(startIdx == 0 && mbType.MbPartPredMode() == MB_PART_PRED_MODE::Intra_16x16){
            // 解 DC 分量
        }

        for(int i8x8Y = 0; i8x8Y < 4; i8x8Y += 2){
            for (int i8x8X = 0; i8x8X < 4; i8x8X += 2) {
                int i8x8 = 2 * (i8x8Y / 2) + i8x8X / 2;
                if(!transform_size_8x8_flag || !pps.entropy_coding_mode_flag){
                    for(int blockY = i8x8Y; blockY < i8x8Y + 2; blockY ++) {
                        for (int blockX = i8x8X; blockX < i8x8X + 2; blockX++) {
                            if(CodedBlockPatternLuma & (1 << i8x8)){
                                EyerLog("====================================(%d, %d)====================================\n", blockX, blockY);
                                EyerLog("有残差, x: %d, y: %d\n", blockX, blockY);
                                if(mbType.MbPartPredMode() == MB_PART_PRED_MODE::Intra_16x16){
                                    // 解 AC 分量
                                }
                                else{
                                    ResidualBlockCavlc(bs, blockX, blockY, startIdx, endIdx);
                                }
                            }
                            else if(mbType.MbPartPredMode() == MB_PART_PRED_MODE::Intra_16x16){
                                // 将所有 AC 分量赋值为 0 ， 一共 15 个
                            }
                            else{

                            }
                            if(!pps.entropy_coding_mode_flag && transform_size_8x8_flag){
                                // 8x8
                                for(int i = 0; i < 16; i++){
                                    // level8x8[ i8x8 ][ 4 * i + i4x4 ] = level4x4[ i8x8 * 4 + i4x4 ][ i ]
                                }
                            }
                        }
                    }
                }
                else if( CodedBlockPatternLuma & ( 1 << i8x8 ) ){
                    // residual_block( level8x8[ i8x8 ], 4 * startIdx, 4 * endIdx + 3, 64 )
                }
                else{
                    for(int i = 0; i < 64; i++ ){
                        // level8x8[ i8x8 ][ i ] = 0;
                    }
                }
            }
        }

        return 0;
    }

    int EyerMacroblock::ResidualBlockCavlc(EyerBitStream & bs, int blockX, int blockY, int startIdx, int endIdx)
    {
        int nC = GetNumberCurrent(blockX, blockY);

        int totleCoeff = 0;
        int trailingOnes = 0;

        EyerCAVLC cavlc;
        cavlc.Get_TotalCoeff_TrailingOnes(bs, totleCoeff, trailingOnes, nC);

        EyerLog("totleCoeff: %d, trailingOnes: %d\n", totleCoeff, trailingOnes);

        int levelVal[32] = {0};

        if(totleCoeff > 0){
            int suffixLength = 0;
            if(totleCoeff > 10 && trailingOnes < 3) {
                suffixLength = 1;
            }
            else {
                suffixLength = 0;
            }

            for(int i = 0; i < totleCoeff; i++) {
                if(i < trailingOnes) {
                    uint32_t trailing_ones_sign_flag = bs.bs_read_u1();
                    levelVal[i] = 1 - 2 * trailing_ones_sign_flag;
                }
                else{
                    // 读取 level_prefix
                    int level_prefix = 0;
                    while (!bs.bs_read_u1()) {
                        level_prefix++;
                    }
                    EyerLog("level_prefix: %d\n", level_prefix);

                    int levelSuffixSize = 0;
                    if (level_prefix == 14 && suffixLength == 0) {
                        levelSuffixSize = 4;
                    }
                    else if (level_prefix == 15) {
                        levelSuffixSize = level_prefix - 3;
                    }
                    else {
                        levelSuffixSize = suffixLength;
                    }

                    int level_suffix = 0;
                    if (levelSuffixSize > 0) {
                        level_suffix = bs.bs_read_u(levelSuffixSize);
                    }
                    else {
                        level_suffix = 0;
                    }

                    int levelCode = (std::min(15, level_prefix) << suffixLength) + level_suffix;
                    if (level_prefix >= 15 && suffixLength == 0) {
                        levelCode += 15;
                    }

                    if(level_prefix >= 16){
                        levelCode += (1 << ( level_prefix - 3)) - 4096;
                    }
                    if( i == trailingOnes && trailingOnes < 3 ){
                        levelCode += 2;
                    }
                    if( levelCode % 2 == 0 ){
                        levelVal[i] = ( levelCode + 2) >> 1;
                    }
                    else{
                        levelVal[i] = (-levelCode - 1) >> 1;
                    }
                    if( suffixLength == 0 ){
                        suffixLength = 1;
                    }
                    if(std::abs( levelVal[ i ] ) > (3 << ( suffixLength - 1 )) && suffixLength < 6 ) {
                        suffixLength++;
                    }
                }
            }



            int zerosLeft = 0;
            if(totleCoeff < endIdx - startIdx + 1) {
                int totalZeros = 0;
                get_total_zeros(bs, totalZeros, totleCoeff - 1);
                zerosLeft = totalZeros;
            }
            else{
                zerosLeft = 0;
            }
            EyerLog("zerosLeft: %d\n", zerosLeft);

            uint32_t runVal[32] = {0};
            for(int i = 0; i < totleCoeff - 1; i++) {
                int runBefore_vlcIdx = (zerosLeft - 1 < 6 ? zerosLeft - 1 : 6);
                if(zerosLeft > 0) {
                    int run_before;
                    get_run_before(bs, run_before, runBefore_vlcIdx);
                    runVal[ i ] = run_before;
                } else {
                    runVal[i] = 0;
                }
                zerosLeft = zerosLeft - runVal[i];
            }
            runVal[totleCoeff - 1] = zerosLeft;

            int coeffLevel[32] = {0};

            int coeffNum = -1;
            for(int i = totleCoeff - 1; i >= 0; i--) {
                coeffNum += runVal[i] + 1;
                coeffLevel[startIdx + coeffNum] = levelVal[i];

                // EyerLog("%d\n", levelVal[i]);
            }
            // EyerLog("coeffNum: %d\n", coeffNum);
        }

        lumaResidual[blockY][blockX].numCoeff = (uint8_t)totleCoeff;

        return 0;
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
                leftNum = GetLeftNeighborCoeffNum(leftIndex, x, y);
            }
            if(available_top){
                topNum = GetTopNeighborCoeffNum(topIndex, x, y);
            }

            nC = topNum + leftNum;
            if(available_left && available_top){
                nC++;
                nC = nC >> 1;
            }
            // EyerLog("nC top: %d, left: %d, nC: %d\n", topNum, leftNum, nC);
        }

        return nC;
    }

    int EyerMacroblock::GetTopNeighborCoeffNum(int topIdx, int blockX, int blockY)
    {
        int nzCeoff = 0;
        int target_idx_y = 0;
        if(topIdx == mbIndex){
            target_idx_y = blockY - 1;
            nzCeoff = lumaResidual[target_idx_y][blockX].numCoeff;
        }

        return nzCeoff;
    }

    int EyerMacroblock::GetLeftNeighborCoeffNum(int leftIdx, int blockX, int blockY)
    {
        int nzCeoff = 0;
        int target_idx_x = 0;
        if(leftIdx == mbIndex){
            target_idx_x = blockX - 1;
            nzCeoff = lumaResidual[blockY][target_idx_x].numCoeff;
        }

        return nzCeoff;
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

    int EyerMacroblock::get_coeff_level(EyerBitStream & bs, int &level, int levelIdx, int trailingOnes, int suffixLength)
    {
        int prefixLength = 0, level_prefix = 0, level_suffix = 0;
        int levelSuffixSize = 0, levelCode = 0, i = 0;

        while (!bs.bs_read_u1()) {
            level_prefix++;
        }
        EyerLog("level_prefix: %d\n", level_prefix);
        prefixLength = level_prefix + 1;
        if (level_prefix == 14 && suffixLength == 0) {
            levelSuffixSize = 4;
        }
        else if (level_prefix == 15) {
            levelSuffixSize = level_prefix - 3;
        }
        else {
            levelSuffixSize = suffixLength;
        }

        EyerLog("levelSuffixSize: %d\n", levelSuffixSize);
        if (levelSuffixSize > 0) {
            // level_suffix = Get_uint_code_num(m_pSODB, m_bypeOffset, m_bitOffset, levelSuffixSize);
            level_suffix = bs.bs_read_u(levelSuffixSize);
        }
        else {
            level_suffix = 0;
        }
        levelCode = (std::min(15, level_prefix) << suffixLength) + level_suffix;
        if (level_prefix >= 15 && suffixLength == 0) {
            levelCode += 15;
        }
        if (level_prefix >= 16) {
            levelCode += (1 << (level_prefix - 3)) - 4096;
        }
        if (levelIdx == 0 && trailingOnes < 3) {
            levelCode += 2;
        }

        if (levelCode % 2 == 0) {
            level = (levelCode + 2) >> 1;
        }
        else {
            level = (-levelCode - 1) >> 1;
        }

        return 0;
    }


    int EyerMacroblock::get_total_zeros(EyerBitStream & bs, int & totalZeros, int totalZeros_vlcIdx)
    {
        int totalZerosTable_Length[15][16] =
            {
                { 1,3,3,4,4,5,5,6,6,7,7,8,8,9,9,9 },
                { 3,3,3,3,3,4,4,4,4,5,5,6,6,6,6 },
                { 4,3,3,3,4,4,3,3,4,5,5,6,5,6 },
                { 5,3,4,4,3,3,3,4,3,4,5,5,5 },
                { 4,4,4,3,3,3,3,3,4,5,4,5 },
                { 6,5,3,3,3,3,3,3,4,3,6 },
                { 6,5,3,3,3,2,3,4,3,6 },
                { 6,4,5,3,2,2,3,3,6 },
                { 6,6,4,2,2,3,2,5 },
                { 5,5,3,2,2,2,4 },
                { 4,4,3,3,1,3 },
                { 4,4,2,1,3 },
                { 3,3,1,2 },
                { 2,2,1 },
                { 1,1 }
            };

        int totalZerosTable_Code[15][16] =
            {
                { 1,3,2,3,2,3,2,3,2,3,2,3,2,3,2,1 },
                { 7,6,5,4,3,5,4,3,2,3,2,3,2,1,0 },
                { 5,7,6,5,4,3,4,3,2,3,2,1,1,0 },
                { 3,7,5,4,6,5,4,3,3,2,2,1,0 },
                { 5,4,3,7,6,5,4,3,2,1,1,0 },
                { 1,1,7,6,5,4,3,2,1,1,0 },
                { 1,1,5,4,3,3,2,1,1,0 },
                { 1,1,1,3,3,2,2,1,0 },
                { 1,0,1,3,2,1,1,1, },
                { 1,0,1,3,2,1,1, },
                { 0,1,1,2,1,3 },
                { 0,1,1,1,1 },
                { 0,1,1,1 },
                { 0,1,1 },
                { 0,1 }
            };

        int err = 0;
        int idx2 = 0;
        int idx1 = 0;
        int *lengthTable = &totalZerosTable_Length[totalZeros_vlcIdx][0];
        int *codeTable = &totalZerosTable_Code[totalZeros_vlcIdx][0];
        err = AVCTable::SearchForValueIn2DTable(bs, totalZeros, idx1, idx2, lengthTable, codeTable, 16, 1);
        if (err < 0) {
            return err;
        }

        return 0;
    }


    int EyerMacroblock::get_run_before(EyerBitStream & bs, int & runBefore, int runBefore_vlcIdx)
    {
        int runBeforeTable_Length[15][16] =
            {
                { 1,1 },
                { 1,2,2 },
                { 2,2,2,2 },
                { 2,2,2,3,3 },
                { 2,2,3,3,3,3 },
                { 2,3,3,3,3,3,3 },
                { 3,3,3,3,3,3,3,4,5,6,7,8,9,10,11 }
            };

        int runBeforeTable_Code[15][16] =
            {
                { 1,0 },
                { 1,1,0 },
                { 3,2,1,0 },
                { 3,2,1,1,0 },
                { 3,2,3,2,1,0 },
                { 3,0,1,3,2,5,4 },
                { 7,6,5,4,3,2,1,1,1,1,1,1,1,1,1 }
            };


        int idx1 = 0;
        int idx2 = 0, err = 0;
        int *lengthTable = &runBeforeTable_Length[runBefore_vlcIdx][0];
        int *codeTable = &runBeforeTable_Code[runBefore_vlcIdx][0];
        err = AVCTable::SearchForValueIn2DTable(bs, runBefore, idx1, idx2, lengthTable, codeTable, 16, 1);
        if (err < 0)
        {
            return err;
        }

        return 0;
    }
}