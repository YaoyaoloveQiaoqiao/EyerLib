#ifndef EYERLIB_SIPSERVERMAINTHREAD_HPP
#define EYERLIB_SIPSERVERMAINTHREAD_HPP

#include "EyerThread/EyerThread.hpp"

namespace Eyer
{
    class SIPServerMainThread : public EyerThread {
    public:
        SIPServerMainThread(int _port);
        ~SIPServerMainThread();

        virtual void Run();

    private:
        int port = 5060;
    };
}

#endif //EYERLIB_SIPSERVERMAINTHREAD_HPP
