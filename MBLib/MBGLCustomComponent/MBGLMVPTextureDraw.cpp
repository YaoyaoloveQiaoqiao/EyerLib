#include "MBGLCustomComponent.hpp"
#include "MBGLShader/Shader.hpp"

namespace MB
{
    MBGLMVPTextureDraw::MBGLMVPTextureDraw()
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


        textureDraw = new MBGLDraw(GL_SHADER::MVP_TEXTURE_VERTEX_SHADER, GL_SHADER::MVP_TEXTURE_FRAGMENT_SHADER);
        textureDraw->Init();

        vao = new MBGLVAO();

        vao->AddVBO(vertex, sizeof(vertex), 0);
        vao->AddVBO(coor, sizeof(coor), 1);
        vao->SetEBO(vertexIndex, sizeof(vertexIndex));

        textureDraw->SetVAO(vao);
    }

    MBGLMVPTextureDraw::~MBGLMVPTextureDraw()
    {
        if(textureDraw != nullptr){
            delete textureDraw;
            textureDraw = nullptr;
        }
        if(vao != nullptr){
            delete vao;
            vao = nullptr;
        }
    }

    int MBGLMVPTextureDraw::SetTexture(MBGLTexture * _texture)
    {
        texture = _texture;
        return 0;
    }

    int MBGLMVPTextureDraw::SetMVP(MBMat4x4 & _mvp)
    {
        mvp = _mvp;
        return 0;
    }

    int MBGLMVPTextureDraw::Draw()
    {
        if(texture != nullptr){
            textureDraw->PutTexture("imageTex",texture);
        }

        textureDraw->PutMatrix4fv("mvp", mvp);

        textureDraw->Draw();

        return 0;
    }
}