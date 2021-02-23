#ifndef EYERCOLORSPACE_SPHERESPIRIT_HPP
#define EYERCOLORSPACE_SPHERESPIRIT_HPP

#include "EyerGLCustomComponent/MVPImagePlane.hpp"
#include "EyerVideoEditor/EyerVideoEditor.hpp"
#include "EyerGLCustomComponent/MVPSphere.hpp"

namespace Eyer
{
    class SphereSpirit : public EyerSpirit{
    public:
        virtual int RenderContent(EatrixF4x4 & vp, EyerKey & key);
        virtual int RenderInit();
        virtual int RenderDestory();

        MVPSphere * mvpSphere = nullptr;
    };
}

#endif //EYERCOLORSPACE_SPHERESPIRIT_HPP
