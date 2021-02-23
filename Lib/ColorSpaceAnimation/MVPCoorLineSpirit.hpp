#ifndef EYERCOLORSPACE_MVPCOORLINESPIRIT_HPP
#define EYERCOLORSPACE_MVPCOORLINESPIRIT_HPP

#include "EyerGLCustomComponent/MVPImagePlane.hpp"
#include "EyerGLCustomComponent/MVPCoorLine.hpp"
#include "EyerVideoEditor/EyerVideoEditor.hpp"

namespace Eyer
{
    class MVPCoorLineSpirit : public EyerSpirit
    {
    public:
        virtual int RenderInit();
        virtual int RenderDestory();
        virtual int RenderContent(EatrixF4x4 & vp, EyerKey & key);


        MVPCoorLine * coorLine = nullptr;
    };
}

#endif //EYERCOLORSPACE_MVPCOORLINESPIRIT_HPP
