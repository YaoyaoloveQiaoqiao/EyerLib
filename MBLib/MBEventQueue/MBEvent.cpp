//
// Created by redknot on 2020/3/26.
//

#include "MBEventQueue.hpp"

namespace MB
{
    MBEvent::MBEvent()
    {

    }

    MBEvent::~MBEvent()
    {

    }

    MBEvent::MBEvent(MBEvent & event)
    {
        *this = event;
    }

    MBEvent & MBEvent::operator = (const MBEvent & event)
    {
        from = event.from;
        to = event.to;
        id = event.id;

        return *this;
    }

    MBString MBEvent::GetFrom()
    {
        return from;
    }

    MBString MBEvent::GetTo()
    {
        return to;
    }

    int MBEvent::SetFrom(const MBString & _from)
    {
        from = _from;
        return 0;
    }

    int MBEvent::SetTo(const MBString & _to)
    {
        to = _to;
        return 0;
    }

    int MBEvent::SetId(long long _id)
    {
        id = _id;
        return  0;
    }

    long long MBEvent::GetId()
    {
        return id;
    }

    int MBEvent::SetRequestId(long long id)
    {
        requestId = id;
        return 0;
    }
    long long MBEvent::GetRequestId()
    {
        return requestId;
    }
}