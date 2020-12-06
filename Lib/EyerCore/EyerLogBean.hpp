#ifndef EYERLIB_EYERLOGBEAN_HPP
#define EYERLIB_EYERLOGBEAN_HPP

#include "EyerString.hpp"

namespace Eyer
{
    class EyerLogBean {
    public:
        EyerLogBean(const char * _file, const char * _function, int _line, int _level, const char * _log);
        ~EyerLogBean();
        EyerLogBean(const EyerLogBean & log);
        EyerLogBean & operator = (const EyerLogBean & log);

        EyerString & GetFile();
        EyerString & GetFunction();
        EyerString & GetLog();
        int GetLine();
        int GetLevel();

    private:
        int logLevel = 5;
        EyerString log;
        EyerString file;
        EyerString function;
        int line;
    };
}

#endif //EYERLIB_EYERLOGBEAN_HPP
