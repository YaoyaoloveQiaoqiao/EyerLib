#ifndef EYERCOLORSPACE_MVPNORMALIZEPLANESPIRIT_HPP
#define EYERCOLORSPACE_MVPNORMALIZEPLANESPIRIT_HPP

#include "EyerGLCustomComponent/MVPImagePlane.hpp"
#include "EyerGLCustomComponent/MVPCoorLine.hpp"
#include "EyerVideoEditor/EyerVideoEditor.hpp"
#include "EyerGLCustomComponent/MVPNormalizePlane.hpp"

namespace Eyer
{
    class MVPNormalizePlaneSpirit : public EyerSpirit
    {
    public:
        virtual int RenderInit();
        virtual int RenderDestory();
        virtual int RenderContent(EatrixF4x4 & vp, EyerKey & key);

        MVPNormalizePlane * normalizePlane = nullptr;
    };
}



#endif //EYERCOLORSPACE_MVPNORMALIZEPLANESPIRIT_HPP
