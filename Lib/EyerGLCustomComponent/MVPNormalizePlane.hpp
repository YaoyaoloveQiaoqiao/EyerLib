#ifndef EYERCOLORSPACE_MVPNORMALIZEPLANE_HPP
#define EYERCOLORSPACE_MVPNORMALIZEPLANE_HPP

#include "EyerGLCustomComponent.hpp"

namespace Eyer
{
    class MVPNormalizePlane : public EyerGLComponent {
    public:
        MVPNormalizePlane();
        ~MVPNormalizePlane();

        int SetMVP(EatrixF4x4 & mat);

        virtual int Draw();

    private:
        EyerGLDraw * draw = nullptr;
        EyerGLVAO * vao = nullptr;

        EatrixF4x4 mvp;
    };
}

#endif //EYERCOLORSPACE_MVPNORMALIZEPLANE_HPP
