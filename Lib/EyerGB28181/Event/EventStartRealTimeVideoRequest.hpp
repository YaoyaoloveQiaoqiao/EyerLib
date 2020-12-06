#ifndef EYERLIB_EVENTSTARTREALTIMEVIDEOREQUEST_HPP
#define EYERLIB_EVENTSTARTREALTIMEVIDEOREQUEST_HPP

#include "SIPEvent.hpp"

namespace Eyer
{
    class EventStartRealTimeVideoRequest : public SIPEvent{
    public:
        EventStartRealTimeVideoRequest();
        ~EventStartRealTimeVideoRequest();

        EventStartRealTimeVideoRequest(const EventStartRealTimeVideoRequest & event);
        EventStartRealTimeVideoRequest & operator = (const EventStartRealTimeVideoRequest & event);

        virtual SIPEventType GetEventType();

        virtual int Do(struct eXosip_t * excontext, SIPServerContext * context);

    public:
        EyerString streamServerIp;
        int streamServerPort;
        EyerString deviceId;
        EyerString channelId;
    };
}

#endif //EYERLIB_EVENTSTARTREALTIMEVIDEOREQUEST_HPP
