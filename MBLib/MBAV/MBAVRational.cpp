#include "MBAV.hpp"

namespace MB
{
    MBAVRational::MBAVRational()
    {
        num = 0;
        den = 0;
    }

    MBAVRational::MBAVRational(const MBAVRational & avRational)
    {
        *this = avRational;
    }

    MBAVRational::~MBAVRational()
    {

    }

    MBAVRational & MBAVRational::operator = (const MBAVRational & avRational)
    {
        num = avRational.num;
        den = avRational.den;

        return *this;
    }
}