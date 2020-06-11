#include "EyerGPUDomino.hpp"
#include "EyerGLShader/Shader.hpp"

#include <iostream>
#include <chrono>
#include <math.h>
using namespace std;

namespace Eyer
{
    EyerCommonComponent::EyerCommonComponent(char * V_SHADER, char * F_SHADER)
    {
        float vertex[] = {
                1.0, 1.0, 0.0,
                1.0, -1.0, 0.0,
                -1.0, -1.0, 0.0,
                -1.0, 1.0, 0.0
        };
        float coor[] = {
                1.0, 1.0, 0.0,
                1.0, 0.0, 0.0,
                0.0, 0.0, 0.0,
                0.0, 1.0, 0.0
        };
        unsigned int vertexIndex[] = {
                0, 1, 2,
                0, 2, 3
        };


        draw = new EyerGLDraw(V_SHADER, F_SHADER);
        draw->Init();

        vao = new EyerGLVAO();

        vao->AddVBO(vertex, sizeof(vertex), 0);
        vao->AddVBO(coor, sizeof(coor), 1);
        vao->SetEBO(vertexIndex, sizeof(vertexIndex));

        draw->SetVAO(vao);
    }

    EyerCommonComponent::~EyerCommonComponent()
    {
        if(draw != nullptr){
            delete draw;
            draw = nullptr;
        }

        if(vao != nullptr){
            delete vao;
            vao = nullptr;
        }
    }


    float t = 0.0f;
    int EyerCommonComponent::Draw()
    {
        if(texture != nullptr){
            draw->PutTexture("imageTex",texture);
        }

        draw->PutUniform1f("w", w * 1.0);
        draw->PutUniform1f("h", h * 1.0);

        draw->PutUniform1f("Time", t);
        draw->Draw();

        t += 0.04f;
        return 0;
    }

    int EyerCommonComponent::SetTexture(EyerGLTexture * _texture)
    {
        texture = _texture;
        return 0;
    }

    int EyerCommonComponent::SetWH(int _w, int _h)
    {
        w = _w;
        h = _h;
        return 0;
    }
}