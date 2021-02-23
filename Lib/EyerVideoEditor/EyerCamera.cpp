#include "EyerCamera.hpp"

namespace Eyer
{
    int EyerCamera::RenderInit()
    {
        return 0;
    }

    int EyerCamera::RenderDestory()
    {
        return 0;
    }

    int EyerCamera::RenderContent(EatrixF4x4 & _vp, EyerKey & key)
    {
        EatrixF4x4 p;
        p.SetPerspective(Eath::DegreesToRadians(60.0), w * 1.0 / h, 0.1, 100.0);

        EatrixF4x4 v;
        v.LookAt(key.position.x(), key.position.y(), key.position.z(),
                 key.cameraTarget.x(), key.cameraTarget.y(), key.cameraTarget.z(),
                 0.0, 1.0, 0.0);

        vp = p * v;

        return 0;
    }

    int EyerCamera::SetWH(int _w, int _h)
    {
        w = _w;
        h = _h;
        return 0;
    }
}