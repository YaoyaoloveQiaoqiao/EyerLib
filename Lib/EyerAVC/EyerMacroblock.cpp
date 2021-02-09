#include "EyerMacroblock.hpp"
#include "EyerBitStream.hpp"
#include "EyerCAVLC.hpp"
#include "AVCTable.hpp"
#include "EyerSLICEBody.hpp"
#include "EyerNeighbourSamples.hpp"

#include <algorithm>
#include <cstdio>
#include <cmath>
#include <iostream>

namespace Eyer
{
    EyerMacroblock::EyerMacroblock()
    {
        predTable.Resize(16, 16);

        mbIndex = -1;
        mbAddrA = nullptr;
        mbAddrB = nullptr;
        mbAddrC = nullptr;
        mbAddrD = nullptr;
        mbAddrF = nullptr;
    }

    EyerMacroblock::EyerMacroblock(int _mbIndex, EyerMacroblock * _mbAddrA, EyerMacroblock * _mbAddrB, EyerMacroblock * _mbAddrC, EyerMacroblock * _mbAddrD, EyerMacroblock * _mbAddrF)
    {
        predTable.Resize(16, 16);

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
        if(_mbAddrF != nullptr){
            mbAddrF = new EyerMacroblock(*_mbAddrF);
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
        if(mbAddrF != nullptr){
            delete mbAddrF;
            mbAddrF = nullptr;
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
                int mb_qp_delta = bs.bs_read_se();

                qp = pps.pic_init_qp_minus26 + 26 + sliceHeader.sh.slice_qp_delta + mb_qp_delta;
                EyerLog("\tpic_init_qp_minus26: %d\n", pps.pic_init_qp_minus26);
                EyerLog("\tslice_qp_delta: %d\n", sliceHeader.sh.slice_qp_delta);
                EyerLog("\tmb_qp_delta: %d\n", mb_qp_delta);
                EyerLog("\tQP: %d\n", qp);

                for(int luma4x4BlkIdx=0; luma4x4BlkIdx<16; luma4x4BlkIdx++) {
                    //转换序号到 8x8 4x4
                    int i8x8 = luma4x4BlkIdx / 4;
                    int i4x4 = luma4x4BlkIdx % 4;

                    lumaResidual[i8x8][i4x4].SetQP(qp);
                }

                EyerLog("\tqp: %d\n", qp);
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
            EyerLog("\tRead luma Pred Mode\n");
            if(mbType.MbPartPredMode() == MB_PART_PRED_MODE::Intra_4x4){
                EyerLog("\t\tIntra_4x4\n");
                uint32_t prev_intra4x4_pred_mode_flag[16];
                memset(prev_intra4x4_pred_mode_flag, 0, 16 * sizeof(uint32_t));
                uint32_t rem_intra4x4_pred_mode_flag[16];
                memset(rem_intra4x4_pred_mode_flag, 0, 16 * sizeof(uint32_t));
                for(int luma4x4BlkIdx=0; luma4x4BlkIdx<16; luma4x4BlkIdx++){
                    //转换序号到 8x8 4x4
                    int i8x8 = luma4x4BlkIdx / 4;
                    int i4x4 = luma4x4BlkIdx % 4;
                    EyerLog("\t\t\t转换序号 luma4x4BlkIdx: %d, i8x8: %d, i4x4: %d\n", luma4x4BlkIdx, i8x8, i4x4);

                    // 获取模式
                    EyerCoeff4x4Block * top = nullptr;
                    EyerCoeff4x4Block * left = nullptr;
                    GetTopLeftBlock(&top, &left, i8x8, i4x4, RESIDUAL_TYPE::LUMA);

                    int upIntraPredMode = -1;
                    if(top != nullptr){
                        upIntraPredMode = top->luma_pred_mode;
                    }
                    int leftIntraPredMode = -1;
                    if(left != nullptr){
                        leftIntraPredMode = left->luma_pred_mode;
                    }

                    int mostProbableIntraPredMode  = (upIntraPredMode < 0 || leftIntraPredMode < 0) ? 2 : upIntraPredMode < leftIntraPredMode ? upIntraPredMode : leftIntraPredMode;
                    EyerLog("\t\t\t\tupIntraPredMode: %d, leftIntraPredMode: %d, mostProbableIntraPredMode: %d\n", upIntraPredMode, leftIntraPredMode, mostProbableIntraPredMode);

                    rem_intra4x4_pred_mode_flag[luma4x4BlkIdx] = -1;
                    prev_intra4x4_pred_mode_flag[luma4x4BlkIdx] = bs.bs_read_u1();
                    if(!prev_intra4x4_pred_mode_flag[luma4x4BlkIdx]){
                        rem_intra4x4_pred_mode_flag[luma4x4BlkIdx] = bs.bs_read_u(3);
                    }
                    lumaResidual[i8x8][i4x4].luma_pred_mode = ((rem_intra4x4_pred_mode_flag[luma4x4BlkIdx] == -1) ? mostProbableIntraPredMode : rem_intra4x4_pred_mode_flag[luma4x4BlkIdx] + (rem_intra4x4_pred_mode_flag[luma4x4BlkIdx] >= mostProbableIntraPredMode));
                    EyerLog("\t\t\t\t\t最终预测模式是：%d\n", lumaResidual[i8x8][i4x4].luma_pred_mode);
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
                    ResidualBlockCavlc(bs, chromaResidualDC[iCbCr], nC, 0, 4 * NumC8x8 - 1, 4 * NumC8x8, true);
                    chromaResidualDC[iCbCr].Restore();
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
                                chromaCbResidualAC[i8x8][i4x4].Restore();
                            }
                            if(iCbCr == 1){
                                // Cr
                                EyerLog("\t\t\txxxxxxxxxxxxxxxx Chroma AC Cr : %d xxxxxxxxxxxxxxxx\n", i4x4);
                                int nC = GetNumberCurrent(i8x8, i4x4, RESIDUAL_TYPE::CHROMA_CR);
                                ResidualBlockCavlc(bs, chromaCrResidualAC[i8x8][i4x4], nC, std::max(0, startIdx - 1), endIdx - 1, 15);
                                chromaCrResidualAC[i8x8][i4x4].Restore();
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
                            ResidualBlockCavlc(bs, lumaResidual[i8x8][i4x4], nC, startIdx, endIdx, 16);


                            lumaResidual[i8x8][i4x4].Restore();
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
                cavlc.Get_Coeff_Level(bs, levelVal, k, trailingOnes, suffixLength);

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
                    cavlc.Get_Total_Zeros_Chrome_DC(bs, totleZeros, totleCoeff - 1);
                }else{
                    cavlc.Get_Total_Zeros(bs, totleZeros, totleCoeff - 1);
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
                    cavlc.Get_Run_Before(bs, run, runBeforeVlcIdx);

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

        return 0;
    }

    int EyerMacroblock::GetNumberCurrent(int i8x8, int i4x4, RESIDUAL_TYPE & type)
    {
        int nC = 0;

        EyerCoeff4x4Block * top = nullptr;
        EyerCoeff4x4Block * left = nullptr;

        GetTopLeftBlock(&top, &left, i8x8, i4x4, type);

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

    int EyerMacroblock::GetTopLeftBlock(EyerCoeff4x4Block ** top, EyerCoeff4x4Block ** left, int i8x8, int i4x4, RESIDUAL_TYPE & type)
    {
        // TODO 422 444
        int blockX = i8x8 % 2 * 2 + i4x4 % 2;
        int blockY = i8x8 / 2 * 2 + i4x4 / 2;

        // Get Top
        if(blockY > 0){
            // 宏块内查找
            *top = findBlock(blockX, blockY - 1, type);
        }
        else{
            // 宏块外查找
            if(mbAddrB != nullptr){
                if(type == RESIDUAL_TYPE::LUMA){
                    *top = mbAddrB->findBlock(blockX, 3, type);
                }
                if(type == RESIDUAL_TYPE::CHROMA_CB || type == RESIDUAL_TYPE::CHROMA_CR){
                    *top = mbAddrB->findBlock(blockX, 1, type);
                }
            }
        }

        // Get Left
        if(blockX > 0){
            // 宏块内查找
            *left = findBlock(blockX - 1, blockY, type);
        }
        else{
            // 宏块外查找
            if(mbAddrA != nullptr){
                // EyerLog_8("MbIndex: %d, blockX: %d, blockY: %d, Block\n", mbIndex, blockX, blockY);
                if(type == RESIDUAL_TYPE::LUMA){
                    *left = mbAddrA->findBlock(3, blockY, type);
                }
                if(type == RESIDUAL_TYPE::CHROMA_CB || type == RESIDUAL_TYPE::CHROMA_CR){
                    *left = mbAddrA->findBlock(1, blockY, type);
                }
            }
        }

        return 0;
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

    int EyerMacroblock::Decode()
    {
        if(mbType.MbPartPredMode() == MB_PART_PRED_MODE::Intra_4x4){
            // LUMA
            for(int luma4x4BlkIdx = 0; luma4x4BlkIdx < 16; luma4x4BlkIdx++) {
                //转换序号到 8x8 4x4
                int i8x8 = luma4x4BlkIdx / 4;
                int i4x4 = luma4x4BlkIdx % 4;

                int mb8x8X = i8x8 % 2 * 8;
                int mb8x8Y = i8x8 / 2 * 8;

                int i4x4X = i4x4 % 2;
                int i4x4Y = i4x4 / 2;

                int x = mb8x8X + i4x4X * 4;
                int y = mb8x8Y + i4x4Y * 4;

                EyerLog("i8x8: %d, i4x4: %d, x: %d, y: %d\n", i8x8, i4x4, x, y);

                Sample Q;
                GetSample(x - 1, y - 1, Q);

                Sample A;
                Sample B;
                Sample C;
                Sample D;
                GetSample(x + 0, y - 1, A);
                GetSample(x + 1, y - 1, B);
                GetSample(x + 2, y - 1, C);
                GetSample(x + 3, y - 1, D);

                Sample E;
                Sample F;
                Sample G;
                Sample H;
                GetSample(x + 4, y - 1, E);
                GetSample(x + 5, y - 1, F);
                GetSample(x + 6, y - 1, G);
                GetSample(x + 7, y - 1, H);

                Sample I;
                Sample J;
                Sample K;
                Sample L;
                GetSample(x - 1, y + 0, I);
                GetSample(x - 1, y + 1, J);
                GetSample(x - 1, y + 2, K);
                GetSample(x - 1, y + 3, L);

                EyerNeighbourSamples neighbourSamples;
                neighbourSamples.Init(Q, A, B, C, D, E, F, G, H, I, J, K, L);

                EyerTable<Sample> res;
                lumaResidual[i8x8][i4x4].Decode(neighbourSamples, res);
            }

            // CHROMA
        }

        if(mbType.MbPartPredMode() == MB_PART_PRED_MODE::Intra_16x16){

        }
        return 0;
    }

    int EyerMacroblock::GetSample(int x, int y, Sample & sample)
    {
        sample.SetUnavailable();
        // 宏块内
        if(x >= 0 && x <= 15 && y >=0 && y <= 15) {
            predTable.Get(sample, x, y);
        }
        // 宏块外
        if(x == -1 && y == -1) {
            // D 宏块
            if(mbAddrD == nullptr) {
                sample.SetUnavailable();
            }
            else {
                mbAddrD->GetSample(15, 15, sample);
            }
        }
        if(y == -1) {
            if(x >= 0 && x <= 15) {
                if(mbAddrB == nullptr) {
                    sample.SetUnavailable();
                }
                else {
                    mbAddrB->GetSample(x, 15, sample);
                }
            }
        }
        if(x == -1) {
            if(y >= 0 && y <= 15) {
                if(mbAddrA == nullptr) {
                    sample.SetUnavailable();
                }
                else {
                    mbAddrA->GetSample(15, y, sample);
                }
            }
        }

        if(x > 15){
            if(y == -1){
                if(mbAddrC == nullptr) {
                    sample.SetUnavailable();
                }
                else {
                    mbAddrC->GetSample(x % 15, 15, sample);
                }
            }
        }

        return 0;
    }

    int EyerMacroblock::GetABCDBlock (EyerCoeff4x4Block ** a, EyerCoeff4x4Block ** b, EyerCoeff4x4Block ** c, EyerCoeff4x4Block ** d, int i8x8, int i4x4, RESIDUAL_TYPE & type)
    {
        /*
         ***************
         *  D  B  C
         *  A  E
         ***************
         */

        // TODO 422 444
        int blockX = i8x8 % 2 * 2 + i4x4 % 2;
        int blockY = i8x8 / 2 * 2 + i4x4 / 2;

        // Get A
        if(blockX > 0){
            // 宏块内查找
            *a = findBlock(blockX - 1, blockY, type);
        }
        else{
            // 宏块外查找
            if(mbAddrA != nullptr){
                if(type == RESIDUAL_TYPE::LUMA){
                    *a = mbAddrA->findBlock(3, blockY, type);
                }
                if(type == RESIDUAL_TYPE::CHROMA_CB || type == RESIDUAL_TYPE::CHROMA_CR){
                    *a = mbAddrA->findBlock(1, blockY, type);
                }
            }
        }

        // Get B
        if(blockY > 0){
            // 宏块内查找
            *b = findBlock(blockX, blockY - 1, type);
        }
        else{
            // 宏块外查找
            if(mbAddrB != nullptr){
                if(type == RESIDUAL_TYPE::LUMA){
                    *b = mbAddrB->findBlock(blockX, 3, type);
                }
                if(type == RESIDUAL_TYPE::CHROMA_CB || type == RESIDUAL_TYPE::CHROMA_CR){
                    *b = mbAddrB->findBlock(blockX, 1, type);
                }
            }
        }

        // Get C
        if(blockX >= 0 && blockX < 3){
            if(blockY > 0){
                *c = findBlock(blockX + 1, blockY - 1, type);
            }
            else if(blockY == 0){
                if(mbAddrB != nullptr){
                    *c = mbAddrB->findBlock(blockX + 1, 3, type);
                }
            }
        }
        else if(blockX == 3){
            if(blockY > 0){
                // TODO F Block
                // mbAddrF
            }
            else if(blockY == 0){
                if(mbAddrC != nullptr){
                    *c = mbAddrC->findBlock(0, 3, type);
                }
            }
        }

        // Get D
        if(blockY > 0 && blockX > 0){
            // 宏块内查找
            *d = findBlock(blockX - 1, blockY - 1, type);
        }
        else if(blockY > 0 && blockX == 0){
            if(mbAddrA != nullptr){
                *d = mbAddrA->findBlock(3, blockY - 1, type);
            }
        }
        else if(blockX > 0 && blockY == 0){
            if(mbAddrB != nullptr){
                *d = mbAddrB->findBlock(blockX - 1, 3, type);
            }
        }
        else if(blockX == 0 && blockY == 0){
            if(mbAddrD != nullptr){
                *d = mbAddrD->findBlock(3, 3, type);
            }
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

    int EyerMacroblock::MIN(int a, int b)
    {
        if(a > b){
            return b;
        }
        return a;
    }
}