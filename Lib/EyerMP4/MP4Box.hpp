#ifndef EYERLIB_MP4BOX_HPP
#define EYERLIB_MP4BOX_HPP

#include <stdint.h>
#include <vector>
#include "BoxType.hpp"
#include "EyerCore/EyerCore.hpp"

namespace Eyer
{
    class MP4Box {
    public:
        MP4Box();
        ~MP4Box();

        int Parse(EyerBuffer & buffer);

        int ParseSubBox(EyerBuffer & buffer, int offset);
        virtual int ParseParam(EyerBuffer & buffer, int offset);

        uint64_t GetSize();

    private:
        uint32_t size = 0;
        BoxType type;

        uint64_t largesize = 0;


        std::vector<MP4Box *> subBoxList;
    };
}

#endif //EYERLIB_MP4BOX_HPP
