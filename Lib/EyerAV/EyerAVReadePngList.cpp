#include "EyerAV.hpp"
extern "C"{
#include <libavformat/avformat.h>
}
/* how many yuv pic you want to save */
#define FRAME_NUM 1

namespace Eyer{
    EyerAVReadePngList::EyerAVReadePngList(EyerString _path)
    {
        path = _path;
    }

    EyerAVReadePngList::~EyerAVReadePngList()
    {

    }

    int EyerAVReadePngList::read()
    {
        AVCodecContext *pCodecContext = nullptr;
        AVFrame *pFrame = nullptr;
        AVCodec *pCodec = nullptr;
        AVFormatContext *pFormatContext = nullptr;

        int decodeLen = 0;
        int frameNum = 0;

        av_register_all();
        avformat_network_init();

        int ret = avformat_open_input(&pFormatContext, path.str, 0, 0);
        if(ret != 0)
        {
            printf("avformat_open_input fail:%s ; ret:%d\n", path.str, ret);
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

        //printf("stream: codec_name:%d,  time_base:%d \n", pFormatContext->streams[videoIndex]->codec->codec_id, pFormatContext->streams[videoIndex]->time_base.den);
        pCodecContext = pFormatContext->streams[videoIndex]->codec;
        pCodec = avcodec_find_decoder(pCodecContext->codec_id);
        if(pCodec == nullptr){
            printf("can not find codec. \n");
            return -1;
        }

        //open codec
        if(avcodec_open2(pCodecContext, pCodec, NULL)<0){
            printf("can not open codec. \n");
            return -1;
        }

        pFrame = av_frame_alloc();
        if(pFrame == nullptr){
            printf("avframe can not alloc \n");
            return -1;
        }

        int frameFinished;
        int packetno =0;
        AVPacket packet;
        av_init_packet(&packet);

        while(av_read_frame(pFormatContext, &packet)>=0){
            if(packet.stream_index == videoIndex){
                packetno++;
                while(packet.size > 0){
                    decodeLen = avcodec_decode_video2(pCodecContext, pFrame, &frameFinished, &packet);
                    if(decodeLen < 0){
                        printf("decode frame fail, framenum:%d \n", frameNum);
                        //if decode one frame error, ignore this frame
                        decodeLen = packet.size;
                    }
                    if(frameFinished){
                        if(frameNum ==0){
                            printf("[video_decode_example]picture->linesize[0]=%d, c->width=%d,c->height=%d \n", pFrame->linesize[0],pCodecContext->width, pCodecContext->height);
                        }
                    }

                }
            }
        }


        return 0;
    }
}