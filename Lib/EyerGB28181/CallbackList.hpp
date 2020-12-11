#ifndef EYERLIB_CALLBACKLIST_HPP
#define EYERLIB_CALLBACKLIST_HPP

#include <vector>
#include "Callback/Callback.hpp"

namespace Eyer
{
    class CallbackBean
    {
    public:
        Callback * callback = nullptr;
        int callbackId = 0;
    };

    class CallbackList
    {
    public:
        CallbackList();
        ~CallbackList();

        int PutCallback(Callback * callback, int callbackId);

    private:
        std::vector<CallbackBean *> callbackList;
    };
}

#endif //EYERLIB_CALLBACKLIST_HPP
