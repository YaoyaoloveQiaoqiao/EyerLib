#ifndef EYERLIB_EYERMP4BOX_MDIA_HPP
#define EYERLIB_EYERMP4BOX_MDIA_HPP

#include "EyerMP4Box.hpp"
#include "EyerCore/EyerCore.hpp"

#include "EyerMP4Constant.hpp"

namespace Eyer
{
    class EyerMP4Box_mdia : public EyerMP4Box {
    public:
        EyerMP4Box_mdia(const EyerBuffer & _buffer);
        ~EyerMP4Box_mdia();

        virtual BoxType GetType();
        virtual int PrintInfo();

        virtual bool HasSub();
    };
}

#endif //EYERLIB_EYERMP4BOX_MDIA_HPP
