#include "EyerDASHReader.hpp"
#include "EyerNet/EyerNet.hpp"
#include "EyerMPD.hpp"

namespace Eyer
{
    EyerDASHReader::EyerDASHReader(const EyerString & _mpdUrl)
    {
        mpdUrl = _mpdUrl;
    }

    EyerDASHReader::~EyerDASHReader()
    {
        if(mpd != nullptr){
            delete mpd;
            mpd = nullptr;
        }
    }

    int EyerDASHReader::SetCacheDir(const EyerString & _cacheUrl)
    {
        cacheUrl = _cacheUrl;
        return 0;
    }

    int EyerDASHReader::read_packet(void * opaque, uint8_t * buf, int buf_size)
    {
        int ret = 0;
        if(mpd == nullptr){
            ret = LoadMPD();
            if(ret){
                return -1;
            }
        }

        int representationIndex = 0;

        EyerString m4vUrl;
        ret = mpd->GetVideoURL(m4vUrl, index, representationIndex);
        if(ret){
            return -1;
        }

        Eyer::EyerURLUtil urlUtil(mpdUrl);
        m4vUrl = urlUtil.GetAbsolutePath(m4vUrl);

        printf("URL: %s\n", m4vUrl.str);


        Eyer::EyerSimplestHttp http;

        Eyer::EyerBuffer buffer;
        ret = http.Get(buffer, m4vUrl);
        if(ret){
            EyerLog("Read mpd file error");
            return -1;
        }

        int bufferLen = buffer.GetBuffer(nullptr);
        printf("Buffer len: %d, Target buffer len: %d\n", bufferLen, buf_size);
        buffer.GetBuffer(buf);

        index++;

        return bufferLen;
    }

    int EyerDASHReader::seek_packet(void * opaque, int64_t offset, int whence)
    {
        return 0;
    }

    int EyerDASHReader::LoadMPD()
    {
        Eyer::EyerSimplestHttp http;

        Eyer::EyerBuffer buffer;
        int ret = http.Get(buffer, mpdUrl);
        if(ret){
            EyerLog("Read mpd file error");
            return -1;
        }

        if(mpd != nullptr){
            delete mpd;
            mpd = nullptr;
        }
        mpd = new Eyer::EyerMPD();
        ret = mpd->LoadMPD(buffer);
        if(ret){
            delete mpd;
            mpd = nullptr;
            return -1;
        }

        mpd->PrintInfo();

        return 0;
    }
}