#include "MVPCoorLineSpirit.hpp"

namespace Eyer
{
    int MVPCoorLineSpirit::RenderInit()
    {
        coorLine = new MVPCoorLine();
        return 0;
    }

    int MVPCoorLineSpirit::RenderDestory()
    {
        if(coorLine != nullptr){
            delete coorLine;
            coorLine = nullptr;
        }
        return 0;
    }

    int MVPCoorLineSpirit::RenderContent(EatrixF4x4 & vp, EyerKey & key)
    {
        coorLine->SetColor(key.color);
        coorLine->SetVP(vp);
        coorLine->SetModel(key.position, key.rotato, key.scale);
        coorLine->Draw();
        return 0;
    }
}