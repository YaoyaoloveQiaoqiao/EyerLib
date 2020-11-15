#ifndef EYERLIB_SIPTEST_H
#define EYERLIB_SIPTEST_H

#include <gtest/gtest.h>
#include <string.h>
#include <stdio.h>

#include <osip2/osip.h>
#include <osipparser2/osip_parser.h>

#include "EyerCore/EyerCore.hpp"
#include "EyerNetwork/EyerNetwork.hpp"

TEST(EyerNetwork, SIPTest)
{
    printf("=======================SipTest=======================\n");

    char a[] = "REGISTER sip:34020000002000000001@3402000000 SIP/2.0\n"
             "Via: SIP/2.0/UDP 192.168.2.104:5060;rport;branch=z9hG4bK1202409645\n"
             "From: <sip:34020000001320000001@3402000000>;tag=1264282510\n"
             "To: <sip:34020000001320000001@3402000000>\n"
             "Call-ID: 943904717\n"
             "CSeq: 1 REGISTER\n"
             "Contact: <sip:34020000001320000001@192.168.2.104:5060>\n"
             "Max-Forwards: 70\n"
             "User-Agent: IP Camera\n"
             "Expires: 3600\n"
             "Content-Length: 0";

    parser_init();

    osip_message_t *sip;
    int osip_ret;
    osip_ret = osip_message_init(&sip);
    osip_ret = osip_message_parse(sip, a, strlen(a));
    osip_message_free(sip);
}

#endif //EYERLIB_SIPTEST_H
