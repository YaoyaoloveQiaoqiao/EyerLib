#include "SIPProcessMessage.hpp"

#include <string>
#include <EyerSIP/EyerSIPMessgae.hpp>

namespace Eyer
{
    int SIPProcessMessage::Process(SIPServerContext * context, struct eXosip_t * excontext, eXosip_event_t * je)
    {
        osip_body_t * dest = NULL;
        osip_message_get_body(je->request, 0, &dest);
        if(dest != NULL){
            printf("%s\n", dest->body);
        }

        // 验证是否已经注册
        EyerSIPMessgae sipMessgae(je->request);
        EyerString deviceID = sipMessgae.GetDeviceId();

        SIPDevice device;
        int ret = context->deviceManager.FindDevice(device, deviceID);
        if(ret){
            // 尚未注册
            printf("No Register\n");
            osip_message_t * answer = NULL;
            eXosip_message_build_answer (excontext, je->tid, 407, &answer);
            eXosip_message_send_answer (excontext, je->tid, 407, answer);
        }
        else{
            // 已经注册
            printf("Already Register\n");
            osip_message_t * answer = NULL;
            eXosip_message_build_answer (excontext, je->tid, 200, &answer);
            eXosip_message_send_answer (excontext, je->tid, 200, answer);
        }

        return 0;
    }
}