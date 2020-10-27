#include "CAVLC.hpp"

#include <stdio.h>
#include <math.h>

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

        int totalCoeffs = 0;
        for(int i=0;i<16;i++){
            if(coeff[i] != 0){
                totalCoeffs++;
            }
        }
        printf("Total Coeffs: %d\n", totalCoeffs);

        int trailingOnes = 0;
        for(int i=15; i>=0; i--){
            if(abs(coeff[i]) == 1){

            }
        }

        return 0;
    }
}