#ifndef EYERLIB_SIPSERVERMAINTHREAD_HPP
#define EYERLIB_SIPSERVERMAINTHREAD_HPP

#include "EyerThread/EyerThread.hpp"
#include "eXosipHeader.hpp"

namespace Eyer
{
    class SIPServerMainThread : public EyerThread {
    public:
        SIPServerMainThread(int _port);
        ~SIPServerMainThread();

        virtual void Run();

    private:
        int port = 5060;

        int PrintJe(eXosip_event_t * je);
    };
}

#endif //EYERLIB_SIPSERVERMAINTHREAD_HPP
