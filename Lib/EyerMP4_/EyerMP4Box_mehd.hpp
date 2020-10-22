#ifndef EYERLIB_EYERMP4BOX_MEHD_HPP
#define EYERLIB_EYERMP4BOX_MEHD_HPP

#include "EyerMP4Box.hpp"
#include "EyerCore/EyerCore.hpp"

#include "EyerMP4Constant.hpp"

namespace Eyer
{
    class EyerMP4Box_mehd : public EyerMP4Box {
    public:
        EyerMP4Box_mehd();
        EyerMP4Box_mehd(const EyerBuffer & _buffer);
        ~EyerMP4Box_mehd();

        virtual BoxType GetType();
        virtual int PrintInfo();

        virtual bool HasSub();

    private:

    };
}

#endif //EYERLIB_EYERMP4BOX_MEHD_HPP
