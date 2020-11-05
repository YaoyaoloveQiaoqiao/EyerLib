#ifndef EYER_LIB_EYERDASHSTREAM_HPP
#define EYER_LIB_EYERDASHSTREAM_HPP

#include "EyerCore/EyerCore.hpp"
#include "EyerDASHStreamReaderThread.hpp"

namespace Eyer
{
    class EyerDASHStream {
    public:
        EyerDASHStream(const EyerString & _mpdUrl, int _streamId);
        ~EyerDASHStream();

        int StartLoad();
        int StopLoad();

        EyerBufferMut * GetBuffer();

    private:
        EyerString mpdUrl;
        int streamId = -1;
        EyerBufferMut dataBuffer;

        EyerDASHStreamReaderThread * streamReaderThread = nullptr;
    };
}

#endif //EYER_LIB_EYERDASHSTREAM_HPP
