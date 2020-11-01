#ifndef EYERLIB_EYERDASHREADER_HPP
#define EYERLIB_EYERDASHREADER_HPP

#include "EyerCore/EyerCore.hpp"
#include "EyerMPD.hpp"
#include "EyerDASHReaderThread.hpp"

namespace Eyer{
    class EyerDASHReader {
    public:
        EyerDASHReader(const EyerString & _mpdUrl);
        ~EyerDASHReader();

        int SetCacheDir(const EyerString & _cacheUrl);

        int read_packet(uint8_t *buf, int buf_size);
        int seek_packet(int64_t offset, int whence);

    private:
        EyerString mpdUrl;
        EyerString cacheUrl;

        EyerDASHReaderThread * readerThread = nullptr;
        EyerBufferMut dataBuffer;
    };
}


#endif //EYERLIB_EYERDASHREADER_HPP
