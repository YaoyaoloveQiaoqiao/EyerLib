#include "EyerLogBean.hpp"

namespace Eyer
{
    EyerLogBean::EyerLogBean(const char * _file, const char * _function, int _line, int _level, const char * _log)
    {
        file        = _file;
        function    = _function;
        line        = _line;
        log         = _log;
        logLevel    = _level;
    }

    EyerLogBean::~EyerLogBean()
    {

    }

    EyerLogBean::EyerLogBean(const EyerLogBean & log)
    {
        *this = log;
    }

    EyerLogBean & EyerLogBean::operator = (const EyerLogBean & logBean)
    {
        log         = logBean.log;
        file        = logBean.file;
        function    = logBean.function;
        line        = logBean.line;
        return *this;
    }

    EyerString & EyerLogBean::GetFile()
    {
        return file;
    }

    EyerString & EyerLogBean::GetFunction()
    {
        return function;
    }

    EyerString & EyerLogBean::GetLog()
    {
        return log;
    }

    int EyerLogBean::GetLevel()
    {
        return logLevel;
    }

    int EyerLogBean::GetLine()
    {
        return line;
    }
}