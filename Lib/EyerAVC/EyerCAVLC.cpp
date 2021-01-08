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
        EyerLog("nC: %d\n", nC);
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
            EyerLog("Token: %d\n", token);
        }
        if(nC == -2){

        }

        return 0;
    }
}