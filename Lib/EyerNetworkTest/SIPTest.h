#ifndef EYERLIB_SIPTEST_H
#define EYERLIB_SIPTEST_H

#include <gtest/gtest.h>
#include <string.h>
#include <stdio.h>

#include <osip2/osip.h>
#include <osipparser2/osip_parser.h>

#include "EyerCore/EyerCore.hpp"
#include "EyerNetwork/EyerNetwork.hpp"

TEST(SIPTest, REGISTER)
{
    printf("=======================SIP Test REGISTER=======================\n");

    char sipStr[] =
             "REGISTER sip:34020000002000000001@3402000000 SIP/2.0\r\n"
             "Via: SIP/2.0/UDP 192.168.2.104:5060;rport;branch=z9hG4bK1202409645\r\n"
             "From: <sip:34020000001320000001@3402000000>;tag=1264282510\r\n"
             "To: <sip:34020000001320000001@3402000000>\r\n"
             "Call-ID: 943904717\r\n"
             "CSeq: 1 REGISTER\r\n"
             "Contact: <sip:34020000001320000001@192.168.2.104:5060>\r\n"
             "Max-Forwards: 70\r\n"
             "User-Agent: IP Camera\r\n"
             "Expires: 3600\r\n"
             "Content-Length: 0\r\n";

    parser_init();

    osip_message_t *sip;
    int osip_ret;
    osip_ret = osip_message_init(&sip);
    osip_ret = osip_message_parse(sip, sipStr, strlen(sipStr));

    // osip_message_get_via()

    printf("sip_version: %s\n", sip->sip_version);
    printf("sip_method: %s\n", sip->sip_method);
    printf("req_uri->string: %s\n", sip->req_uri->password);
    printf("sip->to->url->host: %s\n", sip->to->url->host);

    osip_message_free(sip);
}


TEST(SIPTest, REGISTER_401) {
    printf("=======================SIP Test REGISTER_401=======================\n");

    parser_init();

    osip_message_t *sip;
    int osip_ret;
    osip_ret = osip_message_init(&sip);

    // osip_message_set_method(sip, "REGISTER");
    osip_message_set_version(sip, osip_strdup("SIP/2.0"));
    osip_message_set_via(sip, "SIP/2.0/UDP 192.168.2.104:5060;rport;branch=z9hG4bK1202409645");
    osip_message_set_status_code(sip, 401);
    osip_message_set_reason_phrase (sip, osip_strdup("Unauthorized"));

    char * str_out = nullptr;
    size_t str_out_len = 0;
    osip_message_to_str(sip, &str_out, &str_out_len);

    printf("%s\n", str_out);

    osip_message_free(sip);
}

#endif //EYERLIB_SIPTEST_H
