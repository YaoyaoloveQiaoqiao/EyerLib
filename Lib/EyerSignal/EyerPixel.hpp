#ifndef EYERLIB_EYERPIXEL_HPP
#define EYERLIB_EYERPIXEL_HPP

namespace Eyer
{
    class EyerPixel {
    public:
        EyerPixel(int channel);
        ~EyerPixel();

        float r = 0.0f;
        float g = 0.0f;
        float b = 0.0f;
    };
}

#endif //EYERLIB_EYERPIXEL_HPP
