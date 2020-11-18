#ifndef EYERLIB_EYERUDPCALLBACK_HPP
#define EYERLIB_EYERUDPCALLBACK_HPP

#include <stdint.h>

namespace Eyer
{
    class EyerUDPCallback {
    public:
        virtual int OnMessageRecv(uint8_t * buffer, int bufferSize) = 0;
    };
}

#endif //EYERLIB_EYERUDPCALLBACK_HPP
