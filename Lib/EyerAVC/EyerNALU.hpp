#ifndef EYERLIB_EYERNALU_HPP
#define EYERLIB_EYERNALU_HPP

#include "EyerNALUData.hpp"
#include "EyerField.hpp"
#include "EyerCodecCommon/EyerCodecCommon.hpp"

namespace Eyer
{
    class EyerNALU {
    public:
        EyerNALU();
        EyerNALU(const EyerNALU & nalu);
        virtual ~EyerNALU();

        EyerNALU & operator = (const EyerNALU & nalu);

        virtual int Parse();

        int SetNALUData(EyerNALUData & _naluData);

        int PrintInfo();

        bool isValid();

        NALUType & GetNALUType();

    protected:
        EyerNALUData naluData;
        EyerSyntax rootSyntax;

        bool valid = false;
        int intlog2(int x);
    };
}

#endif //EYERLIB_EYERNALU_HPP
