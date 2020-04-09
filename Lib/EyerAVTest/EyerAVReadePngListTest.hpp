#ifndef EYE_LIB_EYERAVREADPNG_H
#define EYE_LIB_EYERAVREADPNG_H

#include "EyerAV/EyerAV.hpp"
#include <gtest/gtest.h>

TEST(EyerAVReadePngList, readPngList){
    Eyer::EyerAVReadePngList * pngList = new Eyer::EyerAVReadePngList("earl_000.png");
    pngList->read();
}

#endif