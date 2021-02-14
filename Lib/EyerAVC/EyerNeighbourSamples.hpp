#ifndef EYERLIB_EYERNEIGHBOURSAMPLES_SSSS_HPP
#define EYERLIB_EYERNEIGHBOURSAMPLES_SSSS_HPP

#include "Sample.hpp"

namespace Eyer
{
    class EyerNeighbourSamples
    {
    public:
        EyerNeighbourSamples();
        ~EyerNeighbourSamples();

        int Init(Sample & _Q,

                 Sample & _A,
                 Sample & _B,
                 Sample & _C,
                 Sample & _D,

                 Sample & _E,
                 Sample & _F,
                 Sample & _G,
                 Sample & _H,

                 Sample & _I,
                 Sample & _J,
                 Sample & _K,
                 Sample & _L
                 );

        bool AvailableUp();
        bool AvailableLeft();
        bool AvailableUpLeft();
        bool AvailableUpRight();

    public:
        Sample Q;

        Sample A;
        Sample B;
        Sample C;
        Sample D;

        Sample E;
        Sample F;
        Sample G;
        Sample H;

        Sample I;
        Sample J;
        Sample K;
        Sample L;
    };
}

#endif //EYERLIB_EYERNEIGHBOURSAMPLES_SSSS_HPP
