#ifndef EYERLIB_EYERANNEXB_HPP
#define EYERLIB_EYERANNEXB_HPP

#include <stdlib.h>
#include <stdio.h>
#include "EyerCore/EyerCore.hpp"

namespace Eyer
{
    class EyerAnnexB {
    public:
        EyerAnnexB(const EyerString & _path);
        ~EyerAnnexB();
    private:
        EyerString path;
    };
}

#endif //EYERLIB_EYERANNEXB_HPP
