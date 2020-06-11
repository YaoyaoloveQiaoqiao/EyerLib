#include "EyerGPUDomino.hpp"
#include "EyerGLShader/Shader.hpp"

namespace Eyer
{
    EyerSplitScreen2::EyerSplitScreen2() : EyerGomino("SplitScreen2")
    {

    }

    EyerSplitScreen2::~EyerSplitScreen2()
    {

    }

    int EyerSplitScreen2::Go(EyerGLTexture * input, EyerGLTexture * output, int width, int height)
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

                                          void main(){
                                              vec2 uv = vec2(outCoor.x, outCoor.y);
                                              // vec3 rgb = texture(imageTex, TexCoords).rgb;
                                              if (uv.x <= 1.0 / 3.0) {
                                                  uv.x = uv.x * 3.0;
                                              }else if (uv.x <= 2.0 / 3.0) {
                                                  uv.x = (uv.x - 1.0 / 3.0) * 3.0;
                                              }else {
                                                  uv.x = (uv.x - 2.0 / 3.0) * 3.0;
                                              }

                                              if (uv.y <= 1.0 / 3.0) {
                                                  uv.y = uv.y * 3.0;
                                              }else if (uv.y <= 2.0 / 3.0) {
                                                  uv.y = (uv.y - 1.0 / 3.0) * 3.0;
                                              }else {
                                                  uv.y = (uv.y - 2.0 / 3.0) * 3.0;
                                              }

                                              colorFrag = texture2D(Texture, uv);
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