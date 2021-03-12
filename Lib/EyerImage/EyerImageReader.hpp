#ifndef EYERCOLORSPACE_EYERIMAGEREADER_HPP
#define EYERCOLORSPACE_EYERIMAGEREADER_HPP

#include "EyerCore/EyerCore.hpp"
#include "EyerImageBuffer.hpp"

namespace Eyer
{
    class EyerImageReader {
    public:
        EyerImageReader();
        ~EyerImageReader();

        int Reader(unsigned char * data, int size, EyerImageBuffer & outBuffer);
    };
}

#endif //EYERCOLORSPACE_EYERIMAGEREADER_HPP
