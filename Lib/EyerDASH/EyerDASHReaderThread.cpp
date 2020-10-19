#include "EyerDASHReaderThread.hpp"
#include "EyerNet/EyerNet.hpp"
#include "EyerMPD.hpp"

#include "EyerMP4/EyerMP4.hpp"

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

        Eyer::EyerMPD mpd;
        ret = mpd.LoadMPD(buffer);
        if(ret){
            EyerLog("Read mpd file error");
            return;
        }

        mpd.PrintInfo();

        int representationIndex = 3;


        EyerMP4Box_ftyp ftyp;

        EyerMP4Box_moov moov;
        EyerMP4Box_mvhd mvhd;
        EyerMP4Box_trak trakVideo;
        EyerMP4Box_trak trakAudio;

        // get video init buffer
        Eyer::EyerBuffer m4vBuffer;
        {
            EyerString m4vUrl;
            mpd.GetInitURL(m4vUrl, representationIndex);

            Eyer::EyerURLUtil urlUtil(mpdUrl);
            m4vUrl = urlUtil.GetAbsolutePath(m4vUrl);

            EyerLog("m4v url: %s\n", m4vUrl.str);

            Eyer::EyerSimplestHttp http;

            ret = http.Get(m4vBuffer, m4vUrl);
            if(ret){
                // Http fail
                return;
            }

            EyerMP4Box videoBox(m4vBuffer);
            videoBox.PrintAll();

            int ret = videoBox.GetFTYP(ftyp);
            if(ret){
                // Read ftyp Error
                return;
            }

            ret = videoBox.GetMOOV(moov);
            if(ret){
                // Read Moov Error
                return;
            }

            ret = moov.GetMVHD(mvhd);
            if(ret){
                // Read MVHD Error
                return;
            }

            ret = moov.GetTRAK(trakVideo);
            if(ret){
                // Read TRAK Error
                return;
            }
        }

        {
            EyerString m4vUrl = "https:/redknot.cn/DASH/./audio/xiaomai_dashinit.mp4";

            EyerLog("m4v url: %s\n", m4vUrl.str);

            Eyer::EyerSimplestHttp http;

            ret = http.Get(m4vBuffer, m4vUrl);
            if(ret){
                // Http fail
                return;
            }

            EyerMP4Box videoBox(m4vBuffer);
            videoBox.PrintAll();

            int ret = videoBox.GetFTYP(ftyp);
            if(ret){
                // Read ftyp Error
                return;
            }

            ret = videoBox.GetMOOV(moov);
            if(ret){
                // Read Moov Error
                return;
            }

            ret = moov.GetMVHD(mvhd);
            if(ret){
                // Read MVHD Error
                return;
            }

            ret = moov.GetTRAK(trakAudio);
            if(ret){
                // Read TRAK Error
                return;
            }
        }

        printf("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
        printf("=======================================================\n");
        // rebuild Mp4
        EyerBuffer outBuffer;
        // Add ftyp
        {
            int ftypLen = ftyp.GetTotalBufferData() + 8;

            printf("bufferLen: %d\n", ftypLen);

            char ftypHead[8];
            ftypHead[0] = *((char *)&ftypLen + 3);
            ftypHead[1] = *((char *)&ftypLen + 2);
            ftypHead[2] = *((char *)&ftypLen + 1);
            ftypHead[3] = *((char *)&ftypLen + 0);

            ftypHead[4] = 'f';
            ftypHead[5] = 't';
            ftypHead[6] = 'y';
            ftypHead[7] = 'p';

            outBuffer.Append((unsigned char *)ftypHead, 8);
            outBuffer.Append(ftyp.GetTotalBuffer());
        }

        // Add moov
        {
            int mvhdLen = mvhd.GetTotalBufferData() + 8;

            int trakLen = trakVideo.GetTotalBufferData() + 8;

            int moovLen = mvhdLen + trakLen + 8;
            moovLen = moov.GetTotalBufferData() + 8;

            char moovHead[8];
            moovHead[0] = *((char *)&moovLen + 3);
            moovHead[1] = *((char *)&moovLen + 2);
            moovHead[2] = *((char *)&moovLen + 1);
            moovHead[3] = *((char *)&moovLen + 0);

            moovHead[4] = 'm';
            moovHead[5] = 'o';
            moovHead[6] = 'o';
            moovHead[7] = 'v';

            outBuffer.Append((unsigned char *)moovHead, 8);
            outBuffer.Append(moov.GetTotalBuffer());


            char mvhdHead[8];
            mvhdHead[0] = *((char *)&mvhdLen + 3);
            mvhdHead[1] = *((char *)&mvhdLen + 2);
            mvhdHead[2] = *((char *)&mvhdLen + 1);
            mvhdHead[3] = *((char *)&mvhdLen + 0);

            mvhdHead[4] = 'm';
            mvhdHead[5] = 'v';
            mvhdHead[6] = 'h';
            mvhdHead[7] = 'd';

            // outBuffer.Append((unsigned char *)mvhdHead, 8);
            // outBuffer.Append(mvhd.GetTotalBuffer());



            char trackHead[8];
            trackHead[0] = *((char *)&trakLen + 3);
            trackHead[1] = *((char *)&trakLen + 2);
            trackHead[2] = *((char *)&trakLen + 1);
            trackHead[3] = *((char *)&trakLen + 0);

            trackHead[4] = 't';
            trackHead[5] = 'r';
            trackHead[6] = 'a';
            trackHead[7] = 'k';

            // outBuffer.Append((unsigned char *)trackHead, 8);
            // outBuffer.Append(trakVideo.GetTotalBuffer());
        }

        dataBuffer->Append(outBuffer);
        // dataBuffer->Append(m4vBuffer);



        {
            printf("uuuuuuuuuuuuuuuuuuuuu\n");
            unsigned char * a = (unsigned char *)malloc(outBuffer.GetBuffer());
            outBuffer.GetBuffer(a);

            for(int i=0;i<outBuffer.GetBuffer();i++){
                printf(" [%d]=%d ", i, a[i]);
            }

            free(a);
            printf("\nuuuuuuuuuuuuuuuuuuuuu\n");
        }
        {
            printf("uuuuuuuuuuuuuuuuuuuuu\n");
            unsigned char * a = (unsigned char *)malloc(m4vBuffer.GetBuffer());
            m4vBuffer.GetBuffer(a);

            for(int i=0;i<m4vBuffer.GetBuffer();i++){
                printf(" [%d]=%d ", i, a[i]);
            }

            free(a);
            printf("\nuuuuuuuuuuuuuuuuuuuuu\n");
        }

        EyerMP4Box videoBox(outBuffer);
        videoBox.PrintAll();


        printf("=======================================================\n");






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