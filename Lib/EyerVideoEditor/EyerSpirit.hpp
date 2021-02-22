#ifndef EYERCOLORSPACE_EYERSPIRIT_HPP
#define EYERCOLORSPACE_EYERSPIRIT_HPP

#include "EyerMath/EyerMath.hpp"
#include "EyerKey.hpp"

namespace Eyer
{
    class EyerSpirit {
    public:
        EyerSpirit();
        ~EyerSpirit();

        EyerSpirit(const EyerSpirit & spirit);
        EyerSpirit & operator = (const EyerSpirit & spirit);

        int AddKey(EyerKey & key);

        int Render(EatrixF4x4 & vp, int frameIndex);

        virtual int RenderContent(EatrixF4x4 & vp, EyerKey & key) = 0;
        virtual int RenderInit() = 0;
        virtual int RenderDestory() = 0;

    private:
        std::vector<EyerKey *> keyList;

        bool init = false;
    };
}

#endif //EYERCOLORSPACE_EYERSPIRIT_HPP
