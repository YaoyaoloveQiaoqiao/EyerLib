#ifndef EYERLIB_SLICETYPE_HPP
#define EYERLIB_SLICETYPE_HPP

#include "EyerEnum.hpp"

namespace Eyer
{
    class SLICEType : public EyerEnum {
    public:
        SLICEType(int _val, const EyerString & _name);
        SLICEType(const SLICEType & sliceType);
        SLICEType(const int & sliceType);
        ~SLICEType();


        SLICEType & operator = (const SLICEType & sliceType);
        SLICEType & operator = (const int & sliceType);
        bool operator == (const SLICEType & sliceType);
    public:
        static SLICEType SLICE_TYPE_P;
        static SLICEType SLICE_TYPE_B;
        static SLICEType SLICE_TYPE_I;
        static SLICEType SLICE_TYPE_SP;
        static SLICEType SLICE_TYPE_SI;
    };
}

#endif //EYERLIB_SLICETYPE_HPP
