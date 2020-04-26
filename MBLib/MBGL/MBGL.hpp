#ifndef	EYER_LIB_GL_AV_H
#define	EYER_LIB_GL_AV_H

#include "MBCore/MBCore.hpp"
#include <vector>

#ifdef QT_EYER_PLAYER
#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#else
#endif

namespace MB
{
    class MBGLWindow;
    class MBGLWindowPrivate;
    class MBGLCMD;

    class MBGLComponent;
    class MBGLTextDraw;
    class MBGLSingleTextureDraw;
    class MBGLFrameDraw;

    class MBGLShader;
    class MBGLProgram;
    class MBGLVAO;
    class MBGLTexture;

    class _MBGLContext
    {
    };

#ifdef QT_EYER_PLAYER
#define MBGLContext QOpenGLFunctions_3_3_Core
#else
#define MBGLContext _MBGLContext
#endif

    class MBGLCMD
    {
    public:
        virtual ~MBGLCMD()
        {

        }
    };

    enum MBGLShaderType
    {
        VERTEX_SHADER,
        FRAGMENT_SHADER
    };

    class MBGLShader : public MBGLCMD
    {
    private:
        MBGLShaderType type = MBGLShaderType::VERTEX_SHADER;
        MBString src;
        unsigned int shaderId = 0;

        MBGLContext * ctx = nullptr;
    public:
        MBGLShader(MBGLShaderType type, MBString src, MBGLContext * _ctx = nullptr);
        ~MBGLShader();

        int Compile();

        unsigned int GL_GetShaderId();
    };

    class MBGLProgram : public MBGLCMD
    {
    private:
        MBString vertexShaderSrc;
        MBString fragmentShaderSrc;

        unsigned int programId = 0;

        MBGLContext * ctx = nullptr;
    public:
        MBGLProgram(MBString vertexShaderSrc, MBString fragmentShaderSrc, MBGLContext * _ctx = nullptr);
        ~MBGLProgram();
        int LinkProgram();
        int UseProgram();

        int PutUniform1i(MBString key, int value);
        int PutMatrix4fv(MBString key, MBMat4x4 & mat);
        int PutUniform1f(MBString key, float value);
    };

    class MBGLVAO : public MBGLCMD
    {
    private:
        unsigned int VAOId = 0;
        unsigned int EBOId = 0;
        std::vector<unsigned int> vboList;

        int DrawTime = 0;

        MBGLContext * ctx = nullptr;
    public:
        MBGLVAO(MBGLContext * ctx = nullptr);
        ~MBGLVAO();

        int SetEBO(unsigned int * EBOdata, int bufferSize);
        int AddVBO(float * VBOdata, int bufferSize, int layout, int size = 3, unsigned int stride = 0);

        int DrawVAO();
    };

    class MBGLDrawTexture
    {
    public:
        MBString uniformName;
        MBGLTexture * texture = nullptr;
    };

    class MBGLDraw : public MBGLCMD
    {
    private:
        MBString vertexShaderSrc;
        MBString fragmentShaderSrc;

        MBGLProgram * program = nullptr;
        MBGLVAO * vao = nullptr;

        MBGLContext * ctx = nullptr;
    public:
        MBGLDraw(MBString vertexShaderSrc, MBString fragmentShaderSrc, MBGLContext * ctx = nullptr);
        ~MBGLDraw();

        int Init();

        int SetVAO(MBGLVAO * vao);
        int PutTexture(MBString uniform, MBGLTexture * texture, int textureIndex = 0);
        int PutMatrix4fv(MBString uniform, MBMat4x4 & mat);
        int PutUniform1f(MBString uniform, float val);
        int PutUniform1i(MBString uniform, int val);

        int Draw();
    };

    class MBGLTexture : public MBGLCMD
    {
    private:
        unsigned int textureId = 0;
        MBGLContext * ctx = nullptr;
    public:
        MBGLTexture(MBGLContext * ctx = nullptr);
        ~MBGLTexture();

        unsigned int GL_GetTextureId();

        int SetDataRedChannel(unsigned char * data,int width,int height);
        int SetDataRGBAChannel(unsigned char * data,int width,int height);
    };

    class MBGLFrameBuffer : public MBGLCMD
    {
    private:
        MBLinkedList<MBGLDraw *> drawList;
        MBLinkedList<MBGLComponent *> componentList;

        unsigned int fbo = 0;

        int width = 0;
        int height = 0;

        MBGLTexture * texture = nullptr;
        MBGLContext * ctx = nullptr;
    public:
        MBGLFrameBuffer(int w, int h, MBGLTexture * texture = nullptr, MBGLContext * ctx = nullptr);
        ~MBGLFrameBuffer();

        int AddDraw(MBGLDraw * draw);
        int AddComponent(MBGLComponent * component);
        int ClearAllComponent();

        int Clear();

        int Draw();

        int ReadPixel(int x, int y, int width, int height, unsigned char * data);
    };


    class MBGLComponent
    {
    public:
        int width = 0;
        int height = 0;
    public:
        virtual ~MBGLComponent();

        virtual int Draw() = 0;

        int Viewport(int w, int h);
    };
}

#endif
