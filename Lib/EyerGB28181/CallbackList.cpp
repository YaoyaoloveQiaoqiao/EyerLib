#include "CallbackList.hpp"

namespace Eyer
{
    CallbackList::CallbackList()
    {

    }

    CallbackList::~CallbackList()
    {
        for(int i=0;i<callbackList.size();i++){
            delete callbackList[i];
        }
        callbackList.clear();
    }

    int CallbackList::PutCallback(Callback * callback, int callbackId)
    {
        CallbackBean * callbackBean = new CallbackBean();
        callbackBean->callback = callback;
        callbackBean->callbackId = callbackId;
        callbackList.push_back(callbackBean);
        return 0;
    }
}