#include "MB_TYPE.hpp"

namespace Eyer
{
    MB_TYPE MB_TYPE::I_NxN              (SLICEType::SLICE_TYPE_I,   0,      "I_NxN");
    MB_TYPE MB_TYPE::I_16x16_0_0_0      (SLICEType::SLICE_TYPE_I,   1,      "I_16x16_0_0_0");
    MB_TYPE MB_TYPE::I_16x16_1_0_0      (SLICEType::SLICE_TYPE_I,   2,      "I_16x16_1_0_0");
    MB_TYPE MB_TYPE::I_16x16_2_0_0      (SLICEType::SLICE_TYPE_I,   3,      "I_16x16_2_0_0");
    MB_TYPE MB_TYPE::I_16x16_3_0_0      (SLICEType::SLICE_TYPE_I,   4,      "I_16x16_3_0_0");
    MB_TYPE MB_TYPE::I_16x16_0_1_0      (SLICEType::SLICE_TYPE_I,   5,      "I_16x16_0_1_0");
    MB_TYPE MB_TYPE::I_16x16_1_1_0      (SLICEType::SLICE_TYPE_I,   6,      "I_16x16_1_1_0");
    MB_TYPE MB_TYPE::I_16x16_2_1_0      (SLICEType::SLICE_TYPE_I,   7,      "I_16x16_2_1_0");
    MB_TYPE MB_TYPE::I_16x16_3_1_0      (SLICEType::SLICE_TYPE_I,   8,      "I_16x16_3_1_0");
    MB_TYPE MB_TYPE::I_16x16_0_2_0      (SLICEType::SLICE_TYPE_I,   9,      "I_16x16_0_2_0");
    MB_TYPE MB_TYPE::I_16x16_1_2_0      (SLICEType::SLICE_TYPE_I,   10,     "I_16x16_1_2_0");
    MB_TYPE MB_TYPE::I_16x16_2_2_0      (SLICEType::SLICE_TYPE_I,   11,     "I_16x16_2_2_0");
    MB_TYPE MB_TYPE::I_16x16_3_2_0      (SLICEType::SLICE_TYPE_I,   12,     "I_16x16_3_2_0");
    MB_TYPE MB_TYPE::I_16x16_0_0_1      (SLICEType::SLICE_TYPE_I,   13,     "I_16x16_0_0_1");
    MB_TYPE MB_TYPE::I_16x16_1_0_1      (SLICEType::SLICE_TYPE_I,   14,     "I_16x16_1_0_1");
    MB_TYPE MB_TYPE::I_16x16_2_0_1      (SLICEType::SLICE_TYPE_I,   15,     "I_16x16_2_0_1");
    MB_TYPE MB_TYPE::I_16x16_3_0_1      (SLICEType::SLICE_TYPE_I,   16,     "I_16x16_3_0_1");
    MB_TYPE MB_TYPE::I_16x16_0_1_1      (SLICEType::SLICE_TYPE_I,   17,     "I_16x16_0_1_1");
    MB_TYPE MB_TYPE::I_16x16_1_1_1      (SLICEType::SLICE_TYPE_I,   18,     "I_16x16_1_1_1");
    MB_TYPE MB_TYPE::I_16x16_2_1_1      (SLICEType::SLICE_TYPE_I,   19,     "I_16x16_2_1_1");
    MB_TYPE MB_TYPE::I_16x16_3_1_1      (SLICEType::SLICE_TYPE_I,   20,     "I_16x16_3_1_1");
    MB_TYPE MB_TYPE::I_16x16_0_2_1      (SLICEType::SLICE_TYPE_I,   21,     "I_16x16_0_2_1");
    MB_TYPE MB_TYPE::I_16x16_1_2_1      (SLICEType::SLICE_TYPE_I,   22,     "I_16x16_1_2_1");
    MB_TYPE MB_TYPE::I_16x16_2_2_1      (SLICEType::SLICE_TYPE_I,   23,     "I_16x16_2_2_1");
    MB_TYPE MB_TYPE::I_16x16_3_2_1      (SLICEType::SLICE_TYPE_I,   24,     "I_16x16_3_2_1");
    MB_TYPE MB_TYPE::I_PCM              (SLICEType::SLICE_TYPE_I,   25,     "I_PCM");

    MB_TYPE::MB_TYPE(SLICEType & _sliceType, int _mbTypeId, EyerString _name)
    {
        sliceType = _sliceType;
        mbTypeId = _mbTypeId;
        name = _name;
    }

    MB_TYPE::~MB_TYPE()
    {

    }

    MB_TYPE::MB_TYPE(const MB_TYPE & mbType)
    {
        *this = mbType;
    }

    MB_TYPE & MB_TYPE::operator = (const MB_TYPE & mbType)
    {
        sliceType = mbType.sliceType;
        mbTypeId = mbType.mbTypeId;
        name = mbType.name;
        return *this;
    }

    bool MB_TYPE::operator == (const MB_TYPE & mbType)
    {
        if(sliceType == mbType.sliceType && mbTypeId == mbType.mbTypeId){
            return true;
        }
        return false;
    }

    bool MB_TYPE::operator != (const MB_TYPE & mbType)
    {
        return !(*this == mbType);
    }

    MB_PART_PRED_MODE MB_TYPE::MbPartPredMode()
    {
        if(*this == MB_TYPE::I_NxN){
            return MB_PART_PRED_MODE::Intra_4x4;
        }
        if(*this == MB_TYPE::I_PCM){
            return MB_PART_PRED_MODE::NA;
        }
        return MB_PART_PRED_MODE::Intra_16x16;
    }

    int MB_TYPE::MunMbPart()
    {
        if(sliceType == SLICEType::SLICE_TYPE_I){
            return 0;
        }
        return 0;
    }

    MB_TYPE MB_TYPE::Select(SLICEType & _sliceType, int _mbTypeId)
    {
        if(_sliceType == SLICEType::SLICE_TYPE_I){
            if(_mbTypeId == 0){
                return I_NxN;
            }
            if(_mbTypeId == 25){
                return I_PCM;
            }
        }
        return I_PCM;
    }
}