//
// Created by redknot on 2020/3/26.
//

#include "MBEventQueue.hpp"

namespace MB
{
    MBEventQueue::MBEventQueue()
    {

    }

    MBEventQueue::~MBEventQueue()
    {

    }

    int MBEventQueue::FrontTargetAndPop(MBEvent * & event, const MBString & target)
    {
        mutex.lock();
        if(eventQueue.size() > 0) {
            MBEvent * e = eventQueue.front();
            if(e == nullptr){
                mutex.unlock();
                return -1;
            }
            if(e->GetTo() == target){
                event = e;
                eventQueue.pop();
                mutex.unlock();
                return 0;
            }
        }
        mutex.unlock();
        return -1;
    }

    int MBEventQueue::FrontTarget(MBEvent * & event, const MBString & target)
    {
        mutex.lock();
        if(eventQueue.size() > 0) {
            MBEvent * e = eventQueue.front();
            if(e == nullptr){
                mutex.unlock();
                return 0;
            }
            if(e->GetTo() == target){
                event = e;
                mutex.unlock();
                return 0;
            }
        }
        mutex.unlock();
        return -1;
    }

    int MBEventQueue::Push(MBEvent * event)
    {
        mutex.lock();
        eventQueue.push(event);
        mutex.unlock();

        return 0;
    }

    int MBEventQueue::Pop()
    {
        mutex.lock();
        if(eventQueue.size() > 0){
            eventQueue.pop();
        }
        mutex.unlock();

        return 0;
    }

    int MBEventQueue::Front(MBEvent * & event)
    {
        mutex.lock();
        if(eventQueue.size() > 0){
            event = eventQueue.front();
        }
        mutex.unlock();

        return 0;
    }

    long long MBEventQueue::GetEventId()
    {
        idIndex++;
        return idIndex;
    }
}