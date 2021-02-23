#include <EyerGLShader/Shader.hpp>
#include "MVPImagePlane.hpp"
#include "EyerImage/EyerImage.hpp"

namespace Eyer
{
    MVPImagePlane::MVPImagePlane(unsigned char * pngData, int pngDataSize)
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

        draw = new EyerGLDraw(EYER_GL_SHADER::IMAGE_PLANE_VERTEX_SHADER, EYER_GL_SHADER::IMAGE_PLANE_FRAGMENT_SHADER);
        draw->Init();

        vao = new EyerGLVAO();

        vao->AddVBO(vertex, sizeof(vertex), 0);
        vao->AddVBO(coor, sizeof(coor), 1);
        vao->SetEBO(vertexIndex, sizeof(vertexIndex));

        draw->SetVAO(vao);

        EyerImageBuffer imageBuffer;

        EyerImageReader imageReader;
        imageReader.Reader(pngData, pngDataSize, imageBuffer);

        texture = new EyerGLTexture();
        texture->SetDataRGBAChannel(imageBuffer.GetPtr(), imageBuffer.width, imageBuffer.height);

        // EyerLog("Width: %d, Height: %d\n", imageBuffer.width, imageBuffer.height);
    }

    MVPImagePlane::~MVPImagePlane()
    {
        if(vao != nullptr){
            delete vao;
            vao = nullptr;
        }
        if(draw != nullptr){
            delete draw;
            draw = nullptr;
        }
        if(texture != nullptr){
            delete texture;
            texture = nullptr;
        }
    }

    int MVPImagePlane::Draw()
    {
        EatrixF4x4 mvp = vpMat * modelMat;
        draw->PutTexture("image", texture, 0);
        draw->PutMatrix4fv("mvp", mvp);
        draw->Draw();
        return 0;
    }
}