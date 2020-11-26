#include "SIPProcessRegister.hpp"

#include <iostream>
#include <string>
#include <stdio.h>
#include <string.h>
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

            char * str = NULL;
            size_t _strlen = 0;
            osip_message_to_str(answer, &str, &_strlen);

            printf("12345: %s\n", str);








            char * to = (char *)"sip:34020000001320000001@192.168.2.101";
            char * from = (char *)"sip:Server@192.168.2.102";
            osip_message_t * invite = NULL;
            int ret = eXosip_call_build_initial_invite(excontext, &invite, to, from, NULL, "This si a call for a conversation");

            char tmp[4096];
            char * localip = "192.168.2.102";
            char * port = "5555";
            snprintf (tmp, 4096,
                      "v=0\r\n"                           // SDP版本
                      "o=josua 0 0 IN IP4 %s\r\n"         // 用户名、ID、版本、网络类型、地址类型、IP地址
                      "s=conversation\r\n"                // 会话名称
                      "c=IN IP4 %s\r\n"
                      "t=0 0\r\n"                         // 开始时间、结束时间。此处不需要设置
                      "m=audio %s RTP/AVP 0 8 101\r\n"    // 音频、传输端口、传输类型、格式列表
                      "a=rtpmap:0 PCMU/8000\r\n"          // 以下为具体描述格式列表中的
                      "a=rtpmap:8 PCMA/8000\r\n"
                      "a=rtpmap:101 telephone-event/8000\r\n"
                      "a=fmtp:101 0-11\r\n", localip, localip, port);

            osip_message_set_body (invite, tmp, strlen (tmp));
            osip_message_set_content_type (invite, "application/sdp");

            ret = eXosip_call_send_initial_invite (excontext, invite);
        }
        return 0;
    }
}