#ifndef EYERLIB_CALLBACKLIST_HPP
#define EYERLIB_CALLBACKLIST_HPP

#include <vector>
#include "Callback/Callback.hpp"
#include "EyerCore/EyerCore.hpp"

namespace Eyer
{
    class CallbackBean
    {
    public:
        Callback * callback = nullptr;
        EyerString callbackId;
    };

    class CallbackList
    {
    public:
        CallbackList();
        ~CallbackList();

        int PutCallback(Callback * callback, EyerString & callbackId);
        int FindCallback(Callback ** callback, EyerString & callbackId);
    private:
        std::vector<CallbackBean *> callbackList;
    };
}

#endif //EYERLIB_CALLBACKLIST_HPP
