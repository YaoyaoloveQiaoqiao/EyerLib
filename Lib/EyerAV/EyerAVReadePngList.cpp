#include "EyerAV.hpp"
extern "C"{
#include <libavformat/avformat.h>
}
/* how many yuv pic you want to save */
#define FRAME_NUM 1

namespace Eyer{
    void yuv420p_save(AVFrame *pFrame, AVCodecContext *pCodecCtx, FILE * pfout)
    {
        int i = 0;
    
        int width = pCodecCtx->width, height = pCodecCtx->height;
        int height_half = height / 2, width_half = width / 2;
        int y_wrap = pFrame->linesize[0];
        int u_wrap = pFrame->linesize[1];
        int v_wrap = pFrame->linesize[2];
    
        unsigned char *y_buf = pFrame->data[0];
        unsigned char *u_buf = pFrame->data[1];
        unsigned char *v_buf = pFrame->data[2];
    
        //save y
        for (i = 0; i < height; i++)
            fwrite(y_buf + i * y_wrap, 1, width, pfout);
        fprintf(stderr, "===>save Y success\n");
        //save u
        for (i = 0; i < height_half; i++)
            fwrite(u_buf + i * u_wrap, 1, width_half, pfout);
        fprintf(stderr, "===>save U success\n");
        //save v
        for (i = 0; i < height_half; i++)
            fwrite(v_buf + i * v_wrap, 1, width_half, pfout);
        fprintf(stderr, "===>save V success\n");
    
        fflush(pfout);
    }

    EyerAVReadePngList::EyerAVReadePngList(EyerString _path)
    {
        path = _path;
    }

    EyerAVReadePngList::~EyerAVReadePngList()
    {

    }

    int EyerAVReadePngList::read()
    {
        int frameNum = 0;

        // FILE *pfout = nullptr;
        // pfout = fopen("out420p.yuv", "wb+");
        // if(nullptr == pfout){
        //     printf("create output file fail\n");
        //     return -1;
        // }

        Eyer::EyerAVReader reader(path.str);
        int ret = reader.Open();
        if(ret!= 0){
            EyerLog("open file fail, ret:%d \n", ret);
        }

        EyerAVStream videoStream;
        ret = reader.GetStream(videoStream, 0);
        if(ret !=0){
            EyerLog("GetStream fail, ret:%d \n", ret);
        }

        EyerAVDecoder videoDecoder;
        videoDecoder.Init(&videoStream);

        // while (1)
        // {

            Eyer::EyerAVPacket packet;
            ret = reader.Read(&packet);
            

            videoDecoder.SendPacket(&packet);

            while(1){
                //if(frameNum < FRAME_NUM){
                    printf("===========in 2while\n");
                    Eyer::EyerAVFrame frame;
                    ret = videoDecoder.RecvFrame(&frame);
                    if(ret){
                        printf("============ret:%d\n", ret);
                        break;
                    }
                    //yuv420p_save(frame.piml, pCodecContext, pfout);
                    printf("frame width: %d, height:%d \n",frame.GetWidth(), frame.GetHeight());

                    unsigned char * rgbaData = nullptr;
                    frame.GetRGBA(rgbaData);
                // }else{
                //     break;
                // }
                // frameNum++;
            }
        //}

        reader.Close();

        

        // //printf("stream: codec_name:%d,  time_base:%d \n", pFormatContext->streams[videoIndex]->codec->codec_id, pFormatContext->streams[videoIndex]->time_base.den);
        // pCodecContext = pFormatContext->streams[videoIndex]->codec;
        // pCodec = avcodec_find_decoder(pCodecContext->codec_id);
        // if(pCodec == nullptr){
        //     printf("can not find codec. \n");
        //     return -1;
        // }

        // //open codec
        // if(avcodec_open2(pCodecContext, pCodec, NULL)<0){
        //     printf("can not open codec. \n");
        //     return -1;
        // }

        // pFrame = av_frame_alloc();
        // if(pFrame == nullptr){
        //     printf("avframe can not alloc \n");
        //     return -1;
        // }

        // int frameFinished;
        // int packetno =0;
        // AVPacket packet;
        // av_init_packet(&packet);

        // while(av_read_frame(pFormatContext, &packet)>=0){
        //     if(packet.stream_index == videoIndex){
        //         packetno++;
        //         while(packet.size > 0){
        //             decodeLen = avcodec_decode_video2(pCodecContext, pFrame, &frameFinished, &packet);
        //             if(decodeLen < 0){
        //                 printf("decode frame fail, framenum:%d \n", frameNum);
        //                 //if decode one frame error, ignore this frame
        //                 decodeLen = packet.size;
        //             }
        //             if(frameFinished){
        //                 if(frameNum ==0){
        //                     //printf("[video_decode_example]picture->linesize[0]=%d, c->width=%d,c->height=%d \n", pFrame->linesize[0],pCodecContext->width, pCodecContext->height);
        //                 }
        //                 if(frameNum < FRAME_NUM){
        //                     switch (pFrame->format)
        //                     {
        //                     case 0:
        //                         printf("yuv420p\n");
        //                         yuv420p_save(pFrame, pCodecContext, pfout);
        //                         break;
                            
        //                     default:
        //                     	fprintf(stderr, "unsupport YUV format for saving\n");
        //                         break;
        //                     }
        //                 }
        //                 frameNum++;
        //             }
        //             //left data in packet, go to decode
        //             packet.data += decodeLen;
        //             packet.size -= decodeLen;

        //         }
        //         if(frameNum == FRAME_NUM){
        //             break;
        //         }
        //     }
        // }

        // av_free(pFrame);
        // avcodec_close(pCodecContext);
        // avformat_close_input(&pFormatContext);
        return 0;
    }
}