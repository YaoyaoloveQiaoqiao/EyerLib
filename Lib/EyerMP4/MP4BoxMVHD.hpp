#ifndef EYERLIB_MP4BOXMVHD_HPP
#define EYERLIB_MP4BOXMVHD_HPP

#include "MP4Box.hpp"
#include "MP4FullBox.hpp"

namespace Eyer
{
    class MP4BoxMVHD : public MP4FullBox {
    public:
        MP4BoxMVHD();
        ~MP4BoxMVHD();

        virtual int ParseParam(EyerBuffer & buffer, int offset);
    };
}



#endif //EYERLIB_MP4BOXMVHD_HPP
