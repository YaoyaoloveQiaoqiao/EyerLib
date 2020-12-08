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
    SIPServerMainThread::SIPServerMainThread(int _port, SIPServerContext * _context)
    {
        port = _port;
        context = _context;
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
            EyerLog("Can't initialize eXosip!\n");
            return;
        } else {
            EyerLog("eXosip_init successfully!\n");
        }

        ret = eXosip_listen_addr(excontext, IPPROTO_UDP, NULL, port, AF_INET, 0);
        if (ret != 0) {
            eXosip_quit(excontext);
            EyerLog("eXosip_listen_addr error! Couldn't initialize transport layer!\n");
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

            /* REGISTER related events */
            if(je->type == EXOSIP_REGISTRATION_SUCCESS) {
                EyerLog_1("============EXOSIP_REGISTRATION_SUCCESS============\n");
            }
            if(je->type == EXOSIP_REGISTRATION_FAILURE) {
                EyerLog_1("============EXOSIP_REGISTRATION_FAILURE============\n");
            }

            /* INVITE related events within calls */
            if(je->type == EXOSIP_CALL_INVITE) {
                EyerLog_1("============EXOSIP_CALL_INVITE============\n");
            }
            if(je->type == EXOSIP_CALL_REINVITE) {
                EyerLog_1("============EXOSIP_CALL_REINVITE============\n");
            }

            if(je->type == EXOSIP_CALL_NOANSWER) {
                EyerLog_1("============EXOSIP_CALL_NOANSWER============\n");
            }
            if(je->type == EXOSIP_CALL_PROCEEDING) {
                EyerLog_1("============EXOSIP_CALL_PROCEEDING============\n");
            }
            if(je->type == EXOSIP_CALL_RINGING) {
                EyerLog_1("============EXOSIP_CALL_RINGING============\n");
            }
            if(je->type == EXOSIP_CALL_ANSWERED) {
                EyerLog_1("============EXOSIP_CALL_ANSWERED============\n");
                PrintJe(je);

                osip_message_t *ack = NULL;
                eXosip_call_build_ack(excontext, je->did, &ack);

                eXosip_lock(excontext);
                eXosip_call_send_ack(excontext, je->did, ack);
                eXosip_unlock(excontext);
            }
            if(je->type == EXOSIP_CALL_REDIRECTED) {
                EyerLog_1("============EXOSIP_CALL_REDIRECTED============\n");
            }
            if(je->type == EXOSIP_CALL_REQUESTFAILURE) {
                EyerLog_1("============EXOSIP_CALL_REQUESTFAILURE============\n");
            }
            if(je->type == EXOSIP_CALL_SERVERFAILURE) {
                EyerLog_1("============EXOSIP_CALL_SERVERFAILURE============\n");
            }
            if(je->type == EXOSIP_CALL_GLOBALFAILURE) {
                EyerLog_1("============EXOSIP_CALL_GLOBALFAILURE============\n");
            }
            if(je->type == EXOSIP_CALL_ACK) {
                EyerLog_1("============EXOSIP_CALL_ACK============\n");
            }

            if(je->type == EXOSIP_CALL_CANCELLED) {
                EyerLog_1("============EXOSIP_CALL_CANCELLED============\n");
            }

            if(je->type == EXOSIP_CALL_MESSAGE_NEW) {
                EyerLog_1("============EXOSIP_CALL_MESSAGE_NEW============\n");
            }
            if(je->type == EXOSIP_CALL_MESSAGE_PROCEEDING) {
                EyerLog_1("============EXOSIP_CALL_MESSAGE_PROCEEDING============\n");
            }
            if(je->type == EXOSIP_CALL_MESSAGE_ANSWERED) {
                EyerLog_1("============EXOSIP_CALL_MESSAGE_ANSWERED============\n");
            }
            if(je->type == EXOSIP_CALL_MESSAGE_REDIRECTED) {
                EyerLog_1("============EXOSIP_CALL_MESSAGE_REDIRECTED============\n");
            }
            if(je->type == EXOSIP_CALL_MESSAGE_REQUESTFAILURE) {
                EyerLog_1("============EXOSIP_CALL_MESSAGE_REQUESTFAILURE============\n");
            }
            if(je->type == EXOSIP_CALL_MESSAGE_SERVERFAILURE) {
                EyerLog_1("============EXOSIP_CALL_MESSAGE_SERVERFAILURE============\n");
            }
            if(je->type == EXOSIP_CALL_MESSAGE_GLOBALFAILURE) {
                EyerLog_1("============EXOSIP_CALL_MESSAGE_GLOBALFAILURE============\n");
            }


            if(je->type == EXOSIP_CALL_CLOSED) {
                EyerLog_1("============EXOSIP_CALL_CLOSED============\n");
            }


            if(je->type == EXOSIP_CALL_RELEASED) {
                EyerLog_1("============EXOSIP_CALL_RELEASED============\n");
            }


            if(je->type == EXOSIP_MESSAGE_NEW) {
                EyerLog_1("============EXOSIP_MESSAGE_NEW============\n");
                PrintJe(je);
                if (MSG_IS_REGISTER(je->request)){
                    SIPProcessRegister sipProcessRegister;
                    sipProcessRegister.Process(context, excontext, je);
                }
                else {
                    SIPProcessMessage sipProcessMessage;
                    sipProcessMessage.Process(context, excontext, je);
                }
            }
            if(je->type == EXOSIP_MESSAGE_PROCEEDING) {
                EyerLog_1("============EXOSIP_MESSAGE_PROCEEDING============\n");
            }
            if(je->type == EXOSIP_MESSAGE_ANSWERED) {
                EyerLog_1("============EXOSIP_MESSAGE_ANSWERED============\n");
            }
            if(je->type == EXOSIP_MESSAGE_REDIRECTED) {
                EyerLog_1("============EXOSIP_MESSAGE_REDIRECTED============\n");
            }
            if(je->type == EXOSIP_MESSAGE_REQUESTFAILURE) {
                EyerLog_1("============EXOSIP_MESSAGE_REQUESTFAILURE============\n");
            }
            if(je->type == EXOSIP_MESSAGE_SERVERFAILURE) {
                EyerLog_1("============EXOSIP_MESSAGE_SERVERFAILURE============\n");
            }
            if(je->type == EXOSIP_MESSAGE_GLOBALFAILURE) {
                EyerLog_1("============EXOSIP_MESSAGE_GLOBALFAILURE============\n");
            }

            /* Presence and Instant Messaging */
            if(je->type == EXOSIP_SUBSCRIPTION_NOANSWER) {
                EyerLog_1("============EXOSIP_SUBSCRIPTION_NOANSWER============\n");
            }
            if(je->type == EXOSIP_SUBSCRIPTION_PROCEEDING) {
                EyerLog_1("============EXOSIP_SUBSCRIPTION_PROCEEDING============\n");
            }
            if(je->type == EXOSIP_SUBSCRIPTION_ANSWERED) {
                EyerLog_1("============EXOSIP_SUBSCRIPTION_ANSWERED============\n");
            }
            if(je->type == EXOSIP_SUBSCRIPTION_REDIRECTED) {
                EyerLog_1("============EXOSIP_SUBSCRIPTION_REDIRECTED============\n");
            }
            if(je->type == EXOSIP_SUBSCRIPTION_REQUESTFAILURE) {
                EyerLog_1("============EXOSIP_SUBSCRIPTION_REQUESTFAILURE============\n");
            }
            if(je->type == EXOSIP_SUBSCRIPTION_SERVERFAILURE) {
                EyerLog_1("============EXOSIP_SUBSCRIPTION_SERVERFAILURE============\n");
            }
            if(je->type == EXOSIP_SUBSCRIPTION_GLOBALFAILURE) {
                EyerLog_1("============EXOSIP_SUBSCRIPTION_GLOBALFAILURE============\n");
            }
            if(je->type == EXOSIP_SUBSCRIPTION_NOTIFY) {
                EyerLog_1("============EXOSIP_SUBSCRIPTION_NOTIFY============\n");
            }


            if(je->type == EXOSIP_IN_SUBSCRIPTION_NEW) {
                EyerLog_1("============EXOSIP_IN_SUBSCRIPTION_NEW============\n");
            }


            if(je->type == EXOSIP_NOTIFICATION_NOANSWER) {
                EyerLog("============EXOSIP_NOTIFICATION_NOANSWER============\n");
            }
            if(je->type == EXOSIP_NOTIFICATION_PROCEEDING) {
                EyerLog_1("============EXOSIP_NOTIFICATION_PROCEEDING============\n");
            }
            if(je->type == EXOSIP_NOTIFICATION_ANSWERED) {
                EyerLog_1("============EXOSIP_NOTIFICATION_ANSWERED============\n");
            }
            if(je->type == EXOSIP_NOTIFICATION_REDIRECTED) {
                EyerLog_1("============EXOSIP_NOTIFICATION_REDIRECTED============\n");
            }
            if(je->type == EXOSIP_NOTIFICATION_REQUESTFAILURE) {
                EyerLog_1("============EXOSIP_NOTIFICATION_REQUESTFAILURE============\n");
            }
            if(je->type == EXOSIP_NOTIFICATION_SERVERFAILURE) {
                EyerLog_1("============EXOSIP_NOTIFICATION_SERVERFAILURE============\n");
            }
            if(je->type == EXOSIP_NOTIFICATION_GLOBALFAILURE) {
                EyerLog_1("============EXOSIP_NOTIFICATION_GLOBALFAILURE============\n");
            }


            if(je->type == EXOSIP_EVENT_COUNT) {
                EyerLog_1("============EXOSIP_EVENT_COUNT============\n");
            }



            SIPEvent * event = nullptr;
            context->eventQueue.GetEvent(&event);
            if(event != nullptr){
                if(event->to == SIPEventTarget::SIPEventTarget_MainThread){
                    EyerLog("SIPEventType: %s\n", event->GetEventType().GetName().str);
                    event->Do(excontext, context);
                    delete event;
                    event = nullptr;
                }
                else{
                    context->eventQueue.PutEvent(event);
                }
            }
        }

        eXosip_quit(excontext);
    }

    int SIPServerMainThread::PrintJe(eXosip_event_t * je)
    {
        if(je->request != NULL){
            // printf("=================Request Start=================\n");
            char * str = NULL;
            size_t len = 0;
            osip_message_to_str(je->request, &str, &len);
            EyerLog("cid: %d\n", je->cid);
            EyerLog("did: %d\n", je->did);
            EyerLog("tid: %d\n", je->tid);
            EyerLog("request msg: \n%s\n", str);
            osip_free(str);
            // printf("=================Request End=================\n");
        }
        if(je->response != NULL){
            // printf("=================Response Start=================\n");


            char * str = NULL;
            size_t len = 0;
            osip_message_to_str(je->response, &str, &len);
            EyerLog("cid: %d\n", je->cid);
            EyerLog("did: %d\n", je->did);
            EyerLog("tid: %d\n", je->tid);
            EyerLog("response msg: \n%s\n", str);
            osip_free(str);
            // printf("=================Response End=================\n");
        }
        return 0;
    }
}