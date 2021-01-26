#include <gtest/gtest.h>
#include <stdio.h>

#include "EyerCore/EyerCore.hpp"

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
        EyerLog("%f\n", srcDCT.col(0).at<float>(i));
    }

    // imshow("src", src);
    // imshow("dct", srcDCT);
    // cv::waitKey();

    return;
}

TEST(CVTest, DCT2D4x4){
    float input2[4][4] = {
            {4, 4, 4, 4},
            {4, 4, 4, 4},
            {4, 4, 4, 4},
            {4, 4, 4, 4},
    };

    float input[4][4] = {
            {-35, -36, -38, -39},
            {-34, -34, -34, -34},
            {-32, -33, -35, -36},
            {-27, -29, -33, -35},
    };

    cv::Mat src(4 ,4,  CV_32FC1, input);
    for(int i=0;i<src.rows;i++){
        for(int j=0;j<src.cols;j++){
            printf( " %.3f ", src.col(j).at<float>(i));
        }
        printf("\n");
    }


    cv::Mat srcDCT;
    dct(src, srcDCT);

    for(int i=0;i<srcDCT.rows;i++){
        for(int j=0;j<srcDCT.cols;j++){
            printf( " %.3f ", srcDCT.col(j).at<float>(i));
        }
        printf("\n");
    }
}

int main(int argc,char **argv){
    eyer_log_path("./aaa.log");

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}