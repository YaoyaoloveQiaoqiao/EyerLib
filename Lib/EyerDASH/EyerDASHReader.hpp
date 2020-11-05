#ifndef EYERLIB_EYERDASHREADER_HPP
#define EYERLIB_EYERDASHREADER_HPP

#include "EyerCore/EyerCore.hpp"
#include "EyerMPD.hpp"
#include "EyerDASHReaderThread.hpp"
#include "EyerDASHStream.hpp"

namespace Eyer{
    class EyerDASHReader {
    public:
        EyerDASHReader(const EyerString & _mpdUrl);
        ~EyerDASHReader();

        int read_packet(uint8_t *buf, int buf_size);
        int seek_packet(int64_t offset, int whence);

    private:
        EyerString mpdUrl;
        EyerDASHStream stream;
    };
}


#endif //EYERLIB_EYERDASHREADER_HPP
