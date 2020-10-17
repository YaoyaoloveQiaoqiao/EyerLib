#ifndef EYERLIB_EYERMP4BOX_MOOV_HPP
#define EYERLIB_EYERMP4BOX_MOOV_HPP

#include "EyerMP4Box.hpp"
#include "EyerCore/EyerCore.hpp"

#include "EyerMP4Constant.hpp"

namespace Eyer
{
    class EyerMP4Box_moov  : public EyerMP4Box {
    public:
        EyerMP4Box_moov(int _boxSize, const EyerBuffer & _buffer);
        ~EyerMP4Box_moov();

    private:
        EyerBuffer buffer;
    };
}

#endif //EYERLIB_EYERMP4BOX_MOOV_HPP
