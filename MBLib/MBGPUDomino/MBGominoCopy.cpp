#include "MBGPUDomino.hpp"

namespace MB
{
    MBGominoCopy::MBGominoCopy() : MBGomino("Copy")
    {

    }

    MBGominoCopy::~MBGominoCopy()
    {

    }

    int MBGominoCopy::Go(MBGLTexture * input, MBGLTexture * output, int width, int height)
    {
        MBGLFrameBuffer frameBuffer(width, height, output);

        frameBuffer.ClearAllComponent();
        frameBuffer.Clear();

        MBCopyTextureComponent copyComponent;
        copyComponent.SetTexture(input);
        copyComponent.SetWH(width, height);

        frameBuffer.AddComponent(&copyComponent);

        frameBuffer.Draw();

        frameBuffer.ClearAllComponent();

        return 0;
    }
}