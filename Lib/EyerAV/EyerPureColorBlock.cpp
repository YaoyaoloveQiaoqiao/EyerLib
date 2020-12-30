//
// Created by chuchun on 2020/12/30.
//

#include "EyerPureColorBlock.hpp"
#include <stdlib.h>
#include <string.h>
#include <EyerCore/EyerLog.hpp>

namespace Eyer {
    EyerPureColorBlock::EyerPureColorBlock(int _width, int _height)
    {
        width = _width;
        height = _height;

        blockContent = (unsigned char *)malloc(width * height);
    }

    EyerPureColorBlock::~EyerPureColorBlock()
    {
        if(blockContent != nullptr){
            free(blockContent);
            blockContent = nullptr;
        }
    }

    int EyerPureColorBlock::CopyData(int line, uint8_t * data)
    {
        memcpy(blockContent + line * width, data, width);
        return 0;
    }

    double EyerPureColorBlock::GetAverage()
    {
        double average = 0.0;
        double sum = 0.0;
        for(int i=0;i<width*height;i++){
            sum += (double)blockContent[i];
        }

        average = sum / (double)(width*height);
        return average;
    }

}