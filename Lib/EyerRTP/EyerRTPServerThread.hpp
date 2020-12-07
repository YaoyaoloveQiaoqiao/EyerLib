#ifndef EYERLIB_EYERRTPSERVERTHREAD_HPP
#define EYERLIB_EYERRTPSERVERTHREAD_HPP

#include "EyerThread/EyerThread.hpp"

namespace Eyer
{
    class EyerRTPServerThread : public EyerThread{
    public:
        EyerRTPServerThread();
        ~EyerRTPServerThread();

        virtual void Run();
    };
}

#endif //EYERLIB_EYERRTPSERVERTHREAD_HPP
