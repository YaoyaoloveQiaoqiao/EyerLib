#ifndef EYERLIB_SIPPROCESS_HPP
#define EYERLIB_SIPPROCESS_HPP

#include "eXosipHeader.hpp"

namespace Eyer
{
    class SIPProcess {
    public:
        virtual int Process(struct eXosip_t * excontext, eXosip_event_t * je) = 0;
    };
}

#endif //EYERLIB_SIPPROCESS_HPP
