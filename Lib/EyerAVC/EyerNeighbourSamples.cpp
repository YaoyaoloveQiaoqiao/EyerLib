#include "EyerNeighbourSamples.hpp"

namespace Eyer
{
    EyerNeighbourSamples::EyerNeighbourSamples()
    {

    }

    EyerNeighbourSamples::~EyerNeighbourSamples()
    {

    }

    int EyerNeighbourSamples::Init(
             Sample & _Q,

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
    )
    {
        Q = _Q;

        A = _A;
        B = _B;
        C = _C;
        D = _D;

        E = _E;
        F = _F;
        G = _G;
        H = _H;

        I = _I;
        J = _J;
        K = _K;
        L = _L;

        return 0;
    }

    bool EyerNeighbourSamples::AvailableUp()
    {
        return A.available;
    }

    bool EyerNeighbourSamples::AvailableLeft()
    {
        return I.available;
    }

    bool EyerNeighbourSamples::AvailableUpLeft()
    {
        return Q.available;
    }

    bool EyerNeighbourSamples::AvailableUpRight()
    {
        return E.available;
    }
}