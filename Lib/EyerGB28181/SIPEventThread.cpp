#include "SIPEventThread.hpp"

#include "EyerCore/EyerCore.hpp"
#include "SIPServerContext.hpp"

namespace Eyer
{
    SIPEventThread::SIPEventThread(SIPServerContext * _context)
    {
        context = _context;
    }

    SIPEventThread::~SIPEventThread()
    {
        while(eventQueue.Size() > 0){
            SIPEvent * event = nullptr;
            eventQueue.GetEvent(&event);
            if(event != nullptr){
                delete event;
                event = nullptr;
            }
        }
    }

    void SIPEventThread::Run()
    {
        while(!stopFlag){
            Eyer::EyerTime::EyerSleepMilliseconds(1);

            {
                SIPEvent * event = nullptr;
                context->eventQueue.GetEvent(&event);
                if(event != nullptr){
                    eventQueue.PutEvent(event);
                }
            }

            {
                SIPEvent * event = nullptr;
                eventQueue.GetEvent(&event);
                if(event != nullptr){
                    SIPEventType eventType = event->GetEventType();

                    if(context->callback != nullptr){
                        context->callback->UserRegister();
                    }

                    delete event;
                    event = nullptr;
                }
            }
        }
    }
}