#include "EyerVideoTweenAnimation.hpp"
namespace Eyer
{
    EyerVideoTweenAnimation::EyerVideoTweenAnimation()
    {

    }
    EyerVideoTweenAnimation::~EyerVideoTweenAnimation()
    {
        for(int i=0;i<animationKeyList.getLength();i++){
            EyerVideoAnimationKey * animationKey = nullptr;
            animationKeyList.find(i, animationKey);
            if(animationKey != nullptr){
                delete animationKey;
            }
        }
        animationKeyList.clear();
    }

    EyerVideoTweenAnimation::EyerVideoTweenAnimation(const EyerVideoTweenAnimation & animation)
    {
        *this = animation;
    }

    EyerVideoTweenAnimation & EyerVideoTweenAnimation::operator = (const EyerVideoTweenAnimation & animation)
    {
        if(this == &animation){
            return *this;
        }

        for(int i=0; i<animation.animationKeyList.getLength(); i++){
            EyerVideoAnimationKey * animationKey = nullptr;
            animation.animationKeyList.find(i, animationKey);
            if(animationKey != nullptr){
                EyerVideoAnimationKey * animationKeyNew = new EyerVideoAnimationKey(*animationKey);
                animationKeyList.insertBack(animationKeyNew);
            }
        }

        return *this;
    }

    int EyerVideoTweenAnimation::GetLinearValue(EyerVideoAnimationKey & outKey)
    {
        if (animationKeyList.getLength() == 0) {
            outKey.x = 0;
            outKey.y = 0;
            outKey.z = 0;
            return 0;
        }

        EyerLinkedEle<EyerVideoAnimationKey*>* currentEle = animationKeyList.head;
        for (int i = 0; i < animationKeyList.getLength() - 1; i++) {
            EyerLinkedEle<EyerVideoAnimationKey*>* temp = currentEle->next;
            while (temp != nullptr) {
                if (temp->data->t < currentEle->data->t) {
                    EyerVideoAnimationKey* data = currentEle->data;
                    currentEle->data = temp->data;
                    temp->data = data;
                }
                temp = temp->next;
            }
            if (currentEle->next != nullptr) {
                currentEle = currentEle->next;
            }
        }

        EyerVideoAnimationKey* firstdata = nullptr;
        EyerVideoAnimationKey* lastdata = nullptr;
        animationKeyList.find(0, firstdata);
        animationKeyList.find(animationKeyList.getLength() - 1, lastdata);

        if (outKey.t <= firstdata->t) {
            outKey.x = firstdata->x;
            outKey.y = firstdata->y;
            outKey.z = firstdata->z;
            return 0;
        }
        else if (outKey.t >= lastdata->t) {
            outKey.x = lastdata->x;
            outKey.y = lastdata->y;
            outKey.z = lastdata->z;
            return 0;
        }

        for (int i = 0; i < animationKeyList.getLength() - 1; i++) {
            animationKeyList.find(i, firstdata);
            animationKeyList.find(i + 1, lastdata);

            if (outKey.t >= firstdata->t && outKey.t <= lastdata->t) {
                double tPart = (outKey.t - firstdata->t) / (lastdata->t - firstdata->t);
                outKey.x = tPart * (lastdata->x - firstdata->x) + firstdata->x;
                outKey.y = tPart * (lastdata->y - firstdata->y) + firstdata->y;
                outKey.z = tPart * (lastdata->z - firstdata->z) + firstdata->z;
                return 0;
            }
        }

        return 0;
    }

    int EyerVideoTweenAnimation::AddKey(EyerVideoAnimationKey & key)
    {
        EyerVideoAnimationKey * innerKey = new EyerVideoAnimationKey(key.t, key.x, key.y, key.y);
        return animationKeyList.insertBack(innerKey);
    }

}