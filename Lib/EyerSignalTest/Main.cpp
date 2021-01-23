#include <gtest/gtest.h>

#include "EyerCore/EyerCore.hpp"
#include "EyerSignal/EyerSignal.hpp"

#include <libyuv.h>

TEST(EyerSignal, EyerSignalTest)
{

}

TEST(EyerSignal, GenPic)
{
    // 8bit R G B W
    int w = 1920;
    int h = 1080;

    FILE * f = fopen("yuv420_8bit_1920_1080_100frames_rgbw.yuv", "wb");

    for(int frame = 0; frame < 100; frame++){
        unsigned char * rgbData = (unsigned char *)malloc(w * h * 3);

        for(int y=0;y<h;y++){
            int colorSliceWidth = w / 4;

            unsigned char r = 0;
            unsigned char g = 0;
            unsigned char b = 0;

            // 1 0 0
            for(int x=colorSliceWidth * 0;x<colorSliceWidth * 1;x++){
                r = 255; g = 0; b = 0;
                rgbData[y * w * 3 + x * 3 + 0] = r;
                rgbData[y * w * 3 + x * 3 + 1] = g;
                rgbData[y * w * 3 + x * 3 + 2] = b;
            }

            // 0 1 0
            for(int x=colorSliceWidth * 1;x<colorSliceWidth * 2;x++){
                r = 0; g = 255; b = 0;
                rgbData[y * w * 3 + x * 3 + 0] = r;
                rgbData[y * w * 3 + x * 3 + 1] = g;
                rgbData[y * w * 3 + x * 3 + 2] = b;
            }

            // 0 0 1
            for(int x=colorSliceWidth * 2;x<colorSliceWidth * 3;x++){
                r = 0; g = 0; b = 255;
                rgbData[y * w * 3 + x * 3 + 0] = r;
                rgbData[y * w * 3 + x * 3 + 1] = g;
                rgbData[y * w * 3 + x * 3 + 2] = b;
            }

            // 1 1 1
            for(int x=colorSliceWidth * 3;x<colorSliceWidth * 4;x++){
                r = 255; g = 255; b = 255;
                rgbData[y * w * 3 + x * 3 + 0] = r;
                rgbData[y * w * 3 + x * 3 + 1] = g;
                rgbData[y * w * 3 + x * 3 + 2] = b;
            }
        }

        // memset(rgbData, 127, w * h * 3);

        unsigned char * y = (unsigned char *)malloc(w * h);
        unsigned char * u = (unsigned char *)malloc(w / 2 * h / 2);
        unsigned char * v = (unsigned char *)malloc(w / 2 * h / 2);

        libyuv::RGB24ToI420(
                rgbData,
                w * 3,
                y,
                w,
                u,
                w / 2,
                v,
                w / 2,
                w,
                h
        );

        fwrite(y, w * h, 1, f);
        fwrite(u, w / 2 * h / 2, 1, f);
        fwrite(v, w / 2 * h / 2, 1, f);

        free(y);
        free(u);
        free(v);

        free(rgbData);
    }

    fclose(f);
}

TEST(EyerSignal, DCT)
{

    int len = 128;
    float input[len];
    for(int i = 0;i<len;i++){
        input[i] = sin(i * 1.0f) * 0.5f + 0.5f;        // EyerLog("%f\n", input[i]);
    }

    Eyer::DCT<float> dct;

    float output[len];
    dct.DCT1D(input, len, output, len);

    for(int i = 0;i<len;i++){
        EyerLog("%f\n", output[i]);
    }
}

int main(int argc,char **argv){
    testing::InitGoogleTest(&argc, argv);
    int ret = RUN_ALL_TESTS();
    return ret;
}
