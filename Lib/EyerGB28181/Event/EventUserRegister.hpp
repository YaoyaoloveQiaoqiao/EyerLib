#ifndef EYERLIB_EVENTUSERREGISTER_HPP
#define EYERLIB_EVENTUSERREGISTER_HPP

#include "SIPEvent.hpp"

namespace Eyer
{
    class EventUserRegister : public SIPEvent{
    public:
        EventUserRegister();
        ~EventUserRegister();

        SIPEventType GetEventType();
    };
}

#endif //EYERLIB_EVENTUSERREGISTER_HPP
