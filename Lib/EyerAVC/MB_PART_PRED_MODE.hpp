#ifndef EYERLIB_MB_PART_PRED_MODE_HPP
#define EYERLIB_MB_PART_PRED_MODE_HPP

#include "EyerEnum.hpp"

namespace Eyer
{
    class MB_PART_PRED_MODE : public EyerEnum{
    public:
        MB_PART_PRED_MODE(int _val, const EyerString & _name);
        MB_PART_PRED_MODE(const MB_PART_PRED_MODE & predMode);
        MB_PART_PRED_MODE(const int & predMode);
        ~MB_PART_PRED_MODE();

        MB_PART_PRED_MODE & operator = (const MB_PART_PRED_MODE & predMode);
        bool operator == (const MB_PART_PRED_MODE & predMode);
        bool operator != (const MB_PART_PRED_MODE & predMode);

    public:
        static MB_PART_PRED_MODE NA;
        static MB_PART_PRED_MODE Intra_4x4;
        static MB_PART_PRED_MODE Intra_8x8;
        static MB_PART_PRED_MODE Intra_16x16;
    };
}

#endif //EYERLIB_MB_PART_PRED_MODE_HPP
