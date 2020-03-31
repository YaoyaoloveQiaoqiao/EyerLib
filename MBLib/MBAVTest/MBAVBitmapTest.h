//
// Created by redknot on 2020/1/5.
//

#ifndef EYE_LIB_EYERAVBITMAPTEST_H
#define EYE_LIB_EYERAVBITMAPTEST_H

#include "MBAV/MBAV.hpp"
#include <gtest/gtest.h>

TEST(MBAVBitmap, bitmap){
    for(int i=0;i<1000;i++){
        int width = 100 + i;
        int height = 200 + i;

        unsigned char * pixelData = (unsigned char *)malloc(width * height * 4);
        memset(pixelData, 0, width * height * 4);

        MB::MBAVBitmap bitmap;
        bitmap.SetRGBA8888(width, height, pixelData);

        free(pixelData);

        ASSERT_EQ(width, bitmap.GetW()) << "宽度不匹配";
        ASSERT_EQ(height, bitmap.GetH()) << "高度不匹配";
        ASSERT_EQ(MB::MBAVBitmapFormat::BITMAP_FORMAT_RGBA8888, bitmap.GetFormat()) << "格式不匹配";
    }
}


#endif //EYE_LIB_EYERAVBITMAPTEST_H
