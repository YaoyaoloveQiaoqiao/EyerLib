#ifndef	EYER_LIB_AV_PACKET_PRIVATE_H
#define	EYER_LIB_AV_PACKET_PRIVATE_H

extern "C"{
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
}

namespace MB
{
    class MBAVPacketPrivate
    {
    public:
        AVPacket * packet = nullptr;
    };
}

#endif