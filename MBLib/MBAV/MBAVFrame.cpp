#include "MBAV.hpp"

extern "C"{
#include <libavformat/avformat.h>
#include <libavutil/imgutils.h>
}

#include "MBAVEncoderPrivate.hpp"
#include "MBAVFramePrivate.hpp"

namespace MB {
    MBAVFrame::MBAVFrame() {
        piml = new MBAVFramePrivate();
        piml->frame = av_frame_alloc();
    }

    MBAVFrame::~MBAVFrame() {
        av_frame_unref(piml->frame);
        av_frame_free(&piml->frame);
        if (piml != nullptr) {
            delete piml;
            piml = nullptr;
        }

        for(int i=0;i<dataManager.size();i++){
            free(dataManager[i]);
        }
        dataManager.clear();
    }

    MBAVFrame::MBAVFrame(const MBAVFrame & frame)
    {
        piml = new MBAVFramePrivate();
        piml->frame = av_frame_alloc();
        *this = frame;
    }
    MBAVFrame & MBAVFrame::operator = (const MBAVFrame & frame)
    {
        // Copy data
        // YUV 420 Data
        int width                           = frame.piml->frame->width;
        int height                          = frame.piml->frame->height;

        // Copy width ,height
        piml->frame->width                  = frame.piml->frame->width;
        piml->frame->height                 = frame.piml->frame->height;

        piml->frame->channels               = frame.piml->frame->channels;
        piml->frame->channel_layout         = frame.piml->frame->channel_layout;
        piml->frame->nb_samples             = frame.piml->frame->nb_samples;
        piml->frame->format                 = frame.piml->frame->format;
        piml->frame->key_frame              = frame.piml->frame->key_frame;
        piml->frame->pict_type              = frame.piml->frame->pict_type;
        piml->frame->sample_aspect_ratio    = frame.piml->frame->sample_aspect_ratio;
        piml->frame->pts                    = frame.piml->frame->pts;
        piml->frame->pkt_dts                = frame.piml->frame->pkt_dts;
        piml->frame->coded_picture_number   = frame.piml->frame->coded_picture_number;
        piml->frame->display_picture_number = frame.piml->frame->display_picture_number;
        piml->frame->quality                = frame.piml->frame->quality;

        // Copy linesize
        for(int i=0;i<AV_NUM_DATA_POINTERS;i++){
            piml->frame->linesize[i] = frame.piml->frame->linesize[i];
        }

        if(frame.GetPixFormat() < 200 && frame.GetPixFormat() >= 100){
            // 图像
            {
                int linesizeIndex = 0;
                int h = height;
                if(frame.GetPixFormat() == MBAVPixelFormat::MB_AV_PIX_FMT_YUV420P || frame.GetPixFormat() == MBAVPixelFormat::MB_AV_PIX_FMT_YUVJ420P){
                    h = height;
                }
                if(frame.GetPixFormat() == MBAVPixelFormat::MB_AV_PIX_FMT_YUV444P || frame.GetPixFormat() == MBAVPixelFormat::MB_AV_PIX_FMT_YUVJ444P){
                    h = height;
                }

                int dataLen = h * frame.piml->frame->linesize[linesizeIndex];
                unsigned char * data = (unsigned char *)malloc(dataLen);

                memcpy(data, frame.piml->frame->data[linesizeIndex], dataLen);

                piml->frame->data[linesizeIndex] = data;
                dataManager.push_back(data);
            }
            {
                int linesizeIndex = 1;
                int h = height;
                if(frame.GetPixFormat() == MBAVPixelFormat::MB_AV_PIX_FMT_YUV420P || frame.GetPixFormat() == MBAVPixelFormat::MB_AV_PIX_FMT_YUVJ420P){
                    h = height / 2;
                }
                if(frame.GetPixFormat() == MBAVPixelFormat::MB_AV_PIX_FMT_YUV444P || frame.GetPixFormat() == MBAVPixelFormat::MB_AV_PIX_FMT_YUVJ444P){
                    h = height;
                }

                int dataLen = h * frame.piml->frame->linesize[linesizeIndex];
                unsigned char * data = (unsigned char *)malloc(dataLen);

                memcpy(data, frame.piml->frame->data[linesizeIndex], dataLen);

                piml->frame->data[linesizeIndex] = data;
                dataManager.push_back(data);
            }
            {
                int linesizeIndex = 2;
                int h = height;
                if(frame.GetPixFormat() == MBAVPixelFormat::MB_AV_PIX_FMT_YUV420P || frame.GetPixFormat() == MBAVPixelFormat::MB_AV_PIX_FMT_YUVJ420P){
                    h = height / 2;
                }
                if(frame.GetPixFormat() == MBAVPixelFormat::MB_AV_PIX_FMT_YUV444P || frame.GetPixFormat() == MBAVPixelFormat::MB_AV_PIX_FMT_YUVJ444P){
                    h = height;
                }

                int dataLen = h * frame.piml->frame->linesize[linesizeIndex];
                unsigned char * data = (unsigned char *)malloc(dataLen);

                memcpy(data, frame.piml->frame->data[linesizeIndex], dataLen);

                piml->frame->data[linesizeIndex] = data;
                dataManager.push_back(data);
            }
        }

        {
            if(piml->frame->format == AVSampleFormat::AV_SAMPLE_FMT_FLTP){
                int sizePerSample = av_get_bytes_per_sample((AVSampleFormat)piml->frame->format);
                int channelSize = piml->frame->nb_samples * sizePerSample;

                for(int channelIndex=0; channelIndex<piml->frame->channels; channelIndex++){
                    unsigned char * data = (unsigned char *)malloc(channelSize);
                    memcpy(data, frame.piml->frame->data[channelIndex], channelSize);
                    piml->frame->data[channelIndex] = data;
                    dataManager.push_back(data);
                }
            }
        }

        

        // Copy extended_data




        return *this;
    }

    int MBAVFrame::GetYData(unsigned char * yData)
    {
        int width = GetWidth();
        int height = GetHeight();

        int h = height;
        int w = width;

        if(GetPixFormat() == MBAVPixelFormat::MB_AV_PIX_FMT_YUV420P || GetPixFormat() == MBAVPixelFormat::MB_AV_PIX_FMT_YUVJ420P){
            h = height;
            w = width;
        }
        if(GetPixFormat() == MBAVPixelFormat::MB_AV_PIX_FMT_YUV444P || GetPixFormat() ==  MBAVPixelFormat::MB_AV_PIX_FMT_YUVJ444P){
            h = height;
            w = width;
        }

        int offset = 0;
        for(int i=0;i<h;i++){
            memcpy(yData + offset, piml->frame->data[0] + i * piml->frame->linesize[0], w);
            offset += w;
        }

        return 0;
    }

    int MBAVFrame::GetUData(unsigned char * uData)
    {
        int width = GetWidth();
        int height = GetHeight();

        int h = height;
        int w = width;

        if(GetPixFormat() == MBAVPixelFormat::MB_AV_PIX_FMT_YUV420P || GetPixFormat() == MBAVPixelFormat::MB_AV_PIX_FMT_YUVJ420P){
            h = height / 2;
            w = width / 2;
        }
        if(GetPixFormat() == MBAVPixelFormat::MB_AV_PIX_FMT_YUV444P || GetPixFormat() == MBAVPixelFormat::MB_AV_PIX_FMT_YUVJ444P){
            h = height;
            w = width;
        }

        int offset = 0;
        for(int i=0;i<h;i++){
            memcpy(uData + offset, piml->frame->data[1] + i * piml->frame->linesize[1], w);
            offset += w;
        }

        return 0;
    }

    int MBAVFrame::GetVData(unsigned char * vData)
    {
        int width = GetWidth();
        int height = GetHeight();

        int h = height;
        int w = width;

        if(GetPixFormat() == MBAVPixelFormat::MB_AV_PIX_FMT_YUV420P || GetPixFormat() == MBAVPixelFormat::MB_AV_PIX_FMT_YUVJ420P){
            h = height / 2;
            w = width / 2;
        }
        if(GetPixFormat() == MBAVPixelFormat::MB_AV_PIX_FMT_YUV444P || GetPixFormat() == MBAVPixelFormat::MB_AV_PIX_FMT_YUVJ444P){
            h = height;
            w = width;
        }

        int offset = 0;
        for(int i=0;i<h;i++){
            memcpy(vData + offset, piml->frame->data[2] + i * piml->frame->linesize[2], w);
            offset += w;
        }
        return 0;
    }

    int MBAVFrame::SetPTS(int64_t pts)
    {
        piml->frame->pts = pts;
        return 0;
    }

    int MBAVFrame::GetLineSize(int channel) {
        return piml->frame->linesize[channel];
    }

    int MBAVFrame::GetWidth() {
        return piml->frame->width;
    }

    int MBAVFrame::GetHeight() {
        return piml->frame->height;
    }

    int64_t MBAVFrame::GetPTS()
    {
        return piml->frame->pts;
    }

    int MBAVFrame::GetInfo() {
        printf("===============================================================\n");

        for(int i=0;i<AV_NUM_DATA_POINTERS;i++) {
            printf("Linesize [%d]: %d\n", i, piml->frame->linesize[i]);
        }
        
        printf("Width: %d\n", piml->frame->width);
        printf("Height: %d\n", piml->frame->height);
        printf("Channels: %d\n", piml->frame->channels);
        printf("channel_layout: %d\n", piml->frame->channel_layout);
        printf("nb_samples: %d\n", piml->frame->nb_samples);
        printf("format: %d\n", piml->frame->format);

        int sizePerSample = av_get_bytes_per_sample((AVSampleFormat)piml->frame->format);
        printf("Size Per Sample: %d\n", sizePerSample);

        {
            if(piml->frame->format == AVPixelFormat::AV_PIX_FMT_YUV420P){
                printf("Format: AV_PIX_FMT_YUV420P\n");
            }
            if(piml->frame->format == AVPixelFormat::AV_PIX_FMT_YUVJ420P){
                printf("Format: AV_PIX_FMT_YUVJ420P\n");
            }
            if(piml->frame->format == AVPixelFormat::AV_PIX_FMT_YUVJ422P){
                printf("Format: AV_PIX_FMT_YUVJ422P\n");
            }
            if(piml->frame->format == AVPixelFormat::AV_PIX_FMT_RGB24){
                printf("Format: AV_PIX_FMT_RGB24\n");
            }
            if(piml->frame->format == AVPixelFormat::AV_PIX_FMT_BGR24){
                printf("Format: AV_PIX_FMT_BGR24\n");
            }
            if(piml->frame->format == AVPixelFormat::AV_PIX_FMT_YUVJ444P){
                printf("Format: AV_PIX_FMT_YUVJ444P\n");
            }
            if(piml->frame->format == AVPixelFormat::AV_PIX_FMT_YUV444P){
                printf("Format: AV_PIX_FMT_YUV444P\n");
            }
            if(piml->frame->format == AVSampleFormat::AV_SAMPLE_FMT_NONE){
                printf("Format: AV_SAMPLE_FMT_NONE\n");
            }
            if(piml->frame->format == AVSampleFormat::AV_SAMPLE_FMT_U8){
                printf("Format: AV_SAMPLE_FMT_U8\n");
            }
            if(piml->frame->format == AVSampleFormat::AV_SAMPLE_FMT_S16){
                printf("Format: AV_SAMPLE_FMT_S16\n");
            }
            if(piml->frame->format == AVSampleFormat::AV_SAMPLE_FMT_S32){
                printf("Format: AV_SAMPLE_FMT_S32\n");
            }
            if(piml->frame->format == AVSampleFormat::AV_SAMPLE_FMT_FLT){
                printf("Format: AV_SAMPLE_FMT_FLT\n");
            }
            if(piml->frame->format == AVSampleFormat::AV_SAMPLE_FMT_DBL){
                printf("Format: AV_SAMPLE_FMT_DBL\n");
            }
            if(piml->frame->format == AVSampleFormat::AV_SAMPLE_FMT_U8P){
                printf("Format: AV_SAMPLE_FMT_U8P\n");
            }
            if(piml->frame->format == AVSampleFormat::AV_SAMPLE_FMT_S16P){
                printf("Format: AV_SAMPLE_FMT_S16P\n");
            }
            if(piml->frame->format == AVSampleFormat::AV_SAMPLE_FMT_S32P){
                printf("Format: AV_SAMPLE_FMT_S32P\n");
            }
            if(piml->frame->format == AVSampleFormat::AV_SAMPLE_FMT_FLTP){
                printf("Format: AV_SAMPLE_FMT_FLTP\n");
            }
            if(piml->frame->format == AVSampleFormat::AV_SAMPLE_FMT_DBLP){
                printf("Format: AV_SAMPLE_FMT_DBLP\n");
            }
            if(piml->frame->format == AVSampleFormat::AV_SAMPLE_FMT_S64){
                printf("Format: AV_SAMPLE_FMT_S64\n");
            }
            if(piml->frame->format == AVSampleFormat::AV_SAMPLE_FMT_S64P){
                printf("Format: AV_SAMPLE_FMT_S64P\n");
            }
            if(piml->frame->format == AVSampleFormat::AV_SAMPLE_FMT_NB){
                printf("Format: AV_SAMPLE_FMT_NB\n");
            }
        }

        // Print Channel Layout
        {
            if(piml->frame->channel_layout == AV_CH_LAYOUT_MONO){
                printf("Channel Layout: AV_CH_LAYOUT_MONO\n");
            }
            if(piml->frame->channel_layout == AV_CH_LAYOUT_STEREO){
                printf("Channel Layout: AV_CH_LAYOUT_STEREO\n");
            }
            if(piml->frame->channel_layout == AV_CH_LAYOUT_2POINT1){
                printf("Channel Layout: AV_CH_LAYOUT_2POINT1\n");
            }
            if(piml->frame->channel_layout == AV_CH_LAYOUT_SURROUND){
                printf("Channel Layout: AV_CH_LAYOUT_SURROUND\n");
            }
            if(piml->frame->channel_layout == AV_CH_LAYOUT_2_1){
                printf("Channel Layout: AV_CH_LAYOUT_2_1\n");
            }
            if(piml->frame->channel_layout == AV_CH_LAYOUT_4POINT0){
                printf("Channel Layout: AV_CH_LAYOUT_4POINT0\n");
            }
            if(piml->frame->channel_layout == AV_CH_LAYOUT_3POINT1){
                printf("Channel Layout: AV_CH_LAYOUT_3POINT1\n");
            }
            if(piml->frame->channel_layout == AV_CH_LAYOUT_5POINT0_BACK){
                printf("Channel Layout: AV_CH_LAYOUT_5POINT0_BACK\n");
            }
            if(piml->frame->channel_layout == AV_CH_LAYOUT_5POINT0){
                printf("Channel Layout: AV_CH_LAYOUT_5POINT0\n");
            }
            if(piml->frame->channel_layout == AV_CH_LAYOUT_5POINT1_BACK){
                printf("Channel Layout: AV_CH_LAYOUT_5POINT1_BACK\n");
            }
            if(piml->frame->channel_layout == AV_CH_LAYOUT_5POINT1){
                printf("Channel Layout: AV_CH_LAYOUT_5POINT1\n");
            }
        }
        
        return 0;
    }

    MBAVPixelFormat MBAVFrame::GetPixFormat() const {
        if(piml->frame->format == AVPixelFormat::AV_PIX_FMT_YUV420P){
            return MBAVPixelFormat::MB_AV_PIX_FMT_YUV420P;
        }
        if(piml->frame->format == AVPixelFormat::AV_PIX_FMT_YUVJ420P){
            return MBAVPixelFormat::MB_AV_PIX_FMT_YUVJ420P;
        }
        if(piml->frame->format == AVPixelFormat::AV_PIX_FMT_YUV444P){
            return MBAVPixelFormat::MB_AV_PIX_FMT_YUV444P;
        }
        if(piml->frame->format == AVPixelFormat::AV_PIX_FMT_YUVJ444P){
            return MBAVPixelFormat::MB_AV_PIX_FMT_YUVJ444P;
        }

        return MBAVPixelFormat::MB_AV_PIX_FMT_UNKNOW;
    }


    int MBAVFrame::SetVideoData420P(unsigned char * _y, unsigned char * _u, unsigned char * _v, int _width, int _height)
    {
        unsigned char * y = (unsigned char *)malloc(_width * _height);
        memcpy(y, _y, _width * _height);

        unsigned char * u = (unsigned char *)malloc(_width * _height / 4);
        memcpy(u, _u, _width * _height / 4);

        unsigned char * v = (unsigned char *)malloc(_width * _height / 4);
        memcpy(v, _v, _width * _height / 4);

        dataManager.push_back(y);
        dataManager.push_back(u);
        dataManager.push_back(v);

        piml->frame->format = AV_PIX_FMT_YUV420P;
        piml->frame->width = _width;
        piml->frame->height = _height;

        piml->frame->linesize[0] = _width;
        piml->frame->linesize[1] = _width / 2;
        piml->frame->linesize[2] = _width / 2;

        piml->frame->data[0] = y;
        piml->frame->data[1] = u;
        piml->frame->data[2] = v;

        /*
        int ret = av_image_alloc(piml->frame->data, piml->frame->linesize, _width, _height, AV_PIX_FMT_YUV420P, 16);

        MBLog("=====================================\n");
        MBLog("linesize[0]:%d\n", piml->frame->linesize[0]);
        MBLog("linesize[1]:%d\n", piml->frame->linesize[1]);
        MBLog("linesize[2]:%d\n", piml->frame->linesize[2]);

        memcpy(piml->frame->data[0], _y, _width * _height);
        memcpy(piml->frame->data[1], _u, _width * _height / 4);
        memcpy(piml->frame->data[2], _v, _width * _height / 4);
        */

        return 0;
    }

    int MBAVFrame::GetAudioData(unsigned char * data)
    {
        memcpy(data, piml->frame->data[0], 8192 / 2);
        memcpy(data + 8192 / 2, piml->frame->data[1], 8192 / 2);
        return 0;
    }

    int MBAVFrame::GetChannels()
    {
        return piml->frame->channels;
    }

    int MBAVFrame::GetNBSamples()
    {
        return piml->frame->nb_samples;
    }

    int MBAVFrame::GetPerSampleSize()
    {
        int sizePerSample = av_get_bytes_per_sample((AVSampleFormat)piml->frame->format);
        return sizePerSample;
    }

    int MBAVFrame::InitAACFrame(int channels)
    {
        if(channels >= AV_NUM_DATA_POINTERS){
            channels = AV_NUM_DATA_POINTERS;
        }

        piml->frame->format = AVSampleFormat::AV_SAMPLE_FMT_FLTP;
        piml->frame->channels = channels;
        piml->frame->nb_samples = 1024;

        for(int channelIndex=0; channelIndex<channels; channelIndex++){
            int len = GetPerSampleSize() * GetNBSamples();

            unsigned char * d = (unsigned char *)malloc(len);
            memset(d, 0, len);

            piml->frame->data[channelIndex] = d;
            dataManager.push_back(d);
        }
        return 0;
    }

    float MBAVFrame::GetAudioFloatData(int channel, int index)
    {
        if(channel >= GetChannels()){
            return 0;
        }

        if(index >= GetNBSamples()){
            return 0;
        }

        float * d = (float *)piml->frame->data[channel];
        return d[index];
    }

    int MBAVFrame::SetAudioFloatData(int channel, int index, float d)
    {
        if(channel >= GetChannels()){
            return 0;
        }

        if(index >= GetNBSamples()){
            return 0;
        }

        float * dArr = (float *)piml->frame->data[channel];
        dArr[index] = d;

        return 0;
    }

    int MBAVFrame::SetAudioData(unsigned char * _data, int _dataLen, int nbSamples, int channel, MBAVFormat _format)
    {
        if(_format == MBAVFormat::EYER_AV_SAMPLE_FMT_FLTP){
            // float, planar
            unsigned char * data = (unsigned char *)malloc(_dataLen);
            dataManager.push_back(data);

            memcpy(data, _data, _dataLen);

            piml->frame->format = AV_SAMPLE_FMT_FLTP;
            piml->frame->channels = channel;
            piml->frame->nb_samples = nbSamples;
            int ret = avcodec_fill_audio_frame(piml->frame, channel, AV_SAMPLE_FMT_FLTP, (const uint8_t *) data, _dataLen, 0);
            // printf("avcodec_fill_audio_frame ret:%d\n", ret);

            /*
            printf("====================================================\n");
            printf("Linesize 0:%d\n", piml->frame->linesize[0]);
            printf("Linesize 1:%d\n", piml->frame->linesize[1]);
            printf("Channels:%d\n", piml->frame->channels);
            printf("nb_samples:%d\n", piml->frame->nb_samples);
            printf("channel_layout:%lld\n", piml->frame->channel_layout);
            printf("format:%lld\n", piml->frame->format);
            */

            return 0;
        }
        return -1;
    }
}