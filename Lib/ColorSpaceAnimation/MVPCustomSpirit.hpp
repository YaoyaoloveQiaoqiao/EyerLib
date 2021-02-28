#ifndef EYERLIB_MVPCUSTOMSPIRIT_HPP
#define EYERLIB_MVPCUSTOMSPIRIT_HPP

#include "EyerGLCustomComponent/MVPImagePlane.hpp"
#include "EyerGLCustomComponent/MVPCoorLine.hpp"
#include "EyerVideoEditor/EyerVideoEditor.hpp"
#include "EyerGLCustomComponent/MVPNormalizePlane.hpp"
#include "EyerGLCustomComponent/MVPLine.hpp"
#include "EyerGLCustomComponent/MVPCustomG.hpp"

namespace Eyer {
    class MVPCustomSpirit  : public EyerSpirit
    {

        ~MVPCustomSpirit();

        virtual int RenderInit();
        virtual int RenderDestory();
        virtual int RenderContent(EatrixF4x4 & vp, EyerKey & key);

        float * vertex = nullptr;
        int vertexLen = 0;

        float * coor = nullptr;
        int coorLen = 0;

        unsigned int * vertexIndex = nullptr;
        int vertexIndexLen = 0;

        MVPCustomG * mvpCustomG = nullptr;
    public:
        MVPCustomSpirit(float * vertex, int vertexLen, float * coor, int coorLen, unsigned int * vertexIndex, int vertexIndexLen);
    };
}

#endif //EYERLIB_MVPCUSTOMSPIRIT_HPP
