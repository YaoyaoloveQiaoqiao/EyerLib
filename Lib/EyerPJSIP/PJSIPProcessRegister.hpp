#ifndef EYERLIB_PJSIPPROCESSREGISTER_HPP
#define EYERLIB_PJSIPPROCESSREGISTER_HPP

#include "PJSIPHeader.hpp"

namespace Eyer
{
    class PJSIPProcessRegister {
    public:
        pj_bool_t Process(pjsip_rx_data * rdata);
    };
}

#endif //EYERLIB_PJSIPPROCESSREGISTER_HPP
