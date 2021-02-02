#ifndef EYERLIB_EATRIX4X4_HPP
#define EYERLIB_EATRIX4X4_HPP

#include "Eatrix.hpp"
#include <math.h>
#include "Eatrix3x1.hpp"

/*
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
*/

namespace Eyer
{
    template<typename T>
    class Eatrix4x4 : public Eatrix<T>
    {
    public:
        Eatrix4x4() : Eatrix<T>(4, 4)
        {

        }

        ~Eatrix4x4()
        {

        }

        Eatrix4x4(const Eatrix<T> & mat) : Eatrix4x4()
        {
            *this = mat;
        }

        const Eatrix4x4 & operator = (const Eatrix<T> & mat)
        {
            if(this == &mat) {
                return *this;
            }
            Eatrix<T>::operator = (mat);
            return *this;
        }

        int SetRotate(T x, T y, T z, T a)
        {
            Eatrix<T>::mat[0][0] = cos(a) + x * x * (1 - cos(a));      Eatrix<T>::mat[0][1] = x * y * (1 - cos(a)) - z * sin(a); Eatrix<T>::mat[0][2] = x * z * (1 - cos(a)) + y * sin(a);  Eatrix<T>::mat[0][3] = 0.0;
            Eatrix<T>::mat[1][0] = y * x * (1 - cos(a)) + z * sin(a);  Eatrix<T>::mat[1][1] = cos(a) + y * y * (1 - cos(a));     Eatrix<T>::mat[1][2] = y * z * (1 - cos(a)) - x * sin(a);  Eatrix<T>::mat[1][3] = 0.0;
            Eatrix<T>::mat[2][0] = z * x * (1 - cos(a)) - y * sin(a);  Eatrix<T>::mat[2][1] = z * y * (1 - cos(a)) + x * sin(a); Eatrix<T>::mat[2][2] = cos(a) + z * z * (a - cos(a));      Eatrix<T>::mat[2][3] = 0.0;
            Eatrix<T>::mat[3][0] = 0.0;                                Eatrix<T>::mat[3][1] = 0.0;                               Eatrix<T>::mat[3][2] = 0.0;                                Eatrix<T>::mat[3][3] = 1.0;
            return 0;
        }

        int SetRotateX(T a)
        {
            Eatrix<T>::mat[0][0] = 1.0f;                                       Eatrix<T>::mat[0][1] = 0.0f;                               Eatrix<T>::mat[0][2] = 0.0f;                               Eatrix<T>::mat[0][3] = 0.0f;
            Eatrix<T>::mat[1][0] = 0.0f;                                       Eatrix<T>::mat[1][1] = cos(a);                             Eatrix<T>::mat[1][2] = -sin(a);                            Eatrix<T>::mat[1][3] = 0.0f;
            Eatrix<T>::mat[2][0] = 0.0f;                                       Eatrix<T>::mat[2][1] = sin(a);                             Eatrix<T>::mat[2][2] = cos(a);                             Eatrix<T>::mat[2][3] = 0.0f;
            Eatrix<T>::mat[3][0] = 0.0f;                                       Eatrix<T>::mat[3][1] = 0.0f;                               Eatrix<T>::mat[3][2] = 0.0f;                               Eatrix<T>::mat[3][3] = 1.0f;
            return 0;
        }

        int SetRotateY(T a)
        {
            Eatrix<T>::mat[0][0] = cos(a);                                     Eatrix<T>::mat[0][1] = 0.0f;                               Eatrix<T>::mat[0][2] = sin(a);                             Eatrix<T>::mat[0][3] = 0.0f;
            Eatrix<T>::mat[1][0] = 0.0f;                                       Eatrix<T>::mat[1][1] = 1.0f;                               Eatrix<T>::mat[1][2] = 0.0f;                               Eatrix<T>::mat[1][3] = 0.0f;
            Eatrix<T>::mat[2][0] = -sin(a);                                    Eatrix<T>::mat[2][1] = 0.0f;                               Eatrix<T>::mat[2][2] = cos(a);                             Eatrix<T>::mat[2][3] = 0.0f;
            Eatrix<T>::mat[3][0] = 0.0f;                                       Eatrix<T>::mat[3][1] = 0.0f;                               Eatrix<T>::mat[3][2] = 0.0f;                               Eatrix<T>::mat[3][3] = 1.0f;
            return 0;
        }

        int SetRotateZ(T a)
        {
            Eatrix<T>::mat[0][0] = cos(a);                                     Eatrix<T>::mat[0][1] = -sin(a);                            Eatrix<T>::mat[0][2] = 0.0f;                               Eatrix<T>::mat[0][3] = 0.0f;
            Eatrix<T>::mat[1][0] = sin(a);                                     Eatrix<T>::mat[1][1] = cos(a);                             Eatrix<T>::mat[1][2] = 0.0f;                               Eatrix<T>::mat[1][3] = 0.0f;
            Eatrix<T>::mat[2][0] = 0.0f;                                       Eatrix<T>::mat[2][1] = 0.0f;                               Eatrix<T>::mat[2][2] = 1.0f;                               Eatrix<T>::mat[2][3] = 0.0f;
            Eatrix<T>::mat[3][0] = 0.0f;                                       Eatrix<T>::mat[3][1] = 0.0f;                               Eatrix<T>::mat[3][2] = 0.0f;                               Eatrix<T>::mat[3][3] = 1.0f;
            return 0;
        }

        int SetOrtho(T l, T r, T t, T b, T near, T far)
        {
            Eatrix<T>::mat[0][0] = 2.0 / (r - l);                              Eatrix<T>::mat[0][1] = 0.0f;                               Eatrix<T>::mat[0][2] = 0.0f;                               Eatrix<T>::mat[0][3] = - (r + l) / (r - l);
            Eatrix<T>::mat[1][0] = 0.0f;                                       Eatrix<T>::mat[1][1] = 2.0 / (t - b);                      Eatrix<T>::mat[1][2] = 0.0f;                               Eatrix<T>::mat[1][3] = - (t + b) / (t - b);
            Eatrix<T>::mat[2][0] = 0.0f;                                       Eatrix<T>::mat[2][1] = 0.0f;                               Eatrix<T>::mat[2][2] = -2.0 / (far - near);                Eatrix<T>::mat[2][3] = - (far + near) / (far - near);
            Eatrix<T>::mat[3][0] = 0.0f;                                       Eatrix<T>::mat[3][1] = 0.0f;                               Eatrix<T>::mat[3][2] = 0.0f;                               Eatrix<T>::mat[3][3] = 1.0f;
            return 0;
        }

        int SetTrans(float x, float y, float z)
        {
            Eatrix<T>::mat[0][3] = x;
            Eatrix<T>::mat[1][3] = y;
            Eatrix<T>::mat[2][3] = z;
            return 0;
        }

        int SetPerspective(float fov, float aspect, float near, float far)
        {
            Eatrix<T>::mat[0][0] = tan(M_PI / 2.0 - (fov / 2.0)) / aspect;     Eatrix<T>::mat[0][1] = 0.0f;                               Eatrix<T>::mat[0][2] = 0.0f;                               Eatrix<T>::mat[0][3] = 0.0f;
            Eatrix<T>::mat[1][0] = 0.0f;                                       Eatrix<T>::mat[1][1] = tan(M_PI / 2.0 - (fov / 2.0));      Eatrix<T>::mat[1][2] = 0.0f;                               Eatrix<T>::mat[1][3] = 0.0f;
            Eatrix<T>::mat[2][0] = 0.0f;                                       Eatrix<T>::mat[2][1] = 0.0f;                               Eatrix<T>::mat[2][2] = -((far + near) / (far - near));     Eatrix<T>::mat[2][3] = - ((2 * near * far) / (far - near));
            Eatrix<T>::mat[3][0] = 0.0f;                                       Eatrix<T>::mat[3][1] = 0.0f;                               Eatrix<T>::mat[3][2] = -1.0f;                              Eatrix<T>::mat[3][3] = 0.0f;
            return 0;
        }

        int LookAt(
                T eyeX, T eyeY, T eyeZ,
                T targetX, T targetY, T targetZ,
                T upX, T upY, T upZ
                )
        {
            Eatrix3x1<float> eye(eyeX, eyeY, eyeZ);
            Eatrix3x1<float> target(targetX, targetY, targetZ);
            Eatrix3x1<float> up(upX, upY, upZ);

            // 摄像机方向
            Eatrix3x1<float> cameraDirection = eye - target;
            cameraDirection.Normalize();
            // cameraDirection.PrintInfo();

            // 右轴
            Eatrix3x1<float> cameraRight = Eatrix3x1<float>::CrossProduct(up, cameraDirection);
            cameraRight.Normalize();
            // cameraRight.PrintInfo();

            // 上轴
            Eatrix3x1<float> cameraUP = Eatrix3x1<float>::CrossProduct(cameraDirection, cameraRight);
            // cameraUP.PrintInfo();

            Eatrix4x4 mR;
            mR.mat[0][0] = cameraRight.x();    mR.mat[0][1] = cameraRight.y();    mR.mat[0][2] = cameraRight.z();    mR.mat[0][3] = 0.0f;
            mR.mat[1][0] = cameraUP.x();       mR.mat[1][1] = cameraUP.y();       mR.mat[1][2] = cameraUP.z();       mR.mat[1][3] = 0.0f;
            mR.mat[2][0] = cameraDirection.x();mR.mat[2][1] = cameraDirection.y();mR.mat[2][2] = cameraDirection.z();mR.mat[2][3] = 0.0f;
            mR.mat[3][0] = 0.0f;               mR.mat[3][1] = 0.0f;               mR.mat[3][2] = 0.0f;               mR.mat[3][3] = 1.0f;

            /*
            glm::vec3 cameraPos = glm::vec3(eye.x(), eye.y(), eye.z());
            glm::vec3 cameraTarget = glm::vec3(target.x(), target.y(), target.z());
            glm::vec3 cameraDirectionGLM = glm::normalize(cameraPos - cameraTarget);
            EyerLog("%f, %f, %f\n", cameraDirectionGLM.x, cameraDirectionGLM.y, cameraDirectionGLM.z);

            glm::vec3 upGLM = glm::vec3(up.x(), up.y(), up.z());
            glm::vec3 cameraRightGLM = glm::normalize(glm::cross(upGLM, cameraDirectionGLM));
            EyerLog("%f, %f, %f\n", cameraRightGLM.x, cameraRightGLM.y, cameraRightGLM.z);

            glm::vec3 cameraUPGLM = glm::cross(cameraDirectionGLM, cameraRightGLM);
            EyerLog("%f, %f, %f\n", cameraUPGLM.x, cameraUPGLM.y, cameraUPGLM.z);
            */

            Eatrix4x4 mT;
            mT.SetTrans(-eyeX, -eyeY, -eyeZ);

            *this = mR * mT;

            return 0;
        }
    };
}

#endif //EYERLIB_EATRIX4X4_HPP
