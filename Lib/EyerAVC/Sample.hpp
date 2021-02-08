#ifndef EYERLIB_SAMPLE_HPP
#define EYERLIB_SAMPLE_HPP

namespace Eyer
{
    class Sample {
    public:
        Sample();
        ~Sample();

        int SetUnavailable();

        int sample = 0;
        bool available = false;
    };
}

#endif //EYERLIB_SAMPLE_HPP
