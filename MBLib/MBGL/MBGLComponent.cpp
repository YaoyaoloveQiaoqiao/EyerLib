#include "MBGL.hpp"

namespace MB
{
    int MBGLComponent::Viewport(int w, int h)
    {
        width = w;
        height = h;

        return 0;
    }

    MBGLComponent::~MBGLComponent()
    {

    }
}