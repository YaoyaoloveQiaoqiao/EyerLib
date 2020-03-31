#include "MBGPUDomino.hpp"
#include "MBGLShader/Shader.hpp"

namespace MB
{
    MBGaussianBlurComponent::MBGaussianBlurComponent()
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

            float SCurve (float x) {
                x = x * 2.0 - 1.0;
                return -x * abs(x) * 0.5 + x + 0.5;
            }

            vec4 BlurH (sampler2D source, vec2 size, vec2 uv, float radius) {
                if (radius >= 1.0)
                {
                    vec4 A = vec4(0.0);
                    vec4 C = vec4(0.0);

                    float width = 1.0 / size.x;

                    float divisor = 0.0;
                    float weight = 0.0;

                    float radiusMultiplier = 1.0 / radius;

                    for (float x = -20.0; x <= 20.0; x++)
                    {
                        A = texture(source, uv + vec2(x * width, 0.0));
                        weight = SCurve(1.0 - (abs(x) * radiusMultiplier));
                        C += A * weight;
                        divisor += weight;
                    }

                    return vec4(C.r / divisor, C.g / divisor, C.b / divisor, 1.0);
                }

                return texture(source, uv);
            }

            void main(){
                vec2 TexCoords = vec2(outCoor.x, outCoor.y);
                // vec3 rgb = texture(imageTex, TexCoords).rgb;

                // color = vec4(rgb.r, 1.0);
                vec4 color = vec4(1.0);

                vec2 uv = TexCoords;

                vec2 resolution = vec2(w, h);

                color = BlurH(imageTex, resolution.xy, uv, 20.0);

                colorFrag = color;
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

    MBGaussianBlurComponent::~MBGaussianBlurComponent()
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

    int MBGaussianBlurComponent::Draw()
    {
        if(texture != nullptr){
            draw->PutTexture("imageTex",texture);
        }

        draw->PutUniform1f("w", w * 1.0);
        draw->PutUniform1f("h", h * 1.0);

        draw->Draw();
        return 0;
    }

    int MBGaussianBlurComponent::SetTexture(MBGLTexture * _texture)
    {
        texture = _texture;
        return 0;
    }

    int MBGaussianBlurComponent::SetWH(int _w, int _h)
    {
        w = _w;
        h = _h;
        return 0;
    }
}