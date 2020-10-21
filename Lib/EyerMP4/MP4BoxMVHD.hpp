#ifndef EYERLIB_MP4BOXMVHD_HPP
#define EYERLIB_MP4BOXMVHD_HPP

#include "MP4Box.hpp"

namespace Eyer
{
    class MP4BoxMVHD : public MP4Box {
    public:
        MP4BoxMVHD();
        ~MP4BoxMVHD();

        virtual int ParseParam(EyerBuffer & buffer, int offset);
    };
}



#endif //EYERLIB_MP4BOXMVHD_HPP
