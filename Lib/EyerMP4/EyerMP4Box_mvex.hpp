#ifndef EYERLIB_EYERMP4BOX_MVEX_HPP
#define EYERLIB_EYERMP4BOX_MVEX_HPP

#include "EyerMP4Box.hpp"
#include "EyerCore/EyerCore.hpp"

#include "EyerMP4Constant.hpp"

namespace Eyer {
    class EyerMP4Box_mvex : public EyerMP4Box {
    public:
        EyerMP4Box_mvex();
        EyerMP4Box_mvex(const EyerBuffer & _buffer);
        ~EyerMP4Box_mvex();

        virtual BoxType GetType();
        virtual int PrintInfo();

        virtual bool HasSub();
    };
}


#endif //EYERLIB_EYERMP4BOX_MVEX_HPP
