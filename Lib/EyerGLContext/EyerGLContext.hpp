#ifndef	EYER_LIB_GL_CONTEXT_THREAD_AV_H
#define	EYER_LIB_GL_CONTEXT_THREAD_AV_H

#include "EyerCore/EyerCore.hpp"
#include "EyerThread/EyerThread.hpp"
#include "EyerGL/EyerGLCustomComponent/EyerGLCustomComponent.hpp"
#include "EyerGL/EyerGLRenderTask/EyerGLRenderTask.hpp"

#include <android/native_window_jni.h>
#include <GLES3/gl3.h>
#include <GLES3/gl3ext.h>

namespace Eyer
{
    class EyerGLContextThread : public EyerThread
    {
    public:
        EyerGLContextThread(ANativeWindow * nativeWindow);
        ~EyerGLContextThread();
        virtual void Run();

        int SetWH(int w, int h);

        int AddTaskToRenderQueue(EyerGLRenderTask * task);
        int AddTaskToRenderAndFreeQueue(EyerGLRenderTask * task);
        
        int AddTaskToDestoryQueue(EyerGLRenderTask * task);

        int GetW();
        int GetH();
    private:
        ANativeWindow * nativeWindow = nullptr;

        int w = 0;
        int h = 0;

        EyerGLRenderTaskQueue taskQueue;
        EyerGLRenderTaskQueue renderAndFreeTaskQueue;
        EyerLockQueue<EyerGLRenderTask> destoryTaskQueue;
    };
}

#endif
