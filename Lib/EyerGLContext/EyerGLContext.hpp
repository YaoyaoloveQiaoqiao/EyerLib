#ifndef	EYER_LIB_GL_CONTEXT_THREAD_AV_H
#define	EYER_LIB_GL_CONTEXT_THREAD_AV_H

#include "EyerCore/EyerCore.hpp"
#include "EyerThread/EyerThread.hpp"
#include "EyerGLCustomComponent/EyerGLCustomComponent.hpp"
#include "EyerGLRenderTask/EyerGLRenderTask.hpp"

#ifdef EYER_PLATFORM_ANDROID
#include <android/native_window_jni.h>
#include <GLES3/gl3.h>
#include <GLES3/gl3ext.h>

#include <EGL/egl.h>
#include <EGL/eglext.h>
#else

#endif



namespace Eyer
{
    class EyerGLContextThread : public EyerThread
    {
    public:
#ifdef EYER_PLATFORM_ANDROID
        EyerGLContextThread(ANativeWindow * nativeWindow);
#else
#endif

        ~EyerGLContextThread();
        virtual void Run();

        int SetWH(int w, int h);

        int AddTaskToRenderQueue(EyerGLRenderTask * task);
        int AddTaskToRenderAndFreeQueue(EyerGLRenderTask * task);
        
        int AddTaskToDestoryQueue(EyerGLRenderTask * task);

        int GetW();
        int GetH();
    private:

#ifdef EYER_PLATFORM_ANDROID
        ANativeWindow * nativeWindow = nullptr;
#else
#endif

        int w = 0;
        int h = 0;

        EyerGLRenderTaskQueue taskQueue;
        EyerGLRenderTaskQueue renderAndFreeTaskQueue;
        EyerLockQueue<EyerGLRenderTask> destoryTaskQueue;
    };
}

#endif
