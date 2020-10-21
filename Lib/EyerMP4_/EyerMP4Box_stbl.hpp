#ifndef EYERLIB_EYERMP4BOX_STBL_HPP
#define EYERLIB_EYERMP4BOX_STBL_HPP

#include "EyerMP4Box.hpp"
#include "EyerCore/EyerCore.hpp"

#include "EyerMP4Constant.hpp"

namespace Eyer
{
    class EyerMP4Box_stbl : public EyerMP4Box {
    public:
        EyerMP4Box_stbl(const EyerBuffer & _buffer);
        ~EyerMP4Box_stbl();

        virtual BoxType GetType();
        virtual int PrintInfo();

        virtual bool HasSub();
    };
}



#endif //EYERLIB_EYERMP4BOX_STBL_HPP
