#ifndef EYE_LIB_EYER_CORE_LRU_MAP_HPP
#define EYE_LIB_EYER_CORE_LRU_MAP_HPP

#include <mutex>
#include <map>

namespace Eyer
{

    template <typename T>
    class EyerLRUData
    {
    public:
        int hot = 0;
        T * t = nullptr;

        EyerLRUData(T * _t){
            t = _t;
        }

        ~EyerLRUData(){
            if(t != nullptr){
                delete t;
                t = nullptr;
            }
        }
    };

    template <typename K, typename V>
    class EyerLRUMap
    {
    public:
        EyerLRUMap(int maxSize = 100);
        ~EyerLRUMap();

        int Put(const K & k, V * & v);
        int Get(const K & k, V * & v);

        int Size();
    private:
        std::mutex mut;
        std::map<K, EyerLRUData<V> *> mapSet;

        int maxSize = 0;

        int LruRemoveHotless();
    };


    template <typename K, typename V>
    EyerLRUMap<K, V>::EyerLRUMap(int _maxSize)
    {
        maxSize = _maxSize;
    }

    template <typename K, typename V>
    EyerLRUMap<K, V>::~EyerLRUMap()
    {
        std::lock_guard<std::mutex> lg(mut);
        while(mapSet.size() > 0){
            LruRemoveHotless();
        }
    }

    template <typename K, typename V>
    int EyerLRUMap<K, V>::Put(const K & k, V * & v)
    {
        std::lock_guard<std::mutex> lg(mut);
        while(mapSet.size() >= maxSize){
            LruRemoveHotless();
        }

        EyerLRUData<V> * data = new EyerLRUData<V>(v);

        data->hot = 0;
        data->t = v;

        mapSet.insert(typename std::map<K, EyerLRUData<V> *>::value_type(k, data));
        return 0;
    }

    template <typename K, typename V>
    int EyerLRUMap<K, V>::Size()
    {
        std::lock_guard<std::mutex> lg(mut);
        return mapSet.size();
    }

    template <typename K, typename V>
    int EyerLRUMap<K, V>::Get(const K & k, V * & v)
    {
        typename std::map<K, EyerLRUData<V> *>::iterator iter;
        iter = mapSet.find(k);
        if(iter != mapSet.end()){
            EyerLRUData<V> * data = iter->second;
            data->hot++;
            v = data->t;

            return 0;
        }
        return -1;
    }


    template <typename K, typename V>
    int EyerLRUMap<K, V>::LruRemoveHotless()
    {
        int hot = -1;
        K k;
        typename std::map<K, EyerLRUData<V> *>::iterator iter;
        for(iter=mapSet.begin(); iter!=mapSet.end(); iter++) {
            if(hot == -1){
                hot = iter->second->hot;
                k = iter->first;
            }
            if(hot > iter->second->hot){
                hot = iter->second->hot;
                k = iter->first;
            }
        }

        if(hot >= 0){
            iter = mapSet.find(k);
            if(iter != mapSet.end()){
                EyerLRUData<V> * data = iter->second;
                delete data;
                mapSet.erase(iter);
            }
        }

        return 0;
    }

}

#endif
