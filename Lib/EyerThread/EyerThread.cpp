#include "EyerThread.hpp"

#include <functional>
#include "EyerCore/EyerCore.hpp"

namespace Eyer
{
    EyerThread::EyerThread()
    {

    }

    EyerThread::~EyerThread()
    {
        Stop();

        while(eventQueue.size() > 0){
            EyerRunnable * event = eventQueue.front();
            eventQueue.pop();
        }
    }

    int EyerThread::Stop(int time)
    {
        if(t == nullptr){
            return -1;
        }

        stopFlag = 1;
        if(t != nullptr){
            t->join();
            delete t;
            t = nullptr;
        }
        stopFlag = 0;

        SetStoping();

        return 0;
    }

    int EyerThread::IsRunning()
    {
        return isRun;
    }

    int EyerThread::Start()
    {
        if(t != nullptr){
            return -1;
        }

        SetRunning();
        stopFlag = 0;
        t = new std::thread(&EyerThread::Run, this);

        return 0;
    }

    void EyerThread::SetRunning()
    {
        stopFlag = 0;
        isRun = 1;
    }

    void EyerThread::SetStoping()
    {
        isRun = 0;
    }


    int EyerThread::PushEvent(EyerRunnable * event)
    {
        eventQueue.push(event);
        return 0;
    }


    int EyerThread::StartEventLoop()
    {
        std::unique_lock <std::mutex> lck(eventLoopMtx);
        // 发出 开始指令
        stopEventLoopFlag = 0;

        // 等待 开始
        eventLoopStart.wait(lck);

        return 0;
    }

    int EyerThread::StopEventLoop()
    {
        std::unique_lock <std::mutex> lck(eventLoopMtx);
        // 发出 停止指令
        stopEventLoopFlag = 1;

        // 等待 停止
        eventLoopEnd.wait(lck);

        return 0;
    }

    int EyerThread::EventLoop()
    {
        while(!stopEventLoopFlag){
            eventLoopStart.notify_one();
            while(eventQueue.size()){
                EyerRunnable * event = eventQueue.front();
                eventQueue.pop();
                event->Run();
            }
        }
        eventLoopEnd.notify_one();

        return 0;
    }
}