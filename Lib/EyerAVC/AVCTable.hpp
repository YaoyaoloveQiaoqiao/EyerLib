#ifndef EYERLIB_AVCTABLE_HPP
#define EYERLIB_AVCTABLE_HPP

#include "EyerBitStream.hpp"

namespace Eyer
{
    class AVCTable
    {
    public:
        static int CoeffTokenTableLength[3][4][17];
        static int CoeffTokenTableCode[3][4][17];

        static int CoeffTokenTableChromaDC_Length[4][5];
        static int CoeffTokenTableChromaDC_Code[4][5];

        static int SearchForValueIn2DTable(EyerBitStream & bs, int &value1, int &value2, int &code, int *lengthTable, int *codeTable, int tableWidth, int tableHeight);
    };
}

#endif //EYERLIB_AVCTABLE_HPP
