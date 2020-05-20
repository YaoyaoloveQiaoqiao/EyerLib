#include "EyerYUV.hpp"

#include "libyuv.h"

namespace Eyer
{
    EyerYUV::EyerYUV()
    {

    }

    EyerYUV::~EyerYUV()
    {

    }

    int EyerYUV::RGB2YUV420(int width, int height, unsigned char * rgbData, unsigned char * y, unsigned char * u, unsigned char * v)
    {
        libyuv::RGB24ToI420(
                rgbData,
                width * 3,
                y,
                width,
                u,
                width / 2,
                v,
                width / 2,
                width,
                height
                );
        return 0;
    }


    int EyerYUV::I420_TO_RGBA(int width, int height, unsigned char * y, unsigned char * u, unsigned char * v, unsigned char * rgbData)
    {
        libyuv::I420ToARGB(
            y, 
            width, 
            u, 
            width / 2, 
            v, 
            width / 2,
            rgbData,
            width * 4, 
            width, 
            height);

        return 0;
    }
}