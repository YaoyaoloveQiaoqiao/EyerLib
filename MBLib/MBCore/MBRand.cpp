#include "MBMath.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

namespace MB {
    int MBRand::Rand(int x)
    {
        return (rand() * 1.0f / RAND_MAX) * x;
    }
}