#include "EyerGPUDomino.hpp"
#include "EyerGLShader/Shader.hpp"

namespace Eyer
{
    EyerGominoSoulout::EyerGominoSoulout() : EyerGomino("Soulout")
    {

    }

    EyerGominoSoulout::~EyerGominoSoulout()
    {

    }

    int EyerGominoSoulout::Go(EyerGLTexture * input, EyerGLTexture * output, int width, int height)
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
                                          uniform sampler2D Texture;
                                          in vec3 outCoor;
                                          uniform float Time;

                                          void main(){

                                              float duration = 0.7;
                                              float maxAlpha = 0.4;
                                              float maxScale = 1.8;

                                              vec2 uv = vec2(outCoor.x, outCoor.y);

                                              float progress = mod(Time, duration) / duration; // 0~1
                                              float alpha = maxAlpha * (1.0 - progress);
                                              float scale = 1.0 + (maxScale - 1.0) * progress;

                                              float weakX = 0.5 + (uv.x - 0.5) / scale;
                                              float weakY = 0.5 + (uv.y - 0.5) / scale;
                                              vec2 weakTextureCoords = vec2(weakX, weakY);

                                              vec4 weakMask = texture2D(Texture, weakTextureCoords);

                                              vec4 mask = texture2D(Texture, uv);

                                              colorFrag = mask * (1.0 - alpha) + weakMask * alpha;
                                          }

                                  );


        EyerGLFrameBuffer frameBuffer(width, height, output);

        frameBuffer.ClearAllComponent();
        frameBuffer.Clear();

        EyerCommonComponent commonComponent(V_SHADER, F_SHADER);
        commonComponent.SetTexture(input);
        commonComponent.SetWH(width, height);

        frameBuffer.AddComponent(&commonComponent);

        frameBuffer.Draw();

        frameBuffer.ClearAllComponent();

        return 0;
    }
}