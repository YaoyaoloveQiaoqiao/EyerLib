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
        int len = 16;

        int totalCoeffs = 0;
        for(int i=0; i<len; i++){
            if(coeff[i] != 0){
                totalCoeffs++;
            }
        }
        printf("Total Coeffs: %d\n", totalCoeffs);

        std::vector<int> trailingOnesList;
        int trailingOnes = 0;
        for(int i=len-1; i>=0; i--){
            if(abs(coeff[i]) > 1){
                break;
            }
            if(trailingOnesList.size() >= 3){
                break;
            }
            if(abs(coeff[i]) == 1){
                trailingOnesList.push_back(coeff[i]);
            }
        }
        trailingOnes = trailingOnesList.size();
        printf("Trailing Ones: %d\n", trailingOnes);

        return 0;
    }
}