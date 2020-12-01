#include "PJSIPProcessRegister.hpp"
#include "PJSIPServerPrivate.hpp"
#include <string>

namespace Eyer
{
    pj_bool_t PJSIPProcessRegister::Process(pjsip_rx_data * rdata)
    {
        printf("PJSIPProcessRegister\n");
        if (pjsip_method_e::PJSIP_REGISTER_METHOD == rdata->msg_info.cseq->method.id){
            auto hdr_expires = (pjsip_expires_hdr *)pjsip_msg_find_hdr(rdata->msg_info.msg, pjsip_hdr_e::PJSIP_H_EXPIRES, nullptr);
            if (nullptr == hdr_expires) {
                printf("未知\n");
            }
            else if (0 != hdr_expires->ivalue) {
                printf("注册\n");
            }
            else {
                printf("注销\n");
            }

            auto hdr = (pjsip_www_authenticate_hdr *)pjsip_msg_find_hdr(rdata->msg_info.msg, pjsip_hdr_e::PJSIP_H_AUTHORIZATION, nullptr);
            if (nullptr == hdr){
                printf("不存在注册信息，应当返回 401\n");
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
                pj_status_t status = pjsip_endpt_create_response(PJSIPServerPrivate::mp_sip_endpt, rdata, 401, nullptr, &p_tdata);
                status = pjsip_get_response_addr(rdata->tp_info.pool, rdata, &res_addr);
                pjsip_msg_add_hdr(p_tdata->msg, (pjsip_hdr *)hdr);
                status = pjsip_endpt_send_response(PJSIPServerPrivate::mp_sip_endpt, &res_addr, p_tdata, nullptr, nullptr);
                if (PJ_SUCCESS != status){
                    printf("发送回应帧[401]失败: %d\n", status);
                    return PJ_FALSE;
                }

                return PJ_TRUE;
            }
            else{
                printf("存在注册信息，应当返回 200\n");
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
                pj_status_t status = pjsip_endpt_create_response(PJSIPServerPrivate::mp_sip_endpt, rdata, 200, nullptr, &p_tdata);
                status = pjsip_get_response_addr(rdata->tp_info.pool, rdata, &res_addr);
                pjsip_msg_add_hdr(p_tdata->msg, (pjsip_hdr *)hdr_date);
                pjsip_msg_add_hdr(p_tdata->msg, (pjsip_hdr *)hdr_expires);

                status = pjsip_endpt_send_response(PJSIPServerPrivate::mp_sip_endpt, &res_addr, p_tdata, nullptr, nullptr);
                if (PJ_SUCCESS != status) {
                    printf("发送回应帧[200]失败: %d\n", status);
                    return PJ_FALSE;
                }
                printf("成功\n");

                // 发送目录查询
                {
                    pjsip_tx_data *p_tdata = nullptr;
                    pjsip_method m;
                    m.id = PJSIP_OTHER_METHOD;
                    m.name = pj_strdup3(rdata->tp_info.pool, "MESSAGE");
                    auto pj_target = pj_strdup3(rdata->tp_info.pool, "sip:34020000001320000001@192.168.2.101:5060");
                    auto pj_from = pj_strdup3(rdata->tp_info.pool, "sip:34020000002000000001@34020000");
                    auto pj_to = pj_strdup3(rdata->tp_info.pool, "sip:34020000001320000001@34020000");
                    auto pj_contact = pj_strdup3(rdata->tp_info.pool, "sip:34020000002000000001@192.168.2.106:5060");
                    status = pjsip_endpt_create_request(PJSIPServerPrivate::mp_sip_endpt, &m, &pj_target, &pj_from, &pj_to, &pj_contact, nullptr, -1, nullptr, &p_tdata);

                    auto pj_type = pj_strdup3(rdata->tp_info.pool, "Application");
                    auto pj_subtype = pj_strdup3(rdata->tp_info.pool, "MANSCDP+xml");
                    auto pj_text = pj_strdup3(rdata->tp_info.pool, "<?xml version=\"1.0\"?>\r\n<Query><CmdType>Catalog</CmdType><SN>4</SN><DeviceID>34020000001320000001</DeviceID></Query>");
                    p_tdata->msg->body = pjsip_msg_body_create(rdata->tp_info.pool, &pj_type, &pj_subtype, &pj_text);
                    status = pjsip_endpt_send_request(PJSIPServerPrivate::mp_sip_endpt, p_tdata, 1000 * 3, nullptr, nullptr);
                    if (PJ_SUCCESS != status)
                    {
                        printf("Send Catalog Error\n");
                    }
                }

                return PJ_TRUE;
            }
        }
        return PJ_FALSE;
    }
}