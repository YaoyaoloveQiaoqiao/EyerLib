#ifndef	EYER_LINKEDElE_H
#define	EYER_LINKEDElE_H

#include <stdio.h>

namespace MB {
    
    template <typename T>
    class MBLinkedEle
    {
    public:
        T data;
        MBLinkedEle<T> * next;
    public:
        MBLinkedEle<T>(T _data, MBLinkedEle<T> * _next = nullptr){
            data = _data;
            next = _next;
        }
        ~MBLinkedEle<T>(){
            
        }
    };  
}

#endif