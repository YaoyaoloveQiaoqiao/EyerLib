//
// Created by redknot on 2020/1/5.
//

#include "MBAV.hpp"

namespace MB
{
    MBAVBitmap::MBAVBitmap()
    {

    }

    MBAVBitmap::~MBAVBitmap()
    {
        if(pixelData != nullptr){
            free(pixelData);
            pixelData = nullptr;
        }
    }

    int MBAVBitmap::SetRGBA8888(int w, int h, unsigned char * _pixelData)
    {
        if(pixelData != nullptr){
            free(pixelData);
            pixelData = nullptr;
        }

        format = MBAVBitmapFormat::BITMAP_FORMAT_RGBA8888;

        SetW(w);
        SetH(h);

        int pixelDataLen = w * h * 4;
        pixelData = (unsigned char *)malloc(pixelDataLen);
        memcpy(pixelData, _pixelData, pixelDataLen);

        return 0;
    }

    MBAVBitmapFormat MBAVBitmap::GetFormat()
    {
        return format;
    }

    int MBAVBitmap::GetW()
    {
        return width;
    }

    int MBAVBitmap::GetH()
    {
        return height;
    }

    int MBAVBitmap::SetW(int w)
    {
        width = w;
        return 0;
    }

    int MBAVBitmap::SetH(int h)
    {
        height = h;
        return 0;
    }
}
