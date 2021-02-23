#ifndef EYERCOLORSPACE_MVPLINE_HPP
#define EYERCOLORSPACE_MVPLINE_HPP

#include "EyerGLCustomComponent.hpp"

namespace Eyer
{
    class MVPLine : public EyerGLComponent
    {
    public:
        MVPLine(Eyer::EectorF3 & a, Eyer::EectorF3 & b);
        ~MVPLine();

        virtual int Draw();

    private:
        EyerGLDraw * draw = nullptr;
        EyerGLVAO * vao = nullptr;
    };
}

#endif //EYERCOLORSPACE_MVPLINE_HPP
