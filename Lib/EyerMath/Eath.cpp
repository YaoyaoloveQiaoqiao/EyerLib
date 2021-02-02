#include "Eath.hpp"

#include <math.h>

namespace Eyer
{
    float Eath::DegreesToRadians(float degrees)
    {
        return degrees * float(M_PI/180);
    }
}