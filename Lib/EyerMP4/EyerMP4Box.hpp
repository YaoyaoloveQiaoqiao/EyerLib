#ifndef EYERLIB_EYERMP4BOX_HPP
#define EYERLIB_EYERMP4BOX_HPP

#include "EyerCore/EyerCore.hpp"
#include <string.h>

namespace Eyer
{
    enum BoxType
    {
        UNKNOW = 0,
        FTYP = 1,
        MOOV = 2,
        MVHD = 3,
        TRAK = 4,
        TKHD = 5,
        EDTS = 6,
        MDHD = 7,
        HDLR = 8,
        MDIA = 9,
        MINF = 10,
        STBL = 11
    };

    class EyerMP4Box {
    public:
        EyerMP4Box(const EyerBuffer & _buffer);
        virtual ~EyerMP4Box();

        int Get(EyerMP4Box * * box);

        virtual bool HasSub();
        virtual BoxType GetType();
        virtual int PrintInfo();

        int GetTotalBuffer(unsigned char * data = nullptr);

    protected:
        EyerBuffer buffer;
        EyerBuffer totalBuffer;
    };
}

#endif //EYERLIB_EYERMP4BOX_HPP
