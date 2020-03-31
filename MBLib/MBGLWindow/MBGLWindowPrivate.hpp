#ifndef	EYER_LIB_GL_WINDOWS_PRIVATE_H
#define	EYER_LIB_GL_WINDOWS_PRIVATE_H

#include "MBGLWindow.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace MB
{
    class MBGLWindowPrivate
    {
    public:
        GLFWwindow * window = NULL;
    };
}

#endif