#include "MBAV.hpp"

extern "C"{
#include <libavformat/avformat.h>
}

#include "MBAVReaderPrivate.hpp"
#include "MBAVPacketPrivate.hpp"
#include "MBAVStreamPrivate.hpp"

namespace MB
{
    MBAVReader::MBAVReader(MBString _path)
    {
        piml = new MBAVReaderPrivate();
        piml->path = _path;

        av_register_all();
        avformat_network_init();

        piml->formatCtx = avformat_alloc_context();
    }

    MBAVReader::~MBAVReader()
    {
        if(piml->formatCtx != NULL){
            Close();
            avformat_free_context(piml->formatCtx);
            piml->formatCtx = NULL;
        }

        if(piml != nullptr){
            delete piml;
            piml = nullptr;
        }
    }

    int MBAVReader::SeekFrame(int streamIndex, double timestamp)
    {
        int64_t t = timestamp / av_q2d(piml->formatCtx->streams[streamIndex]->time_base);
        return SeekFrame(streamIndex, t);
    }

    int MBAVReader::SeekFrame(int streamIndex, int64_t timestamp)
    {
        if(piml->formatCtx == nullptr){
            return -1;
        }

        // TODO 判断文件是否打开成功

        int ret = av_seek_frame(piml->formatCtx, streamIndex, timestamp, AVSEEK_FLAG_BACKWARD);

        return ret;
    }

    int MBAVReader::Open()
    {
        int ret = avformat_open_input(&piml->formatCtx, piml->path.str, NULL, NULL);
        if(ret){
            return -1;
        }

        avformat_find_stream_info(piml->formatCtx, NULL);

        return 0;
    }

    int MBAVReader::Close()
    {
        avformat_close_input(&piml->formatCtx);
        return 0;
    }

    int MBAVReader::Read(MBAVPacket * packet)
    {
        int ret = av_read_frame(piml->formatCtx, packet->piml->packet);
        return ret;
    }

    int MBAVReader::GetStreamCount()
    {
        if(piml->formatCtx == nullptr){
            return -1;
        }

        // TODO 判断文件是否打开成功

        return piml->formatCtx->nb_streams;
    }

    int MBAVReader::GetStream(MBAVStream & stream, int index)
    {
        if(piml->formatCtx == nullptr){
            return -1;
        }

        // TODO 判断文件是否打开成功
        if(index < 0){
            return -1;
        }
        if(index >= GetStreamCount()){
            return -1;
        }

        double duration = piml->formatCtx->streams[index]->duration * 1.0 * piml->formatCtx->streams[index]->time_base.num / piml->formatCtx->streams[index]->time_base.den;

        stream.SetDuration(duration);

        stream.streamIndex = piml->formatCtx->streams[index]->index;
        stream.piml->type = MBAVStreamType::STREAM_TYPE_UNKNOW;
        avcodec_copy_context(stream.piml->codecContext, piml->formatCtx->streams[index]->codec);

        return 0;
    }

    int MBAVReader::GetStreamTimeBase(MBAVRational & rational, int streamIndex)
    {
        if(streamIndex < 0){
            return -1;
        }
        if(streamIndex >= piml->formatCtx->nb_streams){
            return -1;
        }

        rational.num = piml->formatCtx->streams[streamIndex]->time_base.num;
        rational.den = piml->formatCtx->streams[streamIndex]->time_base.den;

        return 0;
    }
}
