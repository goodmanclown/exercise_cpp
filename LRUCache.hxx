#ifndef _LRU_CACHE_HXX
#define _LRU_CACHE_HXX


/**
 * template class of a least recently used cache
 */

#include <stdint.h>

#include <iostream>
#include <map>
#include <list>
#include <memory>

using std::ostream;
using std::map;
using std::list;
using std::pair;
using std::make_pair;
using std::move;


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
        KVPMapIterator mapIter =  mKVPMap.find(key);
        
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
        KVPListIterator listIter = mKVPList.insert(mKVPList.end(), move(make_pair(key, value)));

        // insert the kvp to the map
        mKVPMap.insert(move(make_pair(key, listIter)));

        return true;
    }


    /**
     *
     * @return true if remove is ok
     */
    bool remove(K key)
    {
        // check if the key is already there
        KVPMapIterator mapIter = mKVPMap.find(key);
        
        if (mapIter == mKVPMap.end()) return false;

        KVPListIterator listIter = mapIter->second;

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
    bool get(K key, V& value) 
    {
        // check if the key is there
        KVPMapIterator mapIter =  mKVPMap.find(key);
        
        if (mapIter == mKVPMap.end()) return false;

        KVPListIterator listIter = mapIter->second;

        // return the value
        value = listIter->second;

        // move this kvp to the end of the list
        auto kvp = *listIter;

        // remove this pair from the list
        mKVPList.erase(listIter);

        // reinsert to the end
        listIter = mKVPList.insert(mKVPList.end(), kvp);

        // update the map
        mapIter->second = listIter;

        return true;
    }


    /**
     * a list of kvp
     */
    using KVPList = list<pair<K,V>>;
    using KVPListIterator = typename KVPList::iterator;

    KVPList     mKVPList;

    using KVPMap = map<K, KVPListIterator>;
    using KVPMapIterator = typename KVPMap::iterator;

    /**
     * a map of K and pointer to list
     */
    KVPMap mKVPMap;


    /**
     * size of this cache
     */
    size_t mSize;

};


#endif	// _ARRAY_QUEUE_HXX
