#ifndef EYERLIB_SIPMESSGAE_HPP
#define EYERLIB_SIPMESSGAE_HPP

#include <gtest/gtest.h>
#include "EyerSIP/EyerSIP.hpp"

TEST(SIP, SIPMessage)
{
    printf("=======================SIP Test SIPMessage=======================\n");

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

    Eyer::EyerBuffer buffer;
    buffer.Append((uint8_t *)sipStr, strlen(sipStr));

    Eyer::EyerSIPMessgae sipMessgae;

    int ret = sipMessgae.Parse(buffer);
}

#endif //EYERLIB_SIPMESSGAE_HPP
