#ifndef	EYER_LIB_AV_WRITE_PRIVATE_H
#define	EYER_LIB_AV_WRITE_PRIVATE_H

#include "MBAV.hpp"

extern "C"{
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
}

namespace MB
{
    class MBAVWriterPrivate
    {
    public:
        MBString path;
        AVFormatContext * formatCtx = nullptr;
    };
}

#endif