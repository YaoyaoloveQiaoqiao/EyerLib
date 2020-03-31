#include "MBGLCustomComponent.hpp"
#include "MBType/MBType.hpp"
#include "MBGLShader/Shader.hpp"

#ifdef EYER_PLATFORM_WINDOWS
#include <windows.h>
#else
#include <locale.h>
#endif

namespace MB
{
    MBGLTextDraw::MBGLTextDraw(MBString _typeFilePath)
    {
        typeFilePath = _typeFilePath;

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

        {
            typeCreator = new MBType(typeFilePath.str);
            typeCreator->Init();
        }
        {
            pointDraw = new MBGLDraw(GL_SHADER::POINT_VERTEX_SHADER, GL_SHADER::POINT_FRAGMENT_SHADER);
            pointDraw->Init();

            pointVao = new MBGLVAO();
            pointVao->AddVBO(vertex, sizeof(vertex), 0);
            pointVao->AddVBO(coor, sizeof(coor), 1);
            pointVao->SetEBO(vertexIndex, sizeof(vertexIndex));

            pointDraw->SetVAO(pointVao);
        }

        {
            textDraw = new MBGLDraw(GL_SHADER::TEXT_VERTEX_SHADER, GL_SHADER::TEXT_FRAGMENT_SHADER);
            textDraw->Init();

            vao = new MBGLVAO();

            vao->AddVBO(vertex, sizeof(vertex), 0);
            vao->AddVBO(coor, sizeof(coor), 1);
            vao->SetEBO(vertexIndex, sizeof(vertexIndex));

            textDraw->SetVAO(vao);
        }
    }

    MBGLTextDraw::~MBGLTextDraw()
    {
        if(pointVao != nullptr){
            delete pointVao;
            pointVao = nullptr;
        }
        if(pointDraw != nullptr){
            delete pointDraw;
            pointDraw = nullptr;
        }
        if(typeCreator != nullptr){
            delete typeCreator;
            typeCreator = nullptr;
        }
        if(textDraw != nullptr){
            delete textDraw;
            textDraw = nullptr;
        }
        if(vao != nullptr){
            delete vao;
            vao = nullptr;
        }

        std::map<wchar_t, MBGLCacheTexture *>::iterator iter;
        for (iter=textureCache.begin(); iter!=textureCache.end(); iter++){
            MB::MBGLCacheTexture * texture = iter->second;
            delete texture->texture;
            texture->texture = nullptr;
            delete texture;
        }
        textureCache.clear();
    }

    int MBGLTextDraw::GetTextWidth()
    {
        if(text.IsEmpty()){
            return 0;
        }

        char * char_str = text.str;
        int char_strLen = strlen(char_str);

#ifdef EYER_PLATFORM_WINDOWS
        wchar_t * str = nullptr;
        int strLen = MultiByteToWideChar(CP_UTF8, 0, char_str, -1, str, 0);
        str = new wchar_t[strLen];
        MultiByteToWideChar(CP_UTF8, 0, char_str, -1, str, strLen);
#else
        setlocale(LC_CTYPE, "zh_CN.utf8");

        wchar_t * str = nullptr;
        int strLen = mbstowcs(NULL, char_str, 0) + 1;
        str = new wchar_t[strLen];
        int ret = mbstowcs(str, char_str, char_strLen + 1);
#endif

        int x = 0;
        for(int i=0;i<strLen;i++){
            wchar_t c = str[i];
            // wchar_t c = L'喵';

            MB::MBGLCacheTexture * texture = nullptr;
            std::map<wchar_t, MBGLCacheTexture *>::iterator iter = textureCache.find(c);
            if(iter != textureCache.end()) {
                texture = iter->second;
            }
            else{
                int index = typeCreator->GenChar(c, size);
                if(index <= 0){
                    continue;
                }

                MBTypeBitmap bitmap;
                typeCreator->GetCharBitmap(index, &bitmap);

                MB::MBGLTexture * ttt = new MB::MBGLTexture();
                ttt->SetDataRedChannel(bitmap.data, bitmap.width, bitmap.height);

                MBGLCacheTexture * t = new MBGLCacheTexture();
                t->texture = ttt;
                t->width = bitmap.width;
                t->height = bitmap.height;
                t->bearingY = bitmap.bearingY;
                t->bearingX = bitmap.bearingX;
                t->advance = bitmap.advance;

                textureCache.insert(std::pair<wchar_t, MBGLCacheTexture *>(c, t));

                texture = t;
            }

            if(texture == nullptr){
                continue;
            }

            x += texture->width;
            if(i < strLen - 1) {
                x += texture->advance / 64 - texture->width - texture->bearingX;
            }
        }

        delete[] str;

        return x;
    }

    int MBGLTextDraw::Draw()
    {
        if(text.IsEmpty()){
            return -1;
        }
        char * char_str = text.str;
        int char_strLen = strlen(char_str);

#ifdef EYER_PLATFORM_WINDOWS
        wchar_t * str = nullptr;
        int strLen = MultiByteToWideChar(CP_UTF8, 0, char_str, -1, str, 0);
        str = new wchar_t[strLen];
        MultiByteToWideChar(CP_UTF8, 0, char_str, -1, str, strLen);
#else
        setlocale(LC_CTYPE, "zh_CN.utf8");

        wchar_t * str = nullptr;
        int strLen = mbstowcs(NULL, char_str, 0) + 1;
        str = new wchar_t[strLen];
        int ret = mbstowcs(str, char_str, char_strLen + 1);
#endif
        

        int x = 0;
        for(int i=0;i<strLen;i++){
            MB::MBGLCacheTexture * texture = nullptr;
            wchar_t c = str[i];
            // wchar_t c = L'喵';
            // wchar_t c = L'大';

            std::map<wchar_t, MBGLCacheTexture *>::iterator iter = textureCache.find(c);
            if(iter != textureCache.end()) {
                texture = iter->second;
            }
            else{
                int index = typeCreator->GenChar(c, size);
                if(index <= 0){
                    continue;
                }

                MBTypeBitmap bitmap;
                typeCreator->GetCharBitmap(index, &bitmap);

                MB::MBGLTexture * ttt = new MB::MBGLTexture();
                ttt->SetDataRedChannel(bitmap.data, bitmap.width, bitmap.height);

                MBGLCacheTexture * t = new MBGLCacheTexture();
                t->texture = ttt;
                t->width = bitmap.width;
                t->height = bitmap.height;
                t->bearingY = bitmap.bearingY;
                t->bearingX = bitmap.bearingX;
                t->advance = bitmap.advance;

                textureCache.insert(std::pair<wchar_t, MBGLCacheTexture *>(c, t));

                texture = t;
            }

            // 缩放高度到 1.0
            float heightScale = texture->height * 1.0f / height;
            float widthScale = texture->width * 1.0 / width;

            float bearingYScale = texture->bearingY * 1.0 / height * 2.0;

            MB::MBMat4x4 matScale;
            matScale.SetScale(widthScale, heightScale, 1.0);

            float posX = positionX / width * 2.0 - 1.0;
            float posY = -(positionY / height * 2.0 - 1.0);

            MB::MBMat4x4 matTrans;
            matTrans.SetTrans(posX + widthScale + (x * 1.0 / width * 2.0), posY - heightScale + bearingYScale, 0.0);

            x += texture->width;
            x += texture->advance / 64 - texture->width - texture->bearingX;

            MB::MBMat4x4 mat = (matTrans * matScale);

            // MBLog("Render: %c %d %d\n", c, texture->width, texture->height);

            textDraw->PutTexture("charTex", texture->texture);
            textDraw->PutMatrix4fv("mat", mat);

            textDraw->PutUniform1f("color_r", r);
            textDraw->PutUniform1f("color_g", g);
            textDraw->PutUniform1f("color_b", b);

            textDraw->Draw();
        }

        delete[] str;

        return 0;
    }

    int MBGLTextDraw::SetText(MBString _text)
    {
        text = _text;
        return 0;
    }

    int MBGLTextDraw::SetSize(float _size)
    {
        size = _size;
        return 0;
    }

    int MBGLTextDraw::SetPos(float x, float y)
    {
        positionX = x;
        positionY = y;
        return 0;
    }

    int MBGLTextDraw::SetColor(float _r, float _g, float _b)
    {
        r = _r;
        g = _g;
        b = _b;
        return 0;
    }

}