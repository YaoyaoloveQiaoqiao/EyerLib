#include "CIE_RGB_COOR_EyerSpirit.hpp"

#include "EyerImage/EyerImage.hpp"
#include "image_r.hpp"

namespace Eyer
{
    int CIE_RGB_COOR_EyerSpirit::RenderInit()
    {
        coor = new MVPCoor();
        return 0;
    }

    int CIE_RGB_COOR_EyerSpirit::RenderDestory()
    {
        if(coor != nullptr){
            delete coor;
            coor = nullptr;
        }
        return 0;
    }

    int CIE_RGB_COOR_EyerSpirit::RenderContent(EatrixF4x4 & vp, EyerKey & key)
    {
        // EyerLog("CIE_RGB_COOR_EyerSpirit RenderContent\n");

        // vp.PrintInfo();
        coor->SetColor(key.color);
        coor->SetMVP(vp);
        coor->SetScale(key.scale);

        coor->Draw();
        return 0;
    }
}