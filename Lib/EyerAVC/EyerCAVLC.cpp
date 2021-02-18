#include "EyerCAVLC.hpp"
#include "AVCTable.hpp"

namespace Eyer
{
    EyerCAVLC::EyerCAVLC()
    {

    }

    EyerCAVLC::~EyerCAVLC()
    {

    }

    int EyerCAVLC::Get_TotalCoeff_TrailingOnes(EyerBitStream & bs, int & totleCoeff, int & trailingOnes, int nC)
    {
        if(nC >= 0){
            int numCoeffIndex = 0;
            if (nC < 2){
                numCoeffIndex = 0;
            }
            else if(nC < 4){
                numCoeffIndex = 1;
            }
            else if(nC < 8){
                numCoeffIndex = 2;
            }
            else{
                numCoeffIndex = 3;
            }

            if(numCoeffIndex < 3){
                int * lengthTable = &AVCTable::CoeffTokenTableLength[numCoeffIndex][0][0];
                int * codeTable = &AVCTable::CoeffTokenTableCode[numCoeffIndex][0][0];

                int token = 0;
                AVCTable::SearchForValueIn2DTable(bs, totleCoeff, trailingOnes, token, lengthTable, codeTable, 17, 4);
            }
            if(numCoeffIndex == 3){
                uint32_t code = bs.bs_read_u(6);

                uint32_t b = code & 3;
                uint32_t a = code >> 2;

                if (!a && b == 3) {
                    b = 0;
                }
                else{
                    a++;
                }
                // EyerLog("a: %d, b: %d\n", a, b);
                totleCoeff = a;
                trailingOnes = b;
            }
        }
        if(nC == -1){
            int * lengthTable = &AVCTable::CoeffTokenTableChromaDC_Length[0][0];
            int * codeTable = &AVCTable::CoeffTokenTableChromaDC_Code[0][0];

            int token = 0;
            AVCTable::SearchForValueIn2DTable(bs, totleCoeff, trailingOnes, token, lengthTable, codeTable, 5, 4);
            // EyerLog("Token: %d\n", token);
        }
        if(nC == -2){

        }

        return 0;
    }

    int EyerCAVLC::Get_Coeff_Level(EyerBitStream & bs, int &level, int levelIdx, int trailingOnes, int suffixLength)
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

    int EyerCAVLC::Get_Total_Zeros(EyerBitStream & bs, int & totalZeros, int totalZeros_vlcIdx)
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

    int EyerCAVLC::Get_Total_Zeros_Chrome_DC(EyerBitStream & bs, int & totalZeros, int totalZeros_vlcIdx)
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

    int EyerCAVLC::Get_Run_Before(EyerBitStream & bs, int & runBefore, int runBefore_vlcIdx)
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