#ifndef EYERCOLORSPACE_MVPIMAGEPLANE_HPP
#define EYERCOLORSPACE_MVPIMAGEPLANE_HPP

#include "EyerGLCustomComponent.hpp"

namespace Eyer
{
    class MVPImagePlane  : public EyerGLComponent
    {
    public:
        MVPImagePlane(unsigned char * pngData, int size);
        ~MVPImagePlane();
        virtual int Draw();

        EyerGLDraw * draw = nullptr;
        EyerGLVAO * vao = nullptr;

        EyerGLTexture * texture = nullptr;
    };
}

#endif //EYERCOLORSPACE_MVPIMAGEPLANE_HPP
