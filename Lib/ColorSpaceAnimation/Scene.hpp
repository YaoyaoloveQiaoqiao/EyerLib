#ifndef EYERCOLORSPACE_SCENE_HPP
#define EYERCOLORSPACE_SCENE_HPP

#include "EyerGLCustomComponent/EyerGLCustomComponent.hpp"
#include "EyerVideoEditor/EyerVideoEditor.hpp"

#include "CIE_RGB_COOR_EyerSpirit.hpp"
#include "CIE_XYZ_COOR_EyerSpirit.hpp"
#include "Label_EyerSpirit.hpp"
#include "MVPCoorLineSpirit.hpp"
#include "MVPNormalizePlaneSpirit.hpp"
#include "MVPLineSpirit.hpp"
#include "MVPCustomSpirit.hpp"

namespace Eyer
{
    class Scene {
    public:
        Scene(int _w, int _h);
        ~Scene();

        int Start();
        int Update();

        EectorF4 GetColor(int i);

    private:
        int w = 0;
        int h = 0;

        long long startTime;

        double fps = 60;

        Eyer::EyerScene scene;

        int frameIndex = 0;

        CIE_RGB_COOR_EyerSpirit * RGB_COOR = nullptr;
        Label_EyerSpirit * R = nullptr;
        Label_EyerSpirit * G = nullptr;
        Label_EyerSpirit * B = nullptr;

        EyerCamera * camera = nullptr;

        MVPCoorLineSpirit * X = nullptr;
        MVPCoorLineSpirit * Y = nullptr;
        MVPCoorLineSpirit * Z = nullptr;

        MVPNormalizePlaneSpirit * normalizePlaneSpirit = nullptr;


        MVPCustomSpirit * coloPlane = nullptr;
    };
}

#endif //EYERCOLORSPACE_SCENE_HPP
