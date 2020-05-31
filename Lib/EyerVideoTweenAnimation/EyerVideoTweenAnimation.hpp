// CMakeProject1.h: 标准系统包含文件的包含文件

#pragma once

#include <iostream>
#include "EyerCore/EyerCore.hpp"

namespace Eyer
{
    class EyerVideoAnimationKey
    {
    public:
        double t = 0.0;
        float x = 0.0f;
        float y = 0.0f;
        float z = 0.0f;
    public:
        bool operator < (const EyerVideoAnimationKey& key2);

        EyerVideoAnimationKey();
        EyerVideoAnimationKey(double t, float x, float y, float z);
        EyerVideoAnimationKey(const EyerVideoAnimationKey& tk);

        EyerVideoAnimationKey& operator = (const EyerVideoAnimationKey& tk);
    };

    class EyerVideoTweenAnimation
    {
    public:
        EyerVideoTweenAnimation();
        ~EyerVideoTweenAnimation();
        EyerVideoTweenAnimation(const EyerVideoTweenAnimation & animation);
        EyerVideoTweenAnimation & operator = (const EyerVideoTweenAnimation & animation);

        int GetLinearValue(double t, EyerVideoAnimationKey & outKey);
        int AddKey(EyerVideoAnimationKey & key);
    private:
        EyerLinkedList<EyerVideoAnimationKey*> animationKeyList;
    };

}