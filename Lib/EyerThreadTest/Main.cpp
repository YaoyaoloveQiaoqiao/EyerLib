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
        for(int i=0;i<5;i++){
            // Eyer::EyerTime::EyerSleepMilliseconds(1000 * 1);
        }
        Eyer::EyerTime::EyerSleepMilliseconds(1000 * 1);

        EyerLog("End Event\n");
    }
};

TEST(Eyer, EyerEventLoop){
    for(int i=0;i<50;i++){
        EyerLog("=======================================\n");
        EventLoopThread eventLoopThread;
        eventLoopThread.Start();

        for(int j=0;j<10;j++){
            EventLoopEvent event;
            eventLoopThread.PushEvent(&event);

            EyerLog("Start Event Loop A\n");
            long long startTime = Eyer::EyerTime::GetTime();
            eventLoopThread.StartEventLoop();
            EyerLog("Start Event Loop B\n");

            EyerLog("End Event Loop A\n");
            eventLoopThread.StopEventLoop();
            long long endTime = Eyer::EyerTime::GetTime();
            EyerLog("End Event Loop B\n");

            if(endTime - startTime <= 500){
                EyerLog("Error!!!!!!!!!!   %lld\n", endTime - startTime);
            }
        }

        eventLoopThread.Stop();
    }

}

int main(int argc,char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}