#ifndef EYERLIB_CAVLC_HPP
#define EYERLIB_CAVLC_HPP

namespace Eyer
{
    class CAVLC {
    public:
        CAVLC();
        ~CAVLC();

        int Encode();

    private:
        int GetTotleCoeff(const int coeff[16]);
        int GetTrailingOnes(const int coeff[16], int trailingSign[3]);
        int GetLevels(const int coeff[16], int levels[], int levelCnt);
    };
}

#endif //EYERLIB_CAVLC_HPP
