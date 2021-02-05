#include <gtest/gtest.h>
#include "EyerCore/EyerCore.hpp"

#include <pjsip.h>
#include <pjlib-util.h>
#include <pjlib.h>
#include <pjsip_ua.h>
#include <pjmedia.h>
#include <pjsip/sip_auth_parser.h>
#include <pjsip/sip_endpoint.h>

pjsip_endpoint * mp_sip_endpt = nullptr;

pj_bool_t at_rx_request(pjsip_rx_data * rdata) {
    EyerLog("at_rx_request\n");
    if (pjsip_method_e::PJSIP_REGISTER_METHOD == rdata->msg_info.cseq->method.id){
        auto hdr_expires = (pjsip_expires_hdr *)pjsip_msg_find_hdr(rdata->msg_info.msg, pjsip_hdr_e::PJSIP_H_EXPIRES, nullptr);
        if (nullptr == hdr_expires) {
            EyerLog("未知\n");
        }
        else if (0 != hdr_expires->ivalue) {
            EyerLog("注册\n");
        }
        else {
            EyerLog("注销\n");
        }

        auto hdr = (pjsip_www_authenticate_hdr *)pjsip_msg_find_hdr(rdata->msg_info.msg, pjsip_hdr_e::PJSIP_H_AUTHORIZATION, nullptr);
        if (nullptr == hdr){
            hdr = pjsip_www_authenticate_hdr_create(rdata->tp_info.pool);
            char nonce_buf[16];
            pj_str_t random;
            random.ptr = nonce_buf;
            random.slen = sizeof(nonce_buf);
            hdr->scheme = pjsip_DIGEST_STR;
            pj_create_random_string(nonce_buf, sizeof(nonce_buf));
            pj_strdup2(rdata->tp_info.pool, &hdr->challenge.digest.nonce, nonce_buf);
            pj_strdup2(rdata->tp_info.pool, &hdr->challenge.digest.realm, "123");

            pjsip_tx_data *p_tdata = nullptr;
            pjsip_response_addr res_addr;
            pj_status_t status = pjsip_endpt_create_response(mp_sip_endpt, rdata, 401, nullptr, &p_tdata);
            status = pjsip_get_response_addr(rdata->tp_info.pool, rdata, &res_addr);
            pjsip_msg_add_hdr(p_tdata->msg, (pjsip_hdr *)hdr);
            status = pjsip_endpt_send_response(mp_sip_endpt, &res_addr, p_tdata, nullptr, nullptr);
            if (PJ_SUCCESS != status){
                EyerLog("发送回应帧[401]失败: %d\n", status);
                return PJ_FALSE;
            }


            // 发送目录查询
            {
                /*
                pjsip_tx_data *p_tdata = nullptr;
                pjsip_method m;
                m.id = PJSIP_OTHER_METHOD;
                m.name = pj_strdup3(rdata->tp_info.pool, "MESSAGE");
                auto pj_target = pj_strdup3(rdata->tp_info.pool, "sip:34020000001320000001@192.168.2.101:5060");
                auto pj_from = pj_strdup3(rdata->tp_info.pool, "sip:ServerA@Server");
                auto pj_to = pj_strdup3(rdata->tp_info.pool, "sip:34020000001320000001@Server");
                auto pj_contact = pj_strdup3(rdata->tp_info.pool, "<sip:ServerA@192.168.2.106:5060>");
                status = pjsip_endpt_create_request(mp_sip_endpt, &m, &pj_target, &pj_from, &pj_to, &pj_contact, nullptr, -1, nullptr, &p_tdata);

                auto pj_type = pj_strdup3(rdata->tp_info.pool, "Application");
                auto pj_subtype = pj_strdup3(rdata->tp_info.pool, "MANSCDP+xml");
                auto pj_text = pj_strdup3(rdata->tp_info.pool, "<?xml version=\"1.0\"?>\r\n<Query><CmdType>Catalog</CmdType><SN>2</SN><DeviceID>34020000001320000001</DeviceID></Query>");
                p_tdata->msg->body = pjsip_msg_body_create(rdata->tp_info.pool, &pj_type, &pj_subtype, &pj_text);
                status = pjsip_endpt_send_request(mp_sip_endpt, p_tdata, -1, nullptr, nullptr);
                if (PJ_SUCCESS != status)
                {
                    printf("Send Catalog Error\n");
                }
                 */
            }

            return PJ_TRUE;
        }
        else{
            std::string str_date = "2020-12-1T23:00:00";
            pj_str_t n, v;
            pj_strdup2(rdata->tp_info.pool, &n, "Date");
            pj_strdup2(rdata->tp_info.pool, &v, str_date.c_str());
            auto hdr_date = pjsip_generic_string_hdr_create(rdata->tp_info.pool, &n, &v);
            pj_strdup2(rdata->tp_info.pool, &n, "Expires");
            pj_strdup2(rdata->tp_info.pool, &v, "3600");
            auto hdr_expires = pjsip_generic_string_hdr_create(rdata->tp_info.pool, &n, &v);

            pjsip_tx_data *p_tdata = nullptr;
            pjsip_response_addr res_addr;
            pj_status_t status = pjsip_endpt_create_response(mp_sip_endpt, rdata, 200, nullptr, &p_tdata);
            status = pjsip_get_response_addr(rdata->tp_info.pool, rdata, &res_addr);
            pjsip_msg_add_hdr(p_tdata->msg, (pjsip_hdr *)hdr_date);
            pjsip_msg_add_hdr(p_tdata->msg, (pjsip_hdr *)hdr_expires);

            status = pjsip_endpt_send_response(mp_sip_endpt, &res_addr, p_tdata, nullptr, nullptr);
            if (PJ_SUCCESS != status) {
                EyerLog("发送回应帧[200]失败: %d\n", status);
                return PJ_FALSE;
            }
            EyerLog("成功\n");
            return PJ_TRUE;
        }
    }

    else{
        /*
        reinterpret_cast<char *>(rdata->msg_info.msg->body->data);
        rdata->msg_info.msg->body->len;
        */

        // printf("%s\n", reinterpret_cast<char *>(rdata->msg_info.msg->body->data));
    }

    return PJ_FALSE;
}
pj_bool_t at_rx_response(pjsip_rx_data *rdata) {
    EyerLog("at_rx_response\n");
    return PJ_FALSE;
}
pj_status_t at_tx_request(pjsip_tx_data *tdata) {
    EyerLog("at_tx_request\n");
    return PJ_SUCCESS;
}
pj_status_t at_tx_response(pjsip_tx_data *tdata) {
    EyerLog("at_tx_response\n");
    return PJ_SUCCESS;
}
void at_tsx_state(pjsip_transaction *tsx, pjsip_event *event) {
    EyerLog("at_tsx_state\n");
}


int worker_thread(void *arg)
{
    EyerLog("工作线程开始\n");
    while (1) {
        pj_time_val timeout = {0, 1};
        pjsip_endpt_handle_events((pjsip_endpoint *)arg, &timeout);
    }
    EyerLog("工作线程结束\n");
    return 0;
}

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



    /*
     * Register our module to receive incoming requests.
     */
    struct pjsip_module m_module;
    char tmp_str[128] = { 0 };
    sprintf(tmp_str, "server_sip");
    m_module.name.ptr = tmp_str;
    m_module.name.slen = strlen(tmp_str);
    m_module.id = -1;
    m_module.load = nullptr;
    m_module.unload = nullptr;
    m_module.start = nullptr;
    m_module.stop = nullptr;
    m_module.priority = PJSIP_MOD_PRIORITY_APPLICATION;
    m_module.on_rx_request = &at_rx_request;
    m_module.on_rx_response = &at_rx_response;
    m_module.on_tx_request = &at_tx_request;
    m_module.on_tx_response = &at_tx_response;
    m_module.on_tsx_state = &at_tsx_state;

    status = pjsip_endpt_register_module(mp_sip_endpt, &m_module);
    if (status != PJ_SUCCESS) {
        EyerLog("注册自定义模块失败: %d\n", status);
        return;
    }
    // s_module_id = m_module.id;

    status = pjsip_100rel_init_module(mp_sip_endpt);
    if (status != PJ_SUCCESS) {
        EyerLog("注册100rel模块失败: %d\n", status);
        return;
    }

    /*
    pjsip_inv_callback m_inv_callback;
    pj_bzero(&m_inv_callback, sizeof(m_inv_callback));
    m_inv_callback.on_state_changed = &server_sip::at_state_changed;
    m_inv_callback.on_new_session = &server_sip::at_new_session;
    m_inv_callback.on_tsx_state_changed = &server_sip::at_tsx_state_changed;
    m_inv_callback.on_media_update = &server_sip::at_media_update;
    m_inv_callback.on_send_ack = &at_send_ack;
    status = pjsip_inv_usage_init(mp_sip_endpt, &m_inv_callback);
    */

    pj_pool_t * mp_pool = pjsip_endpt_create_pool(mp_sip_endpt, "server_sip", 10000, 10000);
    if (nullptr == mp_pool)
    {
        EyerLog("创建内存池失败: %d\n", status);
        return;
    }

    pj_thread_t * mp_thread = nullptr;
    status = pj_thread_create(mp_pool, "server_sip", worker_thread, mp_sip_endpt, 0, 0, &mp_thread);
    if (PJ_SUCCESS != status)
    {
        EyerLog("创建工作线程失败: %d\n", status);
        return;
    }

    for(int i=0;i<60 * 2;i++){
        Eyer::EyerTime::EyerSleepMilliseconds(1000);
    }

    printf("Eyer PJSIP Test End\n");
}

int main(int argc,char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
