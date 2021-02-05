#ifndef EYERLIB_UDPMESSAGE_HPP
#define EYERLIB_UDPMESSAGE_HPP

#include "EyerCore/EyerCore.hpp"

namespace Eyer
{
    class UDPMessage
    {
    public:
        UDPMessage(EyerBuffer & _buffer, EyerSockaddr & _sockaddr);
        ~UDPMessage();
        UDPMessage(const UDPMessage & udpMessage);
        UDPMessage & operator = (const UDPMessage & udpMessage);

    public:
        EyerBuffer buffer;
        EyerSockaddr sockaddr;
    };
}

#endif //EYERLIB_UDPMESSAGE_HPP
