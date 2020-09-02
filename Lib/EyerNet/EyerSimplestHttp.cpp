#include "EyerNet.hpp"
#include <curl/curl.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

namespace Eyer
{
    size_t EyerSimplestHttp::write_data(void *buffer, size_t size, size_t nmemb, void *userp)
    {
        EyerLog("size: %d, nmemb: %d\n", size, nmemb);
        EyerSimplestHttp * http = (EyerSimplestHttp *)userp;
        http->SetDate((unsigned char *)buffer, size * nmemb);
        return size * nmemb;
    }


    EyerSimplestHttp::EyerSimplestHttp()
    {

    }

    EyerSimplestHttp::~EyerSimplestHttp()
    {

    }

    int EyerSimplestHttp::Get(unsigned char * data, EyerString url)
    {
        int finalRet = -1;
        CURL * curl = curl_easy_init();
        if(curl) {
            curl_easy_setopt(curl, CURLOPT_URL, "https://dash.akamaized.net/akamai/bbb_30fps/bbb_30fps.mpd");
            curl_easy_setopt(curl, CURLOPT_HTTP_VERSION, (long)CURL_HTTP_VERSION_2);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, this);

            CURLcode res = curl_easy_perform(curl);
            if(res != CURLE_OK){
                finalRet = -1;
                fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            }else{
                finalRet = 0;
                //
            }

            curl_easy_cleanup(curl);
        }
        return finalRet;
    }

    int EyerSimplestHttp::SetDate(unsigned char * _data, int _dataLen)
    {
        if(data != nullptr){
            free(data);
            data = nullptr;
            dataLen = 0;
        }

        dataLen = _dataLen;
        data = (unsigned char *)malloc(dataLen);

        memcpy(data, _data, dataLen);

        return 0;
    }
}