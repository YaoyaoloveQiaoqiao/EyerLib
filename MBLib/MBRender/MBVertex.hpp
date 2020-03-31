#ifndef	EYER_LIB_REDNER_VERTEX_AV_H
#define	EYER_LIB_REDNER_VERTEX_AV_H

#include "MBCore/MBCore.hpp"

namespace MB
{
    class MBVertex
    {
    private:
        MBVec3 pos;
        MBVec3 coor;

        MBVec3 posScale;
    public:
        MBVertex();
        MBVertex(const MBVertex & vertex);
        MBVertex(float px, float py, float pz, float coorx, float coory, float coorz);
        ~MBVertex();

        MBVertex & operator = (const MBVertex & vertex);

        float GetPosX();
        float GetPosY();
        float GetPosZ();

        float GetPosScaleX();
        float GetPosScaleY();
        float GetPosScaleZ();

        float GetCoorX();
        float GetCoorY();
        float GetCoorZ();
    };
}

#endif