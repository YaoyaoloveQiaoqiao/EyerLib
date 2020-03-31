//
// Created by redknot on 2020/1/5.
//
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "MBGLWindow.hpp"
#include "MBGLWindowPrivate.hpp"

namespace MB
{

    MBGLWindow::MBGLWindow(MBString _title, int _width, int _height)
    {
        title = _title;
        width = _width;
        height = _height;

        window = new MBGLWindowPrivate();

        glfwInit();
    }

    MBGLWindow::~MBGLWindow()
    {
        Close();

        glfwTerminate();

        if(window != nullptr) {
            delete window;
            window = nullptr;
        }
    }

    int MBGLWindow::Open()
    {
        if(window->window != NULL){
            Close();
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

        window->window = glfwCreateWindow(width, height, title.str, NULL, NULL);
        if (window->window == NULL) {
            glfwTerminate();
            return -1;
        }
        glfwMakeContextCurrent(window->window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            return -1;
        }

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        return 0;
    }

    int MBGLWindow::Close()
    {
        if(window->window == NULL){
            return -1;
        }

        glfwDestroyWindow(window->window);
        window->window = NULL;

        return 0;
    }

    int MBGLWindow::SetBGColor(float r, float g, float b, float a)
    {
        if(window->window == NULL){
            return -1;
        }

        glClearColor(r, g, b, a);

        return 0;
    }

    int MBGLWindow::Clear()
    {
        if(window->window == NULL){
            return -1;
        }
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        return 0;
    }

    int MBGLWindow::ShouldClose()
    {
        if(window->window == NULL){
            return -1;
        }

        int ret = glfwWindowShouldClose(window->window);

        return ret;
    }

    int MBGLWindow::Loop()
    {
        if(window->window == NULL){
            return -1;
        }

        glfwSwapBuffers(window->window);
        glfwPollEvents();

        return 0;
    }
}

