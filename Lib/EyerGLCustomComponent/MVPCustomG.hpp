#ifndef EYERLIB_MVPCUSTOMG_HPP
#define EYERLIB_MVPCUSTOMG_HPP

#include "EyerGLCustomComponent.hpp"

namespace Eyer
{
    class MVPCustomG : public EyerGLComponent
    {
    public:
        MVPCustomG(float * vertex, int vertexLen, float * coor, int coorLen, unsigned int * vertexIndex, int vertexIndexLen);
        ~MVPCustomG();

        int SetMVP(EatrixF4x4 & mat);

        virtual int Draw();

    private:
        EyerGLDraw * draw = nullptr;
        EyerGLVAO * vao = nullptr;

        EatrixF4x4 mvp;
    };
}

#endif //EYERLIB_MVPCUSTOMG_HPP
