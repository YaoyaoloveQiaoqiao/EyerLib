#ifndef	EYER_LIB_AV_DECODER_PRIVATE_H
#define	EYER_LIB_AV_DECODER_PRIVATE_H

extern "C"{
#include <libavformat/avformat.h>
}

namespace MB
{
    class MBAVDecoderPrivate
    {
    public:
        AVCodecContext * codecContext = nullptr;
    };
}

#endif