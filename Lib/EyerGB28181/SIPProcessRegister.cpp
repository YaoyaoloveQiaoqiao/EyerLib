#include "SIPProcessRegister.hpp"

#include <iostream>
#include <string>
#include <sstream>

#define NONCE "9bd055"
#define ALGORITHTHM "MD5"

namespace Eyer
{
    int SIPProcessRegister::Process(struct eXosip_t * excontext, eXosip_event_t * je)
    {
        osip_authorization_t * auth = NULL;
        osip_message_get_authorization(je->request, 0, &auth);

        if (NULL == auth) {
            // 401
            osip_message_t * answer = NULL;
            int result = eXosip_message_build_answer(excontext, je->tid, 401, &answer);

            std::stringstream stream;
            std::string nonce = NONCE;
            std::string algorithm = ALGORITHTHM;
            stream << "Digest realm=\"" << "abc"
                   << "\",nonce=\"" << nonce
                   << "\",algorithm=" << algorithm;
            osip_message_set_header(answer, "WWW-Authenticate", stream.str().c_str());

            eXosip_lock(excontext);
            eXosip_message_send_answer(excontext, je->tid, 401, answer);
            eXosip_unlock(excontext);
        }
        else{
            // 200
            // TODO 验证信息 这里直接返回 200
            osip_message_t * answer = NULL;
            eXosip_message_build_answer (excontext, je->tid, 200, &answer);
            eXosip_message_send_answer (excontext, je->tid, 200, answer);
        }
        return 0;
    }
}