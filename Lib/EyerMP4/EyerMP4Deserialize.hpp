#ifndef EYERLIB_EYERMP4DESERIALIZE_HPP
#define EYERLIB_EYERMP4DESERIALIZE_HPP

#include "EyerCore/EyerCore.hpp"
#include "EyerMP4Box.hpp"

namespace Eyer
{
    class EyerMP4Deserialize {
    public:
        EyerMP4Deserialize(EyerBuffer & _buffer);
        ~EyerMP4Deserialize();

        int Get(EyerMP4Box & box);
    private:
        EyerBuffer buffer;
    };
}

#endif //EYERLIB_EYERMP4DESERIALIZE_HPP
