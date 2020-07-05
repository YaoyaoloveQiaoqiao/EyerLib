#ifndef	EYER_LIB_TYPE_AV_H
#define	EYER_LIB_TYPE_AV_H

#include "EyerCore/EyerCore.hpp"
#include <string.h>
#include <map>

namespace Eyer
{
    class EyerType;
    class EyerTypePrivate;
    class EyerTypeBitmap;

    class EyerType
    {
    private:
        EyerString typeFile;
        EyerTypePrivate * impl = nullptr;

        std::map<int, EyerTypeBitmap *> bitmapCache;

        int indexIndex = 1;
    public:
        EyerType(EyerString typeFile);
        ~EyerType();

        int Init();

        int GenChar(wchar_t c, int pixel_height);
        int GetCharBitmap(int index, EyerTypeBitmap * bitmap);
    };

    class EyerTypeBitmap
    {
    public:
        int width = 0;
        int height = 0;
        int bearingX = 0;
        int bearingY = 0;
        int advance = 0;

        unsigned char * data = nullptr;
        unsigned int dataLen = 0;
    public:
        EyerTypeBitmap();
        EyerTypeBitmap(int width, int height, int bearingX, int bearingY, int advance, unsigned char * data, unsigned int dataLen);

        EyerTypeBitmap(const EyerTypeBitmap & _bitmap);

        ~EyerTypeBitmap();

        EyerTypeBitmap & operator = (const EyerTypeBitmap & _bitmap);
    };


    class EyerTypeMesh
    {
    public:
        EyerTypeMesh(EyerString typeFile);
        ~EyerTypeMesh();

        int Gen(wchar_t c);

    private:
        EyerString typeFile;
    };
}

#endif
