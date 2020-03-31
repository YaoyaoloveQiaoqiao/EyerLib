#include "MBGPUDomino.hpp"
#include "MBGLShader/Shader.hpp"

namespace MB
{
    MBCopyTextureComponent::MBCopyTextureComponent()
    {
        char * V_SHADER = (char *)SHADER(
            layout (location = 0) in vec3 pos;
            layout (location = 1) in vec3 coor;

            out vec3 outCoor;

            void main()
            {
                outCoor = coor;
                gl_Position = vec4(pos, 1.0);
            }
        );

        char * F_SHADER = (char *)SHADER(
            out vec4 colorFrag;
            uniform sampler2D imageTex;
            in vec3 outCoor;

            uniform float w;
            uniform float h;

            void main(){
                vec2 TexCoords = vec2(outCoor.x, outCoor.y);
                vec3 rgb = texture(imageTex, TexCoords).rgb;

                colorFrag = vec4(rgb, 1.0);
            }
        );

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

    MBCopyTextureComponent::~MBCopyTextureComponent()
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

    int MBCopyTextureComponent::Draw()
    {
        if(texture != nullptr){
            draw->PutTexture("imageTex",texture);
        }

        draw->PutUniform1f("w", w * 1.0);
        draw->PutUniform1f("h", h * 1.0);

        draw->Draw();
        return 0;
    }

    int MBCopyTextureComponent::SetTexture(MBGLTexture * _texture)
    {
        texture = _texture;
        return 0;
    }

    int MBCopyTextureComponent::SetWH(int _w, int _h)
    {
        w = _w;
        h = _h;
        return 0;
    }
}