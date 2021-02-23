#include <EyerGLShader/Shader.hpp>
#include "MVPCoorLine.hpp"

namespace Eyer
{
    MVPCoorLine::MVPCoorLine()
    {
        draw = new EyerGLDraw(EYER_GL_SHADER::MVP_GEOM_VERTEX_SHADER, EYER_GL_SHADER::MVP_GEOM_FRAGMENT_SHADER);
        draw->Init();
    }

    MVPCoorLine::~MVPCoorLine()
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

    int MVPCoorLine::Draw()
    {
        float vertex[] = {
                0.0f, 0.0f, 0.0f,
                p.x(), p.y(), p.z(),
        };
        float coor[] = {
                0.0f, 0.0f, 0.0f,
                1.0f, 0.0f, 0.0f,
        };
        unsigned int vertexIndex[] = {
                0, 1
        };

        if(vao != nullptr){
            delete vao;
            vao = nullptr;
        }
        vao = new EyerGLVAO();
        vao->AddVBO(vertex, sizeof(vertex), 0);
        vao->AddVBO(coor, sizeof(coor), 1);
        vao->SetEBO(vertexIndex, sizeof(vertexIndex));
        draw->SetVAO(vao);

        EatrixF4x4 scale;
        scale.SetScale(s.x(), s.y(), s.z());
        modelMat = scale;

        EatrixF4x4 mvp = vpMat * modelMat;
        draw->PutUniform1f("color_r", color.x());
        draw->PutUniform1f("color_g", color.y());
        draw->PutUniform1f("color_b", color.z());
        draw->PutUniform1f("color_a", color.w());
        draw->PutMatrix4fv("mvp", mvp);
        draw->Draw(EyerGLDrawType::LINE_LOOP);
        return 0;
    }
}