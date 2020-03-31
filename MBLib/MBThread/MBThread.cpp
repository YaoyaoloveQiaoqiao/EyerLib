#include "MBThread.hpp"

#include <functional>
#include "MBCore/MBCore.hpp"

namespace MB
{
    MBThread::MBThread()
    {

    }

    MBThread::~MBThread()
    {

    }

    int MBThread::Stop(int t)
    {
        stopFlag = 1;
        while(1){
            if(!IsRunning()){
                break;
            }
            MBTime::MBSleep(t);
        }
        stopFlag = 0;
        return 0;
    }

    int MBThread::IsRunning()
    {
        return isRun;
    }

    void MBThread::Detach()
    {
        std::thread t(std::bind(&MBThread::Run, this));
        t.detach();
    }

    void MBThread::Join()
    {
        std::thread t(std::bind(&MBThread::Run, this));
        t.join();
    }

    void MBThread::SetRunning()
    {
        stopFlag = 0;
        isRun = 1;
    }

    void MBThread::SetStoping()
    {
        isRun = 0;
    }
}