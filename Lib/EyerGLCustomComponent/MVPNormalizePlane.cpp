#include "MVPNormalizePlane.hpp"
#include "EyerGLShader/Shader.hpp"

namespace Eyer
{
    MVPNormalizePlane::MVPNormalizePlane()
    {
        float vertex[] = {
                1.0f, 0.0f, 0.0f,
                0.0f, 1.0f, 0.0f,
                0.0f, 0.0f, 1.0f,
        };
        float coor[] = {
                0.0f, 0.0f, 0.0f,
                1.0f, 0.0f, 0.0f,
                0.0f, 1.0f, 0.0f,
        };
        unsigned int vertexIndex[] = {
                0, 1, 2,
        };

        draw = new EyerGLDraw(EYER_GL_SHADER::MVP_GEOM_VERTEX_SHADER, EYER_GL_SHADER::MVP_GEOM_FRAGMENT_SHADER);
        draw->Init();

        vao = new EyerGLVAO();

        vao->AddVBO(vertex, sizeof(vertex), 0);
        vao->AddVBO(coor, sizeof(coor), 1);
        vao->SetEBO(vertexIndex, sizeof(vertexIndex));

        draw->SetVAO(vao);
    }

    MVPNormalizePlane::~MVPNormalizePlane()
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

    int MVPNormalizePlane::SetMVP(EatrixF4x4 & mat)
    {
        mvp = mat;
        return 0;
    }

    int MVPNormalizePlane::Draw()
    {
        EatrixF4x4 mvp = vpMat * modelMat;

        draw->PutUniform1f("color_r", color.x());
        draw->PutUniform1f("color_g", color.y());
        draw->PutUniform1f("color_b", color.z());
        draw->PutUniform1f("color_a", color.w());

        draw->PutMatrix4fv("mvp", mvp);
        draw->Draw(EyerGLDrawType::TRIANGLES);

        return 0;
    }
}