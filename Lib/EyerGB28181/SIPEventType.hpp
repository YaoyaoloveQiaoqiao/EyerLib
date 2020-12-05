#ifndef EYERLIB_SIPEVENTTYPE_HPP
#define EYERLIB_SIPEVENTTYPE_HPP

#include "EyerCore/EyerCore.hpp"

namespace Eyer
{
    class SIPEventType {
    public:
        SIPEventType(int _val, EyerString _name);
        ~SIPEventType();

        SIPEventType(const SIPEventType & eventType);
        SIPEventType & operator = (const SIPEventType & eventType);

        EyerString & GetName();

    private:
        int val;
        EyerString name;
    public:
        static SIPEventType USER_REGISTER;
    };
}

#endif //EYERLIB_SIPEVENTTYPE_HPP
