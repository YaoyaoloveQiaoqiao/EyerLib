#ifndef EYERLIB_MB_TYPE_HPP
#define EYERLIB_MB_TYPE_HPP

#include "SLICEType.hpp"
#include "MB_PART_PRED_MODE.hpp"

namespace Eyer
{
    class MB_TYPE {
    public:
        MB_TYPE(SLICEType & _sliceType, int _mbTypeId, EyerString _name);
        ~MB_TYPE();
        MB_TYPE(const MB_TYPE & mbType);

        EyerString & GetStr();

        MB_TYPE & operator = (const MB_TYPE & mbType);

        bool operator == (const MB_TYPE & mbType);
        bool operator != (const MB_TYPE & mbType);

        MB_PART_PRED_MODE MbPartPredMode();

        int MunMbPart();

    public:
        static MB_TYPE I_NxN;
        static MB_TYPE I_16x16_0_0_0;
        static MB_TYPE I_16x16_1_0_0;
        static MB_TYPE I_16x16_2_0_0;
        static MB_TYPE I_16x16_3_0_0;
        static MB_TYPE I_16x16_0_1_0;
        static MB_TYPE I_16x16_1_1_0;
        static MB_TYPE I_16x16_2_1_0;
        static MB_TYPE I_16x16_3_1_0;
        static MB_TYPE I_16x16_0_2_0;
        static MB_TYPE I_16x16_1_2_0;
        static MB_TYPE I_16x16_2_2_0;
        static MB_TYPE I_16x16_3_2_0;
        static MB_TYPE I_16x16_0_0_1;
        static MB_TYPE I_16x16_1_0_1;
        static MB_TYPE I_16x16_2_0_1;
        static MB_TYPE I_16x16_3_0_1;
        static MB_TYPE I_16x16_0_1_1;
        static MB_TYPE I_16x16_1_1_1;
        static MB_TYPE I_16x16_2_1_1;
        static MB_TYPE I_16x16_3_1_1;
        static MB_TYPE I_16x16_0_2_1;
        static MB_TYPE I_16x16_1_2_1;
        static MB_TYPE I_16x16_2_2_1;
        static MB_TYPE I_16x16_3_2_1;
        static MB_TYPE I_PCM;

        static MB_TYPE Select(SLICEType & _sliceType, int _mbTypeId);

    private:
        SLICEType sliceType;
        int mbTypeId;
        EyerString name;

    };
}

#endif //EYERLIB_MB_TYPE_HPP
