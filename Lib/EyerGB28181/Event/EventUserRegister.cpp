#include "EventUserRegister.hpp"

namespace Eyer
{
    EventUserRegister::EventUserRegister()
    {

    }

    EventUserRegister::~EventUserRegister()
    {

    }

    SIPEventType EventUserRegister::GetEventType()
    {
        return SIPEventType::USER_REGISTER;
    }
}