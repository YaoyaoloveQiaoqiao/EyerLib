#ifndef EYERCOLORSPACE_MVPCOORLINE_HPP
#define EYERCOLORSPACE_MVPCOORLINE_HPP

#include "EyerGLCustomComponent.hpp"

namespace Eyer
{
    class MVPCoorLine : public EyerGLComponent
    {
    public:
        MVPCoorLine();
        ~MVPCoorLine();

        virtual int Draw();

        EyerGLDraw * draw = nullptr;
        EyerGLVAO * vao = nullptr;
    };
}

#endif //EYERCOLORSPACE_MVPCOORLINE_HPP
