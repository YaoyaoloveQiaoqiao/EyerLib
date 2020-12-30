#ifndef EYERLIB_EYERAVPURECOLORCHECK_HPP
#define EYERLIB_EYERAVPURECOLORCHECK_HPP

#include "EyerAV/EyerAV.hpp"
#include <gtest/gtest.h>
#include "EyerImg/EyerImg.hpp"

TEST(EyerAV, PureColor){
    // Read Image
    Eyer::EyerImg imgReader((char *)"./3.png");
    int res = imgReader.LoadImg();

    int w = imgReader.GetImgW();
    int h = imgReader.GetImgH();
    int channel = imgReader.GetImgChannel();

    EyerLog("width:%d, height:%d, channel: %d\n", w, h, channel);

    unsigned char * data = (unsigned char *)malloc(w * h * channel);

    imgReader.GetImgData(data);

    //
    unsigned char * r = (unsigned char *)malloc(w * h);
    unsigned char * g = (unsigned char *)malloc(w * h);
    unsigned char * b = (unsigned char *)malloc(w * h);
    unsigned char * a = (unsigned char *)malloc(w * h);

    for(int i=0;i<w*h;i++){
        int rgbIndex = i * channel;
        r[i] = data[rgbIndex + 0];
        g[i] = data[rgbIndex + 1];
        b[i] = data[rgbIndex + 2];
        a[i] = data[rgbIndex + 3];
    }


    Eyer::EyerPureColorCheck pureColorCheck;

    Eyer::EyerPureColorRes colourRes;
    pureColorCheck.GetChannelRes(colourRes, r, w, h);

    EyerLog("res: %f\n", colourRes.standardDeviation);


    free(r);
    free(g);
    free(b);
    free(a);
    free(data);
}

#endif //EYERLIB_EYERAVPURECOLORCHECK_HPP
