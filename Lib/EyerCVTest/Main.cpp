#include <gtest/gtest.h>
#include <stdio.h>

#include "EyerCore/EyerCore.hpp"
#include "EyerSignal/EyerSignal.hpp"

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/core/mat.hpp>

/*
TEST(CVTest, DCT){
    cv::Mat src = cv::imread("./image_d.jpg", 0);
    if(src.empty()) {
        std::cout << "the image is not exist" << std::endl;
        return;
    }
    resize(src, src, cv::Size(512, 512));
    src.convertTo(src, CV_32F, 1.0/255);
    cv::Mat srcDCT;
    dct(src, srcDCT);

    imshow("src", src);
    imshow("dct", srcDCT);
    cv::waitKey();
    return;
}
*/

TEST(CVTest, DCT1D){

    int len = 128;
    float input[len];
    for(int i = 0;i<len;i++){
        input[i] = sin(i * 1.0f * 5.0f) * 0.5f + 0.5f;
        // EyerLog("%f\n", input[i]);
    }

    cv::Mat src(1 ,len,  CV_32FC1, input);

    cv::Mat srcDCT;
    dct(src, srcDCT);

    cv::normalize(srcDCT, srcDCT, 1,0, cv::NORM_MINMAX);

    for(int i=0;i<srcDCT.cols;i++){
        // EyerLog("%f\n", srcDCT.col(0).at<float>(i));
    }

    // imshow("src", src);
    // imshow("dct", srcDCT);
    // cv::waitKey();

    return;
}

TEST(CVTest, DCT2D){
    cv::Mat src = cv::imread("./image_d.jpg", 0);
    resize(src, src, cv::Size(64, 64));

    Eyer::Eatrix<unsigned char> mat(src.rows, src.cols);

    for(int y=0;y<src.rows;y++) {
        uchar * data = src.ptr<uchar>(y);
        for(int x=0;x<src.cols;x++) {
            printf(" %3d ", data[x]);
            mat.Set(y, x, data[x]);
        }
        printf("\n");
    }

    printf("\n");
    printf("\n");

    for(int y=0;y<mat.row;y++){
        for(int x=0;x<mat.col;x++){
            unsigned char xy = mat.Get(y, x);
            printf(" %3d ", xy);
        }
        printf("\n");
    }


    printf("===========================\n\n\n\n\n\n\n");

    src.convertTo(src, CV_32F, 1.0/255);
    cv::Mat srcDCT;
    dct(src, srcDCT);
    srcDCT.convertTo(srcDCT, CV_8UC1, 255);


    Eyer::Eatrix<unsigned char> outmat(src.rows, src.cols);
    Eyer::DCT<unsigned char> dct;
    dct.DCT2D(mat, outmat);


    for(int y=0;y<srcDCT.rows;y++) {
        uchar * data = srcDCT.ptr<uchar>(y);
        for(int x=0;x<srcDCT.cols;x++) {
            printf(" %3d ", data[x]);
        }
        printf("\n");
    }


    printf("\n\n\n");

    for(int y=0;y<outmat.row;y++){
        for(int x=0;x<outmat.col;x++){
            unsigned char xy = outmat.Get(y, x);
            printf(" %3d ", xy);
        }
        printf("\n");
    }

    imshow("src", src);
    imshow("dct", srcDCT);

    cv::waitKey();
}

int main(int argc,char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}