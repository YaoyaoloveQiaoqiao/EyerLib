#include "MBGLCustomComponent.hpp"
#include "MBGLShader/Shader.hpp"

namespace MB
{
    MBGLFrameDraw::MBGLFrameDraw()
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

        textureDraw = new MBGLDraw(GL_SHADER::FRAME_VERTEX_SHADER, GL_SHADER::FRAME_FRAGMENT_SHADER);
        textureDraw->Init();


        vao = new MBGLVAO();

        vao->AddVBO(vertex, sizeof(vertex), 0);
        vao->AddVBO(coor, sizeof(coor), 1);
        vao->SetEBO(vertexIndex, sizeof(vertexIndex));

        textureDraw->SetVAO(vao);
    }

    MBGLFrameDraw::~MBGLFrameDraw()
    {
        if(textureDraw != nullptr){
            delete textureDraw;
            textureDraw = nullptr;
        }
        if(vao != nullptr){
            delete vao;
            vao = nullptr;
        }
        if(mvp != nullptr){
            delete mvp;
            mvp = nullptr;
        }
    }

    int MBGLFrameDraw::SetYTexture(MBGLTexture * _yTex)
    {
        yTex = _yTex;
        return 0;
    }

    int MBGLFrameDraw::SetUTexture(MBGLTexture * _uTex)
    {
        uTex = _uTex;
        return 0;
    }

    int MBGLFrameDraw::SetVTexture(MBGLTexture * _vTex)
    {
        vTex = _vTex;
        return 0;
    }

    int MBGLFrameDraw::SetVideoWH(int w, int h)
    {
        videoW = w;
        videoH = h;
        return 0;
    }

    int MBGLFrameDraw::SetMVP(MBMat4x4 & _mvp)
    {
        if(mvp != nullptr){
            delete mvp;
            mvp = nullptr;
        }

        mvp = new MBMat4x4(_mvp);

        return 0;
    }

    int MBGLFrameDraw::Draw()
    {
        if(yTex != nullptr){
            textureDraw->PutTexture("y",yTex, 0);
        }
        if(uTex != nullptr){
            textureDraw->PutTexture("u",uTex, 1);
        }
        if(vTex != nullptr){
            textureDraw->PutTexture("v",vTex, 2);
        }

        if(mvp != nullptr){
            // mvp->Print();
            textureDraw->PutMatrix4fv("mvp", *mvp);
        }

        textureDraw->Draw();
        return 0;
    }
}