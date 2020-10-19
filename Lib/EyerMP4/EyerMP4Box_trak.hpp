#ifndef EYERLIB_EYERMP4BOX_TRAK_HPP
#define EYERLIB_EYERMP4BOX_TRAK_HPP

#include "EyerMP4Box.hpp"
#include "EyerCore/EyerCore.hpp"

#include "EyerMP4Constant.hpp"

namespace Eyer
{
    class EyerMP4Box_trak : public EyerMP4Box {
    public:
        EyerMP4Box_trak();
        EyerMP4Box_trak(const EyerBuffer & _buffer);
        ~EyerMP4Box_trak();

        virtual BoxType GetType();
        virtual int PrintInfo();
        virtual bool HasSub();
    };
}

#endif //EYERLIB_EYERMP4BOX_TRAK_HPP
