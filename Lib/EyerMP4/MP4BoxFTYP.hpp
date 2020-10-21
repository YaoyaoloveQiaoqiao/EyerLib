#ifndef EYERLIB_MP4BOXFTYP_HPP
#define EYERLIB_MP4BOXFTYP_HPP

#include "MP4Box.hpp"

namespace Eyer
{
    class MP4BoxFTYP : public MP4Box {
    public:
        MP4BoxFTYP();
        ~MP4BoxFTYP();

        virtual int ParseParam(EyerBuffer & buffer, int offset);

    private:
        uint8_t major_brand[4];
        uint32_t minor_version = 0;
    };
}



#endif //EYERLIB_MP4BOXFTYP_HPP
