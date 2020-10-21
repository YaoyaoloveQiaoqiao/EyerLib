#ifndef EYERLIB_MP4BOX_HPP
#define EYERLIB_MP4BOX_HPP

#include "stdint.h"
#include "BoxType.hpp"
#include "EyerCore/EyerCore.hpp"

namespace Eyer
{
    class MP4Box {
    public:
        MP4Box();
        ~MP4Box();

        int Parse(EyerBuffer & buffer);

        uint64_t GetSize();

    private:
        uint32_t size = 0;
        BoxType type;

        uint64_t largesize = 0;
    };
}

#endif //EYERLIB_MP4BOX_HPP
