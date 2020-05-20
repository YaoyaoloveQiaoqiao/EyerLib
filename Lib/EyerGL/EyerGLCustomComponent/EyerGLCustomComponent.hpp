#ifndef	EYER_LIB_GL_CUSTOM_COMPONENT_H
#define	EYER_LIB_GL_CUSTOM_COMPONENT_H

#include "EyerGL/EyerGL.hpp"
#include "EyerType/EyerType.hpp"
#include "EyerCore/EyerCore.hpp"

namespace Eyer
{
    class EyerGLCacheTexture;

    class EyerGLTextDraw : public EyerGLComponent
    {
    public:
        EyerGLTextDraw(EyerString _typeFilePath);
        ~EyerGLTextDraw();

        int GetTextWidth();

        int SetText(EyerString text);

        int SetSize(float size);
        int SetPos(float x, float y);

        int SetColor(float r, float g, float b);

        virtual int Draw();

    private:
        EyerString typeFilePath;

        EyerString text;
        EyerGLDraw * pointDraw = nullptr;
        EyerGLVAO * pointVao = nullptr;
        EyerType * typeCreator = nullptr;
        EyerGLDraw * textDraw = nullptr;
        EyerGLVAO * vao = nullptr;

        std::map<wchar_t, EyerGLCacheTexture *> textureCache;

        float positionX = 0.0f;
        float positionY = 0.0f;

        int size = 100;

        float r = 0.0f;
        float g = 0.0f;
        float b = 0.0f;
    };   


    class EyerGLMVPTextureDraw : public EyerGLComponent
    {
    public:
        EyerGLMVPTextureDraw();
        ~EyerGLMVPTextureDraw();

        int SetTexture(EyerGLTexture * texture);
        int SetMVP(EyerMat4x4 & mvp);

        virtual int Draw();

    private:
        EyerMat4x4 mvp;

        EyerGLTexture * texture = nullptr;

        EyerGLVAO * vao = nullptr;
        EyerGLDraw * textureDraw = nullptr;
    };


    class EyerGLFrameDraw : public EyerGLComponent
    {
    public:
        EyerGLFrameDraw();
        ~EyerGLFrameDraw();

        int SetVideoWH(int w, int h);

        int SetYTexture(EyerGLTexture * yTex);
        int SetUTexture(EyerGLTexture * uTex);
        int SetVTexture(EyerGLTexture * vTex);

        int SetMVP(EyerMat4x4 & mvp);

        virtual int Draw();

    private:
        EyerGLVAO * vao = nullptr;
        EyerGLDraw * textureDraw = nullptr;

        EyerGLTexture * yTex = nullptr;
        EyerGLTexture * uTex = nullptr;
        EyerGLTexture * vTex = nullptr;

        EyerMat4x4 * mvp = nullptr;

        int videoW = 0;
        int videoH = 0;
    };


    class EyerGLSingleTextureDraw : public EyerGLComponent
    {
    public:
        EyerGLSingleTextureDraw();
        ~EyerGLSingleTextureDraw();

        int SetTexture(EyerGLTexture * texture);

        virtual int Draw();

    private:
        EyerGLTexture * texture = nullptr;

        EyerGLVAO * vao = nullptr;
        EyerGLDraw * textureDraw = nullptr;
    };

    enum EyerGLYUV2TextureComponentColorRange
    {
        COLOR_RANGE_FULL = 1,
        COLOR_RANGE_JPEG = 2,
    };

    class EyerGLYUV2TextureComponent : public EyerGLComponent
    {
    public:
        EyerGLYUV2TextureComponent();
        ~EyerGLYUV2TextureComponent();

        int SetYTexture(EyerGLTexture * yTex);
        int SetUTexture(EyerGLTexture * uTex);
        int SetVTexture(EyerGLTexture * vTex);

        int SetColoRange(EyerGLYUV2TextureComponentColorRange _colorRange);
        int SetReverseY(int reverseY);

        virtual int Draw();

    private:
        EyerGLDraw * yuv2texture = nullptr;
        EyerGLVAO * vao = nullptr;

        EyerGLTexture * yTex = nullptr;
        EyerGLTexture * uTex = nullptr;
        EyerGLTexture * vTex = nullptr;

        int reverseY = 0;

        EyerGLYUV2TextureComponentColorRange colorRange = EyerGLYUV2TextureComponentColorRange::COLOR_RANGE_FULL;
    };

    class EyerGLCacheTexture
    {
    public:
        Eyer::EyerGLTexture * texture = nullptr;
        int width = 0;
        int height = 0;
        int bearingY = 0;
        int bearingX = 0;
        int advance = 0;
    };


    class EyerGLTest : public EyerGLComponent
    {
    public:
        EyerGLTest();
        ~EyerGLTest();

        virtual int Draw();

    private:
        EyerGLVAO * vao = nullptr;
        EyerGLDraw * textureDraw = nullptr;
    };


    class EyerGLJulia : public EyerGLComponent
    {
    public:
        EyerGLJulia();
        ~EyerGLJulia();

        int SetWH(int w, int h);

        virtual int Draw();

    private:
        EyerGLVAO * vao = nullptr;
        EyerGLDraw * textureDraw = nullptr;

        float startTime = 0;
        int w = 0;
        int h = 0;
    };


    class EyerGLChessboard : public EyerGLComponent
    {
    public:
        EyerGLChessboard();
        ~EyerGLChessboard();

        int SetWH(int w, int h);

        virtual int Draw();

    private:
        int w = 0;
        int h = 0;
    };
}


#endif