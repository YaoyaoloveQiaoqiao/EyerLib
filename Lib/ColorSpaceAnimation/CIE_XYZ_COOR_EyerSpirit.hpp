#ifndef EYERCOLORSPACE_CIE_XYZ_COOR_EYERSPIRIT_HPP
#define EYERCOLORSPACE_CIE_XYZ_COOR_EYERSPIRIT_HPP

#include "EyerVideoEditor/EyerVideoEditor.hpp"

namespace Eyer
{
    class CIE_XYZ_COOR_EyerSpirit : public EyerSpirit
    {
    public:
        virtual int RenderContent(EatrixF4x4 & vp, EyerKey & key);
        virtual int RenderInit();
        virtual int RenderDestory();
    };
}

#endif //EYERCOLORSPACE_CIE_XYZ_COOR_EYERSPIRIT_HPP
