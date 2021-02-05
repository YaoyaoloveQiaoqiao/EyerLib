#include "EyerUDPThread.hpp"

namespace Eyer
{
    UDPMessage::UDPMessage(EyerBuffer & _buffer, EyerSockaddr & _sockaddr)
    {
        buffer = _buffer;
        sockaddr = _sockaddr;
    }

    UDPMessage::~UDPMessage()
    {

    }

    UDPMessage::UDPMessage(const UDPMessage & udpMessage)
    {
        *this = udpMessage;
    }

    UDPMessage & UDPMessage::operator = (const UDPMessage & udpMessage)
    {
        buffer = udpMessage.buffer;
        sockaddr = udpMessage.sockaddr;
        return *this;
    }
}