#include "EyerSockaddr.hpp"

namespace Eyer
{
    EyerSockaddr::EyerSockaddr()
    {

    }

    EyerSockaddr::~EyerSockaddr()
    {

    }

    EyerSockaddr::EyerSockaddr(const EyerSockaddr & addr)
    {
        *this = addr;
    }

    EyerSockaddr & EyerSockaddr::operator = (const EyerSockaddr & _addr)
    {
        int len = sizeof(sockaddr_in);
        memcpy(&addr, &_addr.addr, len);
        return *this;
    }

    int EyerSockaddr::GetLen()
    {
        return sizeof(sockaddr_in);
    }

    void * EyerSockaddr::GetPtr()
    {
        return &addr;
    }
}