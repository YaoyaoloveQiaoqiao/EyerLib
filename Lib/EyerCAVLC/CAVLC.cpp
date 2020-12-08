#include "CAVLC.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>

namespace Eyer
{
    CAVLC::CAVLC()
    {

    }

    CAVLC::~CAVLC()
    {

    }

    int CAVLC::Encode()
    {
        int coeff[] = {0, 3, -1, 0, 0, -1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0};

        // 统计非零系数
        int totalCoeffs = GetTotleCoeff(coeff);
        printf("Total Coeffs: %d\n", totalCoeffs);

        // 统计拖尾系数
        int trailingSign[3] = {};
        int trailingOnes = GetTrailingOnes(coeff, trailingSign);

        printf("trailingSign: ");
        for(int i=0;i<trailingOnes;i++){
            printf("%d ", trailingSign[i]);
        }
        printf("\n");

        int levelCnt = totalCoeffs - trailingOnes;
        int * levels = new int[levelCnt];



        if(levels != nullptr){
            delete[] levels;
            levels = nullptr;
        }

        // 当前块值 numberCurrent

        // 普通非零系数幅值

        // Totle Zeros

        // Run Before

        return 0;
    }

    int CAVLC::GetTotleCoeff(const int coeff[16])
    {
        int ret = 0;
        for(int i=0; i<16; i++) {
            if(coeff[i]) {
                ret++;
            }
        }
        return ret;
    }

    int CAVLC::GetTrailingOnes(const int coeff[16], int trailingSign[3])
    {
        int ret = 0;

        for(int i=15; i>=0; i--){
            if(abs(coeff[i]) > 1 || ret == 3){
                break;
            }
            else if(abs(coeff[i]) == 1){
                if(coeff[i] == 1){
                    trailingSign[ret] = 1;
                }
                else{
                    trailingSign[ret] = -1;
                }
                ret++;
            }
        }

        return ret;
    }

    int CAVLC::GetLevels(const int coeff[16], int levels[], int levelCnt)
    {
        int levelIndex = levelCnt - 1;
        for(int i=0;i<16;i++){
            if(coeff[i] != 0){

            }
        }
        return 0;
    }
}