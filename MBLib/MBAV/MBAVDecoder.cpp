#include "MBAV.hpp"

#include "MBAVStreamPrivate.hpp"
#include "MBAVDecoderPrivate.hpp"
#include "MBAVPacketPrivate.hpp"
#include "MBAVFramePrivate.hpp"

namespace MB
{
    MBAVDecoder::MBAVDecoder()
    {
        piml = new MBAVDecoderPrivate();
        piml->codecContext = avcodec_alloc_context3(nullptr);
    }

    MBAVDecoder::~MBAVDecoder()
    {
        if(piml->codecContext != nullptr){
            avcodec_free_context(&piml->codecContext);
            piml->codecContext = nullptr;
        }
        if(piml != nullptr){
            delete piml;
            piml = nullptr;
        }
    }

    int MBAVDecoder::Init(MBAVStream * stream)
    {
        avcodec_copy_context(piml->codecContext, stream->piml->codecContext);

        AVCodec * codec = avcodec_find_decoder(piml->codecContext->codec_id);

        piml->codecContext->thread_count = 4;

        int ret = avcodec_open2(piml->codecContext, codec, nullptr);
        if(ret){
            MBLog("Open Decoder Fail\n");
            return -1;
        }

        // printf("NUM:%d\n", piml->codecContext->time_base.num);
        // printf("DEN:%d\n", piml->codecContext->time_base.den);

        return 0;
    }

    int MBAVDecoder::GetFrameSize()
    {
        return piml->codecContext->frame_size;
    }

    int MBAVDecoder::GetSampleRate()
    {
        return piml->codecContext->sample_rate;
    }

    int MBAVDecoder::SendPacket(MBAVPacket * packet)
    {
        // TODO 判断解码器是否打开
        AVPacket * avpkt = nullptr;
        if(packet != nullptr){
            avpkt = packet->piml->packet;
        }

        int ret = avcodec_send_packet(piml->codecContext, avpkt);
        return ret;
    }

    int MBAVDecoder::RecvFrame(MBAVFrame * frame)
    {
        // TODO 判断解码器是否打开
        int ret = avcodec_receive_frame(piml->codecContext, frame->piml->frame);
        return ret;
    }
}
