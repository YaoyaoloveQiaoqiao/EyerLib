#include "SLICEType.hpp"

namespace Eyer
{
    SLICEType SLICEType::SLICE_TYPE_P(0, "SLICE_TYPE_P");
    SLICEType SLICEType::SLICE_TYPE_B(1, "SLICE_TYPE_B");
    SLICEType SLICEType::SLICE_TYPE_I(2, "SLICE_TYPE_I");
    SLICEType SLICEType::SLICE_TYPE_SP(3, "SLICE_TYPE_SP");
    SLICEType SLICEType::SLICE_TYPE_SI(4, "SLICE_TYPE_SI");

    SLICEType::SLICEType(int _val, const EyerString & _name) : EyerEnum(_val, _name)
    {

    }

    SLICEType::SLICEType(const SLICEType & sliceType)
    {
        *this = sliceType;
    }

    SLICEType::SLICEType(const int & sliceType)
    {
        *this = sliceType;
    }

    SLICEType::~SLICEType()
    {

    }

    SLICEType & SLICEType::operator = (const SLICEType & sliceType)
    {
        EyerEnum::operator=(sliceType);
        return *this;
    }

    SLICEType & SLICEType::operator = (const int & _sliceType)
    {
        int sliceType = _sliceType;
        if(sliceType >= 5){
            sliceType = sliceType - 5;
        }
        if(sliceType == 0){
            *this = SLICE_TYPE_P;
        }
        else if(sliceType == 1){
            *this = SLICE_TYPE_B;
        }
        else if(sliceType == 2){
            *this = SLICE_TYPE_I;
        }
        else if(sliceType == 3){
            *this = SLICE_TYPE_SP;
        }
        else if(sliceType == 4){
            *this = SLICE_TYPE_SI;
        }
        return *this;
    }

    bool SLICEType::operator == (const SLICEType & sliceType)
    {
        return EyerEnum::operator==(sliceType);
    }
}