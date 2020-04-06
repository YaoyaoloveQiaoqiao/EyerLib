#include "EyerAV.hpp"
extern "C"{
#include <libavformat/avformat.h>
}

namespace Eyer{
    EyerAVReadePngList::EyerAVReadePngList(EyerString _path)
    {
        printf("===========in EyerAVReadePngList gouzao path:%s\n", _path.str);
        path = _path;
    }

    EyerAVReadePngList::~EyerAVReadePngList()
    {

    }

    int EyerAVReadePngList::read()
    {
        printf("===========in read\n");
        av_register_all();
        avformat_network_init();

        AVFormatContext *pFormatContext = NULL;
        int ret = avformat_open_input(&pFormatContext, path.str, 0, 0);
        if(ret != 0)
        {
            printf("avformat_open_input fail:%s\n", path.str);
        }

        ret = avformat_find_stream_info(pFormatContext, NULL);
        if(ret != 0)
        {
            printf("avformat_find_stream_info fail \n");
        }

        int videoIndex = -1;
        for(int i=0; i<pFormatContext->nb_streams; i++){
            if(pFormatContext->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO){
                videoIndex = i;
                break;
            }
        }
        if(videoIndex == -1){
            printf("can not find a video stream \n");
            return -1;
        }
        printf("stream: codec_name:%s,  time_base:%d \n", pFormatContext->streams[videoIndex]->codec->codec_name, pFormatContext->streams[videoIndex]->time_base.den);

        return 0;
    }
}