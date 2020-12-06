#include "EyerLogThread.hpp"
#include "EyerTime.hpp"

namespace Eyer
{
    EyerLogThread * EyerLogThread::instance = nullptr;

    EyerLogThread * EyerLogThread::GetInstance()
    {
        if(EyerLogThread::instance == nullptr){
            EyerLogThread::instance = new EyerLogThread();
        }
        return EyerLogThread::instance;
    }

    int EyerLogThread::FreeInstance()
    {
        if(EyerLogThread::instance != nullptr){
            EyerLogThread::instance->Stop();
            delete EyerLogThread::instance;
            EyerLogThread::instance = nullptr;
        }
        return 0;
    }

    EyerLogThread::EyerLogThread()
    {

    }

    EyerLogThread::~EyerLogThread()
    {
        while(logQueue.Size() > 0){
            EyerLogBean * logBean = nullptr;
            logQueue.FrontPop(&logBean);
            if(logBean != nullptr){
                printf("%s", logBean->GetLog().str);

                delete logBean;
                logBean = nullptr;
            }
        }
    }

    void EyerLogThread::Run()
    {
        while(!stopFlag){
            EyerTime::EyerSleepMilliseconds(1);
            EyerLogBean * logBean = nullptr;
            logQueue.FrontPop(&logBean);
            if(logBean != nullptr){
                // printf("[%d] [%s (%d)] [%s] %s", logBean->GetLevel(), logBean->GetFile().str, logBean->GetLine(), logBean->GetFunction().str, logBean->GetLog().str);
                if(logBean->GetLevel() >= level){
                    printf("[%2d] %s", logBean->GetLevel(), logBean->GetLog().str);
                }

                delete logBean;
                logBean = nullptr;
            }
        }
    }

    int EyerLogThread::PutLog(EyerLogBean * logBean)
    {
        logQueue.Push(logBean);
        return 0;
    }

    int EyerLogThread::SetLevel(int _level)
    {
        level = _level;
        return 0;
    }
}