#ifndef EYERLIB_EYERSLICEBODY_HPP
#define EYERLIB_EYERSLICEBODY_HPP

#include "EyerBitStream.hpp"
#include "EyerField.hpp"
#include "EyerSPS.hpp"
#include "EyerPPS.hpp"
#include "EyerSLICEHeader.hpp"
#include "MB_TYPE.hpp"
#include "EyerMacroblock.hpp"
#include "EyerCore/EyerCore.hpp"

namespace Eyer
{
    class EyerSLICEBody {
    public:
        EyerSLICEBody();
        ~EyerSLICEBody();

        int Parse(EyerBitStream & bs, EyerSyntax & syntax, EyerSPS & _sps, EyerPPS & _pps, EyerSLICEHeader & _sliceHeader);

    private:
        EyerSPS sps;
        EyerPPS pps;
        EyerSLICEHeader sliceHeader;

        EyerTable<EyerMacroblock *> mbTable;
    };
}

#endif //EYERLIB_EYERSLICEBODY_HPP
