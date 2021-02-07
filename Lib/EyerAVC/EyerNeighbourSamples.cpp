#include "EyerNeighbourSamples.hpp"

namespace Eyer
{
    EyerNeighbourSamples::EyerNeighbourSamples()
    {

    }

    EyerNeighbourSamples::~EyerNeighbourSamples()
    {

    }

    int EyerNeighbourSamples::Init()
    {
        return 0;
    }

    int EyerNeighbourSamples::Get(int x, int y)
    {
        return 0;
    }

    bool EyerNeighbourSamples::AvailableUp()
    {
        return availableUp;
    }

    bool EyerNeighbourSamples::AvailableLeft()
    {
        return availableLeft;
    }

    bool EyerNeighbourSamples::AvailableUpLeft()
    {
        return availableUpLeft;
    }

    bool EyerNeighbourSamples::AvailableUpRight()
    {
        return availableUpRight;
    }
}