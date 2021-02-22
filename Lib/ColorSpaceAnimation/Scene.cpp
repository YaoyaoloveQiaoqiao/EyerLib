#include "Scene.hpp"
#include "MagicNumber.hpp"

#include "SphereSpirit.hpp"

#include "image_r.hpp"
#include "image_g.hpp"
#include "image_b.hpp"

namespace Eyer
{
    Scene::Scene(int _w, int _h)
    {
        w = _w;
        h = _h;

    }

    Scene::~Scene() {

    }

    int Scene::Start()
    {
        startTime = Eyer::EyerTime::GetTime();

        int endFrame = 30 * 60 * 60;
        {
            camera = new EyerCamera();
            camera->SetWH(w, h);
            {
                EyerKey key;
                key.frame = 0;
                key.position = EectorF3(0.0, 5.0, 5.0);
                camera->AddKey(key);
            }
            {
                EyerKey key;
                key.frame = 10.0 * fps;
                key.position = EectorF3(5.0, 5.0, 5.0);
                camera->AddKey(key);
            }

            {
                EyerKey key;
                key.frame = 25.0 * fps;
                key.position = EectorF3(5.0, 5.0, 5.0);
                camera->AddKey(key);
            }
            {
                EyerKey key;
                key.frame = 30.0 * fps;
                key.position = EectorF3(-5.0, 5.0, 5.0);
                camera->AddKey(key);
            }
            {
                EyerKey key;
                key.frame = 35.0 * fps;
                key.position = EectorF3(-5.0, 5.0, -5.0);
                camera->AddKey(key);
            }
            {
                EyerKey key;
                key.frame = 40.0 * fps;
                key.position = EectorF3(5.0, 5.0, -5.0);
                camera->AddKey(key);
            }
            {
                EyerKey key;
                key.frame = 45.0 * fps;
                key.position = EectorF3(5.0, 5.0, 5.0);
                camera->AddKey(key);
            }

            {
                EyerKey key;
                key.frame = 55.0 * fps;
                key.position = EectorF3(10.0, 10.0, 10.0);
                camera->AddKey(key);
            }
            {
                EyerKey key;
                key.frame = 60.0 * fps;
                key.position = EectorF3(-10.0, 10.0, 10.0);
                camera->AddKey(key);
            }
            {
                EyerKey key;
                key.frame = 65.0 * fps;
                key.position = EectorF3(-10.0, 10.0, -10.0);
                camera->AddKey(key);
            }
            {
                EyerKey key;
                key.frame = 70.0 * fps;
                key.position = EectorF3(10.0, 10.0, -10.0);
                camera->AddKey(key);
            }
            {
                EyerKey key;
                key.frame = 72.0 * fps;
                key.position = EectorF3(5.0, 5.0, 3.0);
                camera->AddKey(key);
            }
            {
                EyerKey key;
                key.frame = 75.0 * fps;
                key.position = EectorF3(2.0, 2.0, 2.0);
                camera->AddKey(key);
            }

            {
                EyerKey key;
                key.frame = 90.0 * fps;
                key.position = EectorF3(2.0, 2.0, 2.0);
                camera->AddKey(key);
            }
            {
                EyerKey key;
                key.frame = 100.0 * fps;
                key.position = EectorF3(2.0, 2.0, 2.0);
                camera->AddKey(key);
            }
            {
                EyerKey key;
                key.frame = 115.0 * fps;
                key.position = EectorF3(2.0, 2.0, 2.0);
                camera->AddKey(key);
            }
            {
                EyerKey key;
                key.frame = 120.0 * fps;
                key.cameraTarget = EectorF3(0.5, 0.5, 0);
                key.position = EectorF3(0.5, 0.5, 1.0);
                camera->AddKey(key);
            }
            {
                EyerKey key;
                key.frame = endFrame;
                key.cameraTarget = EectorF3(0.5, 0.5, 0);
                key.position = EectorF3(0.5, 0.5, 1.0);
                camera->AddKey(key);
            }
            scene.SetCamera(camera);
        }
        {
            RGB_COOR = new CIE_RGB_COOR_EyerSpirit();
            {
                EyerKey key;
                key.frame = 0;
                key.color = EectorF4(1.0, 1.0, 1.0, 1.0);
                key.scale = EectorF3(0.0, 0.0, 0.0);
                RGB_COOR->AddKey(key);
            }
            {
                EyerKey key;
                key.frame = 32.0 * fps;
                key.color = EectorF4(1.0, 1.0, 1.0, 1.0);
                key.scale = EectorF3(1000.0, 1000.0, 1000.0);
                RGB_COOR->AddKey(key);
            }

            {
                EyerKey key;
                key.frame = 45.0 * fps;
                key.color = EectorF4(1.0, 1.0, 1.0, 1.0);
                key.scale = EectorF3(1000.0, 1000.0, 1000.0);
                RGB_COOR->AddKey(key);
            }
            {
                EyerKey key;
                key.frame = 50.0 * fps;
                key.color = EectorF4(0.0, 0.0, 0.0, 0.0);
                key.scale = EectorF3(1000.0, 1000.0, 1000.0);
                RGB_COOR->AddKey(key);
            }
            /*
            {
                EyerKey key;
                key.frame = endFrame;
                key.scale = EectorF3(1000.0, 1000.0, 1000.0);
                RGB_COOR->AddKey(key);
            }
            */
            scene.AddSpirit(RGB_COOR);
        }

        {
            R = new Label_EyerSpirit(image_r, sizeof(image_r));
            EyerKey baseKey;
            baseKey.position = EectorF3(4.0, 0.25, 0.0);
            baseKey.rotato = EectorF4(1.0, 0.0, 0.0, 0.0);
            baseKey.scale = EectorF3(0.2, 0.2, 0.2);
            {
                EyerKey key = baseKey;
                key.frame = 0;
                key.scale = EectorF3(0.0, 0.0, 0.0);
                R->AddKey(key);
            }
            {
                EyerKey key = baseKey;
                key.frame = 1.0 * fps;
                key.scale = EectorF3(0.2, 0.2, 0.2);
                R->AddKey(key);
            }
            {
                EyerKey key = baseKey;
                key.frame = 50.0 * fps;
                key.scale = EectorF3(0.2, 0.2, 0.2);
                R->AddKey(key);
            }
            {
                EyerKey key = baseKey;
                key.frame = 55.0 * fps;
                key.scale = EectorF3(0, 0, 0);
                R->AddKey(key);
            }
            {
                EyerKey key = baseKey;
                key.frame = endFrame;
                key.scale = EectorF3(0, 0, 0);
                R->AddKey(key);
            }
            scene.AddSpirit(R);
        }

        {
            G = new Label_EyerSpirit(image_g, sizeof(image_g));
            EyerKey baseKey;
            baseKey.position = EectorF3(0.25, 4.0, 0);
            baseKey.rotato = EectorF4(1.0, 0.0, 0.0, 0.0);
            baseKey.scale = EectorF3(0.2, 0.2, 0.2);
            {
                EyerKey key = baseKey;
                key.frame = 0;
                key.scale = EectorF3(0.0, 0.0, 0.0);
                G->AddKey(key);
            }
            {
                EyerKey key = baseKey;
                key.frame = 1.0 * fps;
                key.scale = EectorF3(0.2, 0.2, 0.2);
                G->AddKey(key);
            }
            {
                EyerKey key = baseKey;
                key.frame = 50.0 * fps;
                key.scale = EectorF3(0.2, 0.2, 0.2);
                G->AddKey(key);
            }
            {
                EyerKey key = baseKey;
                key.frame = 55.0 * fps;
                key.scale = EectorF3(0, 0, 0);
                G->AddKey(key);
            }
            {
                EyerKey key = baseKey;
                key.scale = EectorF3(0, 0, 0);
                key.frame = endFrame;
                G->AddKey(key);
            }
            scene.AddSpirit(G);
        }

        {
            B = new Label_EyerSpirit(image_b, sizeof(image_b));
            EyerKey baseKey;
            baseKey.position = EectorF3(0.0, 0.25, 4.0);
            baseKey.rotato = EectorF4(0.0, 1.0, 0.0, Eath::DegreesToRadians(90));
            baseKey.scale = EectorF3(0.2, 0.2, 0.2);
            {
                EyerKey key = baseKey;
                key.frame = 0;
                key.scale = EectorF3(0.0, 0.0, 0.0);
                B->AddKey(key);
            }
            {
                EyerKey key = baseKey;
                key.frame = 1.0 * fps;
                key.scale = EectorF3(0.2, 0.2, 0.2);
                B->AddKey(key);
            }
            {
                EyerKey key = baseKey;
                key.frame = 50.0 * fps;
                key.scale = EectorF3(0.2, 0.2, 0.2);
                B->AddKey(key);
            }
            {
                EyerKey key = baseKey;
                key.frame = 55.0 * fps;
                key.scale = EectorF3(0, 0, 0);
                B->AddKey(key);
            }
            {
                EyerKey key = baseKey;
                key.frame = endFrame;
                key.scale = EectorF3(0, 0, 0);
                B->AddKey(key);
            }
            scene.AddSpirit(B);
        }
        {
            EyerKey baseKey;
            baseKey.position = EectorF3(0, 0, 0);
            baseKey.rotato = EectorF4(1.0, 0.0, 0.0, 0.0);
            float scale = 0.05;
            baseKey.scale = EectorF3(scale, scale, scale);

            for(int i=0;i<48;i++){
                float x = MagicNumber::colour_matching_data[i][0];
                float y = MagicNumber::colour_matching_data[i][1];
                float z = MagicNumber::colour_matching_data[i][2];

                Eyer::EectorF3 rgb(x, y, z);

                float xyz_rgb[] = {
                        2.7688, 1.7517, 1.1301,
                        1.0000, 4.5906, 0.0601,
                        0,      0.0565, 5.5942
                };

                Eyer::Eatrix<float> rgb_xyz_mat(3, 3);
                rgb_xyz_mat.SetData(xyz_rgb, 9);

                Eyer::EectorF3 xyz = rgb_xyz_mat * rgb;

                Eyer::EectorF3 xyz_norm = xyz;
                float a = xyz_norm.x() + xyz_norm.y() + xyz_norm.z();
                xyz_norm.SetX(xyz_norm.x() / a);
                xyz_norm.SetY(xyz_norm.y() / a);
                xyz_norm.SetZ(xyz_norm.z() / a);

                Eyer::EectorF3 xyz_norm_xy = xyz_norm;
                xyz_norm_xy.SetZ(0);

                SphereSpirit * ss = new SphereSpirit();
                {
                    EyerKey key = baseKey;
                    key.frame = i * 0.2 * fps + 10.0 * fps;
                    key.position = rgb;
                    key.color = GetColor(i);
                    ss->AddKey(key);
                }
                {
                    EyerKey key = baseKey;
                    key.frame = 45 * fps;
                    key.position = rgb;
                    key.color = GetColor(i);
                    ss->AddKey(key);
                }
                {
                    EyerKey key = baseKey;
                    key.frame = 50 * fps;;
                    key.position = xyz;
                    key.color = GetColor(i);
                    ss->AddKey(key);
                }
                {
                    EyerKey key = baseKey;
                    key.frame = 90 * fps;;
                    key.position = xyz;
                    key.color = GetColor(i);
                    ss->AddKey(key);
                }
                {
                    EyerKey key = baseKey;
                    key.frame = 100 * fps;
                    key.position = xyz_norm;
                    key.color = GetColor(i);
                    float scale = 0.015;
                    key.scale = EectorF3(scale, scale, scale);
                    ss->AddKey(key);
                }
                {
                    EyerKey key = baseKey;
                    key.frame = 105 * fps;
                    key.position = xyz_norm;
                    key.color = GetColor(i);
                    float scale = 0.015;
                    key.scale = EectorF3(scale, scale, scale);
                    ss->AddKey(key);
                }
                {
                    EyerKey key = baseKey;
                    key.frame = 115 * fps;
                    key.position = xyz_norm_xy;
                    key.color = GetColor(i);
                    float scale = 0.015;
                    key.scale = EectorF3(scale, scale, scale);
                    ss->AddKey(key);
                }
                {
                    EyerKey key = baseKey;
                    key.frame = endFrame;
                    key.position = xyz_norm_xy;
                    key.color = GetColor(i);
                    float scale = 0.015;
                    key.scale = EectorF3(scale, scale, scale);
                    ss->AddKey(key);
                }
                scene.AddSpirit(ss);



                Eyer::EectorF3 start(0.0, 0.0, 0.0);
                MVPLineSpirit * lineSpirit = new MVPLineSpirit(start, xyz);
                {
                    EyerKey key = baseKey;
                    key.frame = 90 * fps;;
                    key.color = GetColor(i);
                    float scale = 1.0;
                    key.scale = EectorF3(scale, scale, scale);
                    lineSpirit->AddKey(key);
                }
                {
                    EyerKey key = baseKey;
                    key.frame = 100 * fps;
                    key.color = GetColor(i);
                    float scale = 1.0;
                    key.scale = EectorF3(scale, scale, scale);
                    lineSpirit->AddKey(key);
                }
                scene.AddSpirit(lineSpirit);


                MVPLineSpirit * lineSpirit2 = new MVPLineSpirit(xyz_norm, xyz_norm_xy);
                {
                    EyerKey key = baseKey;
                    key.frame = 105 * fps;
                    key.color = GetColor(i);
                    float scale = 1.0;
                    key.scale = EectorF3(scale, scale, scale);
                    lineSpirit2->AddKey(key);
                }
                {
                    EyerKey key = baseKey;
                    key.frame = 115 * fps;
                    key.color = GetColor(i);
                    float scale = 1.0;
                    key.scale = EectorF3(scale, scale, scale);
                    lineSpirit2->AddKey(key);
                }
                scene.AddSpirit(lineSpirit2);
            }
        }


        EectorF4 xyzColor(1.0, 1.0, 0.2, 1.0);
        // X Coor
        {
            EyerKey baseKey;
            baseKey.position = EectorF3(1, 3, 0);
            baseKey.rotato = EectorF4(1.0, 0.0, 0.0, 0.0);
            float scale = 1.0;
            baseKey.scale = EectorF3(scale, scale, scale);
            baseKey.color = xyzColor;
            X = new MVPCoorLineSpirit();
            {
                EyerKey key = baseKey;
                key.frame = 20.0 * fps;
                float scale = 0.0;
                key.scale = EectorF3(scale, scale, scale);
                key.position = EectorF3(0.4185, -0.0912, 0.0009);
                X->AddKey(key);
            }
            {
                EyerKey key = baseKey;
                key.frame = 25.0 * fps;
                float scale = 100.0;
                key.scale = EectorF3(scale, scale, scale);
                key.position = EectorF3(0.4185, -0.0912, 0.0009);
                X->AddKey(key);
            }
            {
                EyerKey key = baseKey;
                key.frame = 45.0 * fps;
                float scale = 100.0;
                key.scale = EectorF3(scale, scale, scale);
                key.position = EectorF3(0.4185, -0.0912, 0.0009);
                X->AddKey(key);
            }
            {
                EyerKey key = baseKey;
                key.frame = 50.0 * fps;
                float scale = 100.0;
                key.scale = EectorF3(scale, scale, scale);
                key.position = EectorF3(1.0, 0.0, 0.0);
                X->AddKey(key);
            }
            {
                EyerKey key = baseKey;
                key.frame = endFrame;
                float scale = 100.0;
                key.scale = EectorF3(scale, scale, scale);
                key.position = EectorF3(1.0, 0.0, 0.0);
                X->AddKey(key);
            }
            scene.AddSpirit(X);
        }

        // Y Coor
        {
            EyerKey baseKey;
            baseKey.position = EectorF3(1, 3, 0);
            baseKey.rotato = EectorF4(1.0, 0.0, 0.0, 0.0);
            float scale = 1.0;
            baseKey.scale = EectorF3(scale, scale, scale);
            baseKey.color = xyzColor;
            Y = new MVPCoorLineSpirit();
            {
                EyerKey key = baseKey;
                key.frame = 20.0 * fps;
                float scale = 0.0;
                key.scale = EectorF3(scale, scale, scale);
                key.position = EectorF3(-0.1587, 0.2524, -0.0025);
                Y->AddKey(key);
            }
            {
                EyerKey key = baseKey;
                key.frame = 25.0 * fps;
                float scale = 100.0;
                key.scale = EectorF3(scale, scale, scale);
                key.position = EectorF3(-0.1587, 0.2524, -0.0025);
                Y->AddKey(key);
            }
            {
                EyerKey key = baseKey;
                key.frame = 45.0 * fps;
                float scale = 100.0;
                key.scale = EectorF3(scale, scale, scale);
                key.position = EectorF3(-0.1587, 0.2524, -0.0025);
                Y->AddKey(key);
            }
            {
                EyerKey key = baseKey;
                key.frame = 50.0 * fps;
                float scale = 100.0;
                key.scale = EectorF3(scale, scale, scale);
                key.position = EectorF3(0.0, 1.0, 0.0);
                Y->AddKey(key);
            }
            {
                EyerKey key = baseKey;
                key.frame = endFrame;
                float scale = 100.0;
                key.scale = EectorF3(scale, scale, scale);
                key.position = EectorF3(0.0, 1.0, 0.0);
                Y->AddKey(key);
            }
            scene.AddSpirit(Y);
        }

        // Z Coor
        {
            EyerKey baseKey;
            baseKey.position = EectorF3(1, 3, 0);
            baseKey.rotato = EectorF4(1.0, 0.0, 0.0, 0.0);
            float scale = 1.0;
            baseKey.scale = EectorF3(scale, scale, scale);
            baseKey.color = xyzColor;
            Z = new MVPCoorLineSpirit();
            {
                EyerKey key = baseKey;
                key.frame = 20.0 * fps;
                float scale = 0.0;
                key.scale = EectorF3(scale, scale, scale);
                key.position = EectorF3(-0.0828, 0.0157, 0.1786);
                Z->AddKey(key);
            }
            {
                EyerKey key = baseKey;
                key.frame = 25.0 * fps;
                float scale = 100.0;
                key.scale = EectorF3(scale, scale, scale);
                key.position = EectorF3(-0.0828, 0.0157, 0.1786);
                Z->AddKey(key);
            }
            {
                EyerKey key = baseKey;
                key.frame = 45.0 * fps;
                float scale = 100.0;
                key.scale = EectorF3(scale, scale, scale);
                key.position = EectorF3(-0.0828, 0.0157, 0.1786);
                Z->AddKey(key);
            }
            {
                EyerKey key = baseKey;
                key.frame = 50.0 * fps;
                float scale = 100.0;
                key.scale = EectorF3(scale, scale, scale);
                key.position = EectorF3(0.0, 0.0, 1.0);
                Z->AddKey(key);
            }
            {
                EyerKey key = baseKey;
                key.frame = endFrame;
                float scale = 100.0;
                key.scale = EectorF3(scale, scale, scale);
                key.position = EectorF3(0.0, 0.0, 1.0);
                Z->AddKey(key);
            }
            scene.AddSpirit(Z);
        }

        {
            normalizePlaneSpirit = new MVPNormalizePlaneSpirit();
            EyerKey baseKey;
            baseKey.position = EectorF3(0, 0, 0);
            baseKey.rotato = EectorF4(1.0, 0.0, 0.0, 0.0);
            float scale = 1.0;
            baseKey.scale = EectorF3(scale, scale, scale);
            baseKey.color = EectorF4(1.0, 1.0, 1.0, 0.2);
            {
                EyerKey key = baseKey;
                key.frame = 80.0 * fps;
                key.color = EectorF4(1.0, 1.0, 1.0, 0.0);
                normalizePlaneSpirit->AddKey(key);
            }
            {
                EyerKey key = baseKey;
                key.frame = 85.0 * fps;
                normalizePlaneSpirit->AddKey(key);
            }

            {
                EyerKey key = baseKey;
                key.frame = 105.0 * fps;
                key.color = EectorF4(1.0, 1.0, 1.0, 0.2);
                normalizePlaneSpirit->AddKey(key);
            }

            {
                EyerKey key = baseKey;
                key.frame = 115.0 * fps;
                key.color = EectorF4(1.0, 1.0, 1.0, 0.0);
                normalizePlaneSpirit->AddKey(key);
            }

            scene.AddSpirit(normalizePlaneSpirit);
        }

        return 0;
    }

    int Scene::Update()
    {
        long long currTime = Eyer::EyerTime::GetTime();
        long long dTime = currTime - startTime;

        double time = dTime / 1000.0;

        time += 0;

        if(time < 0){
            return 0;
        }

        int frame = time * fps;

        scene.Render(frame);

        return 0;
    }


    EectorF4 Scene::GetColor(int i)
    {
        float r = 0;
        float g = 0;
        float b = 0;
        if(i >=0 && i <= 22){
            r = 0;
            g = 1.0 / 22.0 * (i - 0);
            b = 1.0;
        }
        else if(i > 22 && i <= 26){
            r = 0;
            g = 1.0;
            b = 1.0 - (1.0 / 4 * (i - 22));
        }
        else if(i > 26 && i <= 34){
            r = 1.0 / 8 * (i - 26);
            g = 1.0;
            b = 0;
        }
        else if(i >= 35){
            r = 1.0;
            g = 1.0 - (1.0 / 12 * (i - 35));
            b = 0;
        }

        EectorF4 res(r, g, b, 1.0);
        return res;
    }
}


