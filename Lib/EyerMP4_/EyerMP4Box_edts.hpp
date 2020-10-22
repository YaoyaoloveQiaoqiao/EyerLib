#ifndef EYERLIB_EYERMP4BOX_EDTS_HPP
#define EYERLIB_EYERMP4BOX_EDTS_HPP

#include "EyerMP4Box.hpp"
#include "EyerCore/EyerCore.hpp"

#include "EyerMP4Constant.hpp"

namespace Eyer
{
    class EyerMP4Box_edts : public EyerMP4Box {
    public:
        EyerMP4Box_edts(const EyerBuffer & _buffer);
        ~EyerMP4Box_edts();

        virtual BoxType GetType();

        virtual int PrintInfo();
    };
}

#endif //EYERLIB_EYERMP4BOX_EDTS_HPP
