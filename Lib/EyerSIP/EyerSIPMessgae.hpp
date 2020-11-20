#ifndef EYERLIB_EYERSIPMESSGAE_HPP
#define EYERLIB_EYERSIPMESSGAE_HPP

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "EyerCore/EyerCore.hpp"
#include "EyerSIPFrom.hpp"
#include "EyerSIPCallID.hpp"

namespace Eyer
{
    class EyerSIPMessgaePrivate;

    class EyerSIPMessgae {
    public:
        EyerSIPMessgae();
        ~EyerSIPMessgae();

        int Parse(EyerBuffer & buffer);




        EyerString & GetMethod();

        int GetFrom(EyerSIPFrom & from);
        int GetTo(EyerSIPFrom & to);
        int GetCallID(EyerSIPCallID & callId);



        int SetInfo();

        int SetFrom(EyerSIPFrom & from);
        int SetTo(EyerSIPFrom & to);
        int SetCallID(EyerSIPCallID & callId);

        EyerBuffer ToBuffer();
    private:
        EyerSIPMessgaePrivate * impl = nullptr;
    };
}

#endif //EYERLIB_EYERSIPMESSGAE_HPP
