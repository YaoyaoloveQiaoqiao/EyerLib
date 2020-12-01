#include "SIPProcessMessage.hpp"

#include <string>

namespace Eyer
{
    int SIPProcessMessage::Process(SIPServerContext * context, struct eXosip_t * excontext, eXosip_event_t * je)
    {
        osip_body_t * dest = NULL;
        osip_message_get_body(je->request, 0, &dest);
        if(dest != NULL){
            printf("%s\n", dest->body);
        }

        osip_message_t * answer = NULL;
        eXosip_message_build_answer (excontext, je->tid, 200, &answer);
        eXosip_message_send_answer (excontext, je->tid, 200, answer);

        return 0;
    }
}