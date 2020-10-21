#ifndef EYERLIB_EYERMP4BOX_HDLR_HPP
#define EYERLIB_EYERMP4BOX_HDLR_HPP

#include "EyerMP4Box.hpp"
#include "EyerCore/EyerCore.hpp"

#include "EyerMP4Constant.hpp"

namespace Eyer
{
    class EyerMP4Box_hdlr : public EyerMP4Box {
    public:
        EyerMP4Box_hdlr(const EyerBuffer & _buffer);
        ~EyerMP4Box_hdlr();

        virtual BoxType GetType();
        virtual int PrintInfo();

        virtual bool HasSub();

    private:
        unsigned char handler_type[MAX_HANDLER_TYPE_LEN+1];
        unsigned char name[MAX_HDLR_NAME_LEN+1];
    };
}



#endif //EYERLIB_EYERMP4BOX_HDLR_HPP
