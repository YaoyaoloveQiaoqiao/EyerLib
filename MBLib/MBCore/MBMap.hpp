#ifndef	EYER_MAP_H
#define	EYER_MAP_H
#include "MBMapEle.hpp"

namespace MB {

	template<typename K, typename V>
	class MBMap
	{	
	public:
		MBMap();
		~MBMap();
		int insert(const K& key, const V& value);
		int find(const K& key, V & value) const;
		int circleEle(MBMapEle<K, V>* ele, const K& key, V& value, int& flag) const;
		int getSize() const;
		int clear();

		MBMapEle<K, V>* head;

	private:
		int size = 0;
        int insertInner(const K & key, const V & value, MBMapEle<K,V> * & ele);
		int clearInner(MBMapEle<K, V> * & ele);

	};

	template<typename K, typename V>
	int MBMap<K, V>::insertInner(const K& key, const V& value, MBMapEle<K, V> * & ele)
	{
		if (size == 0) {
			head->key = key;
			head->value = value;
			size++;
			return 0;
		}

		if (nullptr == ele) {
			ele = new MBMapEle<K, V>(key, value);
			size++;
		}else if (key > ele->key) {
			insertInner(key, value, ele->rightMapEle);
		}else if (key < ele->key) {
			insertInner(key, value, ele->leftMapEle);
		}
	}


	template<typename K, typename V>
	MBMap<K, V>::MBMap()
	{
		head = new MBMapEle<K, V>(0, 0);
	}

	template<typename K, typename V>
	MBMap<K, V>::~MBMap()
	{
		clearInner(head);
	}

	template<typename K, typename V>
	int MBMap<K, V>::getSize() const
	{
		return size;
	}

	template<typename K, typename V>
	int MBMap<K, V>::circleEle(MBMapEle<K, V>* ele, const K& key, V& value, int & flag) const
	{
		if (nullptr != ele) {
			//printf("key:%d,vaule:%d \n", ele->key, ele->value);
			if (key == ele->key) {
				value = ele->value;
				flag = 1;
				return 0;
			}
			circleEle(ele->leftMapEle, key, value, flag);
			circleEle(ele->rightMapEle, key, value, flag);
		}
		return 0;
	}

	template<typename K, typename V>
	int MBMap<K, V>::insert(const K& key, const V& value)
	{
		return insertInner(key, value, head);
	}

	template<typename K, typename V>
	int MBMap<K, V>::find(const K& key, V& value) const
	{
		int flag = 0;
		circleEle(head, key, value, flag);
		if (flag) {
			return 0;
		}else{
			return -1;
		}
	}

	template<typename K, typename V>
	int MBMap<K, V>::clearInner(MBMapEle<K, V> * & ele)
	{
		if (nullptr != ele) {
			clearInner(ele->leftMapEle);
			clearInner(ele->rightMapEle);
			//printf("clear-----key:%d,vaule:%d \n", ele->key, ele->value);
			delete ele;
			ele = nullptr;
			size--;
		}
		return 0;
	}

	template<typename K, typename V>
	int MBMap<K, V>::clear()
	{
		if(size == 0){
			return 0;
		}
		clearInner(head);
		if (nullptr == head) {
			head = new MBMapEle<K, V>(0, 0);
		}
		return 0;
	}
}

#endif