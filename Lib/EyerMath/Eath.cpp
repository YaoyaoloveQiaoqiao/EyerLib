#include "Eath.hpp"

#include <math.h>

namespace Eyer
{
    float Eath::DegreesToRadians(float degrees)
    {
        return degrees * float(EYER_PI/180);
    }
}