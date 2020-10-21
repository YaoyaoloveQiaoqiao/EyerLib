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


        // get video init buffer

        EyerMP4Box_ftyp videoftyp;
        EyerMP4Box_mvhd videomvhd;
        EyerMP4Box_mehd videomehd;
        EyerMP4Box_trex videotrex;
        EyerMP4Box_trak videotrak;

        EyerMP4Box_ftyp audioftyp;
        EyerMP4Box_mvhd audiomvhd;
        EyerMP4Box_mehd audiomehd;
        EyerMP4Box_trex audiotrex;
        EyerMP4Box_trak audiotrak;

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

            printf("==========Parse==========\n");
            ParseMP4(videoftyp, videomvhd, videomehd, videotrex, videotrak, videoBox);
        }

        {
            EyerString m4vUrl = "https:/redknot.cn/DASH/./audio/xiaomai_dashinit.mp4";
            EyerLog("m4v url: %s\n", m4vUrl.str);

            Eyer::EyerSimplestHttp http;

            Eyer::EyerBuffer m4vBuffer;
            ret = http.Get(m4vBuffer, m4vUrl);
            if(ret){
                // Http fail
                return;
            }

            EyerMP4Box videoBox(m4vBuffer);
            videoBox.PrintAll();

            printf("==========Parse==========\n");
            ParseMP4(audioftyp, audiomvhd, audiomehd, audiotrex, audiotrak, videoBox);
        }

        printf("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");

        EyerMP4Box_ftyp new_ftyp = videoftyp;
        videoftyp.PrintInfo();
        new_ftyp.PrintInfo();

        EyerMP4Box_moov new_moov;

        EyerMP4Box_mvhd new_mvhd = videomvhd;

        EyerMP4Box_mvex new_mvex;
        EyerMP4Box_mehd new_mehd = videomehd;
        new_mvex.AddSubBox(new_mehd);
        new_mvex.AddSubBox(videotrex);
        new_mvex.AddSubBox(audiotrex);

        new_moov.AddSubBox(new_mvhd);
        new_moov.AddSubBox(new_mvex);
        new_moov.AddSubBox(videotrak);
        new_moov.AddSubBox(audiotrak);

        EyerBuffer mp4Buffer;
        mp4Buffer.Append(new_ftyp.GetTotalBufferWithHead());
        mp4Buffer.Append(new_moov.GetTotalBufferWithHead());

        dataBuffer->Append(mp4Buffer);

        EyerMP4Box b(mp4Buffer);
        // b.PrintAll();



        int index = 1;
        while(!stopFlag){
            EyerTime::EyerSleepMilliseconds(1);
            if(dataBuffer->GetLen() >= 1024 * 1024 * 10){
                continue;
            }

            {
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
            }

            {
                EyerString m4vUrl;
                mpd.GetVideoURL(m4vUrl, index, representationIndex);

                Eyer::EyerURLUtil urlUtil(mpdUrl);
                m4vUrl = urlUtil.GetAbsolutePath(m4vUrl);

                EyerLog("m4v url: %s\n", m4vUrl.str);
                m4vUrl = EyerString("https:/redknot.cn/DASH/./audio/xiaomai_dash") + EyerString::Number(index) + ".m4s";

                Eyer::EyerSimplestHttp http;
                Eyer::EyerBuffer m4vBuffer;
                ret = http.Get(m4vBuffer, m4vUrl);
                if(ret){
                    continue;
                }

                dataBuffer->Append(m4vBuffer);
            }


            index++;
        }
    }


    int EyerDASHReaderThread::ParseMP4(
            EyerMP4Box_ftyp & _outftyp,
            EyerMP4Box_mvhd & _outmvhd,
            EyerMP4Box_mehd & _outmehd,
            EyerMP4Box_trex & _outtrex,
            EyerMP4Box_trak & _outtrak,
            EyerMP4Box & box)
    {
        int ret;

        ret = box.GetFTYP(_outftyp);
        if(ret){
            printf("GetFTYP Fail\n");
            return -1;
        }



        EyerMP4Box_moov moov;
        ret = box.GetMOOV(moov);
        if(ret){
            printf("GetMOOV Fail\n");
            return -1;
        }



        ret = moov.GetMVHD(_outmvhd);
        if(ret){
            printf("GetMVHD Fail\n");
            return -1;
        }
        // _outmvhd.PrintInfo();



        EyerMP4Box_mvex mvex;
        ret = moov.GetMVEX(mvex);
        if(ret){
            printf("GetMVEX Fail\n");
            return -1;
        }
        // mvex.PrintInfo();



        ret = mvex.GetMEHD(_outmehd);
        if(ret){
            printf("GetMEHD Fail\n");
            return -1;
        }
        // _outmehd.PrintInfo();



        ret = mvex.GetTREX(_outtrex);
        if(ret){
            printf("GetTREX Fail\n");
            return -1;
        }
        // _outtrex.PrintInfo();



        ret = moov.GetTRAK(_outtrak);
        if(ret){
            printf("GetTRAK Fail\n");
            return -1;
        }
        // _outtrak.PrintInfo();

        return 0;
    }
}