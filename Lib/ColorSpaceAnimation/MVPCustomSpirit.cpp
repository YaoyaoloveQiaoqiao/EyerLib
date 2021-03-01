#include "MVPCustomSpirit.hpp"

namespace Eyer
{
    MVPCustomSpirit::MVPCustomSpirit(float * _vertex, int _vertexLen, float * _coor, int _coorLen, unsigned int * _vertexIndex, int _vertexIndexLen)
    {
        vertexLen = _vertexLen;
        vertex = (float *)malloc(vertexLen);
        memcpy(vertex, _vertex, vertexLen);

        coorLen = _coorLen;
        coor = (float *)malloc(coorLen);
        memcpy(coor, _coor, coorLen);

        vertexIndexLen = _vertexIndexLen;
        vertexIndex = (unsigned int *)malloc(vertexIndexLen);
        memcpy(vertexIndex, _vertexIndex, vertexIndexLen);
    }

    MVPCustomSpirit::~MVPCustomSpirit()
    {
        if(vertex != nullptr){
            free(vertex);
            vertex = nullptr;
        }

        if(coor != nullptr){
            free(coor);
            coor = nullptr;
        }

        if(vertexIndex != nullptr){
            free(vertexIndex);
            vertexIndex = nullptr;
        }
    }

    int MVPCustomSpirit::RenderInit()
    {
        mvpCustomG = new MVPCustomG(vertex, vertexLen, coor, coorLen, vertexIndex, vertexIndexLen);
        return 0;
    }

    int MVPCustomSpirit::RenderDestory()
    {
        if(mvpCustomG != nullptr){
            delete mvpCustomG;
            mvpCustomG = nullptr;
        }
        return 0;
    }

    int MVPCustomSpirit::RenderContent(EatrixF4x4 & vp, EyerKey & key)
    {
        mvpCustomG->SetColor(key.color);
        mvpCustomG->SetVP(vp);
        mvpCustomG->SetModel(key.position, key.rotato, key.scale);
        mvpCustomG->Draw();
        return 0;
    }
}