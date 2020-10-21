#ifndef EYERLIB_EYERMP4BOX_MINF_HPP
#define EYERLIB_EYERMP4BOX_MINF_HPP

#include "EyerMP4Box.hpp"
#include "EyerCore/EyerCore.hpp"

#include "EyerMP4Constant.hpp"

namespace Eyer
{
    class EyerMP4Box_minf : public EyerMP4Box {
    public:
        EyerMP4Box_minf(const EyerBuffer & _buffer);
        ~EyerMP4Box_minf();

        virtual BoxType GetType();
        virtual int PrintInfo();

        virtual bool HasSub();
    };
}

#endif //EYERLIB_EYERMP4BOX_MINF_HPP
