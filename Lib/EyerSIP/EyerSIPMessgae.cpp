#include "EyerSIPMessgae.hpp"
#include "EyerSIPMessgaePrivate.hpp"
#include "EyerSIPFromPrivate.hpp"
#include "EyerSIPCallIDPrivate.hpp"

namespace Eyer
{
    EyerSIPMessgae::EyerSIPMessgae()
    {
        parser_init();
        impl = new EyerSIPMessgaePrivate();
        osip_message_init(&impl->sip);
    }

    EyerSIPMessgae::~EyerSIPMessgae()
    {
        if(impl->sip != nullptr){
            osip_message_free(impl->sip);
            impl->sip = nullptr;
        }
        if(impl != nullptr){
            delete impl;
            impl = nullptr;
        }
    }

    int EyerSIPMessgae::Parse(EyerBuffer & buffer)
    {
        int ret = osip_message_parse(impl->sip, (const char *)buffer.GetPtr(), buffer.GetLen());
        if(ret){
            return ret;
        }

        impl->method = osip_message_get_method(impl->sip);

        osip_from_t * from = osip_message_get_from(impl->sip);
        osip_to_t * to = osip_message_get_to(impl->sip);

        return ret;
    }

    EyerString & EyerSIPMessgae::GetMethod()
    {
        return impl->method;
    }

    int EyerSIPMessgae::GetFrom(EyerSIPFrom & from)
    {
        osip_from_t * from_t = osip_message_get_from(impl->sip);
        osip_from_clone(from_t, &from.impl->from);
        return 0;
    }

    int EyerSIPMessgae::GetTo(EyerSIPFrom & to)
    {
        osip_from_t * from_t = osip_message_get_to(impl->sip);
        osip_from_clone(from_t, &to.impl->from);
        return 0;
    }

    int EyerSIPMessgae::GetCallID(EyerSIPCallID & callId)
    {
        osip_call_id_clone(impl->sip->call_id, &callId.impl->call_id);
        return 0;
    }



    int EyerSIPMessgae::SetFrom(EyerSIPFrom & from)
    {
        osip_to_clone(from.impl->from, &impl->sip->from);
        return 0;
    }

    int EyerSIPMessgae::SetInfo()
    {
        osip_message_set_version(impl->sip, osip_strdup("SIP/2.0"));
        osip_message_set_status_code(impl->sip, 401);
        osip_message_set_reason_phrase (impl->sip, osip_strdup("Unauthorized"));
        return 0;
    }

    int EyerSIPMessgae::SetTo(EyerSIPFrom & to)
    {
        osip_to_clone(to.impl->from, &impl->sip->to);
        return 0;
    }

    int EyerSIPMessgae::SetCallID(EyerSIPCallID & callId)
    {
        osip_call_id_clone(callId.impl->call_id, &impl->sip->call_id);
        return 0;
    }

    EyerBuffer EyerSIPMessgae::ToBuffer()
    {
        char * dest = nullptr;
        size_t message_length = 0;
        osip_message_to_str(impl->sip, &dest, &message_length);

        printf("message_length: %d\n", message_length);
        printf("message:\n%s\n", dest);

        EyerBuffer buffer;
        buffer.Append((unsigned char *)dest, message_length);

        return buffer;
    }
}