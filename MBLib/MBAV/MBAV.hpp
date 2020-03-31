#ifndef	EYER_LIB_AV_H
#define	EYER_LIB_AV_H

#include "MBCore/MBCore.hpp"
#include <vector>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

namespace MB
{
    class MBAVPacket;
    class MBAVReader;
    class MBAVDecoder;
    class MBAVStream;
    class MBAVEncoder;

    class MBAVPacketPrivate;
    class MBAVReaderPrivate;
    class MBAVDecoderPrivate;
    class MBAVStreamPrivate;
    class MBAVFramePrivate;
    class MBAVEncoderPrivate;
    class MBAVWriterPrivate;

    class MBAVAudioFrameUtil;
    class MBAVFrameWeight;
    class MBAVRational;

    enum MBAVPixelFormat
    {
        MB_AV_PIX_FMT_UNKNOW = 0,
        MB_AV_PIX_FMT_YUV420P = 101,
        MB_AV_PIX_FMT_YUVJ420P = 102,
        MB_AV_PIX_FMT_YUV444P = 103,
        MB_AV_PIX_FMT_YUVJ444P = 104
    };

    enum MBAVStreamType{
        STREAM_TYPE_UNKNOW = 0,
        STREAM_TYPE_AUDIO = 1,
        STREAM_TYPE_VIDEO = 2
    };

    enum MBAVFormat
    {
        EYER_AV_SAMPLE_FMT_FLTP = 1
    };

    class MBAVPacket
    {
    public:
        MBAVPacketPrivate * piml = nullptr;
    public:
        MBAVPacket();
        ~MBAVPacket();

        int GetStreamId();

        uint64_t GetPTS();
        uint64_t GetDTS();

        int RescaleTs(MB::MBAVRational & codecTimebase, MB::MBAVRational & streamTimebase);

        int SetPTS(uint64_t pts);
        int SetDTS(uint64_t dts);

        int SetStreamId(int id);
    };

    class MBAVFrame
    {
    public:
        MBAVFramePrivate * piml = nullptr;

        std::vector<void *> dataManager;
    public:
        MBAVFrame();
        ~MBAVFrame();

        MBAVFrame(const MBAVFrame & frame);
        MBAVFrame & operator = (const MBAVFrame & frame);

        int SetPTS(int64_t pts);
        int64_t GetPTS();

        int GetYData(unsigned char * yData);
        int GetUData(unsigned char * uData);
        int GetVData(unsigned char * vData);

        float GetAudioFloatData(int channel, int index);
        int SetAudioFloatData(int channel, int index, float d);

        int GetAudioData(unsigned char * data);
        int SetAudioData(unsigned char * data, int dataLen, int nbSamples, int channel, MBAVFormat format);

        int GetLineSize(int channel);

        int SetVideoData420P(unsigned char * y, unsigned char * u, unsigned char * v, int width, int height);

        int GetWidth();
        int GetHeight();

        int GetChannels();
        int GetNBSamples();
        int GetPerSampleSize();

        int InitAACFrame(int channels);

        int GetInfo();

        MBAVPixelFormat GetPixFormat() const;
    };

    class MBAVReader
    {
    public:
        MBAVReaderPrivate * piml = nullptr;
    public:
        MBAVReader(MBString _path);
        ~MBAVReader();

        int Open();
        int Close();

        int SeekFrame(int streamIndex, int64_t timestamp);
        int SeekFrame(int streamIndex, double timestamp);

        int Read(MBAVPacket * packet);

        int GetStreamCount();
        int GetStream(MBAVStream & stream, int index);

        int GetStreamTimeBase(MBAVRational & rational, int streamIndex);
    };

    class MBAVWriter
    {
    public:
        MBAVWriterPrivate * piml = nullptr;
    public:
        MBAVWriter(MBString _path);
        ~MBAVWriter();

        int Open();
        int Close();

        int AddStream(MBAVEncoder * encoder);

        int GetStreamTimeBase(MBAVRational & rational, int streamIndex);

        int GetStreamTimeBaseDen(int streamIndex);
        int GetStreamTimeBaseNum(int streamIndex);

        int WriteHand();
        int WritePacket(MBAVPacket * packet);
    };

    class MBAVStream
    {
    public:
        int streamIndex = -1;
        MBAVStreamPrivate * piml = nullptr;

        double duration = 0;
    public:
        MBAVStream();
        ~MBAVStream();

        MBAVStreamType GetStreamType();

        int SetDuration(double _duration);
        double GetDuration();
    };

    class MBAVDecoder
    {
    public:
        MBAVDecoderPrivate * piml = nullptr;
    public:
        MBAVDecoder();
        ~MBAVDecoder();

        int Init(MBAVStream * stream);

        int SendPacket(MBAVPacket * packet);
        int RecvFrame(MBAVFrame * frame);

        int GetFrameSize();
        int GetSampleRate();
    };

    enum CodecId
    {
        CODEC_ID_UNKNOW = 0,
        CODEC_ID_H264 = 1,
        CODEC_ID_AAC = 2
    };

    class EncoderParam
    {
    public:
        CodecId codecId = CodecId::CODEC_ID_UNKNOW;
        int width = 0;
        int height = 0;
        int fps = 25;
    };

    class MBAVEncoder
    {
    public:
        MBAVEncoderPrivate * piml = nullptr;
    public:
        MBAVEncoder();
        ~MBAVEncoder();

        int GetTimeBase(MBAVRational & rational);

        int _Init(MBAVStream * stream);
        int Init(EncoderParam * param);

        int Flush();

        int GetFPS();

        int GetBufferSize();
        int GetFrameSize();
        int GetChannelNum();

        int SendFrame(MBAVFrame * frame);
        int RecvPacket(MBAVPacket * packet);
    };



    enum MBAVBitmapFormat
    {
        BITMAP_FORMAT_RGBA8888 = 1,
    };

    class MBAVBitmap
    {
    private:
        int width = 0;
        int height = 0;
        MBAVBitmapFormat format = MBAVBitmapFormat::BITMAP_FORMAT_RGBA8888;
        unsigned char * pixelData = nullptr;
    public:
        MBAVBitmap();
        ~MBAVBitmap();

        int SetRGBA8888(int w, int h, unsigned char * _pixelData);

        int GetW();
        int GetH();

        int SetW(int w);
        int SetH(int h);

        MBAVBitmapFormat GetFormat();
    };

    class MBAVRational
    {
    public:
        int num = 0;
        int den = 0;

        MBAVRational();
        MBAVRational(const MBAVRational & avRational);
        ~MBAVRational();

        MBAVRational & operator = (const MBAVRational & avRational);
    };


    class MBAVFrameWeight
    {
    public:
        MBAVFrameWeight();
        MBAVFrameWeight(MBAVFrame & frame, float weight);
        ~MBAVFrameWeight();

        MBAVFrameWeight(MBAVFrameWeight & frameWeight);

        MBAVFrameWeight & operator = (MBAVFrameWeight & frameWeight);

    public:
        MBAVFrame * frame = nullptr;
        float weight = 1.0;
    };

    class MBAVAudioFrameUtil
    {
    public:
        MBAVAudioFrameUtil();
        ~MBAVAudioFrameUtil();

        int AddAudioFrame(MBAVFrame & frame, float weight);
        int MergeAudioFrame(MBAVFrame & outFrame);

    private:
        MBLinkedList<MBAVFrameWeight *> frameList;
    };
}

#endif
