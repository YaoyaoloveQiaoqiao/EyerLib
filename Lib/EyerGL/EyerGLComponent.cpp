#include "EyerGL.hpp"

namespace Eyer
{
    int EyerGLComponent::Viewport(int w, int h)
    {
        width = w;
        height = h;

        return 0;
    }

    EyerGLComponent::~EyerGLComponent()
    {

    }

    int EyerGLComponent::SetVP(EatrixF4x4 & _vpMat)
    {
        vpMat = _vpMat;
        return 0;
    }

    int EyerGLComponent::SetModel(EectorF3 & _p, EectorF4 & _r, EectorF3 & _s)
    {
        p = _p;
        r = _r;
        s = _s;

        EatrixF4x4 pos;
        pos.SetTrans(_p.x(), _p.y(), _p.z());

        EatrixF4x4 r;
        r.SetRotate(_r.x(), _r.y(), _r.z(), _r.w());

        EatrixF4x4 s;
        s.SetScale(_s.x(), _s.y(), _s.z());

        modelMat = pos *  r * s;

        return 0;
    }

    int EyerGLComponent::SetColor(EectorF4 & _color)
    {
        color = _color;
        return 0;
    }
}
