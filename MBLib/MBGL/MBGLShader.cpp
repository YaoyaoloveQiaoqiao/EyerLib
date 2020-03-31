#include "MBGL.hpp"

#include "GLHeader.h"

namespace MB{
    MBGLShader::MBGLShader(MBGLShaderType _type, MBString _src, MBGLContext * _ctx)
    {
        ctx = _ctx;

        type = _type;
        src = _src;

        GLenum shaderType = GL_VERTEX_SHADER;
        if(type == MBGLShaderType::VERTEX_SHADER){
            shaderType = GL_VERTEX_SHADER;
        }
        if(type == MBGLShaderType::FRAGMENT_SHADER){
            shaderType = GL_FRAGMENT_SHADER;
        }

#ifdef QT_EYER_PLAYER
        shaderId = ctx->glCreateShader(shaderType);
#else
        shaderId = glCreateShader(shaderType);
#endif

    }

    MBGLShader::~MBGLShader()
    {
        if(shaderId != 0){
#ifdef QT_EYER_PLAYER
            ctx->glDeleteShader(shaderId);
#else
            glDeleteShader(shaderId);
#endif

            shaderId = 0;
        }
    }

    int MBGLShader::Compile()
    {
        if(shaderId == 0){
            return -1;
        }

#ifdef QT_EYER_PLAYER
        // MBLog("Shader Src:\n %s\n", src.str);
        ctx->glShaderSource(shaderId, 1, &src.str , NULL);
        ctx->glCompileShader(shaderId);

        GLint Result = GL_FALSE;
        int InfoLogLength;
        ctx->glGetShaderiv(shaderId, GL_COMPILE_STATUS, &Result);
        ctx->glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &InfoLogLength);
        if ( InfoLogLength > 0 ){
            std::vector<char> ShaderErrorMessage(InfoLogLength+1);
            ctx->glGetShaderInfoLog(shaderId, InfoLogLength, NULL, &ShaderErrorMessage[0]);
            MBLog("%s\n", &ShaderErrorMessage[0]);

            MBLog("Shader Src:\n %s\n", src.str);
        }
#else
        // MBLog("Shader Src:\n %s\n", src.str);
        glShaderSource(shaderId, 1, &src.str , NULL);
        glCompileShader(shaderId);

        GLint Result = GL_FALSE;
        int InfoLogLength;
        glGetShaderiv(shaderId, GL_COMPILE_STATUS, &Result);
        glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &InfoLogLength);
        if ( InfoLogLength > 0 ){
            std::vector<char> ShaderErrorMessage(InfoLogLength+1);
            glGetShaderInfoLog(shaderId, InfoLogLength, NULL, &ShaderErrorMessage[0]);
            MBLog("%s\n", &ShaderErrorMessage[0]);

            MBLog("Shader Src:\n %s\n", src.str);
        }
#endif

        return 0;
    }

    unsigned int MBGLShader::GL_GetShaderId()
    {
        return shaderId;
    }
}
