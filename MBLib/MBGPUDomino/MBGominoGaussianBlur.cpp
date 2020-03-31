#include "MBGPUDomino.hpp"

namespace MB
{
    MBGominoGaussianBlur::MBGominoGaussianBlur() : MBGomino("GaussianBlur")
    {

    }

    MBGominoGaussianBlur::~MBGominoGaussianBlur()
    {

    }

    int MBGominoGaussianBlur::Go(MBGLTexture * input, MBGLTexture * output, int width, int height)
    {
        MBGLFrameBuffer frameBuffer(width, height, output);

        frameBuffer.ClearAllComponent();
        frameBuffer.Clear();

        MBGaussianBlurComponent gaussianBlurComponent;
        gaussianBlurComponent.SetTexture(input);
        gaussianBlurComponent.SetWH(width, height);

        frameBuffer.AddComponent(&gaussianBlurComponent);

        frameBuffer.Draw();

        frameBuffer.ClearAllComponent();

        return 0;
    }
}