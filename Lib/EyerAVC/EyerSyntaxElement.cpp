#include "EyerSyntaxElement.hpp"

namespace Eyer
{
    void EyerSyntaxElement::linfo_ue(int len, int info, int *value1, int *dummy)
    {
        *value1 = (int) (((unsigned int) 1 << (len >> 1)) + (unsigned int) (info) - 1);
    }
}