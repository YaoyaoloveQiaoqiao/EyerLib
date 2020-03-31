#ifndef	EYER_LIB_AV_STREAM_PRIVATE_H
#define	EYER_LIB_AV_STREAM_PRIVATE_H

#include "MBAV.hpp"

extern "C"{
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
}

namespace MB
{
    class MBAVStreamPrivate
    {
    public:
        AVCodecContext * codecContext = nullptr;
        MBAVStreamType type = MBAVStreamType::STREAM_TYPE_UNKNOW;
    };
}


#endif