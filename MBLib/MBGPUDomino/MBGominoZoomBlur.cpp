#include "MBGPUDomino.hpp"
#include "MBGLShader/Shader.hpp"

namespace MB
{
    MBGominoZoomBlur::MBGominoZoomBlur() : MBGomino("ZoomBlur")
    {

    }

    MBGominoZoomBlur::~MBGominoZoomBlur()
    {

    }

    int MBGominoZoomBlur::Go(MBGLTexture * input, MBGLTexture * output, int width, int height)
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


            float perspective = 0.3;

            const int samples = 200;
            const float minBlur = 0.1;
            const float maxBlur = 0.3;
            const float speed = 3.0;

            void main(){
                vec2 TexCoords = vec2(outCoor.x, outCoor.y);
                // vec3 rgb = texture(imageTex, TexCoords).rgb;

                vec2 p = TexCoords;

                vec4 result = vec4(0);

                float timeQ = mix(minBlur, maxBlur, 0.5);
                for (int i=0; i<=samples; i++)
                {        
                    float q = float(i) / float(samples);
                    result += texture(imageTex, p + (vec2(0.5)-p)*q*timeQ)/float(samples);
                }

                colorFrag = result;
            }

        );


        MBGLFrameBuffer frameBuffer(width, height, output);

        frameBuffer.ClearAllComponent();
        frameBuffer.Clear();

        MBCommonComponent commonComponent(V_SHADER, F_SHADER);
        commonComponent.SetTexture(input);
        commonComponent.SetWH(width, height);

        frameBuffer.AddComponent(&commonComponent);

        frameBuffer.Draw();

        frameBuffer.ClearAllComponent();

        return 0;
    }
}