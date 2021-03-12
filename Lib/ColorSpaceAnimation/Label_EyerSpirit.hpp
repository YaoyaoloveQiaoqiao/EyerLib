#ifndef EYERCOLORSPACE_LABEL_EYERSPIRIT_HPP
#define EYERCOLORSPACE_LABEL_EYERSPIRIT_HPP

#include "EyerGLCustomComponent/MVPImagePlane.hpp"
#include "EyerVideoEditor/EyerVideoEditor.hpp"

namespace Eyer
{
    class Label_EyerSpirit : public EyerSpirit
    {
    public:
        Label_EyerSpirit(unsigned char * data, int len);

        virtual int RenderContent(EatrixF4x4 & vp, EyerKey & key);
        virtual int RenderInit();
        virtual int RenderDestory();

        EyerBuffer imageBuffer;

        MVPImagePlane * plane = nullptr;
    };
}

#endif //EYERCOLORSPACE_LABEL_EYERSPIRIT_HPP
