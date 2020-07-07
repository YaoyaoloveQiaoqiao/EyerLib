#include "AVUtil.hpp"
#include <math.h>

namespace Eyer
{
    EyerVideoDecoderLine::EyerVideoDecoderLine(EyerString _resPath, double _startTime, EyerAVStreamType _type)
    {
        resPath = _resPath;
        type = _type;
        startTime = _startTime;

        reader = new EyerAVReader(resPath);
    }

    EyerVideoDecoderLine::~EyerVideoDecoderLine()
    {
        if(decoder != nullptr){
            delete decoder;
            decoder = nullptr;
        }

        if(reader != nullptr){
            reader->Close();

            delete reader;
            reader = nullptr;
        }
    }

    int EyerVideoDecoderLine::Init()
    {
        int ret = reader->Open();
        if(ret){
            return -1;
        }

        streamIndex = reader->GetVideoStreamIndex();
        if(streamIndex < 0){
            reader->Close();
            return -2;
        }

        EyerAVStream stream;
        ret = reader->GetStream(stream, streamIndex);
        if(ret){
            reader->Close();
            return -3;
        }

        if(decoder != nullptr){
            delete decoder;
            decoder = nullptr;
        }

        decoder = new EyerAVDecoder();
        decoder->Init(&stream);
        
        return 0;
    }

    int EyerVideoDecoderLine::GetFrame(EyerAVFrame & frame, double ts)
    {
        while(1){
            // 判断是否到了文件末尾
            // 先查看缓存列表中有没有合适的
            // 读取一帧进缓存


        }

        return 0;
    }

    double EyerVideoDecoderLine::GetStartTime()
    {
        if(reader == nullptr){
            return startTime;
        }

        if(frameList.getLength() <= 0){
            return startTime;
        }

        EyerAVFrame * frame = nullptr;
        frameList.find(0, frame);
        if(frame == nullptr){
            return startTime;
        }

        Eyer::EyerAVRational streamTimebase;
        reader->GetStreamTimeBase(streamTimebase, streamIndex);

        double t = frame->GetPTS() * 1.0 * streamTimebase.num / streamTimebase.den;

        return t;
    }

    int EyerVideoDecoderLine::GetCacheFrameCount()
    {
        return frameList.getLength();
    }

    int EyerVideoDecoderLine::ReadFrame()
    {
        if(decoder == nullptr){
            return -1;
        }

        EyerAVPacket packet;
        int ret = reader->Read(&packet);
        if(ret){
            // 清空解码器
            ret = decoder->SendPacket(nullptr);
            if(ret){
                return -3;
            }
            while(1){
                EyerAVFrame * frame = new EyerAVFrame();
                ret = decoder->RecvFrame(frame);
                if(ret){
                    delete frame;
                    break;
                }

                frameList.insertBack(frame);
            }
        }
        else{
            if(packet.GetStreamId() != streamIndex){
                return -2;
            }
            ret = decoder->SendPacket(&packet);
            if(ret){
                return -3;
            }
            while(1){
                EyerAVFrame * frame = new EyerAVFrame();
                ret = decoder->RecvFrame(frame);
                if(ret){
                    delete frame;
                    break;
                }

                frameList.insertBack(frame);
            }
        }

        return 0;
    }

    int EyerVideoDecoderLine::SelectFrameInList(EyerAVFrame & frame, double ts)
    {
        Eyer::EyerAVRational streamTimebase;
        reader->GetStreamTimeBase(streamTimebase, streamIndex);

        if(frameList.getLength() <= 0){
            return -1;
        }
        /*
        if(frameList.getLength() == 1)
            EyerAVFrame * f = nullptr;
            frameList.find(0, f);
            if(f == nullptr){
                return -2;
            }

            double t = f->GetPTS() * 1.0 * streamTimebase.num / streamTimebase.den;
        }
        */

        for(int i=1;i<frameList.getLength();i++){ 
            EyerAVFrame * fb = nullptr;
            frameList.find(i, fb);
            if(fb == nullptr){
                continue;
            }

            double tb = fb->GetPTS() * 1.0 * streamTimebase.num / streamTimebase.den;



            EyerAVFrame * fa = nullptr;
            frameList.find(i - 1, fa);
            if(fa == nullptr){
                continue;
            }

            double ta = fa->GetPTS() * 1.0 * streamTimebase.num / streamTimebase.den;


            if(ts == ta){

            }
            if(ts == tb){

            }

            if(ts > ta && ts < tb){
                // 落到中间了
            }

            if(ts < ta && ts < tb){
                //出错了
                return -3;
            }

            if(ts > ta && ts > tb){
            }
        }

        // 无论成功还是失败，都要丢帧
        while(frameList.getLength() > 5){
            EyerAVFrame * f = nullptr;
            frameList.find(0, f);
            if(f != nullptr){
                delete f;
            }
            frameList.deleteEle(0);
        }

        return 0;
    }
}