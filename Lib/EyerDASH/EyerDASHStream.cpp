#include "EyerDASHStream.hpp"

namespace Eyer
{
    EyerDASHStream::EyerDASHStream(const EyerString & _mpdUrl, int _streamId)
    {
        mpdUrl = _mpdUrl;
        streamId = _streamId;
    }

    EyerDASHStream::~EyerDASHStream()
    {
        StopLoad();
    }

    int EyerDASHStream::StartLoad()
    {
        StopLoad();
        streamReaderThread = new EyerDASHStreamReaderThread(mpdUrl, streamId, 1, &dataBuffer);
        streamReaderThread->Start();
        return 0;
    }

    int EyerDASHStream::StopLoad()
    {
        if(streamReaderThread != nullptr){
            streamReaderThread->Stop();
            delete streamReaderThread;
            streamReaderThread = nullptr;
        }
        return 0;
    }

    EyerBufferMut * EyerDASHStream::GetBuffer()
    {
        return &dataBuffer;
    }
}
