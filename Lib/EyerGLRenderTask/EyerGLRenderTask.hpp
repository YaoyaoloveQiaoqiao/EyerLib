#ifndef	EYER_LIB_GL_RENDER_TASK_H
#define	EYER_LIB_GL_RENDER_TASK_H

#include "EyerCore/EyerCore.hpp"
#include "EyerGL/EyerGL.hpp"
#include "EyerGLCustomComponent/EyerGLCustomComponent.hpp"

namespace Eyer
{
    class JuliaRenderTask : public EyerGLRenderTask
    {
    public:
        JuliaRenderTask();
        ~JuliaRenderTask();

        virtual int Render();
        virtual int Init();
        virtual int Destory();

    private:
        EyerGLJulia * julia = nullptr;
    };


    class YUVRenderTask : public EyerGLRenderTask
    {
    public:
        YUVRenderTask();
        ~YUVRenderTask();

        virtual int Render();
        virtual int Init();
        virtual int Destory();

        int SetY(unsigned char * y, int w, int h);
        int SetU(unsigned char * u, int w, int h);
        int SetV(unsigned char * v, int w, int h);
    private:
        EyerGLYUV2TextureComponent * yuv2text = nullptr;
        EyerGLTexture * yTex = nullptr;
        EyerGLTexture * uTex = nullptr;
        EyerGLTexture * vTex = nullptr;

        int yW = 0;
        int yH = 0;
        unsigned char * yData = nullptr;

        int uW = 0;
        int uH = 0;
        unsigned char * uData = nullptr;

        int vW = 0;
        int vH = 0;
        unsigned char * vData = nullptr;
    };
}


#endif