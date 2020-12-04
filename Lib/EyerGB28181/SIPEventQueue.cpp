#include "SIPEventQueue.hpp"

namespace Eyer
{
    SIPEventQueue::SIPEventQueue()
    {

    }

    SIPEventQueue::~SIPEventQueue()
    {
        while(eventQueue.Size() > 0){
            SIPEvent * event = nullptr;
            eventQueue.FrontPop(&event);
            if(event != nullptr){
                delete event;
                event = nullptr;
            }
        }
    }
}