#include "EyerDASHReader.hpp"
#include "EyerNet/EyerNet.hpp"
#include "EyerMPD.hpp"

namespace Eyer
{
    EyerDASHReader::EyerDASHReader(const EyerString & _mpdUrl) : stream(_mpdUrl, 1)
    {
        mpdUrl = _mpdUrl;

        stream.StartLoad();
    }

    EyerDASHReader::~EyerDASHReader()
    {
    }

    int EyerDASHReader::read_packet(uint8_t * buf, int buf_size)
    {
        while(1){
            EyerTime::EyerSleepMilliseconds(1);
            if(stream.GetBuffer()->GetLen() > 0){
                break;
            }
        }

        if(stream.GetBuffer()->GetLen() > 0){
            EyerBuffer buffer;
            int len = stream.GetBuffer()->GetLen();
            if(buf_size <= len){
                len = buf_size;
            }
            stream.GetBuffer()->CutOff(buffer, len);

            buffer.GetBuffer(buf);

            // readerThread->DataBufferChange();
            return len;
        }

        return -1;
    }

    int EyerDASHReader::seek_packet(int64_t offset, int whence)
    {
        return 0;
    }
}