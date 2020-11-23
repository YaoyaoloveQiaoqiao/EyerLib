#include "SIPServerMainThread.hpp"

#include "eXosipHeader.hpp"
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <string.h>

#include "SIPProcessRegister.hpp"
#include "SIPProcessMessage.hpp"

namespace Eyer
{
    SIPServerMainThread::SIPServerMainThread(int _port)
    {
        port = _port;
    }

    SIPServerMainThread::~SIPServerMainThread()
    {

    }

    void SIPServerMainThread::Run()
    {
        int ret = 0;
        struct eXosip_t *excontext;
        excontext = eXosip_malloc();
        ret = eXosip_init(excontext);
        if (ret != 0) {
            printf("Can't initialize eXosip!\n");
            return;
        } else {
            printf("eXosip_init successfully!\n");
        }

        ret = eXosip_listen_addr(excontext, IPPROTO_UDP, NULL, port, AF_INET, 0);
        if (ret != 0) {
            eXosip_quit(excontext);
            printf("eXosip_listen_addr error! Couldn't initialize transport layer!\n");
            return;
        }

        eXosip_event_t * je = NULL;
        while(!stopFlag){
            je = eXosip_event_wait(excontext, 0, 50);

            eXosip_lock(excontext);
            eXosip_default_action(excontext, je);
            eXosip_automatic_action(excontext);
            eXosip_unlock(excontext);

            if (je == NULL) {
                continue;
            }


            if(je->type == EXOSIP_MESSAGE_NEW) {
                if(je->request != NULL){
                    printf("=================Request Start=================\n");
                    char * str = NULL;
                    size_t len = 0;
                    osip_message_to_str(je->request, &str, &len);
                    printf("request msg: \n%s\n", str);
                    osip_free(str);
                    printf("=================Request End=================\n");
                }
                if(je->response != NULL){
                    printf("=================Response Start=================\n");
                    char * str = NULL;
                    size_t len = 0;
                    osip_message_to_str(je->response, &str, &len);
                    printf("response msg: \n%s\n", str);
                    osip_free(str);
                    printf("=================Response End=================\n");
                }

                if (MSG_IS_REGISTER(je->request)){
                    SIPProcessRegister sipProcessRegister;
                    sipProcessRegister.Process(excontext, je);
                }
                else {
                    SIPProcessMessage sipProcessMessage;
                    sipProcessMessage.Process(excontext, je);
                }
            }
        }
    }
}