#include "SIPProcessMessage.hpp"

namespace Eyer
{
    int SIPProcessMessage::Process(struct eXosip_t * excontext, eXosip_event_t * je)
    {
        osip_message_t * answer = NULL;
        eXosip_message_build_answer (excontext, je->tid, 200, &answer);
        eXosip_message_send_answer (excontext, je->tid, 200, answer);
        return 0;
    }
}