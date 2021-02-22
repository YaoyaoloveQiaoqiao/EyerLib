#include "MVPLineSpirit.hpp"

namespace Eyer
{
    MVPLineSpirit::MVPLineSpirit(Eyer::EectorF3 & _a, Eyer::EectorF3 & _b)
    {
        a = _a;
        b = _b;
    }
    int MVPLineSpirit::RenderInit()
    {
        mvpLine = new MVPLine(a, b);
        return 0;
    }

    int MVPLineSpirit::RenderDestory()
    {
        if(mvpLine != nullptr){
            delete mvpLine;
            mvpLine = nullptr;
        }
        return 0;
    }

    int MVPLineSpirit::RenderContent(EatrixF4x4 & vp, EyerKey & key)
    {
        mvpLine->SetVP(vp);
        mvpLine->SetModel(key.position, key.rotato, key.scale);
        mvpLine->SetColor(key.color);
        mvpLine->Draw();
        return 0;
    }
}