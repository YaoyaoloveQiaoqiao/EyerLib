#include "MBGL.hpp"

#include "GLHeader.h"

namespace MB
{
    MBGLDraw::MBGLDraw(MBString _vertexShaderSrc, MBString _fragmentShaderSrc, MBGLContext * _ctx)
    {
        ctx = _ctx;

        vertexShaderSrc = _vertexShaderSrc;
        fragmentShaderSrc = _fragmentShaderSrc;

        program = new MBGLProgram(vertexShaderSrc, fragmentShaderSrc, ctx);
    }

    MBGLDraw::~MBGLDraw()
    {
        if(program != nullptr){
            delete program;
            program = nullptr;
        }
    }

    int MBGLDraw::Init()
    {
        if(program == nullptr){
            return -1;
        }

        program->LinkProgram();

        return 0;
    }

    int MBGLDraw::PutTexture(MBString uniform, MBGLTexture * texture, int textureIndex)
    {
        program->UseProgram();

#ifdef QT_EYER_PLAYER
        ctx->glActiveTexture(GL_TEXTURE0 + textureIndex);
        ctx->glBindTexture(GL_TEXTURE_2D, texture->GL_GetTextureId());
#else
        glActiveTexture(GL_TEXTURE0 + textureIndex);
        glBindTexture(GL_TEXTURE_2D, texture->GL_GetTextureId());
#endif
        program->PutUniform1i(uniform.str, textureIndex);

        return 0;
    }

    int MBGLDraw::PutMatrix4fv(MBString uniform, MBMat4x4 & mat)
    {
        program->UseProgram();
        program->PutMatrix4fv(uniform, mat);
        return 0;
    }

    int MBGLDraw::PutUniform1f(MBString uniform, float val)
    {
        program->UseProgram();
        program->PutUniform1f(uniform, val);
        return 0;
    }

    int MBGLDraw::SetVAO(MBGLVAO * _vao)
    {
        vao = _vao;
        return 0;
    }

    int MBGLDraw::Draw()
    {
        if(program == nullptr){
            return -1;
        }

        if(vao == nullptr){
            return -2;
        }

        program->UseProgram();

        vao->DrawVAO();

#ifdef QT_EYER_PLAYER
        ctx->glFinish();
#else
        glFinish();
#endif

        return 0;
    }
}