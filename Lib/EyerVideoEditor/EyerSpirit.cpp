#include "EyerSpirit.hpp"

namespace Eyer
{
    EyerSpirit::EyerSpirit()
    {

    }

    EyerSpirit::~EyerSpirit()
    {
        for(int i=0;i<keyList.size();i++){
            delete keyList[i];
        }
        keyList.clear();
    }

    EyerSpirit::EyerSpirit(const EyerSpirit & spirit)
    {
        *this = spirit;
    }

    EyerSpirit & EyerSpirit::operator = (const EyerSpirit & spirit)
    {
        for(int i=0;i<spirit.keyList.size();i++){
            EyerKey * k = new EyerKey();
            *k = *spirit.keyList[i];
            keyList.push_back(k);
        }
        return *this;
    }

    int EyerSpirit::AddKey(EyerKey & key)
    {
        EyerKey * k = new EyerKey();
        *k = key;

        keyList.push_back(k);

        return 0;
    }

    EectorF4 EyerSpirit::GetColor(int frameIndex)
    {
        EectorF4 color(1.0, 1.0, 1.0, 0.0);

        EyerKey * A = nullptr;
        EyerKey * B = nullptr;

        // 0, 40, 18000

        for(int i=0;i<keyList.size();i++){
            int frame = keyList[i]->frame;
            if(frame < frameIndex){
                if(A == nullptr){
                    A = keyList[i];
                }
                else{
                    if(A->frame < frame){
                        A = keyList[i];
                    }
                }
            }
            if(frame >= frameIndex){
                if(B == nullptr){
                    B = keyList[i];
                }
                else{
                    if(B->frame >= frame){
                        B = keyList[i];
                    }
                }
            }
        }

        if(A == nullptr || B == nullptr){
            return color;
        }

        Eyer::EnterPolation<float> C(A->color, B->color, A->frame, B->frame);

        color = C.Get(frameIndex);

        return color;
    }

    int EyerSpirit::Render(EatrixF4x4 & vp, int frameIndex)
    {
        EyerKey * A = nullptr;
        EyerKey * B = nullptr;

        // 0, 40, 18000

        for(int i=0;i<keyList.size();i++){
            int frame = keyList[i]->frame;
            if(frame < frameIndex){
                if(A == nullptr){
                    A = keyList[i];
                }
                else{
                    if(A->frame < frame){
                        A = keyList[i];
                    }
                }
            }
            if(frame >= frameIndex){
                if(B == nullptr){
                    B = keyList[i];
                }
                else{
                    if(B->frame >= frame){
                        B = keyList[i];
                    }
                }
            }
        }



        if(A == nullptr || B == nullptr){
            return 0;
        }

        /*
        EyerLog("Frame: %d\n", frameIndex);
        EyerLog("A: %d\n", A->frame);
        EyerLog("B: %d\n", B->frame);
        EyerLog("=========================\n");
         */

        if(!init){
            RenderInit();
            init = true;
        }

        Eyer::EnterPolation<float> P(A->position, B->position, A->frame, B->frame);
        Eyer::EnterPolation<float> R(A->rotato, B->rotato, A->frame, B->frame);
        Eyer::EnterPolation<float> S(A->scale, B->scale, A->frame, B->frame);
        Eyer::EnterPolation<float> C(A->color, B->color, A->frame, B->frame);

        Eyer::EnterPolation<float> Target(A->cameraTarget, B->cameraTarget, A->frame, B->frame);

        EyerKey key;
        key.position    = P.Get(frameIndex);
        key.rotato      = R.Get(frameIndex);
        key.scale       = S.Get(frameIndex);
        key.color       = C.Get(frameIndex);
        key.cameraTarget       = Target.Get(frameIndex);

        RenderContent(vp, key);

        return 0;
    }
}