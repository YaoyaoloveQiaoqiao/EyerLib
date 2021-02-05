#include <gtest/gtest.h>
#include <curl/curl.h>
#include "EyerHttp/EyerHttp.hpp"
#include "EyerCore/EyerCore.hpp"

#define MAX_PARALLEL 10

TEST(EyerHttp, cURL_support){
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

TEST(EyerHttp, EyerHttpPool){
    Eyer::EyerHttpPool httpPool;

    std::vector<Eyer::EyerHttpTask *> taskList;
    for(int i=0;i<10;i++){
        Eyer::EyerHttpTask * httpTask = new Eyer::EyerHttpTask();
        // Eyer::EyerString url = Eyer::EyerString("http://redknot.cn/sohu/hls/shuw_000") + Eyer::EyerString::Number(i) + Eyer::EyerString(".ts");
        Eyer::EyerString url = "https://dash.akamaized.net/akamai/bbb_30fps/bbb_30fps.mpd";
        EyerLog("Url: %s\n", url.str);
        httpTask->SetUrl(url);
        httpPool.AddTask(*httpTask);

        taskList.push_back(httpTask);
    }


    httpPool.Start();

    while(httpPool.StillRunning()){
        // EyerLog("Loop\n");
        httpPool.Loop();
    }

    for(int i=0;i<taskList.size();i++){
        Eyer::EyerHttpTask * httpTask = taskList.at(i);

        Eyer::EyerBuffer buffer;
        httpTask->GetBuffer(buffer);

        EyerLog("Buffer Len: %d\n", buffer.GetBuffer(nullptr));

        delete httpTask;
    }
}

TEST(EyerHttp, cURL_Http2_download){

}

TEST(EyerHttp, cURL){

}

TEST(EyerHttp, EyerSimplestHttp){
    Eyer::EyerSimplestHttp http;

    Eyer::EyerBuffer buffer;
    // int ret = http.Get(buffer, "https://dash.akamaized.net/akamai/bbb_30fps/bbb_30fps.mpd");
    int ret = http.Get(buffer, "http://redknot.cn/sohu/hls/shuw_0001.ts");

    ASSERT_EQ(ret, 0) << "Network Error";

    int dataLen = buffer.GetBuffer(nullptr);

    unsigned char * data = (unsigned char *)malloc(dataLen);

    buffer.GetBuffer(data);

    FILE * f = fopen("a.ts", "wb");
    fwrite(data, 1, dataLen, f);
    fclose(f);

    free(data);
}

int main(int argc,char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}