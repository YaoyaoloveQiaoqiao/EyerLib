#ifndef EYERLIB_EYERNAL_HPP
#define EYERLIB_EYERNAL_HPP

#include "EyerNALU.hpp"
#include "EyerField.hpp"
#include "EyerBitStream.hpp"
#include <vector>

namespace Eyer {
    class EyerNAL {
    public:
        EyerNAL();
        virtual ~EyerNAL();

        EyerNAL(const EyerNAL & nal);
        EyerNAL & operator = (const EyerNAL & nal);

        int PrintInfo();

        int GetFieldSize();
        int GetField(EyerField & field, int index);

        virtual NaluType GetNalType() = 0;

        Boolean IsValid();

    protected:
        EyerNALU nalu;
        std::vector<EyerField *> fieldList;
        void ScalingList(int * scalingList, int sizeOfScalingList, Boolean * useDefaultScalingMatrix, EyerBitStream * bitstream, int * used_bits);
        Boolean valid = Boolean::FALSE;
    };
}

#endif //EYERLIB_EYERNAL_HPP
