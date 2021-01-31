#include <gtest/gtest.h>

#include "EyerCore/EyerCore.hpp"
#include "EyerSignal/EyerSignal.hpp"

#include <libyuv.h>

TEST(EyerSignal, EyerSignalTest)
{

}

// #include "DCT.hpp"

TEST(EyerSignal, DCT2D)
{
    int w = 20;
    int h = 20;

    Eyer::Eatrix<unsigned char> mat(w, h);

    for(int y=0;y<h;y++){
        for(int x=0;x<w;x++){
            mat.Set(x, y, 127);
        }
    }

    for(int y=0;y<h;y++){
        for(int x=0;x<w;x++){
            unsigned char xy = mat.Get(x, y);
            printf(" %4d ", xy);
        }
        printf("\n");
    }


    printf("==========================\n");

    Eyer::Eatrix<unsigned char> outmat(w, h);

    Eyer::DCT<unsigned char> dct;
    dct.DCT2D(mat, outmat);


    for(int y=0;y<h;y++){
        for(int x=0;x<w;x++){
            unsigned char xy = outmat.Get(x, y);
            printf(" %4d ", xy);
        }
        printf("\n");
    }

}

int main(int argc,char **argv){
    testing::InitGoogleTest(&argc, argv);
    int ret = RUN_ALL_TESTS();
    return ret;
}
