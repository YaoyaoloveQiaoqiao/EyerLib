#include "EyerAV.hpp"

namespace Eyer
{
    EyerAVTool::EyerAVTool(){

    }

    EyerAVTool::~EyerAVTool(){

    }
    
    int EyerAVTool::GetYUVLen(int width, int height, EyerYUVLen & yuvLen, EyerAVPixelFormat format)
    {
        //420
        if(format == Eyer_AV_PIX_FMT_YUV420P){
            yuvLen.yLen = width * height;
            yuvLen.uLen = (width / 2) * (height / 2);
            yuvLen.vLen = (width / 2) * (height / 2);
        }

        if(format == Eyer_AV_PIX_FMT_YUVNV21 || Eyer_AV_PIX_FMT_YUVNV12){
            yuvLen.yLen = width * height;
            yuvLen.uvLen = width * (height / 2);
        }

        //422
        if(format == Eyer_AV_PIX_FMT_YUV422P){
            yuvLen.yLen = width * height;
            yuvLen.uLen = width * (height / 2);
            yuvLen.vLen = width * (height / 2);
        }

        if(format == Eyer_AV_PIX_FMT_YUVNV16 || Eyer_AV_PIX_FMT_YUVNV61){
            yuvLen.yLen = width * height;
            yuvLen.uvLen = width * height;
        }

        //444
        if(format == Eyer_AV_PIX_FMT_YUV444P){
            yuvLen.yLen = width * height;
            yuvLen.uLen = width * height;
            yuvLen.vLen = width * height;
        }

        return 0;
    }
}
