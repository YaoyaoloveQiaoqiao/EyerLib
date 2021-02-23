#include "MVPLine.hpp"

#include "EyerGLShader/Shader.hpp"

namespace Eyer
{
    MVPLine::MVPLine(Eyer::EectorF3 & a, Eyer::EectorF3 & b)
    {
        float vertex[] = {
                a.x(), a.y(), a.z(),
                b.x(), b.y(), b.z(),
        };
        float coor[] = {
                a.x(), a.y(), a.z(),
                b.x(), b.y(), b.z(),
        };
        unsigned int vertexIndex[] = {
                0, 1,
        };

        draw = new EyerGLDraw(EYER_GL_SHADER::MVP_GEOM_VERTEX_SHADER, EYER_GL_SHADER::MVP_GEOM_FRAGMENT_SHADER);
        draw->Init();

        vao = new EyerGLVAO();

        vao->AddVBO(vertex, sizeof(vertex), 0);
        vao->AddVBO(coor, sizeof(coor), 1);
        vao->SetEBO(vertexIndex, sizeof(vertexIndex));

        draw->SetVAO(vao);
    }

    MVPLine::~MVPLine()
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

    int MVPLine::Draw()
    {
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