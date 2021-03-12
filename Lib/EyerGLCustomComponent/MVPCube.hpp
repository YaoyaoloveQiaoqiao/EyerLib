#ifndef EYERCOLORSPACE_MVPCUBE_HPP
#define EYERCOLORSPACE_MVPCUBE_HPP

#include "EyerGLCustomComponent.hpp"

namespace Eyer
{
    class MVPCube : public EyerGLComponent{
    public:
        MVPCube();
        ~MVPCube();

        int SetMVP(EatrixF4x4 & mat);

        virtual int Draw();

    private:
        EyerGLDraw * draw = nullptr;
        EyerGLVAO * vao = nullptr;

        EatrixF4x4 mvp;
    };
}

#endif //EYERCOLORSPACE_MVPCUBE_HPP
