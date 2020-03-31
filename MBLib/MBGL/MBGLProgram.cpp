#include "MBGL.hpp"

#include "GLHeader.h"
#include <stdio.h>
#include <stdlib.h>

namespace MB
{
    MBGLProgram::MBGLProgram(MBString _vertexShaderSrc, MBString _fragmentShaderSrc, MBGLContext * _ctx)
    {
        ctx = _ctx;
        vertexShaderSrc = _vertexShaderSrc;
        fragmentShaderSrc = _fragmentShaderSrc;
#ifdef QT_EYER_PLAYER
        programId = ctx->glCreateProgram();
#else
        programId = glCreateProgram();
#endif
    }

    MBGLProgram::~MBGLProgram()
    {
        if(programId != 0) {
#ifdef QT_EYER_PLAYER
            ctx->glDeleteProgram(programId);
#else
            glDeleteProgram(programId);
#endif
            programId = 0;
        }
    }

    int MBGLProgram::LinkProgram()
    {
        MB::MBGLShader vertexShader(MB::MBGLShaderType::VERTEX_SHADER, vertexShaderSrc);
        vertexShader.Compile();

        MB::MBGLShader fragmentShader(MB::MBGLShaderType::FRAGMENT_SHADER, fragmentShaderSrc);
        fragmentShader.Compile();

#ifdef QT_EYER_PLAYER
        ctx->glAttachShader(programId, vertexShader.GL_GetShaderId());
        ctx->glAttachShader(programId, fragmentShader.GL_GetShaderId());

        ctx->glLinkProgram(programId);

        GLint Result = GL_FALSE;
        int InfoLogLength;

        // Check the program
        ctx->glGetProgramiv(programId, GL_LINK_STATUS, &Result);
        ctx->glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &InfoLogLength);
        if ( InfoLogLength > 0 ){
            std::vector<char> ProgramErrorMessage(InfoLogLength+1);
            ctx->glGetProgramInfoLog(programId, InfoLogLength, NULL, &ProgramErrorMessage[0]);
            MBLog("%s\n", &ProgramErrorMessage[0]);

            MBLog("%s\n", vertexShaderSrc.str);
            MBLog("%s\n", fragmentShaderSrc.str);
        }
#else
        glAttachShader(programId, vertexShader.GL_GetShaderId());
        glAttachShader(programId, fragmentShader.GL_GetShaderId());

        glLinkProgram(programId);

        GLint Result = GL_FALSE;
        int InfoLogLength;

        // Check the program
        glGetProgramiv(programId, GL_LINK_STATUS, &Result);
        glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &InfoLogLength);
        if ( InfoLogLength > 0 ){
            std::vector<char> ProgramErrorMessage(InfoLogLength+1);
            glGetProgramInfoLog(programId, InfoLogLength, NULL, &ProgramErrorMessage[0]);
            MBLog("%s\n", &ProgramErrorMessage[0]);

            MBLog("%s\n", vertexShaderSrc.str);
            MBLog("%s\n", fragmentShaderSrc.str);
        }
#endif


        return 0;
    }

    int MBGLProgram::UseProgram()
    {
#ifdef QT_EYER_PLAYER
        ctx->glUseProgram(programId);
#else
        glUseProgram(programId);
#endif

        return 0;
    }

    int MBGLProgram::PutUniform1i(MBString key, int value)
    {
#ifdef QT_EYER_PLAYER
        GLuint location = ctx->glGetUniformLocation(programId, key.str);
        ctx->glUniform1i(location, value);
#else
        GLuint location = glGetUniformLocation(programId, key.str);
        glUniform1i(location, value);
#endif


        return 0;
    }

    int MBGLProgram::PutUniform1f(MBString key, float value)
    {
#ifdef QT_EYER_PLAYER
        GLuint location = ctx->glGetUniformLocation(programId, key.str);
        ctx->glUniform1f(location, value);
#else
        GLuint location = glGetUniformLocation(programId, key.str);
        glUniform1f(location, value);
#endif

        return 0;
    }

    int MBGLProgram::PutMatrix4fv(MBString key, MBMat4x4 & _mat)
    {
#ifdef QT_EYER_PLAYER
        GLuint location = ctx->glGetUniformLocation(programId, key.str);
#else
        GLuint location = glGetUniformLocation(programId, key.str);
#endif


        MBMat4x4 mat = ~_mat;
        int matLen = mat.GetMatLen();
        float * m = (float *)malloc(matLen);
        mat.GetMat(m);

#ifdef QT_EYER_PLAYER
        ctx->glUniformMatrix4fv(location, 1, GL_FALSE, m);
#else
        glUniformMatrix4fv(location, 1, GL_FALSE, m);
#endif

        free(m);

        return 0;
    }
}
