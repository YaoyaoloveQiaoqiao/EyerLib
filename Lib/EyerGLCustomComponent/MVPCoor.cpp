#include "EyerGLCustomComponent.hpp"
#include "EyerGLShader/Shader.hpp"
#include "MVPCoor.hpp"

namespace Eyer {
    MVPCoor::MVPCoor()
    {
        {
            float vertex[] = {
                    -1.0f, 0.0f, 0.0f,
                    1.0f, 0.0f, 0.0f,
            };
            float coor[] = {
                    0.0f, 0.0f, 0.0f,
                    1.0f, 0.0f, 0.0f,
            };
            unsigned int vertexIndex[] = {
                    0, 1
            };

            drawX = new EyerGLDraw(EYER_GL_SHADER::MVP_GEOM_VERTEX_SHADER, EYER_GL_SHADER::MVP_GEOM_FRAGMENT_SHADER);
            drawX->Init();

            vaoX = new EyerGLVAO();

            vaoX->AddVBO(vertex, sizeof(vertex), 0);
            vaoX->AddVBO(coor, sizeof(coor), 1);
            vaoX->SetEBO(vertexIndex, sizeof(vertexIndex));

            drawX->SetVAO(vaoX);
        }


        {
            float vertex[] = {
                    0.0f, -1.0f, 0.0f,
                    0.0f, 1.0f, 0.0f,
            };
            float coor[] = {
                    0.0f, 0.0f, 0.0f,
                    1.0f, 0.0f, 0.0f,
            };
            unsigned int vertexIndex[] = {
                    0, 1
            };

            drawY = new EyerGLDraw(EYER_GL_SHADER::MVP_GEOM_VERTEX_SHADER, EYER_GL_SHADER::MVP_GEOM_FRAGMENT_SHADER);
            drawY->Init();

            vaoY = new EyerGLVAO();

            vaoY->AddVBO(vertex, sizeof(vertex), 0);
            vaoY->AddVBO(coor, sizeof(coor), 1);
            vaoY->SetEBO(vertexIndex, sizeof(vertexIndex));

            drawY->SetVAO(vaoY);
        }

        {
            float vertex[] = {
                    0.0f, 0.0f, -1.0f,
                    0.0f, 0.0f, 1.0f,
            };
            float coor[] = {
                    0.0f, 0.0f, 0.0f,
                    1.0f, 0.0f, 0.0f,
            };
            unsigned int vertexIndex[] = {
                    0, 1
            };

            drawZ = new EyerGLDraw(EYER_GL_SHADER::MVP_GEOM_VERTEX_SHADER, EYER_GL_SHADER::MVP_GEOM_FRAGMENT_SHADER);
            drawZ->Init();

            vaoZ = new EyerGLVAO();

            vaoZ->AddVBO(vertex, sizeof(vertex), 0);
            vaoZ->AddVBO(coor, sizeof(coor), 1);
            vaoZ->SetEBO(vertexIndex, sizeof(vertexIndex));

            drawZ->SetVAO(vaoZ);
        }
    }

    MVPCoor::~MVPCoor()
    {
        if(drawX != nullptr){
            delete drawX;
            drawX = nullptr;
        }
        if(vaoX != nullptr){
            delete vaoX;
            vaoX = nullptr;
        }

        if(drawY != nullptr){
            delete drawY;
            drawY = nullptr;
        }
        if(vaoY != nullptr){
            delete vaoY;
            vaoY = nullptr;
        }

        if(drawZ != nullptr){
            delete drawZ;
            drawZ = nullptr;
        }
        if(vaoZ != nullptr){
            delete vaoZ;
            vaoZ = nullptr;
        }
    }

    int MVPCoor::SetMVP(EatrixF4x4 &_mvp)
    {
        mvp = _mvp;
        return 0;
    }

    int MVPCoor::SetScale(EectorF3 & size)
    {
        mScale.SetScale(size.x(), size.y(), size.z());
        return 0;
    }

    int MVPCoor::SetColor(EectorF4 & _color)
    {
        color = _color;
        return 0;
    }

    int MVPCoor::Draw()
    {
        EatrixF4x4 mmvp;

        float color_r = color.x();
        float color_g = color.y();
        float color_b = color.z();
        float color_a = color.w();

        {
            // X
            mmvp = mvp * mScale;

            drawX->PutUniform1f("color_r", color_r);
            drawX->PutUniform1f("color_g", color_g);
            drawX->PutUniform1f("color_b", color_b);
            drawX->PutUniform1f("color_a", color_a);

            drawX->PutMatrix4fv("mvp", mmvp);
            drawX->Draw(EyerGLDrawType::LINE_LOOP);
        }

        {
            // Y
            mmvp = mvp * mScale;

            drawY->PutUniform1f("color_r", color_r);
            drawY->PutUniform1f("color_g", color_g);
            drawY->PutUniform1f("color_b", color_b);
            drawY->PutUniform1f("color_a", color_a);

            drawY->PutMatrix4fv("mvp", mmvp);
            drawY->Draw(EyerGLDrawType::LINE_LOOP);
        }

        {
            // Z
            mmvp = mvp * mScale;

            drawZ->PutUniform1f("color_r", color_r);
            drawZ->PutUniform1f("color_g", color_g);
            drawZ->PutUniform1f("color_b", color_b);
            drawZ->PutUniform1f("color_a", color_a);

            drawZ->PutMatrix4fv("mvp", mmvp);
            drawZ->Draw(EyerGLDrawType::LINE_LOOP);
        }

        return 0;
    }
}