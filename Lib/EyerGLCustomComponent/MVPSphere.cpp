#include "EyerGLCustomComponent.hpp"
#include "EyerGLShader/Shader.hpp"
#include "EyerGL/EyerGL.hpp"
#include "MVPSphere.hpp"

namespace Eyer
{
    MVPSphere::MVPSphere()
    {
        float vertex[] = {};
        float coor[] = {};
        unsigned int vertexIndex[] = {};

        draw = new EyerGLDraw(EYER_GL_SHADER::MVP_GEOM_VERTEX_SHADER, EYER_GL_SHADER::MVP_GEOM_FRAGMENT_SHADER);
        draw->Init();

        vao = new EyerGLVAO();

        std::vector<float> v = GenVBO();
        std::vector<float> c = GenTextureCoordinates();
        std::vector<unsigned int> i = GenEBO();

        vao->AddVBO(&v[0], v.size() * sizeof(float), 0);
        vao->AddVBO(&c[0], c.size() * sizeof(float), 1);
        vao->SetEBO(&i[0], i.size() * sizeof(unsigned int));

        draw->SetVAO(vao);
    }

    MVPSphere::~MVPSphere()
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

    int MVPSphere::SetMVP(EatrixF4x4 & mat)
    {
        mvp = mat;
        return 0;
    }

    int MVPSphere::SetPos(float x, float y, float z)
    {
        mTrans.SetTrans(x, y, z);
        return 0;
    }

    int MVPSphere::SetColor(float r, float g, float b, float a)
    {
        color_r = r;
        color_g = g;
        color_b = b;
        color_a = a;
        return 0;
    }

    int MVPSphere::Draw()
    {
        EatrixF4x4 mvp = vpMat * modelMat;

        draw->PutUniform1f("color_r", color_r);
        draw->PutUniform1f("color_g", color_g);
        draw->PutUniform1f("color_b", color_b);
        draw->PutUniform1f("color_a", color_a);

        draw->PutMatrix4fv("mvp", mvp);
        draw->Draw(EyerGLDrawType::TRIANGLES);
        return 0;
    }

    std::vector<float> MVPSphere::GenVBO(){
        std::vector<float> c;
        float R = 0.5f;    // 半径
        float angleHy = (float)(2 * M_PI) / statcky;    // 横向每份的角度        算出弧度值
        float angleZx = (float)(2 * M_PI) / stlicex;    // 纵向每份的角度        算出弧度值
        // GLfloat NumAngleHy = 0;    // 当前横向角度
        // GLfloat NumAngleZx = 0;    // 当前纵向角度
        float rad_i,rad_j;
        for (int j = 0; j <=statcky; j++ ) {
            rad_j = M_PI*((float)j/statcky);
            for (int i = 0; i <=stlicex; i++) {
                rad_i=2*M_PI*i/stlicex;
                // NumAngleHy = angleHy*i;
                // NumAngleZx = angleZx*j; // 起点都是轴指向的方向。根据右手定则决定转向，只要转向相同，那么两个就合适
                float x = R*cos(rad_i)*sin(rad_j);    // 记得转化精度
                float y = R*cos(rad_j);
                float z = R*sin(rad_i)*sin(rad_j);
                c.push_back(x);
                c.push_back(y);
                c.push_back(z);
            }
        }
        return c;
    }

    std::vector<unsigned int> MVPSphere::GenEBO(){
        std::vector<unsigned int> ebo;
        std::vector<float> vbo = GenVBO();

        for (int i=0; i<stlicex; i++){
            for (int j=0; j<statcky; j++) {
                ebo.push_back(j*    (stlicex+1)+i);
                ebo.push_back((j+1)*(stlicex+1)+i);
                ebo.push_back(j    *(stlicex+1)+i+1);
                ebo.push_back(j    *(stlicex+1)+i+1);
                ebo.push_back((j+1)*(stlicex+1)+i);
                ebo.push_back((j+1)*(stlicex+1)+i+1);
            }
        }
        return ebo;
    }

    std::vector<float> MVPSphere::GenTextureCoordinates(){
        std::vector<float> texCoords;
        for(int j=0; j<=statcky; j++) {
            float radj = j * 1.0 / statcky;
            for(int i=0; i<=stlicex; i++) {
                float radi = i * 1.0 / stlicex;
                texCoords.push_back(radi);
                texCoords.push_back(radj);
                texCoords.push_back(0.0);
            }
        }
        return texCoords;
    }
}