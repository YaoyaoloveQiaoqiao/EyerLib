#ifndef EYERCOLORSPACE_EYERLAYER_HPP
#define EYERCOLORSPACE_EYERLAYER_HPP

namespace Eyer
{
    class EyerLayer {
    public:
        EyerLayer();
        ~EyerLayer();

        int Render(int frameIndex);
    };
}

#endif //EYERCOLORSPACE_EYERLAYER_HPP
