#ifndef EYERLIB_EYERCAVLC_HPP
#define EYERLIB_EYERCAVLC_HPP

#include "EyerBitStream.hpp"

namespace Eyer
{
    class EyerCAVLC {
    public:
        EyerCAVLC();
        ~EyerCAVLC();

        int Get_TotalCoeff_TrailingOnes(EyerBitStream & bs, int & totleCoeff, int & trailingOnes, int nC);

        int Get_Coeff_Level(EyerBitStream & bs, int &level, int levelIdx, int trailingOnes, int suffixLength);

        int Get_Total_Zeros(EyerBitStream & bs, int & totalZeros, int totalZeros_vlcIdx);

        int Get_Total_Zeros_Chrome_DC(EyerBitStream & bs, int & totalZeros, int totalZeros_vlcIdx);

        int Get_Run_Before(EyerBitStream & bs, int & runBefore, int runBefore_vlcIdx);
    };
}

#endif //EYERLIB_EYERCAVLC_HPP
