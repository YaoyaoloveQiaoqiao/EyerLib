#include <gtest/gtest.h>
#include "EyerCore/EyerCore.hpp"
#include "EyerGLWindow/EyerGLWindow.hpp"

#include "Scene.hpp"

int main(int argc,char **argv){
    eyer_log_param(1, 1, 0, 0, 0);

    EyerLog("Hello World\n");

    Eyer::EyerGLWindow window("ColorSpace", 1920, 1080);

    window.Open();
    window.SetBGColor(0.0, 0.0, 0.0, 1.0);

    Eyer::Scene scene(1920, 1080);

    scene.Start();
    while (!window.ShouldClose()){
        window.Clear();
        scene.Update();
        window.Loop();
    }

    window.Close();

    return 0;
}