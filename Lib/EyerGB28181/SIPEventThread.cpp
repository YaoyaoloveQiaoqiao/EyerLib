#include "Event/EventStartRealTimeVideoResponse.hpp"
#include "SIPEventThread.hpp"

#include "EyerCore/EyerCore.hpp"
#include "SIPServerContext.hpp"
#include "Event/EventUserRegister.hpp"

namespace Eyer
{
    SIPEventThread::SIPEventThread(SIPServerContext * _context)
    {
        context = _context;
    }

    SIPEventThread::~SIPEventThread()
    {
        while(context->eventQueue.Size() > 0){
            SIPEvent * event = nullptr;
            context->eventQueue.GetEvent(&event);
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

            SIPEvent * event = nullptr;
            context->eventQueue.GetEvent(&event);
            if(event != nullptr){
                if(event->to == SIPEventTarget::SIPEventTarget_EventThread){
                    SIPEventType eventType = event->GetEventType();
                    if(eventType == SIPEventType::USER_REGISTER){
                        if(context->callback != nullptr){
                            EventUserRegister * eventUserRegister = (EventUserRegister *)event;
                            context->callback->UserRegister(eventUserRegister->deviceId);
                        }
                    }
                    if(eventType == SIPEventType::REALTIME_RESPONSE){
                        EventStartRealTimeVideoResponse * eventStartRealTimeVideoResponse = (EventStartRealTimeVideoResponse *)event;
                        EyerLog("EventStartRealTimeVideoResponse Callback\n");
                    }

                    delete event;
                    event = nullptr;
                }
                else{
                    context->eventQueue.PutEvent(event);
                }
            }
        }
    }
}