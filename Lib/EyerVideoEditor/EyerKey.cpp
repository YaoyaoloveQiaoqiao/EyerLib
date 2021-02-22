#include "EyerKey.hpp"

namespace Eyer
{
    EyerKey::EyerKey()
    {
        position = EectorF3(0.0, 0.0, 0.0);
        rotato = EectorF3(0.0, 0.0, 0.0);
        scale = EectorF3(1.0, 1.0, 1.0);
        cameraTarget = EectorF3(0.0, 0.0, 0.0);
        color = EectorF4(0.0, 0.0, 0.0, 1.0);
    }

    EyerKey::~EyerKey()
    {

    }

    EyerKey::EyerKey(const EyerKey & key)
    {
        *this = key;
    }

    EyerKey & EyerKey::operator = (const EyerKey & key)
    {
        position = key.position;
        rotato = key.rotato;
        scale = key.scale;

        frame = key.frame;

        color = key.color;

        cameraTarget = key.cameraTarget;

        return *this;
    }
}