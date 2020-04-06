#ifndef EYE_LIB_EYERAVREADPNG_H
#define EYE_LIB_EYERAVREADPNG_H

#include "EyerAV/EyerAV.hpp"
#include <gtest/gtest.h>

TEST(EyerAVReadePngList, readPngList){
    printf("===in test\n");
    Eyer::EyerAVReadePngList * pngList = new Eyer::EyerAVReadePngList("./demo.mp4");
    pngList->read();
}

#endif