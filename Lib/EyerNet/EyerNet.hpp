#ifndef	EYER_LIB_NET_H
#define	EYER_LIB_NET_H

#include "EyerCore/EyerCore.hpp"

namespace Eyer
{
    class EyerNet
    {
    public:
        EyerNet();
        ~EyerNet();
    };

    class EyerSimplestHttp
    {
    public:
        EyerSimplestHttp();
        ~EyerSimplestHttp();

        int Get(unsigned char * data, EyerString url);

        int SetDate(unsigned char * data, int dataLen);
    private:
        static size_t write_data(void * buffer, size_t size, size_t nmemb, void * userp);

        unsigned char * data = nullptr;
        int dataLen = 0;
    };
}

#endif