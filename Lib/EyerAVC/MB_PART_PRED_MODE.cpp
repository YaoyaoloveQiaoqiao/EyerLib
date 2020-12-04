#include "MB_PART_PRED_MODE.hpp"

namespace Eyer
{
    MB_PART_PRED_MODE MB_PART_PRED_MODE::NA             (0, "NA");
    MB_PART_PRED_MODE MB_PART_PRED_MODE::Intra_4x4      (1, "Intra_4x4");
    MB_PART_PRED_MODE MB_PART_PRED_MODE::Intra_8x8      (2, "Intra_8x8");
    MB_PART_PRED_MODE MB_PART_PRED_MODE::Intra_16x16    (3, "Intra_16x16");

    MB_PART_PRED_MODE::MB_PART_PRED_MODE(int _val, const EyerString & _name) : EyerEnum(_val, _name)
    {

    }

    MB_PART_PRED_MODE::MB_PART_PRED_MODE(const MB_PART_PRED_MODE & predMode)
    {
        *this = predMode;
    }

    MB_PART_PRED_MODE::MB_PART_PRED_MODE(const int & predMode)
    {
        *this = predMode;
    }

    MB_PART_PRED_MODE::~MB_PART_PRED_MODE()
    {

    }

    MB_PART_PRED_MODE & MB_PART_PRED_MODE::operator = (const MB_PART_PRED_MODE & predMode)
    {
        EyerEnum::operator=(predMode);
        return *this;
    }

    bool MB_PART_PRED_MODE::operator == (const MB_PART_PRED_MODE & predMode)
    {
        return EyerEnum::operator==(predMode);
    }

    bool MB_PART_PRED_MODE::operator != (const MB_PART_PRED_MODE & predMode)
    {
        return !(*this == predMode);
    }
}