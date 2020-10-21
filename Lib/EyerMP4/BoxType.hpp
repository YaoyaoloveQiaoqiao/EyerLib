#ifndef EYERLIB_BOXTYPE_HPP
#define EYERLIB_BOXTYPE_HPP

#include <stdint.h>

namespace Eyer
{
    class BoxType {
    public:
        BoxType();
        BoxType(int id, char a, char b, char c, char d, bool _hasSub);
        ~BoxType();

        bool operator == (const BoxType boxType);

        char GetA();
        char GetB();
        char GetC();
        char GetD();

        uint32_t GetABCD();

        bool HasSub();

        int PrintInfo();

    private:
        int id = 0;
        char a;
        char b;
        char c;
        char d;

        bool hasSub = false;

    public:
        static BoxType GetType(uint32_t net_type);

        static BoxType UNKNOW;
        static BoxType FTYP;
        static BoxType FREE;
        static BoxType MOOV;
        static BoxType MDAT;
        static BoxType MVHD;
    };
}

#endif //EYERLIB_BOXTYPE_HPP
