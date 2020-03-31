#ifndef	EYER_LIB_TYPE_AV_H
#define	EYER_LIB_TYPE_AV_H

#include "MBCore/MBCore.hpp"
#include <string.h>
#include <map>

namespace MB
{
    class MBType;
    class MBTypePrivate;
    class MBTypeBitmap;

    class MBType
    {
    private:
        MBString typeFile;
        MBTypePrivate * impl = nullptr;

        std::map<int, MBTypeBitmap *> bitmapCache;

        int indexIndex = 1;
    public:
        MBType(MBString typeFile);
        ~MBType();

        int Init();

        int GenChar(wchar_t c, int pixel_height);
        int GetCharBitmap(int index, MBTypeBitmap * bitmap);
    };

    class MBTypeBitmap
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
        MBTypeBitmap();
        MBTypeBitmap(int width, int height, int bearingX, int bearingY, int advance, unsigned char * data, unsigned int dataLen);

        MBTypeBitmap(const MBTypeBitmap & _bitmap);

        ~MBTypeBitmap();

        MBTypeBitmap & operator = (const MBTypeBitmap & _bitmap);
    };
}

#endif