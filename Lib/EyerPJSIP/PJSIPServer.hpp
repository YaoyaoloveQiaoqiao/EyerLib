#ifndef EYERLIB_PJSIPSERVER_HPP
#define EYERLIB_PJSIPSERVER_HPP

namespace Eyer
{
    class PJSIPServerPrivate;
    class PJSIPServer {
    public:
        PJSIPServer(int _port);
        ~PJSIPServer();

        int Start();
        int Stop();

    public:
        PJSIPServerPrivate * impl = nullptr;
    };
}

#endif //EYERLIB_PJSIPSERVER_HPP
