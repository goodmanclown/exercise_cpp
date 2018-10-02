#ifndef _LRU_CACHE_HXX
#define _LRU_CACHE_HXX


/**
 * template class of a least recently used cache
 */

#include <stdint.h>

#include <iostream>
#include <map>
#include <list>

using std::ostream;
using std::map;
using std::list;
using std::pair;
using std::make_pair;


template <typename K, typename V, size_t size>
class LRUCache
{
public:


    /**
     * Constructor
     *
     */
    LRUCache():mSize(size) {};


    /**
     * Destructor
     */
    virtual ~LRUCache()=default;


    /**
     *
     * @param: key
     * @param: value
     *
     * @return true if insert ok
     *
     */
    bool insert(K key, V value) 
    {
        // check if the key is already there
        typename map<K, typename list<pair<K,V>>::iterator>::iterator mapIter =  mKVPMap.find(key);
        
        if (mapIter != mKVPMap.end()) return false;

        // check if size is max
        if (mKVPMap.size() >= mSize)
        {   // remove the LRU
            pair<K,V> kvp = mKVPList.front();

            // remove it from the map
            mKVPMap.erase(kvp.first);

            // which is the head of the list
            mKVPList.pop_front();
        }

        // insert the kvp to the end of the list 
        typename list<pair<K,V>>::iterator listIter = mKVPList.insert(mKVPList.end(), make_pair(key, value));

        // insert the kvp to the map
        mKVPMap.insert(make_pair(key, listIter));

        return true;
    }


    /**
     *
     * @return true if remove is ok
     */
    bool remove(K key)
    {
        // check if the key is already there
        typename map<K, typename list<pair<K,V>>::iterator>::iterator mapIter = mKVPMap.find(key);
        
        if (mapIter == mKVPMap.end()) return false;

        typename list<pair<K,V>>::iterator listIter = mapIter->second;

        // remove it from the list
        mKVPList.erase(listIter);

        // remove it from the map
        mKVPMap.erase(key);

        return true;
    }


    /**
     *
     * @return true if get is ok
     */
    bool get(K key, V& value) const
    {
        // check if the key is there
        typename map<K, typename list<pair<K,V>>::iterator>::iterator mapIter =  mKVPMap.find(key);
        
        if (mapIter == mKVPMap.end()) return false;

        typename list<pair<K,V>>::iterator listIter = mapIter->second;

        value = listIter.second;

        // move this kvp to the end of the list
        pair<K,V> kvp = listIter;

        mKVPList.erase(listIter);

        listIter = mKVPList.insert(mKVPList.end(), kvp);

        // update the map
        mapIter->second = listIter;

        return true;
    }


    /**
     * a list of kvp
     */
    list<pair<K,V>> mKVPList;


    /**
     * a map of K and pointer to list
     */
    map<K, typename list<pair<K,V>>::iterator>  mKVPMap;



    /**
     * size of this cache
     */
    size_t mSize;

};


#endif	// _ARRAY_QUEUE_HXX
