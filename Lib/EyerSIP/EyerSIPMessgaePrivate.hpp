#ifndef EYERLIB_EYERSIPMESSGAEPRIVATE_HPP
#define EYERLIB_EYERSIPMESSGAEPRIVATE_HPP

#include <osipparser2/osip_parser.h>

namespace Eyer
{
    class EyerSIPMessgaePrivate
    {
    public:
        osip_message_t * sip = nullptr;
    };
}

#endif //EYERLIB_EYERSIPMESSGAEPRIVATE_HPP
