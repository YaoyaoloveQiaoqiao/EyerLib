#ifndef EYERLIB_EYERNEIGHBOURSAMPLES_HPP
#define EYERLIB_EYERNEIGHBOURSAMPLES_HPP

namespace Eyer
{
    class EyerNeighbourSamples
    {
    public:
        EyerNeighbourSamples();
        ~EyerNeighbourSamples();

        int Init();

        int Get(int x, int y);

        bool AvailableUp();
        bool AvailableLeft();
        bool AvailableUpLeft();
        bool AvailableUpRight();

    private:
        bool availableUp = false;
        bool availableLeft = false;
        bool availableUpLeft = false;
        bool availableUpRight = false;
    };
}

#endif //EYERLIB_EYERNEIGHBOURSAMPLES_HPP
