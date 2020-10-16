#include "EyerDASHReaderThread.hpp"
#include "EyerNet/EyerNet.hpp"
#include "EyerMPD.hpp"

namespace Eyer
{
    EyerDASHReaderThread::EyerDASHReaderThread(EyerString & _mpdUrl, EyerBuffer * _dataBuffer)
        : mpdUrl(_mpdUrl)
    {
        dataBuffer = _dataBuffer;
    }

    EyerDASHReaderThread::~EyerDASHReaderThread()
    {

    }

    void EyerDASHReaderThread::Run()
    {
        Eyer::EyerSimplestHttp http;
        Eyer::EyerBuffer buffer;
        int ret = http.Get(buffer, mpdUrl);
        if(ret){
            EyerLog("Read mpd file error");
            return;
        }
        /*
        unsigned char mpdStr[1024 * 1024];
        buffer.GetBuffer((unsigned char *)mpdStr);
        printf("%s\n", mpdStr);
        */

        Eyer::EyerMPD mpd;
        ret = mpd.LoadMPD(buffer);
        if(ret){
            EyerLog("Read mpd file error");
            return;
        }

        mpd.PrintInfo();

        int representationIndex = 3;


        {
            EyerString m4vUrl;
            mpd.GetInitURL(m4vUrl, representationIndex);

            Eyer::EyerURLUtil urlUtil(mpdUrl);
            m4vUrl = urlUtil.GetAbsolutePath(m4vUrl);

            EyerLog("m4v url: %s\n", m4vUrl.str);

            Eyer::EyerSimplestHttp http;
            Eyer::EyerBuffer m4vBuffer;
            ret = http.Get(m4vBuffer, m4vUrl);
            if(!ret){
                dataBuffer->Append(m4vBuffer);
            }
        }
        /*
        {
            EyerString m4aUrl = "https:/redknot.cn/DASH/./audio/xiaomai_dashinit.mp4";

            EyerLog("m4a url: %s\n", m4aUrl.str);

            Eyer::EyerSimplestHttp http;
            Eyer::EyerBuffer m4aBuffer;

            ret = http.Get(m4aBuffer, m4aUrl);
            if(!ret){
                dataBuffer->Append(m4aBuffer);
            }
        }
        */

        int index = 1;
        while(!stopFlag){
            EyerTime::EyerSleepMilliseconds(1);
            if(dataBuffer->GetLen() >= 1024 * 1024 * 10){
                continue;
            }

            EyerString m4vUrl;
            mpd.GetVideoURL(m4vUrl, index, representationIndex);

            Eyer::EyerURLUtil urlUtil(mpdUrl);
            m4vUrl = urlUtil.GetAbsolutePath(m4vUrl);

            // EyerLog("m4v url: %s\n", m4vUrl.str);
            // m4vUrl = EyerString("https:/redknot.cn/DASH/./audio/xiaomai_dash") + EyerString::Number(index) + ".m4s";

            Eyer::EyerSimplestHttp http;
            Eyer::EyerBuffer m4vBuffer;
            ret = http.Get(m4vBuffer, m4vUrl);
            if(ret){
                continue;
            }

            dataBuffer->Append(m4vBuffer);

            index++;
        }
    }
}