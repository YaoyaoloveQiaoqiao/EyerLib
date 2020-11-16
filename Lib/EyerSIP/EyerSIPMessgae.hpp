#ifndef EYERLIB_EYERSIPMESSGAE_HPP
#define EYERLIB_EYERSIPMESSGAE_HPP

#include <stdio.h>

namespace Eyer
{
    class EyerSIPMessgaePrivate;

    class EyerSIPMessgae {
    public:
        EyerSIPMessgae();
        ~EyerSIPMessgae();

        int Parse(const char *buf, size_t length);

    private:
        EyerSIPMessgaePrivate * impl = nullptr;
    };
}

#endif //EYERLIB_EYERSIPMESSGAE_HPP
