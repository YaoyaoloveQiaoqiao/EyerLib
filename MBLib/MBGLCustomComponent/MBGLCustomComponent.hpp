#ifndef	EYER_LIB_GL_CUSTOM_COMPONENT_H
#define	EYER_LIB_GL_CUSTOM_COMPONENT_H

#include "MBGL/MBGL.hpp"
#include "MBType/MBType.hpp"
#include "MBCore/MBCore.hpp"

namespace MB
{
    class MBGLCacheTexture;

    class MBGLTextDraw : public MBGLComponent
    {
    public:
        MBGLTextDraw(MBString _typeFilePath);
        ~MBGLTextDraw();

        int GetTextWidth();

        int SetText(MBString text);

        int SetSize(float size);
        int SetPos(float x, float y);

        int SetColor(float r, float g, float b);

        virtual int Draw();

    private:
        MBString typeFilePath;

        MBString text;
        MBGLDraw * pointDraw = nullptr;
        MBGLVAO * pointVao = nullptr;
        MBType * typeCreator = nullptr;
        MBGLDraw * textDraw = nullptr;
        MBGLVAO * vao = nullptr;

        std::map<wchar_t, MBGLCacheTexture *> textureCache;

        float positionX = 0.0f;
        float positionY = 0.0f;

        int size = 100;

        float r = 0.0f;
        float g = 0.0f;
        float b = 0.0f;
    };   


    class MBGLMVPTextureDraw : public MBGLComponent
    {
    public:
        MBGLMVPTextureDraw();
        ~MBGLMVPTextureDraw();

        int SetTexture(MBGLTexture * texture);
        int SetMVP(MBMat4x4 & mvp);

        virtual int Draw();

    private:
        MBMat4x4 mvp;

        MBGLTexture * texture = nullptr;

        MBGLVAO * vao = nullptr;
        MBGLDraw * textureDraw = nullptr;
    };


    class MBGLFrameDraw : public MBGLComponent
    {
    public:
        MBGLFrameDraw();
        ~MBGLFrameDraw();

        int SetVideoWH(int w, int h);

        int SetYTexture(MBGLTexture * yTex);
        int SetUTexture(MBGLTexture * uTex);
        int SetVTexture(MBGLTexture * vTex);

        int SetMVP(MBMat4x4 & mvp);

        virtual int Draw();

    private:
        MBGLVAO * vao = nullptr;
        MBGLDraw * textureDraw = nullptr;

        MBGLTexture * yTex = nullptr;
        MBGLTexture * uTex = nullptr;
        MBGLTexture * vTex = nullptr;

        MBMat4x4 * mvp = nullptr;

        int videoW = 0;
        int videoH = 0;
    };


    class MBGLSingleTextureDraw : public MBGLComponent
    {
    public:
        MBGLSingleTextureDraw();
        ~MBGLSingleTextureDraw();

        int SetTexture(MBGLTexture * texture);

        virtual int Draw();

    private:
        MBGLTexture * texture = nullptr;

        MBGLVAO * vao = nullptr;
        MBGLDraw * textureDraw = nullptr;
    };

    enum EyerGLYUV2TextureComponentColorRange
    {
        COLOR_RANGE_FULL = 1,
        COLOR_RANGE_JPEG = 2,
    };

    class MBGLYUV2TextureComponent : public MBGLComponent
    {
    public:
        MBGLYUV2TextureComponent();
        ~MBGLYUV2TextureComponent();

        int SetYTexture(MBGLTexture * yTex);
        int SetUTexture(MBGLTexture * uTex);
        int SetVTexture(MBGLTexture * vTex);

        int SetColoRange(EyerGLYUV2TextureComponentColorRange _colorRange);

        virtual int Draw();

    private:
        MBGLDraw * yuv2texture = nullptr;
        MBGLVAO * vao = nullptr;

        MBGLTexture * yTex = nullptr;
        MBGLTexture * uTex = nullptr;
        MBGLTexture * vTex = nullptr;

        EyerGLYUV2TextureComponentColorRange colorRange = EyerGLYUV2TextureComponentColorRange::COLOR_RANGE_FULL;
    };

    class MBGLCacheTexture
    {
    public:
        MB::MBGLTexture * texture = nullptr;
        int width = 0;
        int height = 0;
        int bearingY = 0;
        int bearingX = 0;
        int advance = 0;
    };
}


#endif