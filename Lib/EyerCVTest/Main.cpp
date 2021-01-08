#include <gtest/gtest.h>
#include <stdio.h>

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/core/mat.hpp>

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

int main(int argc,char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}