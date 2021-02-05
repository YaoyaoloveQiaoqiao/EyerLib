#include "PJSIPServer.hpp"
#include "PJSIPServerPrivate.hpp"
#include "EyerCore/EyerCore.hpp"
#include "PJSIPProcessRegister.hpp"
#include "PJSIPServerPrivate.hpp"

pjsip_endpoint * Eyer::PJSIPServerPrivate::mp_sip_endpt = nullptr;

int eyer_pjsip_worker_thread(void *arg)
{
    Eyer::PJSIPServer * server = (Eyer::PJSIPServer *)arg;

    printf("工作线程开始\n");
    while (1) {
        pj_time_val timeout = {0, 1};
        pjsip_endpt_handle_events((pjsip_endpoint *)server->impl->mp_sip_endpt, &timeout);
    }
    printf("工作线程结束\n");
    return 0;
}

pj_bool_t eyer_pjsip_at_rx_request(pjsip_rx_data * rdata) {
    printf("at_rx_request\n");
    if (pjsip_method_e::PJSIP_REGISTER_METHOD == rdata->msg_info.cseq->method.id)
    {
        Eyer::PJSIPProcessRegister pjsipProcessRegister;
        return pjsipProcessRegister.Process(rdata);
    }
    else{
        pj_status_t status = pjsip_endpt_respond_stateless(Eyer::PJSIPServerPrivate::mp_sip_endpt, rdata, 200, nullptr, nullptr, nullptr);
        printf("%s\n", reinterpret_cast<char *>(rdata->msg_info.msg->body->data));
    }

    return PJ_FALSE;
}
pj_bool_t eyer_pjsip_at_rx_response(pjsip_rx_data *rdata) {
    EyerLog("at_rx_response\n");
    return PJ_FALSE;
}
pj_status_t eyer_pjsip_at_tx_request(pjsip_tx_data *tdata) {
    EyerLog("at_tx_request\n");
    return PJ_SUCCESS;
}
pj_status_t eyer_pjsip_at_tx_response(pjsip_tx_data *tdata) {
    EyerLog("at_tx_response\n");
    return PJ_SUCCESS;
}
void eyer_pjsip_at_tsx_state(pjsip_transaction *tsx, pjsip_event *event) {
    EyerLog("at_tsx_state\n");
}

namespace Eyer
{
    PJSIPServer::PJSIPServer(int _port)
    {
        impl = new PJSIPServerPrivate();
        impl->port = _port;
    }

    PJSIPServer::~PJSIPServer()
    {
        if(impl != nullptr){
            delete impl;
            impl = nullptr;
        }
    }

    int PJSIPServer::Start()
    {
        int logLevel = PJ_LOG_MAX_LEVEL;
        pj_log_set_level(logLevel);

        pj_status_t status;
        status = pj_init();
        if (PJ_SUCCESS != status) {
            EyerLog("初始化[pj_init]失败: %d\n", status);
            return -1;
        }
        /* Then init PJLIB-UTIL: */
        status = pjlib_util_init();
        if (PJ_SUCCESS != status) {
            EyerLog("初始化[pjlib_util_init]失败: %d\n", status);
            return -2;
        }

        /* Must create a pool factory before we can allocate any memory. */
        pj_caching_pool_init(&impl->m_cp, &pj_pool_factory_default_policy, 0);

        /* Create the endpoint: */
        status = pjsip_endpt_create(&impl->m_cp.factory, nullptr, &(impl->mp_sip_endpt));
        if (PJ_SUCCESS != status) {
            EyerLog("创建pj端点失败: %d\n", status);
            return -3;
        }

        pj_sockaddr_in addr;
        addr.sin_family = pj_AF_INET();
        addr.sin_addr.s_addr = 0;
        addr.sin_port = pj_htons(static_cast<pj_uint16_t>(impl->port));
        status = pjsip_udp_transport_start(impl->mp_sip_endpt, &addr, nullptr, 1, nullptr);
        if (status != PJ_SUCCESS) {
            EyerLog("创建udp传输失败: %d\n", status);
            return -4;
        }

        status = pjsip_tsx_layer_init_module(impl->mp_sip_endpt);
        if (status != PJ_SUCCESS) {
            EyerLog("初始化事务层模块失败: %d\n", status);
            return -5;
        }

        status = pjsip_ua_init_module(impl->mp_sip_endpt, NULL);
        if (status != PJ_SUCCESS) {
            EyerLog("初始化ua层模块失败: %d\n", status);
            return -6;
        }

        /*
         * Register our module to receive incoming requests.
         */
        char tmp_str[128] = { 0 };
        sprintf(tmp_str, "server_sip");
        impl->m_module.name.ptr = tmp_str;
        impl->m_module.name.slen = strlen(tmp_str);
        impl->m_module.id = -1;
        impl->m_module.load = nullptr;
        impl->m_module.unload = nullptr;
        impl->m_module.start = nullptr;
        impl->m_module.stop = nullptr;
        impl->m_module.priority = PJSIP_MOD_PRIORITY_APPLICATION;
        impl->m_module.on_rx_request = &eyer_pjsip_at_rx_request;
        impl->m_module.on_rx_response = &eyer_pjsip_at_rx_response;
        impl->m_module.on_tx_request = &eyer_pjsip_at_tx_request;
        impl->m_module.on_tx_response = &eyer_pjsip_at_tx_response;
        impl->m_module.on_tsx_state = &eyer_pjsip_at_tsx_state;

        status = pjsip_endpt_register_module(impl->mp_sip_endpt, &impl->m_module);
        if (status != PJ_SUCCESS) {
            EyerLog("注册自定义模块失败: %d\n", status);
            return -7;
        }
        // s_module_id = m_module.id;

        status = pjsip_100rel_init_module(impl->mp_sip_endpt);
        if (status != PJ_SUCCESS) {
            EyerLog("注册100rel模块失败: %d\n", status);
            return -8;
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

        impl->mp_pool = pjsip_endpt_create_pool(impl->mp_sip_endpt, "server_sip", 10000, 10000);
        if (nullptr == impl->mp_pool) {
            EyerLog("创建内存池失败: %d\n", status);
            return -9;
        }

        status = pj_thread_create(impl->mp_pool, "server_sip", eyer_pjsip_worker_thread, this, 0, 0, &impl->mp_thread);
        if (PJ_SUCCESS != status) {
            EyerLog("创建工作线程失败: %d\n", status);
            return -10;
        }

        return 0;
    }

    int PJSIPServer::Stop()
    {
        return 0;
    }
}
