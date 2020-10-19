#ifndef EYERLIB_EYERMP4BOX_HPP
#define EYERLIB_EYERMP4BOX_HPP

#include "EyerCore/EyerCore.hpp"
#include "EyerMP4Constant.hpp"
#include <string.h>

namespace Eyer
{
    class EyerMP4Box_moov;
    class EyerMP4Box_trak;
    class EyerMP4Box_ftyp;
    class EyerMP4Box_mvhd;

    class EyerMP4Box {
    public:
        EyerMP4Box();
        EyerMP4Box(const EyerBuffer & _buffer);
        virtual ~EyerMP4Box();

        int Get(EyerMP4Box * * box);
        int Get(EyerMP4Box * * box, EyerBuffer & buffer);

        virtual bool HasSub();
        virtual BoxType GetType();
        virtual int PrintInfo();

        int GetTotalBufferData(unsigned char * data = nullptr);
        EyerBuffer & GetTotalBuffer();

        int GetFTYP(EyerMP4Box_ftyp & ftyp);
        int GetMVHD(EyerMP4Box_mvhd & mvhd);

        int GetMOOV(EyerMP4Box_moov & moov);
        int GetTRAK(EyerMP4Box_trak & trak);



        int PrintAll();
        int PrintBox(EyerMP4Box & box, int depth);

    protected:
        EyerBuffer buffer;
        EyerBuffer totalBuffer;
    };
}

#endif //EYERLIB_EYERMP4BOX_HPP
