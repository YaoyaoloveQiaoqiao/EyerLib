#ifndef EYERCOLORSPACE_CIE_RGB_COOR_EYERSPIRIT_HPP
#define EYERCOLORSPACE_CIE_RGB_COOR_EYERSPIRIT_HPP

#include "EyerVideoEditor/EyerVideoEditor.hpp"
#include "EyerGLCustomComponent/MVPCoor.hpp"

namespace Eyer
{
    class CIE_RGB_COOR_EyerSpirit  : public EyerSpirit
    {
    public:
        virtual int RenderContent(EatrixF4x4 & vp, EyerKey & key);
        virtual int RenderInit();
        virtual int RenderDestory();

        MVPCoor * coor = nullptr;
    };
}

#endif //EYERCOLORSPACE_CIE_RGB_COOR_EYERSPIRIT_HPP
