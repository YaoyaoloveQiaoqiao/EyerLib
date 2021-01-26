#include "EyerMacroblock.hpp"
#include "EyerBitStream.hpp"
#include "EyerCAVLC.hpp"
#include "AVCTable.hpp"

#include "EyerSLICEBody.hpp"

#include <algorithm>
#include <cstdio>
#include <cmath>
#include <iostream>

namespace Eyer
{
    EyerMacroblock::EyerMacroblock()
    {
        mbIndex = -1;
        mbAddrA = nullptr;
        mbAddrB = nullptr;
        mbAddrC = nullptr;
        mbAddrD = nullptr;
    }

    EyerMacroblock::EyerMacroblock(int _mbIndex, EyerMacroblock * _mbAddrA, EyerMacroblock * _mbAddrB, EyerMacroblock * _mbAddrC, EyerMacroblock * _mbAddrD)
    {
        mbIndex = _mbIndex;
        if(_mbAddrA != nullptr){
            mbAddrA = new EyerMacroblock(*_mbAddrA);
        }
        if(_mbAddrB != nullptr){
            mbAddrB = new EyerMacroblock(*_mbAddrB);
        }
        if(_mbAddrC != nullptr){
            mbAddrC = new EyerMacroblock(*_mbAddrC);
        }
        if(_mbAddrD != nullptr){
            mbAddrD = new EyerMacroblock(*_mbAddrD);
        }
    }

    EyerMacroblock::~EyerMacroblock()
    {
        if(mbAddrA != nullptr){
            delete mbAddrA;
            mbAddrA = nullptr;
        }
        if(mbAddrB != nullptr){
            delete mbAddrB;
            mbAddrB = nullptr;
        }
        if(mbAddrC != nullptr){
            delete mbAddrC;
            mbAddrC = nullptr;
        }
        if(mbAddrD != nullptr){
            delete mbAddrD;
            mbAddrD = nullptr;
        }
    }

    int EyerMacroblock::Parse(EyerBitStream & bs, EyerSPS & _sps, EyerPPS & _pps, EyerSLICEHeader & _sliceHeader)
    {
        EyerLog("===========================EyerMacroblock: %d===========================\n", mbIndex);
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
        EyerLog("\tMacroblock Type: %s\n", mbType.GetStr().str);

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

            if(mbType.MbPartPredMode() != MB_PART_PRED_MODE::Intra_16x16){
                uint32_t coded_block_pattern = bs.bs_read_me(sps.ChromaArrayType, mbType.MbPartPredMode());

                CodedBlockPatternLuma = coded_block_pattern % 16;
                CodedBlockPatternChroma = coded_block_pattern / 16;

                EyerLog("\tCodedBlockPattern(CBP): %d\n", coded_block_pattern);
                EyerLog("\tCodedBlockPattern(CBP) Luma Part: %d\n", CodedBlockPatternLuma);
                EyerLog("\tCodedBlockPattern(CBP) Chroma Part: %d\n", CodedBlockPatternChroma);
            }

            if(CodedBlockPatternLuma > 0 || CodedBlockPatternChroma > 0 || mbType.MbPartPredMode() == MB_PART_PRED_MODE::Intra_16x16){
                int32_t mb_qp_delta = bs.bs_read_se();
                EyerLog("\tmb_qp_delta: %d\n", mb_qp_delta);
                Residual(bs, 0, 15);
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


        EyerLog("\t===========================Residual Chroma===========================\n");
        if(sps.ChromaArrayType == 1 || sps.ChromaArrayType == 2) {
            int NumC8x8 = 4 / (sps.SubWidthC * sps.SubHeightC);
            EyerLog("\tSubWidthC: %d, SubHeightC: %d\n", sps.SubWidthC, sps.SubHeightC);
            EyerLog("\tNumC8x8: %d\n", NumC8x8);

            EyerLog("\t\txxxxxxxxxxxxxxxxxxxxxxxx Chroma DC xxxxxxxxxxxxxxxxxxxxxxxx\n");
            // 读取 DC 分量
            for (int iCbCr = 0; iCbCr < 2; iCbCr++) {
                EyerLog("\t\t\txxxxxxxxxxxxxxxx Chroma DC : %d xxxxxxxxxxxxxxxx\n", iCbCr);
                if ((CodedBlockPatternChroma & 3) && startIdx == 0) {
                    int nC = 0;
                    if(sps.ChromaArrayType == 1){
                        nC = -1;
                    }
                    if(sps.ChromaArrayType == 2){
                        nC = -2;
                    }
                    int totleCoeff = 0;
                    ResidualBlockCavlc(bs, chromaResidualDC[iCbCr], nC, 0, 4 * NumC8x8 - 1, 4 * NumC8x8, true);
                } else {
                    EyerERROR("Chroma DC Error\n");
                    for (int i = 0; i < 4 * NumC8x8; i++) {

                    }
                }
            }

            for (int iCbCr = 0; iCbCr < 2; iCbCr++){
                EyerLog("\t\txxxxxxxxxxxxxxxxxxxxxxxx Chroma AC xxxxxxxxxxxxxxxxxxxxxxxx\n");
                for(int i8x8 = 0; i8x8 < NumC8x8; i8x8++ ){
                    for(int i4x4 = 0; i4x4 < 4; i4x4++ ){
                        if(CodedBlockPatternChroma & 2){
                            int totleCoeff = 0;
                            if(iCbCr == 0){
                                // Cb
                                EyerLog("\t\t\txxxxxxxxxxxxxxxx Chroma AC Cb : %d xxxxxxxxxxxxxxxx\n", i4x4);
                                int nC = GetNumberCurrent(i8x8, i4x4, RESIDUAL_TYPE::CHROMA_CB);
                                ResidualBlockCavlc(bs, chromaCbResidualAC[i8x8][i4x4], nC, std::max(0, startIdx - 1), endIdx - 1, 15);
                            }
                            if(iCbCr == 1){
                                // Cr
                                EyerLog("\t\t\txxxxxxxxxxxxxxxx Chroma AC Cr : %d xxxxxxxxxxxxxxxx\n", i4x4);
                                int nC = GetNumberCurrent(i8x8, i4x4, RESIDUAL_TYPE::CHROMA_CR);
                                ResidualBlockCavlc(bs, chromaCrResidualAC[i8x8][i4x4], nC, std::max(0, startIdx - 1), endIdx - 1, 15);
                            }
                        }
                        else{
                            EyerERROR("Chroma NO AC\n");
                        }
                    }
                }
            }
        }

        return 0;
    }

    int EyerMacroblock::ResidualLuma (EyerBitStream & bs, int startIdx, int endIdx)
    {
        EyerLog("\t===========================Residual Luma===========================\n");

        if(startIdx == 0 && mbType.MbPartPredMode() == MB_PART_PRED_MODE::Intra_16x16){
            // 解 DC 分量
        }

        for(int i8x8 = 0; i8x8 < 4; i8x8++){
            if(!transform_size_8x8_flag || !pps.entropy_coding_mode_flag){
                for(int i4x4 = 0; i4x4 < 4; i4x4++) {
                    if(CodedBlockPatternLuma & (1 << i8x8)){
                        EyerLog("\t\txxxxxxxxxxxxxxxx Luma 4x4 (i8x8: %d, i4x4: %d) xxxxxxxxxxxxxxxx\n", i8x8, i4x4);
                        EyerLog("\t\t有残差, i8x8: %d, i4x4: %d\n", i8x8, i4x4);
                        if(mbType.MbPartPredMode() == MB_PART_PRED_MODE::Intra_16x16){
                            // 解 AC 分量
                            EyerLog("Intra_16x16 AC\n");
                        }
                        else{
                            EyerLog("\t\tLUMA 4x4\n");
                            int nC = GetNumberCurrent(i8x8, i4x4, RESIDUAL_TYPE::LUMA);
                            int totleCoeff = 0;
                            ResidualBlockCavlc(bs, lumaResidual[i8x8][i4x4], nC, startIdx, endIdx, 16);
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
            else if( CodedBlockPatternLuma & ( 1 << i8x8 ) ){
                // residual_block( level8x8[ i8x8 ], 4 * startIdx, 4 * endIdx + 3, 64 )
            }
            else{
                for(int i = 0; i < 64; i++ ){
                    // level8x8[ i8x8 ][ i ] = 0;
                }
            }
        }

        return 0;
    }

    int EyerMacroblock::ResidualBlockCavlc(EyerBitStream & bs, EyerCoeff4x4Block & coeff4x4Block, int nC, int startIdx, int endIdx, int maxNumCoeff, bool isChromaDC)
    {
        EyerLog("\t\t\tCAVLC:\n");
        EyerLog("\t\t\tnC: %d\n", nC);

        int totleCoeff = 0;
        int trailingOnes = 0;

        EyerCAVLC cavlc;
        cavlc.Get_TotalCoeff_TrailingOnes(bs, totleCoeff, trailingOnes, nC);

        EyerLog("\t\t\t\tTotleCoeff: %d, TrailingOnes: %d\n", totleCoeff, trailingOnes);

        coeff4x4Block.totleCoeff = totleCoeff;
        coeff4x4Block.trailingOnes = trailingOnes;

        if (totleCoeff) {
            EyerLog("\t\t\t\tGet trailing_ones_sign_flag(逆序):\n");
            if (trailingOnes){
                for(int i=0;i<trailingOnes;i++){
                    uint32_t trailing_ones_sign_flag = bs.bs_read_u1();
                    EyerLog("\t\t\t\t\ttrailing_ones_sign_flag[%d]: %d\n", i, trailing_ones_sign_flag);
                    coeff4x4Block.trailingSign[i] = trailing_ones_sign_flag;
                }
            }

            EyerLog("\t\t\t\tGet levels: \n");
            // 读取非零系数的振幅
            int suffixLength = 0;
            if(totleCoeff > 10 && trailingOnes < 3) {
                suffixLength = 1;
            }
            else{
                suffixLength = 0;
            }
            for(int k=0; k<totleCoeff - trailingOnes; k++) {
                // Get levels
                int levelVal = 0;
                get_coeff_level(bs, levelVal, k, trailingOnes, suffixLength);
                if(suffixLength == 0){
                    suffixLength = 1;
                }
                if(abs(levelVal) > (3 << (suffixLength - 1)) && (suffixLength < 6)){
                    suffixLength++;
                }

                EyerLog("\t\t\t\t\tlevels[%d]: %d\n", k, levelVal);
                coeff4x4Block.levels[k] = levelVal;
            }

            EyerLog("\t\t\t\tGet totle zeros: \n");
            // Totle Zeros 对于 Chrome DC 的 SubBlock，是不一样的。
            int totleZeros = 0;
            if(totleCoeff < maxNumCoeff) {
                if(isChromaDC){
                    get_total_zeros_chrome_dc(bs, totleZeros, totleCoeff - 1);
                }else{
                    get_total_zeros(bs, totleZeros, totleCoeff - 1);
                }
            }
            else{
                totleZeros = 0;
            }
            EyerLog("\t\t\t\t\ttotle zeros: %d\n", totleZeros);
            coeff4x4Block.totleZeros = totleZeros;

            EyerLog("\t\t\t\tGet Run Before: \n");
            // Run Before
            int runBeforeVlcIdx = 0;
            int zerosLeft = totleZeros;
            int i = totleCoeff - 1;
            int run = 0;
            if(zerosLeft > 0 && i > 0){
                do{
                    runBeforeVlcIdx = (zerosLeft - 1 < 6) ? zerosLeft - 1 : 6;
                    get_run_before(bs, run, runBeforeVlcIdx);

                    EyerLog("\t\t\t\t\tRun Before: %d\n", run);
                    coeff4x4Block.runBefore[i] = run;

                    zerosLeft -= run;
                    i--;
                }while(zerosLeft != 0 && i != 0);
            }
            else {
                run = 0;
            }
        }

        EyerLog("\t\t\t\tRestore: \n");

        int SNAL_SCAN[16][2] = {
                {0, 0}, {1, 0}, {0, 1}, {0, 2},
                {1, 1}, {2, 0}, {3, 0}, {2, 1},
                {1, 2}, {0, 3}, {1, 3}, {2, 2},
                {3, 1}, {3, 2}, {2, 3}, {3, 3}
        };

        int coeffNum[16] = {0};
        // trailingOnes
        for(int i=coeff4x4Block.totleCoeff - 1, j = trailingOnes - 1; j >= 0; j--) {
            if(coeff4x4Block.trailingSign[j] == 1){
                coeffNum[i--] = -1;
            }
            else{
                coeffNum[i--] = 1;
            }
        }
        // levels
        for(int i=coeff4x4Block.totleCoeff - coeff4x4Block.trailingOnes - 1; i >= 0; i--) {
            coeffNum[i] = coeff4x4Block.levels[coeff4x4Block.totleCoeff - coeff4x4Block.trailingOnes - 1 - i];
        }
        // runbefore
        int totleZeros = coeff4x4Block.totleZeros;
        for(int i=coeff4x4Block.totleCoeff - 1; i > 0; i--) {
            swap(coeffNum[i], coeffNum[i+totleZeros]);
            totleZeros -= coeff4x4Block.runBefore[i];
        }
        swap(coeffNum[0], coeffNum[totleZeros]);


        EyerString logStr = "";
        for(int i=0;i<16;i++){
            logStr = logStr + EyerString::Number(coeffNum[i]) + " ";
        }
        EyerLog("\t\t\t\t\t%s\n", logStr.str);

        int coeffBuf[4][4] = {0};
        int residualBuf[4][4] = {0};

        for(int i=0;i<16;i++){
            int * s = SNAL_SCAN[i];
            coeffBuf[s[0]][s[1]] = coeffNum[i];
        }

        EyerLog("\n\n");
        for(int i=0;i<4;i++){
            EyerString line = "";
            for(int j=0;j<4;j++){
                line = line + EyerString::Number(coeffBuf[i][j], "%4d") + " ";
            }
            EyerLog("\t\t\t\t\t%s\n", line.str);
        }

        // 水平变换
        int temp1[4] = {0};
        int temp2[4] = {0};
        for(int j=0;j<4;j++){
            for(int i=0;i<4;i++){
                temp1[i] = coeffBuf[i][j];
            }
            temp2[0] = temp1[0] + temp1[2];
            temp2[1] = temp1[0] - temp1[2];
            temp2[2] = (temp1[1] >> 1) - temp1[3];
            temp2[3] = temp1[1] + (temp1[3] >> 1);

            for(int i=0;i<2;i++){
                int i1 = 3 - i;
                residualBuf[i][j] = temp2[i] + temp2[i1];
                residualBuf[i1][j] = temp2[i] - temp2[i1];
            }
        }

        // 垂直变换
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                temp1[j] = residualBuf[i][j];
            }
            temp2[0] = temp1[0] + temp1[2];
            temp2[1] = temp1[0] - temp1[2];
            temp2[2] = (temp1[1] >> 1) - temp1[3];
            temp2[3] = temp1[1] + (temp1[3] >> 1);

            for(int j=0;j<2;j++){
                int j1 = 3 - j;
                residualBuf[i][j] = temp2[j] + temp2[j1];
                residualBuf[i][j1] = temp2[j] - temp2[j1];
            }
        }

        EyerLog("\n\n");
        for(int i=0;i<4;i++){
            EyerString line = "";
            for(int j=0;j<4;j++){
                line = line + EyerString::Number(residualBuf[i][j], "%4d") + " ";
            }
            EyerLog("\t\t\t\t\t%s\n", line.str);
        }

        return 0;
    }

    int EyerMacroblock::RestoreCoeffMatrix()
    {
        uint32_t cbpLuma = CodedBlockPatternLuma;
        uint32_t cbpChroma = CodedBlockPatternChroma;

        if(mbType == MB_TYPE::I_NxN){

        }

        return 0;
    }

    int EyerMacroblock::GetNumberCurrent(int i8x8, int i4x4, RESIDUAL_TYPE & type)
    {
        int nC = 0;

        EyerCoeff4x4Block * top = nullptr;
        EyerCoeff4x4Block * left = nullptr;

        int blockX = i8x8 % 2 * 2 + i4x4 % 2;
        int blockY = i8x8 / 2 * 2 + i4x4 / 2;

        // Get Top
        if(blockY > 0){
            // 宏块内查找
            top = findBlock(blockX, blockY - 1, type);
        }
        else{
            // 宏块外查找
            if(mbAddrB != nullptr){
                if(type == RESIDUAL_TYPE::LUMA){
                    top = mbAddrB->findBlock(blockX, 3, type);
                }
                if(type == RESIDUAL_TYPE::CHROMA_CB || type == RESIDUAL_TYPE::CHROMA_CR){
                    top = mbAddrB->findBlock(blockX, 1, type);
                }
            }
        }

        // Get Left
        if(blockX > 0){
            // 宏块内查找
            left = findBlock(blockX - 1, blockY, type);
        }
        else{
            // 宏块外查找
            if(mbAddrA != nullptr){
                // EyerLog_8("MbIndex: %d, blockX: %d, blockY: %d, Block\n", mbIndex, blockX, blockY);
                if(type == RESIDUAL_TYPE::LUMA){
                    left = mbAddrA->findBlock(3, blockY, type);
                }
                if(type == RESIDUAL_TYPE::CHROMA_CB || type == RESIDUAL_TYPE::CHROMA_CR){
                    left = mbAddrA->findBlock(1, blockY, type);
                }
            }
        }


        int topNum = 0;
        int leftNum = 0;
        if(top != nullptr){
            topNum = top->totleCoeff;
        }
        if(left != nullptr){
            leftNum = left->totleCoeff;
        }

        nC = topNum + leftNum;
        if(top != nullptr && left != nullptr){
            nC++;
            nC = nC >> 1;
        }

        return nC;
    }

    EyerCoeff4x4Block * EyerMacroblock::findBlock(int blockX, int blockY, RESIDUAL_TYPE & type)
    {
        int i8x8 = blockY / 2 * 2 + blockX / 2;
        int i4x4 = blockY % 2 * 2 + blockX % 2;

        if(type == RESIDUAL_TYPE::LUMA){
            return &lumaResidual[i8x8][i4x4];
        }
        else if(type == RESIDUAL_TYPE::CHROMA_CR){
            return &chromaCrResidualAC[i8x8][i4x4];
        }
        else if(type == RESIDUAL_TYPE::CHROMA_CB){
            return &chromaCbResidualAC[i8x8][i4x4];
        }

        return &lumaResidual[i8x8][i4x4];
    }

    int EyerMacroblock::get_coeff_level(EyerBitStream & bs, int &level, int levelIdx, int trailingOnes, int suffixLength)
    {
        // 或者 level_prefix
        int level_prefix = 0;
        while(bs.bs_read_u1() == 0){
            level_prefix++;
        }

        // 获取 levelSuffixSize
        int levelSuffixSize = 0;
        if(level_prefix == 14 && suffixLength == 0){
            levelSuffixSize = 4;
        }
        else if(level_prefix >= 15){
            levelSuffixSize = level_prefix - 3;
        }
        else{
            levelSuffixSize = suffixLength;
        }

        // 计算 levelCode
        int levelCode = (std::min(15, level_prefix) << suffixLength);
        if(suffixLength > 0 || level_prefix >= 14){
            // 获取 level_suffix
            int level_suffix = 0;
            if(levelSuffixSize > 0){
                level_suffix = bs.bs_read_u(levelSuffixSize);
            }
            else{
                level_suffix = 0;
            }

            levelCode += level_suffix;
        }

        if(level_prefix >= 15 && suffixLength == 0){
            levelCode += 15;
        }
        if(level_prefix >= 16){
            levelCode += (1 << (level_prefix - 3)) - 4096;
        }

        // if(i == trailingOnes && trailingOnes < 3){
        if(levelIdx == 0 && trailingOnes < 3){
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

        return err;
    }

    int EyerMacroblock::get_total_zeros_chrome_dc(EyerBitStream & bs, int & totalZeros, int totalZeros_vlcIdx)
    {
        int totalZerosTableChromaDC_Length[3][4] =
            {
                { 1, 2, 3, 3, },
                { 1, 2, 2, 0, },
                { 1, 1, 0, 0, }
            };

        int totalZerosTableChromaDC_Code[3][4] =
            {
                { 1, 1, 1, 0, },
                { 1, 1, 0, 0, },
                { 1, 0, 0, 0, }
            };

        int err = 0;
        int idx2 = 0;
        int idx1 = 0;
        int *lengthTable = &totalZerosTableChromaDC_Length[totalZeros_vlcIdx][0];
        int *codeTable = &totalZerosTableChromaDC_Code[totalZeros_vlcIdx][0];
        err = AVCTable::SearchForValueIn2DTable(bs, totalZeros, idx1, idx2, lengthTable, codeTable, 16, 1);
        if (err < 0) {
            return err;
        }

        return err;
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

    int EyerMacroblock::swap(int & x, int & y)
    {
        int c = x;
        x = y;
        y = c;
        return 0;
    }
}