#ifndef	EYER_LIB_GL_AV_WINDOWS_H
#define	EYER_LIB_GL_AV_WINDOWS_H

#include "MBCore/MBCore.hpp"
#include <vector>

namespace MB
{
    class MBGLWindowPrivate;
    
    class MBGLWindow
    {
    private:
        MBString title = "MB GL";

        int width = 0;
        int height = 0;

        MBGLWindowPrivate * window = nullptr;
    public:
        MBGLWindow(MBString title, int width, int height);
        ~MBGLWindow();

        int SetBGColor(float r, float g, float b, float a);
        int Clear();

        int Open();
        int Close();
        int ShouldClose();
        int Loop();
    };
}

#endif
