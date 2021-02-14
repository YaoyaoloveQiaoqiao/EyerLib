#include "Sample.hpp"

namespace Eyer {

    Sample::Sample()
    {

    }

    Sample::~Sample()
    {

    }

    int Sample::SetUnavailable()
    {
        sample = 0;
        available = false;
        return 0;
    }
}