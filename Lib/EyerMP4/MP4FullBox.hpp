#ifndef EYERLIB_MP4FULLBOX_HPP
#define EYERLIB_MP4FULLBOX_HPP

#include "MP4Box.hpp"

namespace Eyer
{
    class MP4FullBox : public MP4Box {
    public:
        MP4FullBox();
        ~MP4FullBox();

        virtual int ParseParam(EyerBuffer & buffer, int offset);

    protected:
        uint8_t version = 0;
        uint32_t flags = 0;
    };
}

#endif //EYERLIB_MP4FULLBOX_HPP
