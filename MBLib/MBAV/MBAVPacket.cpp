#include "MBAV.hpp"

extern "C"{
#include <libavformat/avformat.h>
}

#include "MBAVPacketPrivate.hpp"

namespace MB
{
    MBAVPacket::MBAVPacket()
    {
        piml = new MBAVPacketPrivate();

        piml->packet = av_packet_alloc();
        av_init_packet(piml->packet);
    }

    MBAVPacket::~MBAVPacket()
    {
        if (piml->packet != nullptr) {
            av_packet_free(&piml->packet);
            piml->packet = nullptr;
        }

        if(piml != nullptr){
            delete piml;
            piml = nullptr;
        }
    }

    int MBAVPacket::RescaleTs( MB::MBAVRational & _codecTimebase, MB::MBAVRational & _streamTimebase)
    {
        AVRational codecTimebase;
        codecTimebase.num = _codecTimebase.num;
        codecTimebase.den = _codecTimebase.den;

        AVRational streamTimebase;
        streamTimebase.num = _streamTimebase.num;
        streamTimebase.den = _streamTimebase.den;

        av_packet_rescale_ts(piml->packet, codecTimebase, streamTimebase);
        return 0;
    }

    int MBAVPacket::GetStreamId()
    {
        return piml->packet->stream_index;
    }

    uint64_t MBAVPacket::GetPTS()
    {
        return piml->packet->pts;
    }

    uint64_t MBAVPacket::GetDTS()
    {
        return piml->packet->dts;
    }

    int MBAVPacket::SetPTS(uint64_t pts)
    {
        piml->packet->pts = pts;
        return 0;
    }
    
    int MBAVPacket::SetDTS(uint64_t dts)
    {
        piml->packet->dts = dts;
        return 0;
    }

    int MBAVPacket::SetStreamId(int id)
    {
        piml->packet->stream_index = id;
        return 0;
    }
}