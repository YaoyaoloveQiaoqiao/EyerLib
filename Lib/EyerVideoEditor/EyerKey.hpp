#ifndef EYERCOLORSPACE_EYERKEY_HPP
#define EYERCOLORSPACE_EYERKEY_HPP

#include "EyerMath/EyerMath.hpp"

namespace Eyer
{
    class EyerKey {
    public:
        EyerKey();
        ~EyerKey();

        EyerKey(const EyerKey & key);
        EyerKey & operator = (const EyerKey & key);

    public:
        EectorF3 cameraTarget;

        EectorF3 position;
        EectorF4 rotato;
        EectorF3 scale;

        EectorF4 color;

        int frame = 0;
    };
}

#endif //EYERCOLORSPACE_EYERKEY_HPP
