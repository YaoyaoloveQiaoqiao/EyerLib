#ifndef EYERCOLORSPACE_MVPCOOR_HPP
#define EYERCOLORSPACE_MVPCOOR_HPP

#include "EyerGLCustomComponent.hpp"

namespace Eyer
{
    class MVPCoor : public EyerGLComponent
    {
    public:
        MVPCoor();
        ~MVPCoor();

        int SetMVP(EatrixF4x4 & mat);
        int SetScale(EectorF3 & size);

        virtual int Draw();

        int SetColor(EectorF4 & color);

    private:
        EyerGLDraw * drawX = nullptr;
        EyerGLVAO * vaoX = nullptr;

        EyerGLDraw * drawY = nullptr;
        EyerGLVAO * vaoY = nullptr;

        EyerGLDraw * drawZ = nullptr;
        EyerGLVAO * vaoZ = nullptr;

        EatrixF4x4 mvp;

        EatrixF4x4 mScale;

        EectorF4 color;
    };
}

#endif //EYERCOLORSPACE_MVPCOOR_HPP
