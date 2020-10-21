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
    class EyerMP4Box_mvex;
    class EyerMP4Box_mehd;
    class EyerMP4Box_trex;


    class EyerMP4Box {
    public:
        EyerMP4Box();
        EyerMP4Box(const EyerBuffer & _buffer);
        virtual ~EyerMP4Box();

        EyerMP4Box(const EyerMP4Box & _box);
        EyerMP4Box & operator = (const EyerMP4Box & _box);

        int Get(EyerMP4Box * * box);
        int Get(EyerMP4Box * * box, EyerBuffer & buffer);

        virtual bool HasSub();
        virtual BoxType GetType();
        virtual int PrintInfo();

        int GetTotalBufferData(unsigned char * data = nullptr);
        EyerBuffer & GetTotalBuffer();

        EyerBuffer GetTotalBufferWithHead();

        int AddSubBox(EyerMP4Box & subBox);

        // 获取子 Box
        int GetFTYP(EyerMP4Box_ftyp & ftyp);
        int GetMVHD(EyerMP4Box_mvhd & mvhd);

        int GetMOOV(EyerMP4Box_moov & moov);
        int GetTRAK(EyerMP4Box_trak & trak);

        int GetMVEX(EyerMP4Box_mvex & mvex);
        int GetMEHD(EyerMP4Box_mehd & mehd);
        int GetTREX(EyerMP4Box_trex & trex);

        // 打印信息
        int PrintAll();
        int PrintBox(EyerMP4Box & box, int depth);

    protected:
        EyerBuffer buffer;
        EyerBuffer totalBuffer;
    };
}

#endif //EYERLIB_EYERMP4BOX_HPP
