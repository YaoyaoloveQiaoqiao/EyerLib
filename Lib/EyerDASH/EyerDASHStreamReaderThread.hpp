#ifndef EYERLIB_EYERDASHSTREAMREADERTHREAD_HPP
#define EYERLIB_EYERDASHSTREAMREADERTHREAD_HPP

#include "EyerThread/EyerThread.hpp"
#include "EyerCore/EyerCore.hpp"
#include "EyerMP4/EyerMP4.hpp"
#include "EyerMPD.hpp"

namespace Eyer
{
    class EyerDASHStreamReaderThread : public EyerThread {
    public:
        EyerDASHStreamReaderThread(EyerString & _mpdUrl, int _representationIndex, int _startFragmentIndex, EyerBuffer * _dataBuffer);
        ~EyerDASHStreamReaderThread();

        virtual void Run();

    private:
        EyerString mpdUrl;
        int representationIndex = -1;
        int startFragmentIndex = -1;

        EyerBuffer * dataBuffer = nullptr;

        EyerBuffer MergeVideoAudio(MP4Box & videoBox, MP4Box & audioBox);

        EyerBuffer MergeAllTrack(Eyer::EyerMPD & mpd);
    };
}

#endif //EYERLIB_EYERDASHSTREAMREADERTHREAD_HPP
