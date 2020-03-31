#include "MBType.hpp"

namespace MB
{
    MBTypeBitmap::MBTypeBitmap()
    {
        
    }

    MBTypeBitmap::MBTypeBitmap(int _width, int _height, int _bearingX, int _bearingY, int _advance, unsigned char * _data, unsigned int _dataLen)
    {
        width = _width;
        height = _height;
        dataLen = _dataLen;
        bearingX = _bearingX;
        bearingY = _bearingY;
        advance = _advance;

        data = (unsigned char *)malloc(dataLen);
        memcpy(data, _data, dataLen);
    }

    MBTypeBitmap::MBTypeBitmap(const MBTypeBitmap & _bitmap)
    {
        *this = _bitmap;
    }

    MBTypeBitmap::~MBTypeBitmap()
    {
        if(data != nullptr){
            free(data);
            data = nullptr;
        }
    }

    MBTypeBitmap & MBTypeBitmap::operator = (const MBTypeBitmap & _bitmap)
    {
        width = _bitmap.width;
        height = _bitmap.height;
        dataLen = _bitmap.dataLen;

        bearingX = _bitmap.bearingX;
        bearingY = _bitmap.bearingY;

        advance = _bitmap.advance;

        if(data != nullptr){
            free(data);
            data = nullptr;
        }

        data = (unsigned char *)malloc(dataLen);
        memcpy(data, _bitmap.data, dataLen);

        return *this;
    }
}