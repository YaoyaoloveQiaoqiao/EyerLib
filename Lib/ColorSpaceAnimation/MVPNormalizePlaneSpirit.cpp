#include "MVPNormalizePlaneSpirit.hpp"

namespace Eyer
{
    int MVPNormalizePlaneSpirit::RenderInit()
    {
        normalizePlane = new MVPNormalizePlane();
        return 0;
    }

    int MVPNormalizePlaneSpirit::RenderDestory()
    {
        if(normalizePlane != nullptr){
            delete normalizePlane;
            normalizePlane = nullptr;
        }
        return 0;
    }

    int MVPNormalizePlaneSpirit::RenderContent(EatrixF4x4 & vp, EyerKey & key)
    {
        normalizePlane->SetVP(vp);
        normalizePlane->SetModel(key.position, key.rotato, key.scale);
        normalizePlane->SetColor(key.color);
        normalizePlane->Draw();
        return 0;
    }
}