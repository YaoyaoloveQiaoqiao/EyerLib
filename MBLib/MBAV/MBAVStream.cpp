#include "MBAV.hpp"

#include "MBAVStreamPrivate.hpp"

namespace MB
{
    MBAVStream::MBAVStream()
    {
        piml = new MBAVStreamPrivate();
        piml->codecContext = avcodec_alloc_context3(nullptr);
    }
    
    MBAVStream::~MBAVStream()
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

    MBAVStreamType MBAVStream::GetStreamType()
    {
        if(piml->codecContext->codec_type == AVMediaType::AVMEDIA_TYPE_VIDEO){
            return MBAVStreamType::STREAM_TYPE_VIDEO;
        }
        if(piml->codecContext->codec_type == AVMediaType::AVMEDIA_TYPE_AUDIO){
            return MBAVStreamType::STREAM_TYPE_AUDIO;
        }

        return MBAVStreamType::STREAM_TYPE_AUDIO;
    }

    int MBAVStream::SetDuration(double _duration)
    {
        duration = _duration;
        return 0;
    }

    double MBAVStream::GetDuration()
    {
        return duration;
    }
}
