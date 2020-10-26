#ifndef EYERLIB_EYERDASHREADERTHREAD_HPP
#define EYERLIB_EYERDASHREADERTHREAD_HPP

#include "EyerThread/EyerThread.hpp"
#include "EyerCore/EyerCore.hpp"
#include "EyerMP4/EyerMP4.hpp"

namespace Eyer{
    class EyerDASHReaderThread : public EyerThread {
    public:
        EyerDASHReaderThread(EyerString & _mpdUrl, EyerBuffer * dataBuffer);
        ~EyerDASHReaderThread();

        virtual void Run();

        int ParseMP4(
                EyerMP4Box_ftyp & _outftyp,
                EyerMP4Box_mvhd & _outmvhd,
                EyerMP4Box_mehd & _outmehd,
                EyerMP4Box_trex & _outtrex,
                EyerMP4Box_trak & _outtrak,
                EyerMP4Box & box);

    private:
        EyerString & mpdUrl;
        EyerBuffer * dataBuffer = nullptr;
    };
}

#endif //EYERLIB_EYERDASHREADERTHREAD_HPP
