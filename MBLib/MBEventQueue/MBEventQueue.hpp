//
// Created by redknot on 2020/3/26.
//

#ifndef EYE_LIB_EYEREVENTQUEUE_HPP
#define EYE_LIB_EYEREVENTQUEUE_HPP

#include "MBCore/MBCore.hpp"

#include <queue>
#include <mutex>

namespace MB
{
    class MBEventQueue;
    class MBEvent;

    class MBEventQueue
    {
    public:
        MBEventQueue();
        ~MBEventQueue();

        int Push(MBEvent * event);
        int Pop();

        int Front(MBEvent * & event);

        int FrontTarget(MBEvent * & event, const MBString & target);
        int FrontTargetAndPop(MBEvent * & event, const MBString & target);

        long long GetEventId();
    private:
        std::queue<MBEvent *> eventQueue;
        std::mutex mutex;

        long long idIndex = 0;
    };


    class MBEvent
    {
    public:
        MBEvent();
        virtual ~MBEvent();

        MBEvent(MBEvent & event);

        MBEvent & operator = (const MBEvent & event);

        virtual int GetType() = 0;

        MBString GetFrom();
        MBString GetTo();

        int SetFrom(const MBString & from);
        int SetTo(const MBString & to);

        int SetId(long long id);
        long long GetId();

        int SetRequestId(long long id);
        long long GetRequestId();
    private:
        MBString from;
        MBString to;

        long long id = 0;
        long long requestId = 0;
    };
}

#endif //EYE_LIB_EYEREVENTQUEUE_HPP
