#include "EyerCrop.hpp"
#include <algorithm>

namespace Eyer
{
    EyerAVCropUtil::EyerAVCropUtil()
    {

    }

    EyerAVCropUtil::~EyerAVCropUtil()
    {

    }

    int EyerAVCropUtil::GetCrop(int viewW, int viewH, int imageW, int imageH, int & targetW, int & targetH, EyerAVCropType cropType)
    {
        if(cropType == EyerAVCropType::FIT_CENTER){
            float viewFit = viewW * 1.0 / viewH;
            float imageFit = imageW * 1.0 / imageH;

            if(viewFit > imageFit){
                // 对高进行限定
                targetH = viewH;
                targetW = imageW * 1.0 / imageH * targetH;
            }
            else{
                targetW = viewW;
                targetH = imageH * 1.0 / imageW * targetW;
            }
        }

        if(cropType == EyerAVCropType::FIT_XY){
            targetW = viewW;
            targetH = viewH;
        }
        return 0;
    }

    int GetCrop(int viewW, int viewH, int imageW, int imageH, int& targetW, int& targetH, int& transX, int& transY, EyerAVCropType cropType)
    {
        // https://www.jianshu.com/p/32e335d5b842
        float imageAspect = imageW * 1.0 / imageH;
        targetW = viewW; targetH = viewH;

        switch (cropType)
        {
        case Eyer::FIT_CENTER:
            // 图片会被等比缩放到能够填充控件大小，并居中展示
            if (imageAspect > 1.0)
                targetH = 1.0 / imageAspect * targetW;
            else
                targetW = imageAspect * targetH;
            break;
        case Eyer::FIT_XY:
            // 图片缩放到控件大小，完全填充控件大小展示。注意，此模式不是等比缩放。
            break;
        case Eyer::FIT_END:
            // 同FIT_START 上半部分或者左半部分留白
            if (imageAspect > 1.0)
            {
                targetH = 1.0 / imageAspect * targetW;
                transY = -(viewH - targetH);
            }
            else
            {
                targetW = imageAspect * targetH;
                transX = viewW - targetW;
            }
            break;
        case Eyer::FIT_START:
            // 图片等比缩放到控件大小，并放置在控件的上边或左边展示。
            // 如图所示，此模式下会在ImageView的下半部分留白，如果图片高度大于宽，那么就会在ImageView的右半部份留白。
            if (imageAspect > 1.0)
            {
                targetH = 1.0 / imageAspect * targetW;
                transY = viewH - targetH;
            }
            else
            {
                targetW = imageAspect * targetH;
                transX = -(viewW - targetW);
            }
            break;
        case Eyer::CENTER:
            // 不使用缩放，ImageView会展示图片的中心部分，即图片的中心点和ImageView的中心点重叠，如图。
            // 如果图片的大小小于控件的宽高，那么图片会被居中显示。
            targetW = imageW * 1.0;
            targetH = imageH * 1.0;
            break;
        case Eyer::CENTER_CROP:
            // 图片会被等比缩放直到完全填充整个ImageView，并居中显示。该模式也是最常用的模式了
            if (imageAspect > 1.0)
                targetW = imageAspect * targetH;
            else
                targetH = 1.0 / imageAspect * targetW;
            break;
        case Eyer::CENTER_INSIDE:
            targetW = std::min(viewW, imageW) * 1.0;
            targetH = std::min(viewH, imageH) * 1.0;
            if (imageAspect > 1.0)
                targetH = 1.0 / imageAspect * targetW;
            else
                targetW = imageAspect * targetH;
            break;
        default:
            break;
        }

        return 0;
    }
}