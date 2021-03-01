#include "MVPCustomG.hpp"

#include "EyerGLShader/Shader.hpp"

namespace Eyer
{
    MVPCustomG::MVPCustomG(float * vertex, int vertexLen, float * coor, int coorLen, unsigned int * vertexIndex, int vertexIndexLen)
    {
        char * VERTEX_SHADER = (char *)SHADER(
                layout (location = 0) in vec3 pos;
                layout (location = 1) in vec3 coor;
                out vec3 outCoor;

                uniform mat4 mvp;

                void main(){
                    outCoor = coor;
                    gl_Position = mvp * vec4(pos * 1.0, 1.0);
                    gl_PointSize = 5.0;
                }
        );
        char * FRAGMENT_SHADER = (char *)SHADER(
              out vec4 color;
              in vec3 outCoor;

              uniform float color_r;
              uniform float color_g;
              uniform float color_b;
              uniform float color_a;

              void main()
              {
                  color = vec4(outCoor, color_a);
                  color = pow(color, vec4(1.4));
              }
        );


        draw = new EyerGLDraw(VERTEX_SHADER, FRAGMENT_SHADER);
        draw->Init();

        vao = new EyerGLVAO();

        vao->AddVBO(vertex, vertexLen, 0);
        vao->AddVBO(coor, coorLen, 1);
        vao->SetEBO(vertexIndex, vertexIndexLen);

        draw->SetVAO(vao);
    }

    MVPCustomG::~MVPCustomG()
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

    int MVPCustomG::SetMVP(EatrixF4x4 & mat)
    {
        mvp = mat;
        return 0;
    }

    int MVPCustomG::Draw()
    {
        EatrixF4x4 mvp = vpMat * modelMat;

        draw->PutUniform1f("color_r", color.x());
        draw->PutUniform1f("color_g", color.y());
        draw->PutUniform1f("color_b", color.z());
        draw->PutUniform1f("color_a", color.w());

        draw->PutMatrix4fv("mvp", mvp);
        draw->Draw(EyerGLDrawType::TRIANGLES);
    }
}