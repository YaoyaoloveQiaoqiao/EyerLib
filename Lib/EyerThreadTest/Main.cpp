#include <stdio.h>
#include <gtest/gtest.h>

#include "EyerThread/EyerThread.hpp"
#include "EyerCore/EyerCore.hpp"

class TimeThread : public Eyer::EyerThread
{
private:
    Eyer::EyerString tag;

public:
    TimeThread(Eyer::EyerString _tag){
        tag = _tag;
    }

    virtual void Run()
    {
        SetRunning();

        while(!stopFlag){
            printf("this from: %s\n", tag.str);
            Eyer::EyerTime::EyerSleep(1000 * 1000);
        }

        SetStoping();
    }
};

/*
TEST(Eyer, EyerThread){
    TimeThread a("A");
    TimeThread b("B");

    a.Start();
    b.Start();

    Eyer::EyerTime::EyerSleep(1000 * 1000 * 1);

    a.Stop();
    b.Stop();
}
 */


class EventLoopThread : public Eyer::EyerThread
{
public:
    EventLoopThread()
    {

    }

    ~EventLoopThread()
    {

    }

    virtual void Run() {
        while(!stopFlag){
            EventLoop();
        }
    }
};

class EventLoopEvent : public Eyer::EyerRunnable
{
    virtual void Run(){
        EyerLog("Start Event\n");
        Eyer::EyerTime::EyerSleepMilliseconds(1000 * 1);
        EyerLog("End Event\n");
    }
};

TEST(Eyer, EyerEventLoop){
    for(int i=0;i<50;i++){
        EyerLog("=======================================\n");
        EventLoopThread eventLoopThread;
        eventLoopThread.Start();

        EventLoopEvent event;
        eventLoopThread.PushEvent(&event);

        EyerLog("Start Event Loop\n");
        eventLoopThread.StartEventLoop();
        long long startTime = Eyer::EyerTime::GetTime();

        eventLoopThread.StopEventLoop();
        long long endTime = Eyer::EyerTime::GetTime();
        EyerLog("End Event Loop\n");

        if(endTime - startTime <= 500){
            EyerLog("Error!!!!!!!!!!   %lld\n", endTime - startTime);
        }

        eventLoopThread.Stop();
    }

}

int main(int argc,char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}