#ifndef EYERLIB_EYERMP4BOX_HPP
#define EYERLIB_EYERMP4BOX_HPP

namespace Eyer
{
    class EyerMP4Box {
    public:
        EyerMP4Box(int _boxSize = 0);
        ~EyerMP4Box();

    protected:
        int boxSize = 0;
    };
}

#endif //EYERLIB_EYERMP4BOX_HPP
