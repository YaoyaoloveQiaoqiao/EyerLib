#ifndef EYERLIB_BOXTYPE_HPP
#define EYERLIB_BOXTYPE_HPP

#include <stdint.h>

namespace Eyer
{
    class BoxType {
    public:
        BoxType();
        BoxType(int id, char a, char b, char c, char d);
        ~BoxType();

        bool operator == (const BoxType boxType);

        char GetA();
        char GetB();
        char GetC();
        char GetD();

        uint32_t GetABCD();

    private:
        int id = 0;
        char a;
        char b;
        char c;
        char d;

    public:
        static BoxType GetType(uint32_t net_type);

        static BoxType UNKNOW;
        static BoxType FTYP;
    };
}

#endif //EYERLIB_BOXTYPE_HPP
