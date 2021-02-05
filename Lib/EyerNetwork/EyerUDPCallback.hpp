#ifndef EYERLIB_EYERUDPCALLBACK_HPP
#define EYERLIB_EYERUDPCALLBACK_HPP

#include <stdint.h>
#include "UDPMessage.hpp"

namespace Eyer
{
    class EyerUDPCallback {
    public:
        virtual int OnMessageRecv(UDPMessage * udpMessage) = 0;
    };
}

#endif //EYERLIB_EYERUDPCALLBACK_HPP
