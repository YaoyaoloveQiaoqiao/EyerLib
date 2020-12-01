#include <gtest/gtest.h>
#include "EyerCore/EyerCore.hpp"

#include <pjsip.h>
#include <pjlib-util.h>
#include <pjlib.h>
#include <pjsip_ua.h>
#include <pjmedia.h>
#include <pjsip/sip_auth_parser.h>
#include <pjsip/sip_endpoint.h>


TEST(PJSIP, PJSIPTest)
{
    printf("Eyer PJSIP Test Start\n");

    int port = 5060;

    int logLevel = PJ_LOG_MAX_LEVEL;
    pj_log_set_level(logLevel);


    pj_status_t status;
    status = pj_init();
    if (PJ_SUCCESS != status) {
        EyerLog("初始化[pj_init]失败: %d\n", status);
        return;
    }
    /* Then init PJLIB-UTIL: */
    status = pjlib_util_init();
    if (PJ_SUCCESS != status) {
        EyerLog("初始化[pjlib_util_init]失败: %d\n", status);
        return;
    }

    /* Must create a pool factory before we can allocate any memory. */
    pj_caching_pool m_cp;
    pj_caching_pool_init(&m_cp, &pj_pool_factory_default_policy, 0);

    /* Create the endpoint: */
    pjsip_endpoint *mp_sip_endpt;
    status = pjsip_endpt_create(&m_cp.factory, nullptr, &mp_sip_endpt);
    if (PJ_SUCCESS != status) {
        EyerLog("创建pj端点失败: %d\n", status);
        return;
    }

    pj_sockaddr_in addr;
    addr.sin_family = pj_AF_INET();
    addr.sin_addr.s_addr = 0;
    addr.sin_port = pj_htons(static_cast<pj_uint16_t>(port));
    status = pjsip_udp_transport_start(mp_sip_endpt, &addr, nullptr, 1, nullptr);
    if (status != PJ_SUCCESS) {
        EyerLog("创建udp传输失败: %d\n", status);
        return;
    }

    status = pjsip_tsx_layer_init_module(mp_sip_endpt);
    if (status != PJ_SUCCESS) {
        EyerLog("初始化事务层模块失败: %d\n", status);
        return;
    }

    status = pjsip_ua_init_module(mp_sip_endpt, NULL);
    if (status != PJ_SUCCESS) {
        EyerLog("初始化ua层模块失败: %d\n", status);
        return;
    }

    for(int i=0;i<60;i++){
        Eyer::EyerTime::EyerSleepMilliseconds(1000);
    }

    printf("Eyer PJSIP Test End\n");
}

int main(int argc,char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
