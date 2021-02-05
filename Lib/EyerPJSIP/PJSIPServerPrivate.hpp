#ifndef EYERLIB_PJSIPSERVERPRIVATE_HPP
#define EYERLIB_PJSIPSERVERPRIVATE_HPP

#include "PJSIPHeader.hpp"

namespace Eyer
{
    class PJSIPServerPrivate
    {
    public:
        int port = 5060;

        static pjsip_endpoint * mp_sip_endpt;
        pj_caching_pool m_cp;
        struct pjsip_module m_module;
        pj_pool_t * mp_pool = nullptr;
        pj_thread_t * mp_thread = nullptr;
    };
}

#endif //EYERLIB_PJSIPSERVERPRIVATE_HPP
