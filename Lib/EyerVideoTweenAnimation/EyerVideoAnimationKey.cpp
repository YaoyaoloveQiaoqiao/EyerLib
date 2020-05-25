#include "EyerVideoTweenAnimation.hpp"

namespace Eyer
{
    bool EyerVideoAnimationKey::operator < (const EyerVideoAnimationKey& key2)
    {
        return t < key2.t;
    }

    EyerVideoAnimationKey::EyerVideoAnimationKey()
    {

    }

    EyerVideoAnimationKey::EyerVideoAnimationKey(const EyerVideoAnimationKey& tk)
    {
        *this = tk;
    }

    EyerVideoAnimationKey& EyerVideoAnimationKey::operator = (const EyerVideoAnimationKey& tk)
    {
        t = tk.t;
        x = tk.x;
        y = tk.y;
        z = tk.z;
        return *this;
    }
}