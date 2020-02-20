#include "Shader.hpp"

namespace Eyer
{
    char * GL_SHADER::TEST_VERTEX_SHADER = SHADER(
        layout (location = 0) in vec3 pos;
        void main(){
            gl_Position = vec4(pos * 1.0, 1.0);
        }
    );

    char * GL_SHADER::TEST_FRAGMENT_SHADER = SHADER(
        out vec4 color;

        void main()
        {
            color = vec4(1.0f, 0.0f, 0.0f, 1.0f);
        }
    );




    char * GL_SHADER::YUV_VIDEO_VERTEX_SHADER = SHADER(
        layout (location = 0) in vec3 pos;
        layout (location = 1) in vec3 coor;

        out vec3 outCoor;

        void main(){
            outCoor = coor;
            gl_Position = vec4(pos * 1.0, 1.0);
        }
    );

    char * GL_SHADER::YUV_VIDEO_FRAGMENT_SHADER = SHADER(
        out vec4 color;
        in vec3 outCoor;
        uniform sampler2D numberTex;

        void main()
        {
            vec2 TexCoords = vec2(outCoor.x, 1.0 - outCoor.y);
            color = texture(numberTex, TexCoords);
        }
    );

    char * GL_SHADER::TEXT_VERTEX_SHADER = SHADER(
        layout (location = 0) in vec3 pos;
        layout (location = 1) in vec3 coor;

        out vec3 outCoor;
        uniform mat4 mat;

        void main(){
            outCoor = coor;
            gl_Position = mat * vec4(pos * 1.0, 1.0);
        }
    );

    char * GL_SHADER::TEXT_FRAGMENT_SHADER = SHADER(
        out vec4 color;
        in vec3 outCoor;
        uniform sampler2D charTex;

        uniform float color_r;
        uniform float color_g;
        uniform float color_b;

        void main(){
            vec2 TexCoords = vec2(outCoor.x, 1.0 - outCoor.y);
            float r = texture(charTex, TexCoords).r;

            color = vec4(color_r, color_g, color_b, r);
        }
    );

    char * GL_SHADER::POINT_VERTEX_SHADER = SHADER(
                                                layout (location = 0) in vec3 pos;
                                                layout (location = 1) in vec3 coor;

                                                out vec3 outCoor;
                                                uniform mat4 mat;

                                                void main(){
                                                    outCoor = coor;
                                                    gl_Position = mat * vec4(pos * 1.0, 1.0);
                                                }
    );
    char * GL_SHADER::POINT_FRAGMENT_SHADER = SHADER(
                                                  out vec4 color;
                                                  in vec3 outCoor;
                                                  void main(){
                                                      color = vec4(0.0, 1.0, 0.0, 1.0);
                                                  }
    );


    char * GL_SHADER::SINGLE_TEXTURE_VERTEX_SHADER = SHADER(
            layout (location = 0) in vec3 pos;
            layout (location = 1) in vec3 coor;

            out vec3 outCoor;
            void main(){
                outCoor = coor;
                gl_Position = vec4(pos, 1.0);
            }
            );

    char * GL_SHADER::SINGLE_TEXTURE_FRAGMENT_SHADER = SHADER(
            out vec4 color;
            uniform sampler2D imageTex;
            in vec3 outCoor;
            void main(){
                vec2 TexCoords = vec2(outCoor.x, 1.0 - outCoor.y);
                vec3 rgb = texture(imageTex, TexCoords).rgb;
                color = vec4(rgb, 1.0);
            }
            );


    char * GL_SHADER::FRAME_VERTEX_SHADER = SHADER(
            layout (location = 0) in vec3 pos;
            layout (location = 1) in vec3 coor;

            out vec3 outCoor;

            void main()
            {
                outCoor = coor;
                gl_Position = vec4(pos, 1.0);
            }
            );

    char * GL_SHADER::FRAME_FRAGMENT_SHADER = SHADER(
            out vec4 color;
            uniform sampler2D y;
            in vec3 outCoor;
            void main(){
                vec2 TexCoords = vec2(outCoor.x, 1.0 - outCoor.y);
                vec3 rgb = texture(y, TexCoords).rgb;
                color = vec4(rgb, 1.0);
            }
            );
}