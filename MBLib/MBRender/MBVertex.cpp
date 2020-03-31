#include "MBVertex.hpp"

namespace MB
{
    MBVertex::MBVertex()
    {

    }

    MBVertex::MBVertex(const MBVertex & vertex)
    {
        pos = vertex.pos;
        coor = vertex.coor;

        posScale = pos;
    }

    MBVertex::MBVertex(float px, float py, float pz, float coorx, float coory, float coorz)
    {
        pos.SetX(px);
        pos.SetY(py);
        pos.SetZ(pz);

        coor.SetX(coorx);
        coor.SetY(coory);
        coor.SetZ(coorz);

        posScale = pos;
    }

    MBVertex::~MBVertex()
    {

    }

    MBVertex & MBVertex::operator = (const MBVertex & vertex)
    {
        pos = vertex.pos;
        coor = vertex.coor;
        return *this;
    }

    float MBVertex::GetPosX()
    {
        return pos.x();
    }

    float MBVertex::GetPosY()
    {
        return pos.y();
    }

    float MBVertex::GetPosZ()
    {
        return pos.z();
    }

    float MBVertex::GetCoorX()
    {
        return coor.x();
    }

    float MBVertex::GetCoorY()
    {
        return coor.y();
    }

    float MBVertex::GetCoorZ()
    {
        return coor.z();
    }

    float MBVertex::GetPosScaleX()
    {
        return posScale.x();
    }

    float MBVertex::GetPosScaleY()
    {
        return posScale.y();
    }

    float MBVertex::GetPosScaleZ()
    {
        return posScale.z();
    }
}