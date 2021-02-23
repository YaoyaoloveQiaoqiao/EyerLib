#ifndef EYERCOLORSPACE_MVPLINESPIRIT_HPP
#define EYERCOLORSPACE_MVPLINESPIRIT_HPP

#include "EyerGLCustomComponent/MVPImagePlane.hpp"
#include "EyerGLCustomComponent/MVPCoorLine.hpp"
#include "EyerVideoEditor/EyerVideoEditor.hpp"
#include "EyerGLCustomComponent/MVPNormalizePlane.hpp"
#include "EyerGLCustomComponent/MVPLine.hpp"

namespace Eyer
{
    class MVPLineSpirit : public EyerSpirit
    {
    public:
        MVPLineSpirit(Eyer::EectorF3 & a, Eyer::EectorF3 & b);

        virtual int RenderInit();
        virtual int RenderDestory();
        virtual int RenderContent(EatrixF4x4 & vp, EyerKey & key);

        MVPLine * mvpLine = nullptr;

        Eyer::EectorF3 a;
        Eyer::EectorF3 b;
    };
}

#endif //EYERCOLORSPACE_MVPLINESPIRIT_HPP
