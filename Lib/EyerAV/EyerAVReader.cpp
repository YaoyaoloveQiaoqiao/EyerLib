#include "EyerAV.hpp"

extern "C"{
#include <libavformat/avformat.h>
}

#include "EyerAVReaderPrivate.hpp"
#include "EyerAVPacketPrivate.hpp"
#include "EyerAVStreamPrivate.hpp"

namespace Eyer
{
    EyerAVReader::EyerAVReader(EyerString _path)
    {
        piml = new EyerAVReaderPrivate();
        piml->path = _path;

        av_register_all();
        avformat_network_init();

        piml->formatCtx = avformat_alloc_context();
    }

    EyerAVReader::~EyerAVReader()
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

    int EyerAVReader::GetVideoStreamIndex()
    {
        if(piml->formatCtx == nullptr){
            return -1;
        }

        int streamCount = GetStreamCount();
        for(int streamIndex=0; streamIndex<streamCount; streamCount++){
            AVStream * st = piml->formatCtx->streams[streamIndex];
            if(st->codecpar->codec_type == AVMEDIA_TYPE_VIDEO){
                return streamIndex;
            }
        }

        return -1;
    }

    int EyerAVReader::GetAudioStreamIndex()
    {
        if(piml->formatCtx == nullptr){
            return -1;
        }

        int streamCount = GetStreamCount();
        for(int streamIndex=0; streamIndex<streamCount; streamCount++){
            AVStream * st = piml->formatCtx->streams[streamIndex];
            if(st->codecpar->codec_type == AVMEDIA_TYPE_AUDIO){
                return streamIndex;
            }
        }

        return -1;
    }

    int EyerAVReader::SeekFrame(int streamIndex, double timestamp)
    {
        int64_t t = timestamp / av_q2d(piml->formatCtx->streams[streamIndex]->time_base);
        return SeekFrame(streamIndex, t);
    }

    int EyerAVReader::SeekFrame(int streamIndex, int64_t timestamp)
    {
        if(piml->formatCtx == nullptr){
            return -1;
        }

        // TODO 判断文件是否打开成功
        /**
         * Seek to the keyframe at timestamp.
         * 'timestamp' in 'stream_index'.
         *
         * @param s media file handle
         * @param stream_index If stream_index is (-1), a default
         * stream is selected, and timestamp is automatically converted
         * from AV_TIME_BASE units to the stream specific time_base.
         * @param timestamp Timestamp in AVStream.time_base units
         *        or, if no stream is specified, in AV_TIME_BASE units.
         * @param flags flags which select direction and seeking mode
         * @return >= 0 on success
         */
        int ret = av_seek_frame(piml->formatCtx, streamIndex, timestamp, AVSEEK_FLAG_BACKWARD);

        return ret;
    }

    int EyerAVReader::Open()
    {
        int ret = avformat_open_input(&piml->formatCtx, piml->path.str, NULL, NULL);
        if(ret){
            return -1;
        }

        avformat_find_stream_info(piml->formatCtx, NULL);

        return 0;
    }

    int EyerAVReader::Close()
    {
        avformat_close_input(&piml->formatCtx);
        return 0;
    }

    int EyerAVReader::Read(EyerAVPacket * packet)
    {
        int ret = av_read_frame(piml->formatCtx, packet->piml->packet);
        return ret;
    }

    int EyerAVReader::GetStreamCount()
    {
        if(piml->formatCtx == nullptr){
            return -1;
        }

        // TODO 判断文件是否打开成功

        return piml->formatCtx->nb_streams;
    }

    double EyerAVReader::GetDuration()
    {
        return piml->formatCtx->duration / 1000000;
    }

    int EyerAVReader::GetStream(EyerAVStream & stream, int index)
    {
        if(piml->formatCtx == nullptr){
            return -1;
        }

        // TODO 判断文件是否打开成功
        if(index < 0){
            return -1;
        }
        if(index >= GetStreamCount()) {
            return -1;
        }

        double duration = piml->formatCtx->streams[index]->duration * 1.0 * piml->formatCtx->streams[index]->time_base.num / piml->formatCtx->streams[index]->time_base.den;
        stream.SetDuration(duration);

        stream.streamIndex = piml->formatCtx->streams[index]->index;
        stream.piml->type = EyerAVStreamType::STREAM_TYPE_UNKNOW;

        avcodec_parameters_copy(stream.piml->codecpar, piml->formatCtx->streams[index]->codecpar);

        return 0;
    }

    int EyerAVReader::GetStreamTimeBase(EyerAVRational & rational, int streamIndex)
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
