#ifndef EYERLIB_CALLBACK_HPP
#define EYERLIB_CALLBACK_HPP

namespace Eyer
{
    enum CallbackType
    {
        START_STREAM_CALLBACK
    };

    class Callback {
    public:
        virtual CallbackType GetType() = 0;
    };
}

#endif //EYERLIB_CALLBACK_HPP
