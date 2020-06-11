#include "EyerAV.hpp"

namespace Eyer
{
    EyerAVTool::EyerAVTool(){

    }

    EyerAVTool::~EyerAVTool(){

    }
    
    int EyerAVTool::getYUVLen(int width, int height, EyerYUVLen & yuvLen, EyerAVPixelFormat format)
    {
        if(format == Eyer_AV_PIX_FMT_YUV422P || Eyer_AV_PIX_FMT_YUVJ422P){
            yuvLen.yLen = width * height;
            yuvLen.uLen = width * (height / 2);
            yuvLen.vLen = width * (height / 2);
        }

        if(format == Eyer_AV_PIX_FMT_YUVNV16 || Eyer_AV_PIX_FMT_YUVNV61){
            yuvLen.yLen = width * height;
            yuvLen.uvLen = width * height;
        }

        return 0;
    }
}
