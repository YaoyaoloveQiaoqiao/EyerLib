#include "CAVLC.hpp"
#include "math.h"

namespace Eyer
{
    std::string CAVLC::Encoding_cavlc_16x16(const int coeff[16])
    {
        std::string retStr;

        int totleCoeff = GetTotleCoeff(coeff);
        int trailingSign[3] = {0};
        int trailingOnes = GetTrailingOnes(coeff, trailingSign);

        int levelCnt = totleCoeff - trailingOnes;
        int * levels = new int[levelCnt];
        memset(levels, 0, levelCnt);
        GetLevels(coeff, levels, levelCnt);

        int * runBefore = new int[totleCoeff];
        int * zerosLeft = new int[totleCoeff];
        memset(runBefore, 0, totleCoeff);
        memset(zerosLeft, 0, totleCoeff);

        GetTotleZerosRunbefore(coeff, runBefore, zerosLeft, totleCoeff);

        if(levels != nullptr){
            delete levels;
            levels = nullptr;
        }
        if(runBefore != nullptr){
            delete runBefore;
            runBefore = nullptr;
        }
        if(zerosLeft != nullptr){
            delete zerosLeft;
            zerosLeft = nullptr;
        }
        return retStr;
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
        int levelIdx = levelCnt - 1;

        for(int i=0;i<16;i++) {
            if(coeff[i] != 0) {
                
            }
        }

        return 0;
    }

    int CAVLC::GetTotleZerosRunbefore  (const int coeff[16], int * runBefore, int * zerosLeft, int totalCoeffs)
    {
        int runIdx = 0;
        int totalZeros = 0;
        int idx = 15;
        for(; idx >= 0; idx--){
            if(coeff[idx]){
                break;
            }
        }

        totalZeros = idx - totalCoeffs + 1;

        for(; idx >= 0; idx--) {
            if(coeff[idx] == 0){
                continue;
            }
            for(int run=0;run<=idx;run++){
                if(coeff[idx - 1 - run] == 0){
                    runBefore[runIdx]++;
                    zerosLeft[runIdx]++;
                }
                else{
                    runIdx++;
                    break;
                }
            }
        }

        for(int a=0;a<runIdx;a++){
            for(int b=0;b<runIdx;b++){
                zerosLeft[a] += zerosLeft[b];
            }
        }

        return totalZeros;
    }
}