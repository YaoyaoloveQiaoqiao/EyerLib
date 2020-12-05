#ifndef EYERLIB_EYERLOGTHREAD_HPP
#define EYERLIB_EYERLOGTHREAD_HPP

#include "EyerLogBean.hpp"
#include "EyerLockQueue.hpp"
#include "EyerThread/EyerThread.hpp"

namespace Eyer
{
    class EyerLogThread : public EyerThread
    {
    public:
        static EyerLogThread * instance;
        static EyerLogThread * GetInstance();
        static int FreeInstance();

        EyerLogThread();
        ~EyerLogThread();

        virtual void Run();

        int SetLevel(int _level);

        int PutLog(EyerLogBean * logBean);

    private:
        EyerLockQueue<EyerLogBean> logQueue;

        int level = 5;
    };
}



#endif //EYERLIB_EYERLOGTHREAD_HPP
