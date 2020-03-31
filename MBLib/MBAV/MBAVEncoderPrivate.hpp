#ifndef	EYER_LIB_AV_ENCODER_PRIVATE_H
#define	EYER_LIB_AV_ENCODER_PRIVATE_H

extern "C"{
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
}

namespace MB
{
    class MBAVEncoderPrivate
    {
    public:
        AVCodecContext * codecContext = nullptr;
    };
}

#endif