#include "EyerSIPMessgae.hpp"
#include "EyerSIPMessgaePrivate.hpp"

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

    int EyerSIPMessgae::Parse(const uint8_t * buf, size_t length)
    {
        int ret = osip_message_parse(impl->sip, (const char *)buf, length);
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
}