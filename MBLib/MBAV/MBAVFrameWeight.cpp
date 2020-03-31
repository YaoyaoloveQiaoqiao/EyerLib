//
// Created by redknot on 2020/3/22.
//

#include "MBAV.hpp"

namespace MB
{
    MBAVFrameWeight::MBAVFrameWeight()
    {

    }

    MBAVFrameWeight::MBAVFrameWeight(MBAVFrame & f, float w)
    {
        if(frame != nullptr){
            delete frame;
            frame = nullptr;
        }

        frame = new MBAVFrame(f);
        weight = w;
    }

    MBAVFrameWeight::MBAVFrameWeight(MBAVFrameWeight & frameWeight)
    {
        *this = frameWeight;
    }

    MBAVFrameWeight::~MBAVFrameWeight()
    {
        if(frame != nullptr){
            delete frame;
            frame = nullptr;
        }
    }

    MBAVFrameWeight & MBAVFrameWeight::operator = (MBAVFrameWeight & frameWeight)
    {
        if(frame != nullptr){
            delete frame;
            frame = nullptr;
        }

        frame = new MBAVFrame(*frameWeight.frame);
        weight = frameWeight.weight;

        return *this;
    }
}