#include "MBType.hpp"
#include "MBTypePrivate.hpp"

namespace MB
{
    MBType::MBType(MBString _typeFile)
    {
        typeFile = _typeFile;
        impl = new MBTypePrivate();
    }

    MBType::~MBType()
    {
        std::map<int, MBTypeBitmap *>::iterator it;
        for(it=bitmapCache.begin();it!=bitmapCache.end();++it){
            MBTypeBitmap * bitmap = it->second;
            delete bitmap;
        }
        bitmapCache.clear();

        if(impl->init){
            FT_Done_FreeType(impl->ft);
            impl->init = 0;
        }
        if(impl != nullptr){
            delete impl;
            impl = nullptr;
        }
    }

    int MBType::Init()
    {
        if (FT_Init_FreeType(&impl->ft)) {
            return -1;
        }
        impl->init = 1;

        return 0;
    }


    int MBType::GenChar(wchar_t c, int pixel_height)
    {
        FT_Face face;
        if (FT_New_Face(impl->ft, typeFile.str, 0, &face))
        {
            MBLog("FT_New_Face Fail\n");
            return -2;
        }

        FT_Set_Pixel_Sizes(face, 0, pixel_height);

        if (FT_Load_Char(face, c, FT_LOAD_RENDER));

        unsigned int bitmapDataLen = face->glyph->bitmap.width * face->glyph->bitmap.rows;

        MBTypeBitmap * b = new MBTypeBitmap(face->glyph->bitmap.width, face->glyph->bitmap.rows, face->glyph->bitmap_left, face->glyph->bitmap_top, face->glyph->advance.x, face->glyph->bitmap.buffer, bitmapDataLen);

        bitmapCache.insert(std::pair<int, MBTypeBitmap *>(indexIndex, b));

        FT_Done_Face(face);

        return indexIndex;
    }

    int MBType::GetCharBitmap(int index, MBTypeBitmap * _bitmap)
    {
        std::map<int, MBTypeBitmap *>::iterator it = bitmapCache.find(index);
        if(it == bitmapCache.end()) {
            return -1;
        }
        else {
            MBTypeBitmap * bitmap = it->second;
            *_bitmap = *bitmap;
            delete bitmap;
            bitmapCache.erase(index);
        }

        return 0;
    }
}