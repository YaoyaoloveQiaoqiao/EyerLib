#ifndef EYERLIB_EYERSPS_HPP
#define EYERLIB_EYERSPS_HPP

#include "EyerNALU.hpp"

namespace Eyer{
    typedef enum {
        FALSE,
        TRUE
    } Boolean;

    class EyerSPS {
    public:
        EyerSPS(EyerNALU & _nalu);
        ~EyerSPS();

        int PrintInfo();

    private:
        EyerNALU nalu;

        unsigned int profile_idc;                                       // u(8)
    };
}

#endif //EYERLIB_EYERSPS_HPP
