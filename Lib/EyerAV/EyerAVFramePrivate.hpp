#ifndef	EYER_LIB_AV_FRAME_PRIVATE_H
#define	EYER_LIB_AV_FRAME_PRIVATE_H

extern "C"{
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
}

namespace Eyer
{
    class EyerAVFramePrivate
    {
    public:
        AVFrame * frame = nullptr;
        unsigned char * data = nullptr;
    };
}

#endif
