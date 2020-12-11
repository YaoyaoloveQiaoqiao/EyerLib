#include "CallbackList.hpp"

#include "EyerCore/EyerCore.hpp"

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

    int CallbackList::PutCallback(Callback * callback, EyerString & callbackId)
    {
        CallbackBean * callbackBean = new CallbackBean();
        callbackBean->callback = callback;
        callbackBean->callbackId = callbackId;
        callbackList.push_back(callbackBean);
        return 0;
    }

    int CallbackList::FindCallback(Callback ** callback, EyerString & callbackId)
    {
        int ret = -1;
        for(int i = 0; i < callbackList.size(); i++){
            CallbackBean * callbackBean = callbackList[i];
            if(callbackBean->callbackId == callbackId){
                *callback = callbackBean->callback;
                ret = 0;
            }
        }
        return ret;
    }
}