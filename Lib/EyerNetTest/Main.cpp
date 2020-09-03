#include <gtest/gtest.h>
#include <curl/curl.h>
#include "EyerNet/EyerNet.hpp"
#include "EyerCore/EyerCore.hpp"

#define MAX_PARALLEL 10

TEST(EyerNet, cURL_support){
    curl_version_info_data *ver;

    curl_global_init(CURL_GLOBAL_ALL);

    ver = curl_version_info(CURLVERSION_NOW);
    if(ver->features & CURL_VERSION_HTTP2)
        printf("HTTP/2 support is present\n");

    if(ver->features & CURL_VERSION_HTTP3)
        printf("HTTP/3 support is present\n");

    if(ver->features & CURL_VERSION_ALTSVC)
        printf("Alt-svc support is present\n");

    curl_global_cleanup();
}

TEST(EyerNet, cURL_10_at_a_time){
    /*
    curl_global_init(CURL_GLOBAL_ALL);

    CURLM * cm = curl_multi_init();

    curl_multi_setopt(cm, CURLMOPT_MAXCONNECTS, (long)MAX_PARALLEL);

    for(int transfers = 0; transfers < MAX_PARALLEL; transfers++){
        CURL *eh = curl_easy_init();
        curl_easy_setopt(eh, CURLOPT_WRITEFUNCTION, write_cb);
        curl_easy_setopt(eh, CURLOPT_URL, urls[i]);
        curl_easy_setopt(eh, CURLOPT_PRIVATE, urls[i]);
        curl_multi_add_handle(cm, eh);
    }
     */
}

TEST(EyerNet, cURL_Http2_download){

}

size_t write_data(void *buffer, size_t size, size_t nmemb, void *userp)
{
    EyerLog("size: %d, nmemb: %d\n", size, nmemb);
    return size * nmemb;
}

TEST(EyerNet, cURL){
    CURL *curl;
    CURLcode res;

    EyerLog("cURL Test\n");

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "https://dash.akamaized.net/akamai/bbb_30fps/bbb_30fps.mpd");
        curl_easy_setopt(curl, CURLOPT_HTTP_VERSION, (long)CURL_HTTP_VERSION_2);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, NULL);

        res = curl_easy_perform(curl);
        if(res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

        curl_easy_cleanup(curl);
    }
}

TEST(EyerNet, EyerSimplestHttp){
    Eyer::EyerSimplestHttp http;
    int ret = http.Get(nullptr, "https://www.baidu.com");
}

int main(int argc,char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}