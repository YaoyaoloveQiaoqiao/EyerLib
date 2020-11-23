#ifndef EYERLIB_SIPPROCESSREGISTER_HPP
#define EYERLIB_SIPPROCESSREGISTER_HPP

#include "SIPProcess.hpp"

namespace Eyer
{
    class SIPProcessRegister : public SIPProcess {
    public:
        virtual int Process(struct eXosip_t * excontext, eXosip_event_t * je);
    };
}

#endif //EYERLIB_SIPPROCESSREGISTER_HPP
