#ifndef EYE_LIB_EYERGPUDOMINO_H
#define EYE_LIB_EYERGPUDOMINO_H

#include "MBCore/MBCore.hpp"
#include "MBGL/MBGL.hpp"

#include <map>

namespace MB
{
    class MBGomino;
    class MBGominoPip;
    class MBGominoGaussianBlur;
    class MBGaussianBlurComponent;
    class MBGominoCopy;
    class MBCommonParams;

    class MBGomino
    {
    public:
        MBGomino(MBString name);
        MBGomino(MBGomino & gomino);
        virtual ~MBGomino();

        MBGomino & operator = (MBGomino & gomino);

        int ClearAll();

        MBString name;

        virtual int Go(MBGLTexture * input, MBGLTexture * output, int width, int height) = 0;

    private:

    };

    class MBGominoPip {
    public:
        MBGominoPip();
        ~MBGominoPip();

        int operator << (MBGomino * gomino);

        int ClearAll();

        int PrintStruct();

        int Go(MBGLTexture * input, MBGLTexture * output, int width, int height);

    private:
        MBLinkedList<MBGomino *> gomineList;
    };


    class MBGominoGaussianBlur : public MBGomino
    {
    public:
        MBGominoGaussianBlur();
        ~MBGominoGaussianBlur();

        virtual int Go(MBGLTexture * input, MBGLTexture * output, int width, int height);
    };

    class MBGominoCopy: public MBGomino
    {
    public:
        MBGominoCopy();
        ~MBGominoCopy();

        virtual int Go(MBGLTexture * input, MBGLTexture * output, int width, int height);
    };

    class MBGominoZoomBlur: public MBGomino
    {
    public:
        MBGominoZoomBlur();
        ~MBGominoZoomBlur();

        virtual int Go(MBGLTexture * input, MBGLTexture * output, int width, int height);
    };

    class MBGaussianBlurComponent : public MBGLComponent
    {
    public:
        MBGaussianBlurComponent();
        ~MBGaussianBlurComponent();

        virtual int Draw();

        int SetTexture(MBGLTexture * _texture);

        int SetWH(int _w, int _h);

    private:
        MBGLDraw * draw = nullptr;
        MBGLVAO * vao = nullptr;
        MBGLTexture * texture = nullptr;

        int w = 1920;
        int h = 1080;
    };



    class MBCopyTextureComponent : public MBGLComponent
    {
    public:
        MBCopyTextureComponent();
        ~MBCopyTextureComponent();

        virtual int Draw();

        int SetTexture(MBGLTexture * _texture);

        int SetWH(int _w, int _h);

    private:
        MBGLDraw * draw = nullptr;
        MBGLVAO * vao = nullptr;
        MBGLTexture * texture = nullptr;

        int w = 1920;
        int h = 1080;
    };



    class MBCommonParams
    {
    public:
        MBCommonParams();
        ~MBCommonParams();
        MBCommonParams(const MBCommonParams & params);

        MBCommonParams & operator = (const MBCommonParams & params);

        int PutFloat(MBString key, float val);

    private:
        // std::map<MBString, float> param;
    };

    class MBCommonComponent : public MBGLComponent
    {
    public:
        MBCommonComponent(char * V_SHADER, char * F_SHADER);
        ~MBCommonComponent();

        virtual int Draw();

        int SetTexture(MBGLTexture * _texture);

        int SetWH(int _w, int _h);

    private:
        MBGLDraw * draw = nullptr;
        MBGLVAO * vao = nullptr;
        MBGLTexture * texture = nullptr;

        int w = 1920;
        int h = 1080;
    };
}

#endif //EYE_LIB_EYERGPUDOMINO_H