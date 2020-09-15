#ifndef EYERLIB_EYERDASHREADER_HPP
#define EYERLIB_EYERDASHREADER_HPP

#include "EyerCore/EyerCore.hpp"
#include "EyerMPD.hpp"

namespace Eyer{
    class EyerDASHReader {
    public:
        EyerDASHReader(const EyerString & _mpdUrl);
        ~EyerDASHReader();

        int SetCacheDir(const EyerString & _cacheUrl);

        int read_packet(void * opaque, uint8_t *buf, int buf_size);
        int seek_packet(void * opaque, int64_t offset, int whence);

    private:
        int LoadMPD();

    private:
        EyerString mpdUrl;
        EyerString cacheUrl;

        Eyer::EyerMPD * mpd = nullptr;

        int index = 0;
    };
}


#endif //EYERLIB_EYERDASHREADER_HPP
