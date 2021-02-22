#ifndef EYERCOLORSPACE_EYERCAMERA_HPP
#define EYERCOLORSPACE_EYERCAMERA_HPP

#include "EyerSpirit.hpp"

namespace Eyer
{
    class EyerCamera : public EyerSpirit{
    public:
        virtual int RenderContent(EatrixF4x4 & vp, EyerKey & key);
        virtual int RenderInit();
        virtual int RenderDestory();

        int SetWH(int _w, int _h);

        EatrixF4x4 vp;
        int w = 0;
        int h = 0;
    };
}



#endif //EYERCOLORSPACE_EYERCAMERA_HPP
