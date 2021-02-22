#include "SphereSpirit.hpp"

namespace Eyer
{
    int SphereSpirit::RenderContent(EatrixF4x4 & vp, EyerKey & key)
    {
        mvpSphere->SetVP(vp);
        mvpSphere->SetColor(key.color.x(), key.color.y(), key.color.z(), key.color.w());
        mvpSphere->SetModel(key.position, key.rotato, key.scale);
        mvpSphere->Draw();
        return 0;
    }

    int SphereSpirit::RenderInit()
    {
        mvpSphere = new MVPSphere();
        return 0;
    }

    int SphereSpirit::RenderDestory()
    {
        if(mvpSphere != nullptr){
            delete mvpSphere;
            mvpSphere = nullptr;
        }
        return 0;
    }
}