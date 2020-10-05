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

        int PrintInfo();

        int GetFieldSize();
        int GetField(EyerField & field, int index);

        virtual NaluType GetNalType() = 0;

    protected:
        EyerNALU nalu;
        std::vector<EyerField *> fieldList;
        void ScalingList(int * scalingList, int sizeOfScalingList, Boolean * useDefaultScalingMatrix, EyerBitStream * bitstream, int * used_bits);

    private:

    };
}

#endif //EYERLIB_EYERNAL_HPP
