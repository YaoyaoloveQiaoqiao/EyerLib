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
            printf("EXOSIP_MESSAGE_NEW\n");
            if (MSG_IS_REGISTER(je->request)){
                printf("REGISTER\n");
                osip_authorization_t * auth = NULL;
                osip_message_get_authorization(je->request, 0, &auth);
                if (NULL == auth) {
                    printf("auth is NULL\n");
                }
                else{
                    printf("auth is not NULL\n");
                }
            }
        }
    }
}

int main(int argc,char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}