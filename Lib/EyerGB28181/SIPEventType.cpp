#include "SIPEventType.hpp"

namespace Eyer
{
    SIPEventType SIPEventType::USER_REGISTER(1, "USER_REGISTER");

    SIPEventType::SIPEventType(int _val, EyerString _name)
    {
        val = _val;
        name = _name;
    }

    SIPEventType::~SIPEventType()
    {

    }

    SIPEventType::SIPEventType(const SIPEventType & eventType)
    {
        *this = eventType;
    }

    SIPEventType & SIPEventType::operator = (const SIPEventType & eventType)
    {
        val = eventType.val;
        name = eventType.name;
        return *this;
    }

    EyerString & SIPEventType::GetName()
    {
        return name;
    }
}