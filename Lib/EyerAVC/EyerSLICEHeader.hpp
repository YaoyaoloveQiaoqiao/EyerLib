#ifndef EYERLIB_EYERSLICEHEADER_HPP
#define EYERLIB_EYERSLICEHEADER_HPP

#include "EyerBitStream.hpp"

namespace Eyer
{
    class EyerSLICEHeader {
    public:
        EyerSLICEHeader();
        ~EyerSLICEHeader();

        int ParseA(EyerBitStream & bs);
        int ParseB(EyerBitStream & bs);

    private:
    };
}

#endif //EYERLIB_EYERSLICEHEADER_HPP
