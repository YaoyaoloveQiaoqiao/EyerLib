#include "MVPCube.hpp"
#include "EyerGLShader/Shader.hpp"

namespace Eyer
{
    MVPCube::MVPCube()
    {
        float vertex[] = {
                -0.5f, -0.5f, -0.5f,
                0.5f, -0.5f, -0.5f,
                -0.5f,  0.5f, -0.5f,
                0.5f,  0.5f, -0.5f,
                -0.5f, -0.5f,  0.5f,
                0.5f, -0.5f,  0.5f,
                -0.5f,  0.5f,  0.5f,
                0.5f,  0.5f,  0.5f,
        };
        float coor[] = {
                0.0f, 0.0f, 0.0f,
                1.0f, 0.0f, 0.0f,
                0.0f,  1.0f, 0.0f,
                1.0f,  1.0f, 0.0f,
                0.0f, 0.0f,  1.0f,
                1.0f, 0.0f,  1.0f,
                0.0f,  1.0f,  1.0f,
                1.0f,  1.0f,  1.0f,
        };
        unsigned int vertexIndex[] = {
                0, 1, 3,
                0, 3, 2,

                5, 1, 3,
                5, 3, 7,

                6, 7, 3,
                6, 3, 2,

                4, 0, 6,
                6, 0, 2,

                4, 5, 7,
                4, 7, 6,

                4, 5, 1,
                4, 1, 0
        };

        draw = new EyerGLDraw(EYER_GL_SHADER::MVP_GEOM_VERTEX_SHADER, EYER_GL_SHADER::MVP_GEOM_FRAGMENT_SHADER);
        draw->Init();

        vao = new EyerGLVAO();

        vao->AddVBO(vertex, sizeof(vertex), 0);
        vao->AddVBO(coor, sizeof(coor), 1);
        vao->SetEBO(vertexIndex, sizeof(vertexIndex));

        draw->SetVAO(vao);
    }

    MVPCube::~MVPCube()
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

    int MVPCube::SetMVP(EatrixF4x4 & mat)
    {
        mvp = mat;
        return 0;
    }

    int MVPCube::Draw()
    {
        EatrixF4x4 mmvp;

        float color_r = 0.0f;
        float color_g = 1.0f;
        float color_b = 0.0f;
        float color_a = 1.0f;

        EatrixF4x4 mScale;
        mScale.SetScale(1.0, 1.0, 1.0);

        mmvp = mvp * mScale;

        draw->PutUniform1f("color_r", color_r);
        draw->PutUniform1f("color_g", color_g);
        draw->PutUniform1f("color_b", color_b);
        draw->PutUniform1f("color_a", color_a);

        draw->PutMatrix4fv("mvp", mmvp);
        draw->Draw(EyerGLDrawType::TRIANGLES);

        return 0;
    }
}