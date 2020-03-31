#include "MBGPUDomino.hpp"
#include "MBGLShader/Shader.hpp"

namespace MB
{
    MBCommonComponent::MBCommonComponent(char * V_SHADER, char * F_SHADER)
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


        draw = new MBGLDraw(V_SHADER, F_SHADER);
        draw->Init();

        vao = new MBGLVAO();

        vao->AddVBO(vertex, sizeof(vertex), 0);
        vao->AddVBO(coor, sizeof(coor), 1);
        vao->SetEBO(vertexIndex, sizeof(vertexIndex));

        draw->SetVAO(vao);
    }

    MBCommonComponent::~MBCommonComponent()
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

    int MBCommonComponent::Draw()
    {
        if(texture != nullptr){
            draw->PutTexture("imageTex",texture);
        }

        draw->PutUniform1f("w", w * 1.0);
        draw->PutUniform1f("h", h * 1.0);

        draw->Draw();
        return 0;
    }

    int MBCommonComponent::SetTexture(MBGLTexture * _texture)
    {
        texture = _texture;
        return 0;
    }

    int MBCommonComponent::SetWH(int _w, int _h)
    {
        w = _w;
        h = _h;
        return 0;
    }
}