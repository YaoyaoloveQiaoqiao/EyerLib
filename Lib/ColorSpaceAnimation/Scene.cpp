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

        float xyz_rgb[] = {
                2.7688, 1.7517, 1.1301,
                1.0000, 4.5906, 0.0601,
                0,      0.0565, 5.5942
        };

        Eyer::Eatrix<float> rgb_xyz_mat(3, 3);
        rgb_xyz_mat.SetData(xyz_rgb, 9);

        // BT 709 Point
        float bt709_xyz[] = {
                0.4124, 0.3576, 0.1805,
                0.2126, 0.7152, 0.0722,
                0.0193, 0.1192, 0.9505
        };

        Eyer::Eatrix<float> bt709_xyz_mat(3, 3);
        bt709_xyz_mat.SetData(bt709_xyz, 9);
        bt709_xyz_mat.PrintInfo();

        // BT 2020 Point
        float bt2020_xyz[] = {
                0.6370, 0.1446, 0.1689,
                0.2627, 0.6780, 0.0593,
                0, 0.0281, 1.0610
        };

        Eyer::Eatrix<float> bt2020_xyz_mat(3, 3);
        bt2020_xyz_mat.SetData(bt2020_xyz, 9);
        bt2020_xyz_mat.PrintInfo();


        EectorF3 test_rgb_bt907(0.7, 0.3, 0.1);

        EectorF3 test_rgb_xyz_bt709 = bt709_xyz_mat * test_rgb_bt907;
        EyerLog("=====kkkkkkkkkkkkk=====\n");
        test_rgb_xyz_bt709.PrintInfo();
        EectorF3 test_rgb_bt2020 = (!bt2020_xyz_mat) * test_rgb_xyz_bt709;
        test_rgb_bt2020.PrintInfo();
        EyerLog("=====kkkkkkkkkkkkk=====\n");


        EectorF3 test_rgb_bt907_x(0.0, 0.3, 0.1);
        EectorF3 test_rgb_bt907_y(0.7, 0.0, 0.1);
        EectorF3 test_rgb_bt907_z(0.7, 0.3, 0.0);

        EectorF3 test_rgb_xyz = bt709_xyz_mat * test_rgb_bt907;
        EectorF3 test_rgb_xyz_x = bt709_xyz_mat * test_rgb_bt907_x;
        EectorF3 test_rgb_xyz_y = bt709_xyz_mat * test_rgb_bt907_y;
        EectorF3 test_rgb_xyz_z = bt709_xyz_mat * test_rgb_bt907_z;

        EectorF3 bt2020_test_rgb_xyz = bt2020_xyz_mat * test_rgb_bt907;
        EectorF3 bt2020_test_rgb_xyz_x = bt2020_xyz_mat * test_rgb_bt907_x;
        EectorF3 bt2020_test_rgb_xyz_y = bt2020_xyz_mat * test_rgb_bt907_y;
        EectorF3 bt2020_test_rgb_xyz_z = bt2020_xyz_mat * test_rgb_bt907_z;

        int colorIndex = 24;

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

            // 点画完了，转圈看一眼
            {
                EyerKey key;
                key.frame = 25.0 * fps;
                key.position = EectorF3(5.0, 5.0, 5.0);
                camera->AddKey(key);
            }
            {
                EyerKey key;
                key.frame = 40.0 * fps;
                key.position = EectorF3(-5.0, 5.0, 5.0);
                camera->AddKey(key);
            }
            {
                EyerKey key;
                key.frame = 45.0 * fps;
                key.position = EectorF3(-5.0, 5.0, 5.0);
                camera->AddKey(key);
            }

            // 转完圈，看负轴
            {
                EyerKey key;
                key.frame = 55.0 * fps;
                key.position = EectorF3(0.0, 5.0, 5.0);
                camera->AddKey(key);
            }
            {
                EyerKey key;
                key.frame = 60.0 * fps;
                key.position = EectorF3(0.0, 5.0, 5.0);
                camera->AddKey(key);
            }
            {
                EyerKey key;
                key.frame = 65.0 * fps;
                key.position = EectorF3(0.0, 5.0, 5.0);
                camera->AddKey(key);
            }

            // 看完负轴，创建 XYZ 的新轴
            {
                EyerKey key;
                key.frame = 70.0 * fps;
                key.position = EectorF3(8.0, 8.0, 12.0);
                camera->AddKey(key);
            }
            {
                EyerKey key;
                key.frame = 90.0 * fps;
                key.position = EectorF3(8.0, 8.0, 12.0);
                camera->AddKey(key);
            }

            // 缩小看变换后的 点
            {
                EyerKey key;
                key.frame = 95.0 * fps;
                key.position = EectorF3(8.0, 8.0, 12.0);
                camera->AddKey(key);
            }
            {
                EyerKey key;
                key.frame = 100.0 * fps;
                key.position = EectorF3(8.0, 8.0, 12.0);
                camera->AddKey(key);
            }

            // 看各个轴上，新的 XYZ 都落在第一象限
            {
                EyerKey key;
                key.frame = 105.0 * fps;
                key.position = EectorF3(10.0, 0.0, 10.0);
                camera->AddKey(key);
            }
            {
                EyerKey key;
                key.frame = 110.0 * fps;
                key.position = EectorF3(10.0, 0.0, 10.0);
                camera->AddKey(key);
            }
            {
                EyerKey key;
                key.frame = 115.0 * fps;
                key.position = EectorF3(0.0, 10.0, 10.0);
                camera->AddKey(key);
            }
            {
                EyerKey key;
                key.frame = 120.0 * fps;
                key.position = EectorF3(0.0, 10.0, 10.0);
                camera->AddKey(key);
            }
            {
                EyerKey key;
                key.frame = 125.0 * fps;
                key.position = EectorF3(10.0, 10.0, 0.0);
                camera->AddKey(key);
            }
            {
                EyerKey key;
                key.frame = 130.0 * fps;
                key.position = EectorF3(10.0, 10.0, 0.0);
                camera->AddKey(key);
            }
            {
                EyerKey key;
                key.frame = 135.0 * fps;
                key.position = EectorF3(8.0, 8.0, 8.0);
                camera->AddKey(key);
            }

            // 看 XYZ 的坐标线
            {
                EyerKey key;
                key.frame = 140.0 * fps;
                key.position = EectorF3(8.0, 8.0, 8.0);
                camera->AddKey(key);
            }
            float x = MagicNumber::colour_matching_data[colorIndex][0];
            float y = MagicNumber::colour_matching_data[colorIndex][1];
            float z = MagicNumber::colour_matching_data[colorIndex][2];
            {
                Eyer::EectorF3 rgb(x, y, z);
                Eyer::EectorF3 xyz = rgb_xyz_mat * rgb;
                Eyer::EectorF3 offset(2.0 ,2.0, 2.0);

                EyerKey key;
                key.frame = 145.0 * fps;
                key.cameraTarget = xyz;
                key.position = xyz + offset;
                camera->AddKey(key);
            }

            {
                Eyer::EectorF3 rgb(x, y, z);
                Eyer::EectorF3 xyz = rgb_xyz_mat * rgb;
                Eyer::EectorF3 offset(2.0 ,2.0, 2.0);

                EyerKey key;
                key.frame = 160.0 * fps;
                key.cameraTarget = xyz;
                key.position = xyz + offset;
                camera->AddKey(key);
            }

            {
                Eyer::EectorF3 rgb(x, y, z);
                Eyer::EectorF3 xyz = rgb_xyz_mat * rgb;
                Eyer::EectorF3 offset(2 ,2, 2);

                EyerKey key;
                key.frame = 165.0 * fps;
                key.cameraTarget = xyz;
                key.position = xyz + offset;
                camera->AddKey(key);
            }

            {
                Eyer::EectorF3 rgb(x, y, z);
                Eyer::EectorF3 xyz = rgb_xyz_mat * rgb * 0.0;
                Eyer::EectorF3 offset(2 ,2, 2);

                EyerKey key;
                key.frame = 170.0 * fps;
                key.cameraTarget = xyz;
                key.position = xyz + offset;
                camera->AddKey(key);
            }

            {
                Eyer::EectorF3 rgb(x, y, z);
                Eyer::EectorF3 xyz = rgb_xyz_mat * rgb * 3;
                Eyer::EectorF3 offset(2 ,2, 2);

                EyerKey key;
                key.frame = 180.0 * fps;
                key.cameraTarget = xyz;
                key.position = xyz + offset;
                camera->AddKey(key);
            }
            {
                EyerKey key;
                key.frame = 190.0 * fps;
                key.cameraTarget = EectorF3(0.0, 0.0, 0.0);
                key.position = EectorF3(8.0, 8.0, 8.0);
                camera->AddKey(key);
            }


            {
                EyerKey key;
                key.frame = 195.0 * fps;
                key.cameraTarget = EectorF3(0.0, 0.0, 0.0);
                key.position = EectorF3(8.0, 8.0, 8.0);
                camera->AddKey(key);
            }

            {
                EyerKey key;
                key.frame = 198.0 * fps;
                key.cameraTarget = EectorF3(0.0, 0.0, 0.0);
                key.position = EectorF3(-5.0, 5.0, 5.0);
                camera->AddKey(key);
            }

            {
                EyerKey key;
                key.frame = 212.0 * fps;
                key.cameraTarget = EectorF3(0.0, 0.0, 0.0);
                key.position = EectorF3(-5.0, 5.0, 5.0);
                camera->AddKey(key);
            }

            {
                EyerKey key;
                key.frame = 215.0 * fps;
                key.cameraTarget = EectorF3(0.0, 0.0, 0.0);
                key.position = EectorF3(2.0, 2.0, 2.0);
                camera->AddKey(key);
            }


            {
                EyerKey key;
                key.frame = 250.0 * fps;
                key.cameraTarget = EectorF3(0.0, 0.0, 0.0);
                key.position = EectorF3(2.0, 2.0, 2.0);
                camera->AddKey(key);
            }
            {
                EyerKey key;
                key.frame = 255.0 * fps;
                key.cameraTarget = EectorF3(0.33, 0.33, 0.0);
                key.position = EectorF3(0.33, 0.33, 1.0);
                camera->AddKey(key);
            }

            {
                EyerKey key;
                key.frame = 350 * fps;
                key.cameraTarget = EectorF3(0.33, 0.33, 0.0);
                key.position = EectorF3(0.33, 0.33, 1.0);
                camera->AddKey(key);
            }

            {
                EyerKey key;
                key.frame = 355 * fps;
                key.cameraTarget = EectorF3(0.0, 0.0, 0.0);
                key.position = EectorF3(2.0, 2.0, 2.0);
                camera->AddKey(key);
            }


            {
                EyerKey key;
                key.frame = 370 * fps;
                key.cameraTarget = EectorF3(0.0, 0.0, 0.0);
                key.position = EectorF3(2.0, 2.0, 2.0);
                camera->AddKey(key);
            }

            {
                EyerKey key;
                key.frame = 380 * fps;
                key.cameraTarget = EectorF3(0.0, 0.0, 0.0);
                key.position = EectorF3(0.0, 2.0, 3.4);
                camera->AddKey(key);
            }

            {
                EyerKey key;
                key.frame = 385 * fps;
                key.cameraTarget = EectorF3(0.0, 0.0, 0.0);
                key.position = EectorF3(0.0, 2.0, 3.4);
                camera->AddKey(key);
            }
            {
                EyerKey key;
                key.frame = 395 * fps;
                key.cameraTarget = EectorF3(0.0, 0.0, 0.0);
                key.position = EectorF3(2.0, 2.0, 2.0);
                camera->AddKey(key);
            }
            {
                EyerKey key;
                key.frame = 405 * fps;
                key.cameraTarget = EectorF3(0.0, 0.0, 0.0);
                key.position = EectorF3(3.4, 2.0, 0.0);
                camera->AddKey(key);
            }
            // 看红色
            {
                EyerKey key;
                key.frame = 410 * fps;
                key.cameraTarget = EectorF3(0.0, 0.0, 0.0);
                key.position = EectorF3(3.4, 2.0, 0.0);
                camera->AddKey(key);
            }
            {
                EyerKey key;
                key.frame = 415 * fps;
                key.cameraTarget = EectorF3(0.4124, 0.2126, 0.0193);
                key.position = EectorF3(1.0, 0.1, -1.0);
                camera->AddKey(key);
            }
            // 看绿色
            {
                EyerKey key;
                key.frame = 425 * fps;
                key.cameraTarget = EectorF3(0.4124, 0.2126, 0.0193);
                key.position = EectorF3(1.0, 0.1, -1.0);
                camera->AddKey(key);
            }
            {
                EyerKey key;
                key.frame = 430 * fps;
                key.cameraTarget = EectorF3(0.3576 , 0.7152, 0.1192);
                key.position = EectorF3(0.0, 1.5, 0.0);
                camera->AddKey(key);
            }
            // 看蓝色
            {
                EyerKey key;
                key.frame = 440 * fps;
                key.cameraTarget = EectorF3(0.3576 , 0.7152, 0.1192);
                key.position = EectorF3(0.0, 1.5, 0.0);
                camera->AddKey(key);
            }
            {
                EyerKey key;
                key.frame = 445 * fps;
                key.cameraTarget = EectorF3(0.1805 , 0.0722, 0.9505);
                key.position = EectorF3(0, 0, 2);
                camera->AddKey(key);
            }
            {
                EyerKey key;
                key.frame = 460 * fps;
                key.cameraTarget = EectorF3(0.1805 , 0.0722, 0.9505);
                key.position = EectorF3(0, 0, 2);
                camera->AddKey(key);
            }
            {
                EyerKey key;
                key.frame = 465 * fps;
                key.cameraTarget = EectorF3(0.0, 0.0, 0.0);
                key.position = EectorF3(1.5, 1.5, 1.5);
                camera->AddKey(key);
            }
            {
                EyerKey key;
                key.frame = 495 * fps;
                key.cameraTarget = EectorF3(0.0, 0.0, 0.0);
                key.position = EectorF3(1.5, 1.5, 1.5);
                camera->AddKey(key);
            }
            {
                EyerKey key;
                key.frame = 500 * fps;
                key.cameraTarget = EectorF3(0.0, 0.0, 0.0);
                key.position = EectorF3(-1.5, 1.5, 1.5);
                camera->AddKey(key);
            }
            {
                EyerKey key;
                key.frame = 510 * fps;
                key.cameraTarget = EectorF3(0.0, 0.0, 0.0);
                key.position = EectorF3(-1.5, 1.5, 1.5);
                camera->AddKey(key);
            }
            {
                EyerKey key;
                key.frame = 515 * fps;
                key.cameraTarget = EectorF3(0.0, 0.0, 0.0);
                key.position = EectorF3(1.5, 1.5, 1.5);
                camera->AddKey(key);
            }
            {
                EyerKey key;
                key.frame = 530 * fps;
                key.cameraTarget = EectorF3(0.0, 0.0, 0.0);
                key.position = EectorF3(1.5, 1.5, 1.5);
                camera->AddKey(key);
            }
            {
                EyerKey key;
                key.frame = 535 * fps;
                key.cameraTarget = EectorF3(0.333, 0.333, 0.0);
                key.position = EectorF3(0.333, 0.333, 1.5);
                camera->AddKey(key);
            }
            {
                EyerKey key;
                key.frame = 560 * fps;
                key.cameraTarget = EectorF3(0.333, 0.333, 0.0);
                key.position = EectorF3(0.333, 0.333, 1.5);
                camera->AddKey(key);
            }
            {
                EyerKey key;
                key.frame = 565 * fps;
                key.cameraTarget = EectorF3(0.0, 0.0, 0.0);
                key.position = EectorF3(1, 2, 2);
                camera->AddKey(key);
            }

            {
                EyerKey key;
                key.frame = 570 * fps;
                key.cameraTarget = EectorF3(0.0, 0.0, 0.0);
                key.position = EectorF3(1, 2, 2);
                camera->AddKey(key);
            }

            {
                EyerKey key;
                key.frame = 580 * fps;
                key.cameraTarget = EectorF3(0.0, 0.0, 0.0);
                key.position = EectorF3(1, 2, 2);
                camera->AddKey(key);
            }

            {
                EyerKey key;
                key.frame = 590 * fps;
                key.cameraTarget = test_rgb_xyz;
                key.position = EectorF3(1.5, 0.5, 0.8);
                camera->AddKey(key);
            }

            {
                EyerKey key;
                key.frame = 600 * fps;
                key.cameraTarget = test_rgb_xyz;
                key.position = EectorF3(1.5, 0.5, 0.8);
                camera->AddKey(key);
            }

            {
                EyerKey key;
                key.frame = 610 * fps;
                key.cameraTarget = test_rgb_xyz;
                key.position = EectorF3(-0.5, 0.5, 2);
                camera->AddKey(key);
            }

            {
                EyerKey key;
                key.frame = 620 * fps;
                key.cameraTarget = test_rgb_xyz;
                key.position = EectorF3(-0.5, 0.5, 2);
                camera->AddKey(key);
            }

            {
                EyerKey key;
                key.frame = 630 * fps;
                key.cameraTarget = test_rgb_xyz;
                key.position = EectorF3(0.2, 2, 0.2);
                camera->AddKey(key);
            }
            {
                EyerKey key;
                key.frame = 640 * fps;
                key.cameraTarget = test_rgb_xyz;
                key.position = EectorF3(0.2, 2, 0.2);
                camera->AddKey(key);
            }

            {
                EyerKey key;
                key.frame = 650 * fps;
                key.cameraTarget = test_rgb_xyz;
                key.position = EectorF3(2, 2, 2);
                camera->AddKey(key);
            }

            {
                EyerKey key;
                key.frame = 690 * fps;
                key.cameraTarget = test_rgb_xyz;
                key.position = EectorF3(2, 2, 2);
                camera->AddKey(key);
            }

            {
                EyerKey key;
                key.frame = 700 * fps;
                key.cameraTarget = test_rgb_xyz;
                key.position = EectorF3(2, 0.5, 1);
                camera->AddKey(key);
            }

            {
                EyerKey key;
                key.frame = 710 * fps;
                key.cameraTarget = test_rgb_xyz;
                key.position = EectorF3(2, 0.5, 1);
                camera->AddKey(key);
            }

            {
                EyerKey key;
                key.frame = 720 * fps;
                key.cameraTarget = test_rgb_xyz;
                key.position = EectorF3(0.5, 0.5, 2);
                camera->AddKey(key);
            }

            {
                EyerKey key;
                key.frame = 730 * fps;
                key.cameraTarget = test_rgb_xyz;
                key.position = EectorF3(0.5, 0.5, 2);
                camera->AddKey(key);
            }
            {
                EyerKey key;
                key.frame = 740 * fps;
                key.cameraTarget = test_rgb_xyz;
                key.position = EectorF3(0.5, 2, 0.5);
                camera->AddKey(key);
            }

            {
                EyerKey key;
                key.frame = 750 * fps;
                key.cameraTarget = test_rgb_xyz;
                key.position = EectorF3(0.5, 2, 0.5);
                camera->AddKey(key);
            }

            {
                EyerKey key;
                key.frame = 760 * fps;
                key.cameraTarget = test_rgb_xyz;
                key.position = EectorF3(1.5, 1.5, 1.5);
                camera->AddKey(key);
            }

            {
                EyerKey key;
                key.frame = endFrame;
                key.cameraTarget = test_rgb_xyz;
                key.position = EectorF3(1.5, 1.5, 1.5);
                camera->AddKey(key);
            }

            scene.SetCamera(camera);
        }

        {
            EyerKey baseKey;
            baseKey.position = test_rgb_xyz;
            baseKey.rotato = EectorF4(1.0, 0.0, 0.0, 0.0);
            baseKey.scale = EectorF3(0.03, 0.03, 0.03);
            baseKey.color = EectorF4(1.0, 1.0, 1.0, 1.0);

            SphereSpirit * p = new SphereSpirit();
            {
                EyerKey key = baseKey;
                key.frame = 780 * fps;
                p->AddKey(key);
            }
            {
                EyerKey key = baseKey;
                key.frame = endFrame;
                p->AddKey(key);
            }
            scene.AddSpirit(p);
        }
        {
            EyerKey baseKey;
            baseKey.position = EectorF3(0, 0, 0);
            baseKey.rotato = EectorF4(1.0, 0.0, 0.0, 0.0);
            baseKey.scale = EectorF3(1.0, 1.0, 1.0);
            baseKey.color = EectorF4(1.0, 1.0, 1.0, 1.0);

            EectorF3 test_rgb_xyzA = test_rgb_xyz;
            test_rgb_xyzA.SetX(0);
            EectorF3 test_rgb_xyzB = test_rgb_xyz;
            test_rgb_xyzB.SetY(0);
            EectorF3 test_rgb_xyzC = test_rgb_xyz;
            test_rgb_xyzC.SetZ(0);

            MVPLineSpirit * line1 = new MVPLineSpirit(test_rgb_xyz, test_rgb_xyzA);
            MVPLineSpirit * line2 = new MVPLineSpirit(test_rgb_xyz, test_rgb_xyzB);
            MVPLineSpirit * line3 = new MVPLineSpirit(test_rgb_xyz, test_rgb_xyzC);

            {
                EyerKey key = baseKey;
                key.frame = 780 * fps;
                line1->AddKey(key);
                line2->AddKey(key);
                line3->AddKey(key);
            }
            {
                EyerKey key = baseKey;
                key.frame = 790 * fps;
                line1->AddKey(key);
                line2->AddKey(key);
                line3->AddKey(key);
            }
            scene.AddSpirit(line1);
            scene.AddSpirit(line2);
            scene.AddSpirit(line3);
        }


        {
            EyerKey baseKey;
            baseKey.position = EectorF3(0, 0, 0);
            baseKey.rotato = EectorF4(1.0, 0.0, 0.0, 0.0);
            baseKey.scale = EectorF3(1.0, 1.0, 1.0);
            baseKey.color = EectorF4(1.0, 1.0, 1.0, 1.0);
////////////////////////
            EectorF3 test_rgb_bt2020_x = test_rgb_bt2020;
            test_rgb_bt2020_x.SetX(0.0);
            EectorF3 test_rgb_bt2020_y = test_rgb_bt2020;
            test_rgb_bt2020_y.SetY(0.0);
            EectorF3 test_rgb_bt2020_z = test_rgb_bt2020;
            test_rgb_bt2020_z.SetZ(0.0);

            MVPLineSpirit * line1 = new MVPLineSpirit(bt2020_xyz_mat * test_rgb_bt2020, bt2020_xyz_mat * test_rgb_bt2020_x);
            MVPLineSpirit * line2 = new MVPLineSpirit(bt2020_xyz_mat * test_rgb_bt2020, bt2020_xyz_mat * test_rgb_bt2020_y);
            MVPLineSpirit * line3 = new MVPLineSpirit(bt2020_xyz_mat * test_rgb_bt2020, bt2020_xyz_mat * test_rgb_bt2020_z);

            {
                EyerKey key = baseKey;
                key.frame = 790 * fps;
                line1->AddKey(key);
                line2->AddKey(key);
                line3->AddKey(key);
            }
            {
                EyerKey key = baseKey;
                key.frame = endFrame;
                line1->AddKey(key);
                line2->AddKey(key);
                line3->AddKey(key);
            }
            scene.AddSpirit(line1);
            scene.AddSpirit(line2);
            scene.AddSpirit(line3);
        }


        {
            EyerKey baseKey;
            baseKey.position = test_rgb_xyz;
            baseKey.rotato = EectorF4(1.0, 0.0, 0.0, 0.0);
            baseKey.scale = EectorF3(0.03, 0.03, 0.03);
            baseKey.color = EectorF4(1.0, 1.0, 1.0, 1.0);

            SphereSpirit * p = new SphereSpirit();
            MVPLineSpirit * lineX = new MVPLineSpirit(test_rgb_xyz, test_rgb_xyz_x);
            MVPLineSpirit * lineY = new MVPLineSpirit(test_rgb_xyz, test_rgb_xyz_y);
            MVPLineSpirit * lineZ = new MVPLineSpirit(test_rgb_xyz, test_rgb_xyz_z);
            {
                EyerKey key = baseKey;
                key.frame = 580.0 * fps;
                p->AddKey(key);
                key.position = EectorF3(0.0, 0.0, 0.0);
                key.scale = EectorF3(1.0, 1.0, 1.0);

                lineX->AddKey(key);
                lineY->AddKey(key);
                lineZ->AddKey(key);
            }
            {
                EyerKey key = baseKey;
                key.frame = 780 * fps;
                p->AddKey(key);
                key.position = EectorF3(0.0, 0.0, 0.0);
                key.scale = EectorF3(1.0, 1.0, 1.0);

                lineX->AddKey(key);
                lineY->AddKey(key);
                lineZ->AddKey(key);
            }
            scene.AddSpirit(p);
            scene.AddSpirit(lineX);
            scene.AddSpirit(lineY);
            scene.AddSpirit(lineZ);
        }


        {
            EyerKey baseKey;
            baseKey.position = bt2020_test_rgb_xyz;
            baseKey.rotato = EectorF4(1.0, 0.0, 0.0, 0.0);
            baseKey.scale = EectorF3(0.03, 0.03, 0.03);
            baseKey.color = EectorF4(1.0, 1.0, 1.0, 1.0);

            SphereSpirit * p = new SphereSpirit();
            MVPLineSpirit * lineX = new MVPLineSpirit(bt2020_test_rgb_xyz, bt2020_test_rgb_xyz_x);
            MVPLineSpirit * lineY = new MVPLineSpirit(bt2020_test_rgb_xyz, bt2020_test_rgb_xyz_y);
            MVPLineSpirit * lineZ = new MVPLineSpirit(bt2020_test_rgb_xyz, bt2020_test_rgb_xyz_z);
            {
                EyerKey key = baseKey;
                key.frame = 680.0 * fps;
                p->AddKey(key);
                key.position = EectorF3(0.0, 0.0, 0.0);
                key.scale = EectorF3(1.0, 1.0, 1.0);

                lineX->AddKey(key);
                lineY->AddKey(key);
                lineZ->AddKey(key);
            }
            {
                EyerKey key = baseKey;
                key.frame = 770 * fps;
                p->AddKey(key);
                key.position = EectorF3(0.0, 0.0, 0.0);
                key.scale = EectorF3(1.0, 1.0, 1.0);

                lineX->AddKey(key);
                lineY->AddKey(key);
                lineZ->AddKey(key);
            }
            scene.AddSpirit(p);
            scene.AddSpirit(lineX);
            scene.AddSpirit(lineY);
            scene.AddSpirit(lineZ);
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
                key.frame = 80.0 * fps;
                key.color = EectorF4(1.0, 1.0, 1.0, 1.0);
                key.scale = EectorF3(1000.0, 1000.0, 1000.0);
                RGB_COOR->AddKey(key);
            }
            {
                EyerKey key;
                key.frame = 85.0 * fps;
                key.color = EectorF4(0.0, 0.0, 0.0, 0.0);
                key.scale = EectorF3(1000.0, 1000.0, 1000.0);
                RGB_COOR->AddKey(key);
            }
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
                key.frame = 75.0 * fps;
                key.scale = EectorF3(0.2, 0.2, 0.2);
                R->AddKey(key);
            }
            {
                EyerKey key = baseKey;
                key.frame = 80.0 * fps;
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
                key.frame = 75.0 * fps;
                key.scale = EectorF3(0.2, 0.2, 0.2);
                G->AddKey(key);
            }
            {
                EyerKey key = baseKey;
                key.frame = 80.0 * fps;
                key.scale = EectorF3(0, 0, 0);
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
                key.frame = 75.0 * fps;
                key.scale = EectorF3(0.2, 0.2, 0.2);
                B->AddKey(key);
            }
            {
                EyerKey key = baseKey;
                key.frame = 80.0 * fps;
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
                    key.frame = 55 * fps;
                    key.position = rgb;
                    key.color = GetColor(i);
                    ss->AddKey(key);
                }
                {
                    EyerKey key = baseKey;
                    key.frame = 56 * fps;
                    key.position = rgb;
                    key.color = GetColor(i);
                    key.color.SetW(0.0);
                    ss->AddKey(key);
                }
                {
                    EyerKey key = baseKey;
                    key.frame = 57 * fps;
                    key.position = rgb;
                    key.color = GetColor(i);
                    ss->AddKey(key);
                }
                {
                    EyerKey key = baseKey;
                    key.frame = 58 * fps;
                    key.position = rgb;
                    key.color = GetColor(i);
                    key.color.SetW(0.0);
                    ss->AddKey(key);
                }
                {
                    EyerKey key = baseKey;
                    key.frame = 59 * fps;
                    key.position = rgb;
                    key.color = GetColor(i);
                    ss->AddKey(key);
                }
                {
                    EyerKey key = baseKey;
                    key.frame = 60 * fps;
                    key.position = rgb;
                    key.color = GetColor(i);
                    ss->AddKey(key);
                }

                {
                    EyerKey key = baseKey;
                    key.frame = 75 * fps;;
                    key.position = rgb;
                    key.color = GetColor(i);
                    ss->AddKey(key);
                }
                {
                    EyerKey key = baseKey;
                    key.frame = 80 * fps;;
                    key.position = rgb;
                    key.color = GetColor(i);
                    ss->AddKey(key);
                }
                {
                    EyerKey key = baseKey;
                    key.frame = 85 * fps;;
                    key.position = xyz;
                    key.color = GetColor(i);
                    ss->AddKey(key);
                }
                {
                    EyerKey key = baseKey;
                    key.frame = 95 * fps;
                    key.position = xyz;
                    key.color = GetColor(i);
                    float scale = 0.05;
                    key.scale = EectorF3(scale, scale, scale);
                    ss->AddKey(key);
                }
                {
                    EyerKey key = baseKey;
                    key.frame = 100 * fps;
                    key.position = xyz;
                    key.color = GetColor(i);
                    float scale = 0.05;
                    key.scale = EectorF3(scale, scale, scale);
                    ss->AddKey(key);
                }

                {
                    EyerKey key = baseKey;
                    key.frame = 200 * fps;
                    key.position = xyz;
                    key.color = GetColor(i);
                    float scale = 0.05;
                    key.scale = EectorF3(scale, scale, scale);
                    ss->AddKey(key);
                }

                {
                    EyerKey key = baseKey;
                    key.frame = 210 * fps;
                    key.position = xyz_norm;
                    key.color = GetColor(i);
                    float scale = 0.05;
                    key.scale = EectorF3(scale, scale, scale);
                    ss->AddKey(key);
                }

                {
                    EyerKey key = baseKey;
                    key.frame = 215 * fps;
                    key.position = xyz_norm;
                    key.color = GetColor(i);
                    float scale = 0.015;
                    key.scale = EectorF3(scale, scale, scale);
                    ss->AddKey(key);
                }

                {
                    EyerKey key = baseKey;
                    key.frame = 235 * fps;
                    key.position = xyz_norm;
                    key.color = GetColor(i);
                    float scale = 0.015;
                    key.scale = EectorF3(scale, scale, scale);
                    ss->AddKey(key);
                }

                {
                    EyerKey key = baseKey;
                    key.frame = 240 * fps;
                    key.position = xyz_norm_xy;
                    key.color = GetColor(i);
                    float scale = 0.015;
                    key.scale = EectorF3(scale, scale, scale);
                    ss->AddKey(key);
                }

                {
                    EyerKey key = baseKey;
                    key.frame = 350 * fps;
                    key.position = xyz_norm_xy;
                    key.color = GetColor(i);
                    key.color.SetW(1.0);
                    float scale = 0.015;
                    key.scale = EectorF3(scale, scale, scale);
                    ss->AddKey(key);
                }
                {
                    EyerKey key = baseKey;
                    key.frame = 355 * fps;
                    key.position = xyz_norm_xy;
                    key.color = GetColor(i);
                    key.color.SetW(0.0);
                    float scale = 0.015;
                    key.scale = EectorF3(scale, scale, scale);
                    ss->AddKey(key);
                }

                {
                    EyerKey key = baseKey;
                    key.frame = 535 * fps;
                    key.position = xyz_norm_xy;
                    key.color = GetColor(i);
                    key.color.SetW(0.0);
                    float scale = 0.015;
                    key.scale = EectorF3(scale, scale, scale);
                    ss->AddKey(key);
                }
                {
                    EyerKey key = baseKey;
                    key.frame = 540 * fps;
                    key.position = xyz_norm_xy;
                    key.color = GetColor(i);
                    key.color.SetW(1.0);
                    float scale = 0.015;
                    key.scale = EectorF3(scale, scale, scale);
                    ss->AddKey(key);
                }

                {
                    EyerKey key = baseKey;
                    key.frame = 550 * fps;
                    key.position = xyz_norm_xy;
                    key.color = GetColor(i);
                    key.color.SetW(0.0);
                    float scale = 0.015;
                    key.scale = EectorF3(scale, scale, scale);
                    ss->AddKey(key);
                }

                scene.AddSpirit(ss);


                Eyer::EectorF3 start(0.0, 0.0, 0.0);
                MVPLineSpirit * lineSpirit = new MVPLineSpirit(start, xyz * 10);
                {
                    EyerKey key = baseKey;
                    key.frame = 190 * fps;;
                    key.color = GetColor(i);
                    key.color.SetW(0.0);
                    float scale = 1.0;
                    key.scale = EectorF3(scale, scale, scale);
                    lineSpirit->AddKey(key);
                }
                {
                    EyerKey key = baseKey;
                    key.frame = 195 * fps;
                    key.color = GetColor(i);
                    key.color.SetW(0.5);
                    float scale = 1.0;
                    key.scale = EectorF3(scale, scale, scale);
                    lineSpirit->AddKey(key);
                }
                {
                    EyerKey key = baseKey;
                    key.frame = 215 * fps;
                    key.color = GetColor(i);
                    float scale = 1.0;
                    key.scale = EectorF3(scale, scale, scale);
                    lineSpirit->AddKey(key);
                }
                {
                    EyerKey key = baseKey;
                    key.frame = 220 * fps;
                    key.color = GetColor(i);
                    key.color.SetW(0.0);
                    float scale = 1.0;
                    key.scale = EectorF3(scale, scale, scale);
                    lineSpirit->AddKey(key);
                }
                scene.AddSpirit(lineSpirit);

                MVPLineSpirit * lineSpirit2 = new MVPLineSpirit(xyz_norm, xyz_norm_xy);
                {
                    EyerKey key = baseKey;
                    key.frame = 230 * fps;
                    key.color = GetColor(i);
                    key.color.SetW(0.0);
                    float scale = 1.0;
                    key.scale = EectorF3(scale, scale, scale);
                    lineSpirit2->AddKey(key);
                }
                {
                    EyerKey key = baseKey;
                    key.frame = 233 * fps;
                    key.color = GetColor(i);
                    float scale = 1.0;
                    key.scale = EectorF3(scale, scale, scale);
                    lineSpirit2->AddKey(key);
                }
                {
                    EyerKey key = baseKey;
                    key.frame = 242 * fps;
                    key.color = GetColor(i);
                    float scale = 1.0;
                    key.scale = EectorF3(scale, scale, scale);
                    lineSpirit2->AddKey(key);
                }
                {
                    EyerKey key = baseKey;
                    key.frame = 245 * fps;
                    key.color = GetColor(i);
                    key.color.SetW(0.0f);
                    float scale = 1.0;
                    key.scale = EectorF3(scale, scale, scale);
                    lineSpirit2->AddKey(key);
                }
                scene.AddSpirit(lineSpirit2);
            }
        }


        for(int i=0;i<3;i++)
        {
            float x = MagicNumber::colour_matching_data[colorIndex][0];
            float y = MagicNumber::colour_matching_data[colorIndex][1];
            float z = MagicNumber::colour_matching_data[colorIndex][2];

            Eyer::EectorF3 rgb(x, y, z);

            Eyer::EectorF3 xyz = rgb_xyz_mat * rgb;
            Eyer::EectorF3 start = xyz;
            Eyer::EectorF3 end = start;
            if(i == 0){
                end.SetX(0);
            }
            if(i == 1){
                end.SetY(0);
            }
            if(i == 2){
                end.SetZ(0);
            }

            MVPLineSpirit * lineSpirit = new MVPLineSpirit(start, end);

            EyerKey baseKey;
            baseKey.position = EectorF3(0, 0, 0);
            baseKey.rotato = EectorF4(1.0, 0.0, 0.0, 0.0);
            float scale = 1.0;
            baseKey.scale = EectorF3(scale, scale, scale);
            baseKey.color = EectorF4(1.0, 1.0, 1.0, 1.0);
            {
                EyerKey key = baseKey;
                key.frame = 140 * fps;
                lineSpirit->AddKey(key);
            }
            {
                EyerKey key = baseKey;
                key.frame = 145 * fps;
                lineSpirit->AddKey(key);
            }
            {
                EyerKey key = baseKey;
                key.frame = 146 * fps;
                key.color.SetW(0.1);
                lineSpirit->AddKey(key);
            }
            {
                EyerKey key = baseKey;
                key.frame = 147 * fps;
                key.color.SetW(1.0);
                lineSpirit->AddKey(key);
            }
            {
                EyerKey key = baseKey;
                key.frame = 148 * fps;
                key.color.SetW(0.1);
                lineSpirit->AddKey(key);
            }
            {
                EyerKey key = baseKey;
                key.frame = 149 * fps;
                key.color.SetW(1.0);
                lineSpirit->AddKey(key);
            }
            {
                EyerKey key = baseKey;
                key.frame = 150 * fps;
                lineSpirit->AddKey(key);
            }
            {
                EyerKey key = baseKey;
                key.frame = 155 * fps;
                lineSpirit->AddKey(key);
            }
            {
                EyerKey key = baseKey;
                key.frame = 185 * fps;
                key.color.SetW(1.0);
                lineSpirit->AddKey(key);
            }
            {
                EyerKey key = baseKey;
                key.frame = 190 * fps;
                key.color.SetW(0.0);
                lineSpirit->AddKey(key);
            }

            scene.AddSpirit(lineSpirit);
        }


        {
            float x = MagicNumber::colour_matching_data[colorIndex][0];
            float y = MagicNumber::colour_matching_data[colorIndex][1];
            float z = MagicNumber::colour_matching_data[colorIndex][2];

            Eyer::EectorF3 rgb(x, y, z);

            Eyer::EectorF3 xyz = rgb_xyz_mat * rgb;
            Eyer::EectorF3 start = xyz * 10;
            Eyer::EectorF3 end = EectorF3(0.0, 0.0, 0.0);

            MVPLineSpirit * lineSpirit = new MVPLineSpirit(start, end);

            EyerKey baseKey;
            baseKey.position = EectorF3(0, 0, 0);
            baseKey.rotato = EectorF4(1.0, 0.0, 0.0, 0.0);
            float scale = 1.0;
            baseKey.scale = EectorF3(scale, scale, scale);
            baseKey.color = GetColor(colorIndex);
            {
                EyerKey key = baseKey;
                key.frame = 160 * fps;
                key.color.SetW(0.0);
                lineSpirit->AddKey(key);
            }
            {
                EyerKey key = baseKey;
                key.frame = 165 * fps;
                key.color.SetW(1.0);
                lineSpirit->AddKey(key);
            }
            {
                EyerKey key = baseKey;
                key.frame = 190 * fps;
                lineSpirit->AddKey(key);
            }
            {
                EyerKey key = baseKey;
                key.frame = 195 * fps;
                key.color.SetW(0.0);
                lineSpirit->AddKey(key);
            }

            scene.AddSpirit(lineSpirit);
        }


        EectorF4 xyzColor(1.0, 1.0, 0.2, 1.0);
        EectorF3 xPosA(0.4185, -0.0912, 0.0009);
        EectorF3 yPosA(-0.1587, 0.2524, -0.0025);
        EectorF3 zPosA(-0.0828, 0.0157, 0.1786);

        EectorF3 xPosB(1, 0, 0);
        EectorF3 yPosB(0, 1, 0);
        EectorF3 zPosB(0, 0, 1);

        for(int i=0;i<3;i++){
            MVPCoorLineSpirit * coor = nullptr;
            EectorF3 posA;
            EectorF3 posB;
            if(i == 0){
                posA = xPosA;
                posB = xPosB;
                coor = X;
            }
            if(i == 1){
                posA = yPosA;
                posB = yPosB;
                coor = Y;
            }
            if(i == 2){
                posA = zPosA;
                posB = zPosB;
                coor = Z;
            }

            EyerKey baseKey;
            baseKey.position = EectorF3(1, 3, 0);
            baseKey.rotato = EectorF4(1.0, 0.0, 0.0, 0.0);
            float scale = 1.0;
            baseKey.scale = EectorF3(scale, scale, scale);
            baseKey.color = xyzColor;
            coor = new MVPCoorLineSpirit();
            {
                float scale = 0.0;
                EyerKey key = baseKey;
                key.frame = 70.0 * fps;
                key.scale = EectorF3(scale, scale, scale);
                key.position = posA;
                coor->AddKey(key);
            }
            {
                float scale = 100.0;
                EyerKey key = baseKey;
                key.frame = 75.0 * fps;
                key.scale = EectorF3(scale, scale, scale);
                key.position = posA;
                coor->AddKey(key);
            }
            {
                float scale = 100.0;
                EyerKey key = baseKey;
                key.frame = 80.0 * fps;
                key.scale = EectorF3(scale, scale, scale);
                key.position = posA;
                coor->AddKey(key);
            }
            {
                float scale = 100.0;
                EyerKey key = baseKey;
                key.frame = 85.0 * fps;
                key.scale = EectorF3(scale, scale, scale);
                key.position = posB;
                coor->AddKey(key);
            }
            {
                float scale = 100.0;
                EyerKey key = baseKey;
                key.frame = endFrame;
                key.scale = EectorF3(scale, scale, scale);
                key.position = posB;
                coor->AddKey(key);
            }
            scene.AddSpirit(coor);
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
                key.frame = 220.0 * fps;
                key.color = EectorF4(1.0, 1.0, 1.0, 0.0);
                normalizePlaneSpirit->AddKey(key);
            }
            {
                EyerKey key = baseKey;
                key.frame = 225.0 * fps;
                normalizePlaneSpirit->AddKey(key);
            }

            {
                EyerKey key = baseKey;
                key.frame = 230.0 * fps;
                key.color = EectorF4(1.0, 1.0, 1.0, 0.2);
                normalizePlaneSpirit->AddKey(key);
            }
            {
                EyerKey key = baseKey;
                key.frame = 248.0 * fps;
                key.color = EectorF4(1.0, 1.0, 1.0, 0.2);
                normalizePlaneSpirit->AddKey(key);
            }
            {
                EyerKey key = baseKey;
                key.frame = 250.0 * fps;
                key.color = EectorF4(1.0, 1.0, 1.0, 0.0);
                key.scale = EectorF3(0.0, 0.0, 0.0);
                normalizePlaneSpirit->AddKey(key);
            }

            {
                EyerKey key = baseKey;
                key.frame = 480.0 * fps;
                key.color = EectorF4(1.0, 1.0, 1.0, 0.0);
                key.scale = EectorF3(0.0, 0.0, 0.0);
                normalizePlaneSpirit->AddKey(key);
            }
            {
                EyerKey key = baseKey;
                key.frame = 490.0 * fps;
                key.color = EectorF4(1.0, 1.0, 1.0, 0.2);
                key.scale = EectorF3(1.0, 1.0, 1.0);
                normalizePlaneSpirit->AddKey(key);
            }

            {
                EyerKey key = baseKey;
                key.frame = 520.0 * fps;
                key.color = EectorF4(1.0, 1.0, 1.0, 0.2);
                key.scale = EectorF3(1.0, 1.0, 1.0);
                normalizePlaneSpirit->AddKey(key);
            }

            {
                EyerKey key = baseKey;
                key.frame = 525.0 * fps;
                key.color = EectorF4(1.0, 1.0, 1.0, 0.0);
                key.scale = EectorF3(1.0, 1.0, 1.0);
                normalizePlaneSpirit->AddKey(key);
            }

            scene.AddSpirit(normalizePlaneSpirit);
        }

        {
            float vertex[49 * 3] = {};
            float coor[49 * 3] = {};
            unsigned int vertexIndex[49 * 3] = {};
            for(int i=0;i<48;i++) {
                vertexIndex[i * 3 + 0] = i;
                vertexIndex[i * 3 + 1] = i + 1;
                vertexIndex[i * 3 + 2] = 48;
            }

            vertexIndex[48 * 3 + 0] = 0;
            vertexIndex[48 * 3 + 1] = 47;
            vertexIndex[48 * 3 + 2] = 48;

            for(int i=0;i<48;i++) {
                float x = MagicNumber::colour_matching_data[i][0];
                float y = MagicNumber::colour_matching_data[i][1];
                float z = MagicNumber::colour_matching_data[i][2];

                Eyer::EectorF3 rgb(x, y, z);

                float xyz_rgb[] = {
                        2.7688, 1.7517, 1.1301,
                        1.0000, 4.5906, 0.0601,
                        0, 0.0565, 5.5942
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

                vertex[i * 3 + 0] = xyz_norm_xy.x();
                vertex[i * 3 + 1] = xyz_norm_xy.y();
                vertex[i * 3 + 2] = xyz_norm_xy.z();

                EectorF4 color = GetColor(i);
                coor[i * 3 + 0] = color.x();
                coor[i * 3 + 1] = color.y();
                coor[i * 3 + 2] = color.z();
            }
            vertex[48 * 3 + 0] = 0.33;
            vertex[48 * 3 + 1] = 0.33;
            vertex[48 * 3 + 2] = 0.0;

            coor[48 * 3 + 0] = 1.0;
            coor[48 * 3 + 1] = 1.0;
            coor[48 * 3 + 2] = 1.0;

            coloPlane = new MVPCustomSpirit((float *)vertex, sizeof(vertex), (float *)coor, sizeof(coor), (unsigned int *)vertexIndex, sizeof(vertexIndex));

            EyerKey baseKey;
            baseKey.position = EectorF3(0, 0, 0);
            baseKey.rotato = EectorF4(1.0, 0.0, 0.0, 0.0);
            float scale = 1.0;
            baseKey.scale = EectorF3(scale, scale, scale);
            baseKey.color = EectorF4(1.0, 1.0, 1.0, 1.0);

            {
                EyerKey key = baseKey;
                key.frame = 300.0 * fps;
                key.color.SetW(0.0);
                coloPlane->AddKey(key);
            }
            {
                EyerKey key = baseKey;
                key.frame = 305.0 * fps;
                coloPlane->AddKey(key);
            }

            {
                EyerKey key = baseKey;
                key.frame = 350.0 * fps;
                coloPlane->AddKey(key);
            }
            {
                EyerKey key = baseKey;
                key.frame = 355.0 * fps;
                key.color.SetW(0.0);
                coloPlane->AddKey(key);
            }

            {
                EyerKey key = baseKey;
                key.frame = 535.0 * fps;
                key.color.SetW(0.0);
                coloPlane->AddKey(key);
            }
            {
                EyerKey key = baseKey;
                key.frame = 540.0 * fps;
                key.color.SetW(1.0);
                coloPlane->AddKey(key);
            }
            {
                EyerKey key = baseKey;
                key.frame = 545.0 * fps;
                key.color.SetW(1.0);
                coloPlane->AddKey(key);
            }
            {
                EyerKey key = baseKey;
                key.frame = 550.0 * fps;
                key.color.SetW(0.0);
                coloPlane->AddKey(key);
            }
            scene.AddSpirit(coloPlane);
        }

        Eyer::EectorF3 bt709_red(1.0, 0.0, 0.0);
        Eyer::EectorF3 bt709_green(0.0, 1.0, 0.0);
        Eyer::EectorF3 bt709_blue(0.0, 0.0, 1.0);

        Eyer::EectorF3 bt709_red_xyz = bt709_xyz_mat * bt709_red;
        Eyer::EectorF3 bt709_green_xyz = bt709_xyz_mat * bt709_green;
        Eyer::EectorF3 bt709_blue_xyz = bt709_xyz_mat * bt709_blue;

        float a = bt709_red_xyz.x() + bt709_red_xyz.y() + bt709_red_xyz.z();
        bt709_red_xyz = bt709_red_xyz * (1.0 / a);
        bt709_red_xyz.PrintInfo();

        a = bt709_green_xyz.x() + bt709_green_xyz.y() + bt709_green_xyz.z();
        bt709_green_xyz = bt709_green_xyz * (1.0 / a);
        bt709_green_xyz.PrintInfo();

        a = bt709_blue_xyz.x() + bt709_blue_xyz.y() + bt709_blue_xyz.z();
        bt709_blue_xyz = bt709_blue_xyz * (1.0 / a);
        bt709_blue_xyz.PrintInfo();

        EyerKey baseKey;
        baseKey.position = EectorF3(0, 0, 0);
        baseKey.rotato = EectorF4(1.0, 0.0, 0.0, 0.0);
        float scale = 0.024;
        baseKey.scale = EectorF3(scale, scale, scale);
        baseKey.color = EectorF4(1.0, 1.0, 1.0, 1.0);

        {
            SphereSpirit * red = new SphereSpirit();
            {
                EyerKey key = baseKey;
                key.frame = 310.0 * fps;
                key.position = bt709_red_xyz;
                key.position.SetZ(0.01);
                red->AddKey(key);
            }
            {
                EyerKey key = baseKey;
                key.frame = 350 * fps;
                key.position = bt709_red_xyz;
                key.position.SetZ(0.01);
                // key.color = EectorF4(1.0, 0.0, 0.0, 1.0);
                red->AddKey(key);
            }
            scene.AddSpirit(red);
        }

        {
            SphereSpirit * green = new SphereSpirit();
            {
                EyerKey key = baseKey;
                key.frame = 315.0 * fps;
                key.position = bt709_green_xyz;
                key.position.SetZ(0.01);
                green->AddKey(key);
            }
            {
                EyerKey key = baseKey;
                key.frame = 350 * fps;
                key.position = bt709_green_xyz;
                key.position.SetZ(0.01);
                // key.color = EectorF4(0.0, 1.0, 0.0, 1.0);
                green->AddKey(key);
            }
            scene.AddSpirit(green);
        }
        {
            SphereSpirit * blue = new SphereSpirit();
            {
                EyerKey key = baseKey;
                key.frame = 320.0 * fps;
                key.position = bt709_blue_xyz;
                key.position.SetZ(0.01);
                blue->AddKey(key);
            }
            {
                EyerKey key = baseKey;
                key.frame = 350 * fps;
                key.position = bt709_blue_xyz;
                key.position.SetZ(0.01);
                // key.color = EectorF4(0.0, 0.0, 1.0, 1.0);
                blue->AddKey(key);
            }
            scene.AddSpirit(blue);
        }


        {
            Eyer::EectorF3 a = bt709_red_xyz;
            a.SetZ(0.01);
            Eyer::EectorF3 b = bt709_green_xyz;
            b.SetZ(0.01);
            Eyer::EectorF3 c = bt709_blue_xyz;
            c.SetZ(0.01);
            MVPLineSpirit * lineA = new MVPLineSpirit(a, b);
            MVPLineSpirit * lineB = new MVPLineSpirit(a, c);
            MVPLineSpirit * lineC = new MVPLineSpirit(b, c);
            {
                EyerKey key = baseKey;
                key.frame = 325.0 * fps;
                key.scale = EectorF3(1.0, 1.0, 1.0);
                key.color = EectorF4(0.0, 0.0, 0.0, 1.0);
                lineA->AddKey(key);
                lineB->AddKey(key);
                lineC->AddKey(key);
            }
            {
                EyerKey key = baseKey;
                key.frame = 350 * fps;
                key.scale = EectorF3(1.0, 1.0, 1.0);
                key.color = EectorF4(0.0, 0.0, 0.0, 1.0);
                lineA->AddKey(key);
                lineB->AddKey(key);
                lineC->AddKey(key);
            }
            scene.AddSpirit(lineA);
            scene.AddSpirit(lineB);
            scene.AddSpirit(lineC);
        }




        Eyer::EectorF3 bt709_1_0_0(1.0, 0.0, 0.0);
        Eyer::EectorF3 bt709_0_1_0(0.0, 1.0, 0.0);
        Eyer::EectorF3 bt709_0_0_1(0.0, 0.0, 1.0);

        Eyer::EectorF3 bt709_1_1_0(1.0, 1.0, 0.0);
        Eyer::EectorF3 bt709_0_1_1(0.0, 1.0, 1.0);
        Eyer::EectorF3 bt709_1_0_1(1.0, 0.0, 1.0);

        Eyer::EectorF3 bt709_1_1_1(1.0, 1.0, 1.0);

        Eyer::EectorF3 bt709_1_0_0_xyz = bt709_xyz_mat * bt709_1_0_0;// 红色
        Eyer::EectorF3 bt709_0_1_0_xyz = bt709_xyz_mat * bt709_0_1_0;// 绿色
        Eyer::EectorF3 bt709_0_0_1_xyz = bt709_xyz_mat * bt709_0_0_1;// 蓝色

        Eyer::EectorF3 bt709_1_1_0_xyz = bt709_xyz_mat * bt709_1_1_0;// 黄色
        Eyer::EectorF3 bt709_0_1_1_xyz = bt709_xyz_mat * bt709_0_1_1;// 甸色
        Eyer::EectorF3 bt709_1_0_1_xyz = bt709_xyz_mat * bt709_1_0_1;// 紫色

        Eyer::EectorF3 bt709_0_0_0_xyz(0.0, 0.0, 0.0); // 黑色
        Eyer::EectorF3 bt709_1_1_1_xyz = bt709_xyz_mat * bt709_1_1_1;// 白色
        {
            EyerLog("==========xxxxxxxx=========\n");
            bt709_1_0_0_xyz.PrintInfo();
            bt709_0_1_0_xyz.PrintInfo();
            bt709_0_0_1_xyz.PrintInfo();

            float vertex[] = {
                    // 蓝绿黑
                    bt709_0_0_1_xyz.x(), bt709_0_0_1_xyz.y(), bt709_0_0_1_xyz.z(),
                    bt709_0_1_0_xyz.x(), bt709_0_1_0_xyz.y(), bt709_0_1_0_xyz.z(),
                    bt709_0_0_0_xyz.x(), bt709_0_0_0_xyz.y(), bt709_0_0_0_xyz.z(),
                    // 蓝绿甸
                    bt709_0_0_1_xyz.x(), bt709_0_0_1_xyz.y(), bt709_0_0_1_xyz.z(),
                    bt709_0_1_0_xyz.x(), bt709_0_1_0_xyz.y(), bt709_0_1_0_xyz.z(),
                    bt709_0_1_1_xyz.x(), bt709_0_1_1_xyz.y(), bt709_0_1_1_xyz.z(),


                    //红蓝黑
                    bt709_1_0_0_xyz.x(), bt709_1_0_0_xyz.y(), bt709_1_0_0_xyz.z(),
                    bt709_0_0_1_xyz.x(), bt709_0_0_1_xyz.y(), bt709_0_0_1_xyz.z(),
                    bt709_0_0_0_xyz.x(), bt709_0_0_0_xyz.y(), bt709_0_0_0_xyz.z(),
                    //红蓝紫
                    bt709_1_0_0_xyz.x(), bt709_1_0_0_xyz.y(), bt709_1_0_0_xyz.z(),
                    bt709_0_0_1_xyz.x(), bt709_0_0_1_xyz.y(), bt709_0_0_1_xyz.z(),
                    bt709_1_0_1_xyz.x(), bt709_1_0_1_xyz.y(), bt709_1_0_1_xyz.z(),


                    //红绿黑
                    bt709_1_0_0_xyz.x(), bt709_1_0_0_xyz.y(), bt709_1_0_0_xyz.z(),
                    bt709_0_1_0_xyz.x(), bt709_0_1_0_xyz.y(), bt709_0_1_0_xyz.z(),
                    bt709_0_0_0_xyz.x(), bt709_0_0_0_xyz.y(), bt709_0_0_0_xyz.z(),
                    //红绿黄
                    bt709_1_0_0_xyz.x(), bt709_1_0_0_xyz.y(), bt709_1_0_0_xyz.z(),
                    bt709_0_1_0_xyz.x(), bt709_0_1_0_xyz.y(), bt709_0_1_0_xyz.z(),
                    bt709_1_1_0_xyz.x(), bt709_1_1_0_xyz.y(), bt709_1_1_0_xyz.z(),


                    //红紫黄
                    bt709_1_0_0_xyz.x(), bt709_1_0_0_xyz.y(), bt709_1_0_0_xyz.z(),
                    bt709_1_0_1_xyz.x(), bt709_1_0_1_xyz.y(), bt709_1_0_1_xyz.z(),
                    bt709_1_1_0_xyz.x(), bt709_1_1_0_xyz.y(), bt709_1_1_0_xyz.z(),
                    //紫黄白
                    bt709_1_0_1_xyz.x(), bt709_1_0_1_xyz.y(), bt709_1_0_1_xyz.z(),
                    bt709_1_1_0_xyz.x(), bt709_1_1_0_xyz.y(), bt709_1_1_0_xyz.z(),
                    bt709_1_1_1_xyz.x(), bt709_1_1_1_xyz.y(), bt709_1_1_1_xyz.z(),

                    //蓝紫甸
                    bt709_0_0_1_xyz.x(), bt709_0_0_1_xyz.y(), bt709_0_0_1_xyz.z(),
                    bt709_1_0_1_xyz.x(), bt709_1_0_1_xyz.y(), bt709_1_0_1_xyz.z(),
                    bt709_0_1_1_xyz.x(), bt709_0_1_1_xyz.y(), bt709_0_1_1_xyz.z(),
                    //紫甸白
                    bt709_1_0_1_xyz.x(), bt709_1_0_1_xyz.y(), bt709_1_0_1_xyz.z(),
                    bt709_0_1_1_xyz.x(), bt709_0_1_1_xyz.y(), bt709_0_1_1_xyz.z(),
                    bt709_1_1_1_xyz.x(), bt709_1_1_1_xyz.y(), bt709_1_1_1_xyz.z(),

                    //绿甸黄
                    bt709_0_1_0_xyz.x(), bt709_0_1_0_xyz.y(), bt709_0_1_0_xyz.z(),
                    bt709_0_1_1_xyz.x(), bt709_0_1_1_xyz.y(), bt709_0_1_1_xyz.z(),
                    bt709_1_1_0_xyz.x(), bt709_1_1_0_xyz.y(), bt709_1_1_0_xyz.z(),

                    //甸黄白
                    bt709_0_1_1_xyz.x(), bt709_0_1_1_xyz.y(), bt709_0_1_1_xyz.z(),
                    bt709_1_1_0_xyz.x(), bt709_1_1_0_xyz.y(), bt709_1_1_0_xyz.z(),
                    bt709_1_1_1_xyz.x(), bt709_1_1_1_xyz.y(), bt709_1_1_1_xyz.z(),
            };
            float coor[] = {
                    0.0, 0.0, 1.0,
                    0.0, 1.0, 0.0,
                    0.0, 0.0, 0.0,

                    0.0, 0.0, 1.0,
                    0.0, 1.0, 0.0,
                    0.0, 1.0, 1.0,

                    1.0, 0.0, 0.0,
                    0.0, 0.0, 1.0,
                    0.0, 0.0, 0.0,

                    1.0, 0.0, 0.0,
                    0.0, 0.0, 1.0,
                    1.0, 0.0, 1.0,

                    1.0, 0.0, 0.0,
                    0.0, 1.0, 0.0,
                    0.0, 0.0, 0.0,

                    1.0, 0.0, 0.0,
                    0.0, 1.0, 0.0,
                    1.0, 1.0, 0.0,

                    1.0, 0.0, 0.0,
                    1.0, 0.0, 1.0,
                    1.0, 1.0, 0.0,

                    1.0, 0.0, 1.0,
                    1.0, 1.0, 0.0,
                    1.0, 1.0, 1.0,

                    0.0, 0.0, 1.0,
                    1.0, 0.0, 1.0,
                    0.0, 1.0, 1.0,

                    1.0, 0.0, 1.0,
                    0.0, 1.0, 1.0,
                    1.0, 1.0, 1.0,

                    0.0, 1.0, 0.0,
                    0.0, 1.0, 1.0,
                    1.0, 1.0, 0.0,

                    0.0, 1.0, 1.0,
                    1.0, 1.0, 0.0,
                    1.0, 1.0, 1.0
            };
            unsigned int vertexIndex[] = {
                    0, 1, 2,
                    3, 4, 5,
                    6, 7, 8,
                    9, 10, 11,
                    12, 13, 14,
                    15, 16, 17,
                    18, 19, 20,
                    21, 22, 23,
                    24, 25, 26,
                    27, 28, 29,
                    30, 31, 32,
                    33, 34, 35
            };
            MVPCustomSpirit * bt709 = new MVPCustomSpirit((float *)vertex, sizeof(vertex), (float *)coor, sizeof(coor), (unsigned int *)vertexIndex, sizeof(vertexIndex));
            {
                EyerKey key = baseKey;
                key.frame = 360 * fps;
                key.scale = EectorF3(1.0, 1.0, 1.0);
                key.color = EectorF4(0.0, 0.0, 0.0, 0.0);
                bt709->AddKey(key);
            }
            {
                EyerKey key = baseKey;
                key.frame = 365 * fps;
                key.scale = EectorF3(1.0, 1.0, 1.0);
                key.color = EectorF4(1.0, 1.0, 1.0, 1.0);
                bt709->AddKey(key);
            }
            {
                EyerKey key = baseKey;
                key.frame = 470 * fps;
                key.scale = EectorF3(1.0, 1.0, 1.0);
                key.color = EectorF4(1.0, 1.0, 1.0, 1.0);
                bt709->AddKey(key);
            }

            {
                EyerKey key = baseKey;
                key.frame = 475 * fps;
                key.scale = EectorF3(1.0, 1.0, 1.0);
                key.color = EectorF4(1.0, 1.0, 1.0, 0.0);
                bt709->AddKey(key);
            }

            {
                EyerKey key = baseKey;
                key.frame = 560 * fps;
                key.scale = EectorF3(1.0, 1.0, 1.0);
                key.color = EectorF4(1.0, 1.0, 1.0, 0.0);
                bt709->AddKey(key);
            }
            {
                EyerKey key = baseKey;
                key.frame = 570 * fps;
                key.scale = EectorF3(1.0, 1.0, 1.0);
                key.color = EectorF4(1.0, 1.0, 1.0, 0.5);
                bt709->AddKey(key);
            }

            {
                EyerKey key = baseKey;
                key.frame = endFrame;
                key.scale = EectorF3(1.0, 1.0, 1.0);
                key.color = EectorF4(1.0, 1.0, 1.0, 0.5);
                bt709->AddKey(key);
            }
            scene.AddSpirit(bt709);
        }


        {
            SphereSpirit * redPoint = new SphereSpirit();

            float a = bt709_1_0_0_xyz.x() + bt709_1_0_0_xyz.y() + bt709_1_0_0_xyz.z();
            EectorF3 bt709_1_0_0_xyz_norm = bt709_1_0_0_xyz * (1.0 / a);

            {
                EyerKey key = baseKey;
                key.frame = 420.0 * fps;
                key.position = bt709_1_0_0_xyz;
                redPoint->AddKey(key);
            }
            {
                EyerKey key = baseKey;
                key.frame = 500.0 * fps;
                key.position = bt709_1_0_0_xyz;
                redPoint->AddKey(key);
            }
            {
                EyerKey key = baseKey;
                key.frame = 505.0 * fps;
                key.position = bt709_1_0_0_xyz_norm;
                redPoint->AddKey(key);
            }
            {
                EyerKey key = baseKey;
                key.frame = 520.0 * fps;
                key.position = bt709_1_0_0_xyz_norm;
                redPoint->AddKey(key);
            }
            {
                EyerKey key = baseKey;
                key.frame = 525.0 * fps;
                key.position = bt709_1_0_0_xyz_norm;
                key.position.SetZ(0.0);
                redPoint->AddKey(key);
            }
            {
                EyerKey key = baseKey;
                key.frame = 550 * fps;
                key.position = bt709_1_0_0_xyz_norm;
                key.position.SetZ(0.0);
                redPoint->AddKey(key);
            }
            scene.AddSpirit(redPoint);
        }

        {
            SphereSpirit * greenPoint = new SphereSpirit();

            float a = bt709_0_1_0_xyz.x() + bt709_0_1_0_xyz.y() + bt709_0_1_0_xyz.z();
            EectorF3 bt709_0_1_0_xyz_norm = bt709_0_1_0_xyz * (1.0 / a);

            {
                EyerKey key = baseKey;
                key.frame = 435.0 * fps;
                key.position = bt709_0_1_0_xyz;
                greenPoint->AddKey(key);
            }
            {
                EyerKey key = baseKey;
                key.frame = 500.0 * fps;
                key.position = bt709_0_1_0_xyz;
                greenPoint->AddKey(key);
            }
            {
                EyerKey key = baseKey;
                key.frame = 505.0 * fps;
                key.position = bt709_0_1_0_xyz_norm;
                greenPoint->AddKey(key);
            }
            {
                EyerKey key = baseKey;
                key.frame = 520.0 * fps;
                key.position = bt709_0_1_0_xyz_norm;
                greenPoint->AddKey(key);
            }
            {
                EyerKey key = baseKey;
                key.frame = 525.0 * fps;
                key.position = bt709_0_1_0_xyz_norm;
                key.position.SetZ(0.0);
                greenPoint->AddKey(key);
            }
            {
                EyerKey key = baseKey;
                key.frame = 550 * fps;
                key.position = bt709_0_1_0_xyz_norm;
                key.position.SetZ(0.0);
                greenPoint->AddKey(key);
            }
            scene.AddSpirit(greenPoint);
        }

        {
            SphereSpirit * bluePoint = new SphereSpirit();
            float a = bt709_0_0_1_xyz.x() + bt709_0_0_1_xyz.y() + bt709_0_0_1_xyz.z();
            EectorF3 bt709_0_0_1_xyz_norm = bt709_0_0_1_xyz * (1.0 / a);
            {
                EyerKey key = baseKey;
                key.frame = 450.0 * fps;
                key.position = bt709_0_0_1_xyz;
                bluePoint->AddKey(key);
            }
            {
                EyerKey key = baseKey;
                key.frame = 500.0 * fps;
                key.position = bt709_0_0_1_xyz;
                bluePoint->AddKey(key);
            }
            {
                EyerKey key = baseKey;
                key.frame = 505.0 * fps;
                key.position = bt709_0_0_1_xyz_norm;
                bluePoint->AddKey(key);
            }

            {
                EyerKey key = baseKey;
                key.frame = 520.0 * fps;
                key.position = bt709_0_0_1_xyz_norm;
                bluePoint->AddKey(key);
            }
            {
                EyerKey key = baseKey;
                key.frame = 525.0 * fps;
                key.position = bt709_0_0_1_xyz_norm;
                key.position.SetZ(0.0);
                bluePoint->AddKey(key);
            }
            {
                EyerKey key = baseKey;
                key.frame = 550 * fps;
                key.position = bt709_0_0_1_xyz_norm;
                key.position.SetZ(0.0);
                bluePoint->AddKey(key);
            }
            scene.AddSpirit(bluePoint);
        }


        {
            Eyer::EectorF3 bt709_0_0_0(0.0, 0.0, 0.0);

            MVPLineSpirit * lineSpiritA = new MVPLineSpirit(bt709_1_0_0_xyz, bt709_0_0_0);
            MVPLineSpirit * lineSpiritB = new MVPLineSpirit(bt709_0_1_0_xyz, bt709_0_0_0);
            MVPLineSpirit * lineSpiritC = new MVPLineSpirit(bt709_0_0_1_xyz, bt709_0_0_0);

            EyerKey baseKey;
            baseKey.position = EectorF3(0, 0, 0);
            baseKey.rotato = EectorF4(1.0, 0.0, 0.0, 0.0);
            float scale = 2.0;
            baseKey.scale = EectorF3(scale, scale, scale);
            baseKey.color = EectorF4(1.0, 1.0, 1.0, 1.0);
            {
                EyerKey key = baseKey;
                key.frame = 490 * fps;
                lineSpiritA->AddKey(key);
                lineSpiritB->AddKey(key);
                lineSpiritC->AddKey(key);
            }
            {
                EyerKey key = baseKey;
                key.frame = 505 * fps;
                lineSpiritA->AddKey(key);
                lineSpiritB->AddKey(key);
                lineSpiritC->AddKey(key);
            }
            scene.AddSpirit(lineSpiritA);
            scene.AddSpirit(lineSpiritB);
            scene.AddSpirit(lineSpiritC);
        }


        {
            float a = bt709_1_0_0_xyz.x() + bt709_1_0_0_xyz.y() + bt709_1_0_0_xyz.z();
            EectorF3 bt709_1_0_0_xyz_norm = bt709_1_0_0_xyz * (1.0 / a);
            EectorF3 bt709_1_0_0_xyz_norm_ = bt709_1_0_0_xyz_norm;
            bt709_1_0_0_xyz_norm_.SetZ(0.0);

            a = bt709_0_1_0_xyz.x() + bt709_0_1_0_xyz.y() + bt709_0_1_0_xyz.z();
            EectorF3 bt709_0_1_0_xyz_norm = bt709_0_1_0_xyz * (1.0 / a);
            EectorF3 bt709_0_1_0_xyz_norm_ = bt709_0_1_0_xyz_norm;
            bt709_0_1_0_xyz_norm_.SetZ(0.0);

            a = bt709_0_0_1_xyz.x() + bt709_0_0_1_xyz.y() + bt709_0_0_1_xyz.z();
            EectorF3 bt709_0_0_1_xyz_norm = bt709_0_0_1_xyz * (1.0 / a);
            EectorF3 bt709_0_0_1_xyz_norm_ = bt709_0_0_1_xyz_norm;
            bt709_0_0_1_xyz_norm_.SetZ(0.0);

            MVPLineSpirit * lineSpiritA = new MVPLineSpirit(bt709_1_0_0_xyz_norm, bt709_1_0_0_xyz_norm_);
            MVPLineSpirit * lineSpiritB = new MVPLineSpirit(bt709_0_1_0_xyz_norm, bt709_0_1_0_xyz_norm_);
            MVPLineSpirit * lineSpiritC = new MVPLineSpirit(bt709_0_0_1_xyz_norm, bt709_0_0_1_xyz_norm_);

            EyerKey baseKey;
            baseKey.position = EectorF3(0, 0, 0);
            baseKey.rotato = EectorF4(1.0, 0.0, 0.0, 0.0);
            float scale = 1.0;
            baseKey.scale = EectorF3(scale, scale, scale);
            baseKey.color = EectorF4(1.0, 1.0, 1.0, 1.0);
            {
                EyerKey key = baseKey;
                key.frame = 515 * fps;
                key.color = EectorF4(0.0, 0.0, 0.0, 1.0);
                lineSpiritA->AddKey(key);
                lineSpiritB->AddKey(key);
                lineSpiritC->AddKey(key);
            }
            {
                EyerKey key = baseKey;
                key.frame = 520 * fps;
                key.color = EectorF4(1.0, 1.0, 1.0, 1.0);
                lineSpiritA->AddKey(key);
                lineSpiritB->AddKey(key);
                lineSpiritC->AddKey(key);
            }
            {
                EyerKey key = baseKey;
                key.frame = 525 * fps;
                key.color = EectorF4(1.0, 1.0, 1.0, 1.0);
                lineSpiritA->AddKey(key);
                lineSpiritB->AddKey(key);
                lineSpiritC->AddKey(key);
            }
            {
                EyerKey key = baseKey;
                key.frame = 530 * fps;
                key.color = EectorF4(0.0, 0.0, 0.0, 1.0);
                lineSpiritA->AddKey(key);
                lineSpiritB->AddKey(key);
                lineSpiritC->AddKey(key);
            }
            scene.AddSpirit(lineSpiritA);
            scene.AddSpirit(lineSpiritB);
            scene.AddSpirit(lineSpiritC);
        }

        Eyer::EectorF3 bt2020_1_0_0(1.0, 0.0, 0.0);
        Eyer::EectorF3 bt2020_0_1_0(0.0, 1.0, 0.0);
        Eyer::EectorF3 bt2020_0_0_1(0.0, 0.0, 1.0);

        Eyer::EectorF3 bt2020_1_1_0(1.0, 1.0, 0.0);
        Eyer::EectorF3 bt2020_0_1_1(0.0, 1.0, 1.0);
        Eyer::EectorF3 bt2020_1_0_1(1.0, 0.0, 1.0);

        Eyer::EectorF3 bt2020_1_1_1(1.0, 1.0, 1.0);

        Eyer::EectorF3 bt2020_1_0_0_xyz = bt2020_xyz_mat * bt2020_1_0_0;// 红色
        Eyer::EectorF3 bt2020_0_1_0_xyz = bt2020_xyz_mat * bt2020_0_1_0;// 绿色
        Eyer::EectorF3 bt2020_0_0_1_xyz = bt2020_xyz_mat * bt2020_0_0_1;// 蓝色

        Eyer::EectorF3 bt2020_1_1_0_xyz = bt2020_xyz_mat * bt2020_1_1_0;// 黄色
        Eyer::EectorF3 bt2020_0_1_1_xyz = bt2020_xyz_mat * bt2020_0_1_1;// 甸色
        Eyer::EectorF3 bt2020_1_0_1_xyz = bt2020_xyz_mat * bt2020_1_0_1;// 紫色

        Eyer::EectorF3 bt2020_0_0_0_xyz(0.0, 0.0, 0.0); // 黑色
        Eyer::EectorF3 bt2020_1_1_1_xyz = bt2020_xyz_mat * bt2020_1_1_1;// 白色
        {
            EyerLog("==========xxxxxxxx=========\n");
            bt2020_1_0_0_xyz.PrintInfo();
            bt2020_0_1_0_xyz.PrintInfo();
            bt2020_0_0_1_xyz.PrintInfo();

            float vertex[] = {
                    // 蓝绿黑
                    bt2020_0_0_1_xyz.x(), bt2020_0_0_1_xyz.y(), bt2020_0_0_1_xyz.z(),
                    bt2020_0_1_0_xyz.x(), bt2020_0_1_0_xyz.y(), bt2020_0_1_0_xyz.z(),
                    bt2020_0_0_0_xyz.x(), bt2020_0_0_0_xyz.y(), bt2020_0_0_0_xyz.z(),
                    // 蓝绿甸
                    bt2020_0_0_1_xyz.x(), bt2020_0_0_1_xyz.y(), bt2020_0_0_1_xyz.z(),
                    bt2020_0_1_0_xyz.x(), bt2020_0_1_0_xyz.y(), bt2020_0_1_0_xyz.z(),
                    bt2020_0_1_1_xyz.x(), bt2020_0_1_1_xyz.y(), bt2020_0_1_1_xyz.z(),


                    //红蓝黑
                    bt2020_1_0_0_xyz.x(), bt2020_1_0_0_xyz.y(), bt2020_1_0_0_xyz.z(),
                    bt2020_0_0_1_xyz.x(), bt2020_0_0_1_xyz.y(), bt2020_0_0_1_xyz.z(),
                    bt2020_0_0_0_xyz.x(), bt2020_0_0_0_xyz.y(), bt2020_0_0_0_xyz.z(),
                    //红蓝紫
                    bt2020_1_0_0_xyz.x(), bt2020_1_0_0_xyz.y(), bt2020_1_0_0_xyz.z(),
                    bt2020_0_0_1_xyz.x(), bt2020_0_0_1_xyz.y(), bt2020_0_0_1_xyz.z(),
                    bt2020_1_0_1_xyz.x(), bt2020_1_0_1_xyz.y(), bt2020_1_0_1_xyz.z(),


                    //红绿黑
                    bt2020_1_0_0_xyz.x(), bt2020_1_0_0_xyz.y(), bt2020_1_0_0_xyz.z(),
                    bt2020_0_1_0_xyz.x(), bt2020_0_1_0_xyz.y(), bt2020_0_1_0_xyz.z(),
                    bt2020_0_0_0_xyz.x(), bt2020_0_0_0_xyz.y(), bt2020_0_0_0_xyz.z(),
                    //红绿黄
                    bt2020_1_0_0_xyz.x(), bt2020_1_0_0_xyz.y(), bt2020_1_0_0_xyz.z(),
                    bt2020_0_1_0_xyz.x(), bt2020_0_1_0_xyz.y(), bt2020_0_1_0_xyz.z(),
                    bt2020_1_1_0_xyz.x(), bt2020_1_1_0_xyz.y(), bt2020_1_1_0_xyz.z(),


                    //红紫黄
                    bt2020_1_0_0_xyz.x(), bt2020_1_0_0_xyz.y(), bt2020_1_0_0_xyz.z(),
                    bt2020_1_0_1_xyz.x(), bt2020_1_0_1_xyz.y(), bt2020_1_0_1_xyz.z(),
                    bt2020_1_1_0_xyz.x(), bt2020_1_1_0_xyz.y(), bt2020_1_1_0_xyz.z(),
                    //紫黄白
                    bt2020_1_0_1_xyz.x(), bt2020_1_0_1_xyz.y(), bt2020_1_0_1_xyz.z(),
                    bt2020_1_1_0_xyz.x(), bt2020_1_1_0_xyz.y(), bt2020_1_1_0_xyz.z(),
                    bt2020_1_1_1_xyz.x(), bt2020_1_1_1_xyz.y(), bt2020_1_1_1_xyz.z(),

                    //蓝紫甸
                    bt2020_0_0_1_xyz.x(), bt2020_0_0_1_xyz.y(), bt2020_0_0_1_xyz.z(),
                    bt2020_1_0_1_xyz.x(), bt2020_1_0_1_xyz.y(), bt2020_1_0_1_xyz.z(),
                    bt2020_0_1_1_xyz.x(), bt2020_0_1_1_xyz.y(), bt2020_0_1_1_xyz.z(),
                    //紫甸白
                    bt2020_1_0_1_xyz.x(), bt2020_1_0_1_xyz.y(), bt2020_1_0_1_xyz.z(),
                    bt2020_0_1_1_xyz.x(), bt2020_0_1_1_xyz.y(), bt2020_0_1_1_xyz.z(),
                    bt2020_1_1_1_xyz.x(), bt2020_1_1_1_xyz.y(), bt2020_1_1_1_xyz.z(),

                    //绿甸黄
                    bt2020_0_1_0_xyz.x(), bt2020_0_1_0_xyz.y(), bt2020_0_1_0_xyz.z(),
                    bt2020_0_1_1_xyz.x(), bt2020_0_1_1_xyz.y(), bt2020_0_1_1_xyz.z(),
                    bt2020_1_1_0_xyz.x(), bt2020_1_1_0_xyz.y(), bt2020_1_1_0_xyz.z(),

                    //甸黄白
                    bt2020_0_1_1_xyz.x(), bt2020_0_1_1_xyz.y(), bt2020_0_1_1_xyz.z(),
                    bt2020_1_1_0_xyz.x(), bt2020_1_1_0_xyz.y(), bt2020_1_1_0_xyz.z(),
                    bt2020_1_1_1_xyz.x(), bt2020_1_1_1_xyz.y(), bt2020_1_1_1_xyz.z(),
            };
            float coor[] = {
                    0.0, 0.0, 1.0,
                    0.0, 1.0, 0.0,
                    0.0, 0.0, 0.0,

                    0.0, 0.0, 1.0,
                    0.0, 1.0, 0.0,
                    0.0, 1.0, 1.0,

                    1.0, 0.0, 0.0,
                    0.0, 0.0, 1.0,
                    0.0, 0.0, 0.0,

                    1.0, 0.0, 0.0,
                    0.0, 0.0, 1.0,
                    1.0, 0.0, 1.0,

                    1.0, 0.0, 0.0,
                    0.0, 1.0, 0.0,
                    0.0, 0.0, 0.0,

                    1.0, 0.0, 0.0,
                    0.0, 1.0, 0.0,
                    1.0, 1.0, 0.0,

                    1.0, 0.0, 0.0,
                    1.0, 0.0, 1.0,
                    1.0, 1.0, 0.0,

                    1.0, 0.0, 1.0,
                    1.0, 1.0, 0.0,
                    1.0, 1.0, 1.0,

                    0.0, 0.0, 1.0,
                    1.0, 0.0, 1.0,
                    0.0, 1.0, 1.0,

                    1.0, 0.0, 1.0,
                    0.0, 1.0, 1.0,
                    1.0, 1.0, 1.0,

                    0.0, 1.0, 0.0,
                    0.0, 1.0, 1.0,
                    1.0, 1.0, 0.0,

                    0.0, 1.0, 1.0,
                    1.0, 1.0, 0.0,
                    1.0, 1.0, 1.0
            };
            unsigned int vertexIndex[] = {
                    0, 1, 2,
                    3, 4, 5,
                    6, 7, 8,
                    9, 10, 11,
                    12, 13, 14,
                    15, 16, 17,
                    18, 19, 20,
                    21, 22, 23,
                    24, 25, 26,
                    27, 28, 29,
                    30, 31, 32,
                    33, 34, 35
            };
            MVPCustomSpirit * bt2020 = new MVPCustomSpirit((float *)vertex, sizeof(vertex), (float *)coor, sizeof(coor), (unsigned int *)vertexIndex, sizeof(vertexIndex));
            {
                EyerKey key = baseKey;
                key.frame = 660 * fps;
                key.scale = EectorF3(1.0, 1.0, 1.0);
                key.color = EectorF4(1.0, 1.0, 1.0, 0.0);
                bt2020->AddKey(key);
            }
            {
                EyerKey key = baseKey;
                key.frame = 670 * fps;
                key.scale = EectorF3(1.0, 1.0, 1.0);
                key.color = EectorF4(1.0, 1.0, 1.0, 0.35);
                bt2020->AddKey(key);
            }
            {
                EyerKey key = baseKey;
                key.frame = endFrame;
                key.scale = EectorF3(1.0, 1.0, 1.0);
                key.color = EectorF4(1.0, 1.0, 1.0, 0.35);
                bt2020->AddKey(key);
            }
            scene.AddSpirit(bt2020);
        }

        return 0;
    }

    int Scene::Update()
    {
        long long currTime = Eyer::EyerTime::GetTime();
        long long dTime = currTime - startTime;

        double time = dTime / 1000.0;


        time *= 1;
        // time += 550;


        if(time < 0){
            return 0;
        }

        int frame = time * fps;

        scene.Render(time);
        frameIndex++;

        return 0;
    }


    EectorF4 Scene::GetColor(int i)
    {
        int p1 = 0;
        EectorF4 c1(0.0, 0.0, 1.0, 1.0);

        int p1_2 = 8;
        EectorF4 c1_2(0.0, 0.2, 1.0, 1.0);

        int p2 = 20;
        EectorF4 c2(0.0, 1.0, 1.0, 1.0);

        int p3 = 23;
        EectorF4 c3(0.0, 1.0, 0.0, 1.0);

        int p4 = 30;
        EectorF4 c4(1.0, 1.0, 0.0, 1.0);

        int p5 = 37;
        EectorF4 c5(1.0, 0.0, 0.0, 1.0);

        int p6 = 48;
        EectorF4 c6(1.0, 0.0, 0.0, 1.0);

        EectorF4 color;
        if(i >= p1 && i < p1_2){
            Eyer::EnterPolation<float> P(c1, c1_2, p1, p1_2);
            color = P.Get(i);
        }
        if(i >= p1_2 && i < p2){
            Eyer::EnterPolation<float> P(c1_2, c2, p1_2, p2);
            color = P.Get(i);
        }
        if(i >= p2 && i < p3){
            Eyer::EnterPolation<float> P(c2, c3, p2, p3);
            color = P.Get(i);
        }
        if(i >= p3 && i < p4){
            Eyer::EnterPolation<float> P(c3, c4, p3, p4);
            color = P.Get(i);
        }
        if(i >= p4 && i < p5){
            Eyer::EnterPolation<float> P(c4, c5, p4, p5);
            color = P.Get(i);
        }
        if(i >= p5 && i < p6){
            Eyer::EnterPolation<float> P(c5, c6, p5, p6);
            color = P.Get(i);
        }

        return color;
    }
}


