#ifndef EYERCOLORSPACE_MVPSPHERE_HPP
#define EYERCOLORSPACE_MVPSPHERE_HPP

namespace Eyer
{
    class MVPSphere : public EyerGLComponent
    {
    public:
        MVPSphere();
        ~MVPSphere();

        int SetMVP(EatrixF4x4 & mat);

        virtual int Draw();

        int SetPos(float x, float y, float z);
        int SetColor(float r, float g, float b, float a = 1.0f);

    private:
        EyerGLDraw * draw = nullptr;
        EyerGLVAO * vao = nullptr;

        EatrixF4x4 mTrans;
        EatrixF4x4 mvp;

        float degres = 0.0;

        int statcky = 5;
        int stlicex = 5;

        float color_r = 1.0f;
        float color_g = 0.0f;
        float color_b = 0.0f;
        float color_a = 1.0f;

        std::vector<float> GenVBO();
        std::vector<unsigned int> GenEBO();
        std::vector<float> GenTextureCoordinates();
    };
}

#endif //EYERCOLORSPACE_MVPSPHERE_HPP
