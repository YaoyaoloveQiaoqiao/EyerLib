#ifndef EYERLIB_CAVLC_HPP
#define EYERLIB_CAVLC_HPP

#include <string>

namespace Eyer{
    class CAVLC {
    public:
        std::string Encoding_cavlc_16x16(const int coeff[16]);


    private:
        int GetTotleCoeff       (const int coeff[16]);
        int GetTrailingOnes     (const int coeff[16], int trailingSign[3]);

        int GetLevels           (const int coeff[16], int levels[], int levelCnt);

        int GetTotleZerosRunbefore  (const int coeff[16], int * runBefore, int * zerosLeft, int totalCoeffs);
    };
}

#endif //EYERLIB_CAVLC_HPP
