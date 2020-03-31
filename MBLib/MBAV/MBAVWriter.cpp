#include "MBAV.hpp"

#include "MBAVStreamPrivate.hpp"
#include "MBAVDecoderPrivate.hpp"
#include "MBAVPacketPrivate.hpp"
#include "MBAVFramePrivate.hpp"
#include "MBAVEncoderPrivate.hpp"
#include "MBAVWriterPrivate.hpp"

namespace MB
{
    MBAVWriter::MBAVWriter(MBString _path)
    {
        piml = new MBAVWriterPrivate();
        piml->path = _path;
        av_register_all();
        avformat_network_init();

        avformat_alloc_output_context2(&piml->formatCtx, NULL, NULL, piml->path.str);
    }

    MBAVWriter::~MBAVWriter()
    {
        if(piml->formatCtx != NULL){
            avformat_free_context(piml->formatCtx);
            piml->formatCtx = NULL;
        }

        if(piml != nullptr){
            delete piml;
            piml = nullptr;
        }
    }

    int MBAVWriter::Open()
    {
        int ret = avio_open(&piml->formatCtx->pb, piml->path.str, AVIO_FLAG_WRITE);
        if(ret){
            return -1;
        }

        return 0;
    }

    int MBAVWriter::Close()
    {
        av_write_trailer(piml->formatCtx);
        avio_close(piml->formatCtx->pb);
        return 0;
    }

    int MBAVWriter::AddStream(MBAVEncoder * encoder)
    {
        if(encoder->piml->codecContext == nullptr){
            return -1;
        }
        
        AVStream * avStream = avformat_new_stream(piml->formatCtx, encoder->piml->codecContext->codec);

        avcodec_copy_context(avStream->codec, encoder->piml->codecContext);

        avStream->time_base = encoder->piml->codecContext->time_base;

        avStream->codec->codec_tag = 0;
        encoder->piml->codecContext->codec_tag = 0;
        
        return avStream->index;
    }

    int MBAVWriter::GetStreamTimeBase(MBAVRational & rational, int streamIndex)
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

    int MBAVWriter::GetStreamTimeBaseDen(int streamIndex)
    {
        if(streamIndex < 0){
            return -1;
        }
        if(streamIndex >= piml->formatCtx->nb_streams){
            return -1;
        }

        return piml->formatCtx->streams[streamIndex]->time_base.den;
    }

    int MBAVWriter::GetStreamTimeBaseNum(int streamIndex)
    {
        if(streamIndex < 0){
            return -1;
        }
        if(streamIndex >= piml->formatCtx->nb_streams){
            return -1;
        }

        return piml->formatCtx->streams[streamIndex]->time_base.num;
    }

    int MBAVWriter::WritePacket(MBAVPacket * packet)
    {
        int ret = av_interleaved_write_frame(piml->formatCtx, packet->piml->packet);
        return ret;
    }

    int MBAVWriter::WriteHand()
    {
        avformat_write_header(piml->formatCtx, nullptr);
        return 0;
    }
}
