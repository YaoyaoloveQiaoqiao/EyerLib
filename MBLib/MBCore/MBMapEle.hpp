#ifndef	EYER_MAPElE_H
#define	EYER_MAPElE_H

#include <stdio.h>

namespace MB {

    template<typename K, typename V>
    class MBMapEle
    {
    public:
        K key;
        V value;
        MBMapEle<K, V> * leftMapEle;
        MBMapEle<K, V> * rightMapEle;
    public:
        MBMapEle<K, V>(K _key, V _value, MBMapEle<K, V> * _leftMapEle = nullptr, MBMapEle<K, V>* _rightMapEle = nullptr) {
            key = _key;
            value = _value;
            leftMapEle = _leftMapEle;
            rightMapEle = _rightMapEle;
        }
        ~MBMapEle<K, V>() {

        }
    };
}

#endif
