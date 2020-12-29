//
// Created by chuchun on 2020/12/30.
//

#include <EyerCore/EyerLog.hpp>
#include "EyerPureColorCheck.h"
#include "EyerPureColorBlock.hpp"

Eyer::EyerPureColorCheck::EyerPureColorCheck()
{

}

Eyer::EyerPureColorCheck::~EyerPureColorCheck()
{
    for(int i=0;i<blockList.size();i++){
        delete blockList[i];
    }
    blockList.clear();
}

int Eyer::EyerPureColorCheck::GetChannelRes(EyerPureColorRes & res, uint8_t * channelData, int width, int height)
{
    // block
    int w_num = width / 16;
    if(width % 16 > 0){
        w_num += 1;
    }

    int h_num = height / 16;
    if(height % 16 > 0){
        h_num += 1;
    }

    for(int y=0; y<h_num; y++){
        for(int x=0; x<w_num; x++){
            EyerLog("x: %d, y: %d\n", x, y);
            int block_start_x = x * 16;
            int block_start_y = y * 16;

            int pixel_index = block_start_y * width + block_start_x;

            int block_width = 16;
            if(width % 16 > 0){
                if(x >= w_num - 1){
                    block_width = width % 16;
                }
            }
            EyerLog("block_width: %d\n", block_width);

            int block_height = 16;
            if(height % 16 > 0){
                if(y >= h_num - 1){
                    block_height = height % 16;
                }
            }
            EyerLog("block_height: %d\n", block_height);

            EyerPureColorBlock * block = new EyerPureColorBlock(block_width, block_height);

            for(int pixel_y=0; pixel_y < block_height; pixel_y++){
                uint8_t * data = channelData + pixel_index + width * pixel_y;
                block->CopyData(pixel_y, data);
            }

            blockList.push_back(block);

            EyerLog("pixel_index: %d\n", pixel_index);
        }
    }

    double blockSum = 0.0;
    for(int i=0;i<blockList.size();i++){
        EyerPureColorBlock * block = blockList[i];
        //EyerLog("block->GetAverage: %f\n", block->GetAverage());
        blockSum += block->GetAverage();
    }
    double blockAverage = blockSum / blockList.size();
    double differSquare = 0.0;
    for(int i=0;i<blockList.size();i++) {
        EyerPureColorBlock * block = blockList[i];
        differSquare += pow ((block->GetAverage() - blockAverage), 2);
    }

    res.standardDeviation = sqrt(differSquare);
    return 0;
}