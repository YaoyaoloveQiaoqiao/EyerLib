#include <gtest/gtest.h>

#include <osipparser2/osip_message.h>
#include <osipparser2/osip_parser.h>
#include <osipparser2/osip_port.h>

#include <eXosip2/eXosip.h>
#include <eXosip2/eX_setup.h>
#include <eXosip2/eX_register.h>
#include <eXosip2/eX_options.h>
#include <eXosip2/eX_message.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>

#include "EyerGB28181/EyerGB28181.hpp"
#include "EyerCore/EyerCore.hpp"

TEST(GB28181, GB28181SipServer) {
    Eyer::SIPServer sipServer(5060);
    sipServer.Start();

    for(int i=0;i<60 * 2;i++){
        Eyer::EyerTime::EyerSleepMilliseconds(1000);
    }

    sipServer.Stop();
}

/*
#define NONCE "9bd055"
#define ALGORITHTHM "MD5"

TEST(GB28181, GB28181SipServer) {
    struct eXosip_t *excontext;
    excontext = eXosip_malloc();
    int ret = eXosip_init(excontext);
    if (ret != 0) {
        printf("Can't initialize eXosip!\n");
        return;
    } else {
        printf("eXosip_init successfully!\n");
    }

    ret = eXosip_listen_addr(excontext, IPPROTO_UDP, NULL, 5060, AF_INET, 0);
    if (ret != 0) {
        eXosip_quit(excontext);
        fprintf(stderr, "eXosip_listen_addr error! Couldn't initialize transport layer!\n");
        return;
    }

    eXosip_event_t * je = NULL;
    for (;;) {

        je = eXosip_event_wait(excontext, 0, 50);

        eXosip_lock(excontext);
        eXosip_default_action(excontext, je);
        eXosip_automatic_action(excontext);
        eXosip_unlock(excontext);

        if (je == NULL) {
            continue;
        }

        if(je->type == EXOSIP_MESSAGE_NEW) {
            printf("============================================\n");
            printf("EXOSIP_MESSAGE_NEW\n");
            if(je->request != NULL){
                char * str = NULL;
                size_t len = 0;
                osip_message_to_str(je->request, &str, &len);
                printf("request msg: \n%s\n", str);
                osip_free(str);
            }
            if(je->response != NULL){
                char * str = NULL;
                size_t len = 0;
                osip_message_to_str(je->response, &str, &len);
                printf("response msg: \n%s\n", str);
                osip_free(str);
            }
            printf("============================================\n");
            if (MSG_IS_REGISTER(je->request)){
                printf("REGISTER\n");
                osip_authorization_t * auth = NULL;
                osip_message_get_authorization(je->request, 0, &auth);
                if (NULL == auth) {
                    printf("auth is NULL\n");

                    eXosip_lock(excontext);

                    osip_message_t * answer = NULL;
                    int result = eXosip_message_build_answer(excontext, je->tid, 401, &answer);

                    std::stringstream stream;
                    std::string nonce = NONCE;
                    std::string algorithm = ALGORITHTHM;
                    stream << "Digest realm=\"" << "abc"
                    << "\",nonce=\"" << nonce
                    << "\",algorithm=" << algorithm;
                    osip_message_set_header(answer, "WWW-Authenticate", stream.str().c_str());

                    char * str = NULL;
                    size_t len = 0;
                    osip_message_to_str(answer, &str, &len);
                    printf("msg: \n%s\n", str);

                    eXosip_message_send_answer(excontext, je->tid, 401, answer);

                    // osip_message_free(answer);

                    eXosip_unlock(excontext);
                }
                else{
                    printf("auth is not NULL\n");

                    osip_message_t * answer = NULL;
                    eXosip_message_build_answer (excontext, je->tid, 200, &answer);
                    eXosip_message_send_answer (excontext, je->tid, 200, answer);
                }
            }
        }
    }
}
*/

int main(int argc,char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}