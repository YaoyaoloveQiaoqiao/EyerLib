#include "SIPProcessRegister.hpp"

#include <iostream>
#include <string>
#include <stdio.h>
#include <string.h>
#include <sstream>

#include "EyerSIP/EyerSIP.hpp"

#define NONCE "9bd055"
#define ALGORITHTHM "MD5"

namespace Eyer
{
    int SIPProcessRegister::Process(SIPServerContext * context, struct eXosip_t * excontext, eXosip_event_t * je)
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
            osip_message_t * asw_register = nullptr;
            int ret = eXosip_message_build_answer (excontext, je->tid, 200, &asw_register);

            // TODO 验证信息 这里直接返回 200
            EyerSIPMessgae sipMessgae(asw_register);
            EyerString deviceID         = sipMessgae.GetDeviceId();
            EyerString deviceIp         = sipMessgae.GetIp();
            EyerString devicePort       = sipMessgae.GetPort();

            EyerLog("deviceId: %s\n", deviceID.str);
            EyerLog("deviceIp: %s\n", deviceIp.str);
            EyerLog("devicePort: %s\n", devicePort.str);

            SIPDevice device;
            ret = context->deviceManager.FindDevice(device, deviceID);
            if(ret){
                // 新用户
                EyerLog("New User Register\n");
                context->deviceManager.Register(deviceID, deviceIp, devicePort);
            }
            else{
                // 重复注册
                EyerLog("User Register Again\n");
            }

            osip_message_t * answer = NULL;
            eXosip_message_build_answer (excontext, je->tid, 200, &answer);
            eXosip_message_send_answer (excontext, je->tid, 200, answer);



            EyerString to = EyerString("sip:") + deviceID + "@" + deviceIp + ":" + devicePort;
            char * from = (char *)"sip:34020000002000000001@34020000";
            char * subject = (char *)"34020000001320000001:0,34020000002000000001:0";

            osip_message_t *invite = NULL;
            ret = eXosip_call_build_initial_invite(excontext, &invite, to.str, from, to.str, subject);


            char *localSipId = "34020000002000000001";
            char *localIpAddr= "192.168.2.100";
            //sdp
            char body[500];
            int bodyLen = snprintf(body, 500,
                                   "v=0\r\n"
                                   "o=%s 0 0 IN IP4 %s\r\n"
                                   "s=Play\r\n"
                                   "c=IN IP4 %s\r\n"
                                   "t=0 0\r\n"
                                   "m=video %d RTP/AVP 96 97 98\r\n"
                                   "a=rtpmap:96 PS/90000\r\n"
                                   "a=rtpmap:97 MPEG4/90000\r\n"
                                   "a=rtpmap:98 H264/90000\r\n"
                                   "a=recvonly\r\n"
                                   "y=%s\r\n", localSipId, localIpAddr,
                                   localIpAddr, 6000, "0123");

            osip_message_set_body(invite, body, bodyLen);
            osip_message_set_content_type(invite, "APPLICATION/SDP");

            eXosip_lock(excontext);
            int call_id = eXosip_call_send_initial_invite(excontext, invite);
            eXosip_unlock(excontext);

            /*
            // Query Device Info
            EyerString to = EyerString("sip:") + deviceID + "@" + deviceIp + ":" + devicePort;
            char * from = (char *)"sip:34020000002000000001@34020000";

            osip_message_t * msg = NULL;
            eXosip_message_build_request(excontext, &msg, "MESSAGE", to.str, from, NULL);
            char * queryContent = "<?xml version=\"1.0\"?>\r\n<Query><CmdType>Catalog</CmdType><SN>4</SN><DeviceID>34020000001320000001</DeviceID></Query>";

            osip_message_set_contact(msg, "sip:34020000002000000001@192.168.2.106:5060");
            osip_message_set_body (msg, queryContent, strlen(queryContent));
            osip_message_set_content_type (msg, "Application/MANSCDP+xml");
            eXosip_message_send_request(excontext, msg);
            */


        }
        return 0;
    }
}