#ifndef _TIMED_HASHMAP_HXX
#define _TIMED_HASHMAP_HXX


/**
 * template class of a timed hash map
 */

#include <stdint.h>
#include <time.h>

#include <unordered_map>
#include <memory>

using std::unordered_map;
using std::pair;
using std::make_pair;
using std::move;

template<size_t size>
struct TestStruct {
    int hdr;
    std::array<uint32_t, size> body;
};

template <typename K, typename V>
class TimedHashMap
{
public:

    /**
     * Constructor
     *
     */
    TimedHashMap()=default;


    /**
     * Destructor
     */
    virtual ~TimedHashMap()=default;


    /**
     *
     * @param: key
     * @param: value
     *
     * @return true if put ok
     *
     */
    time_t put(const K& key, const V& value) 
    {
        // check if the key is already there
        KVPMapIterator mapIter =  mKVPMap.find(key);
        
        if (mapIter != mKVPMap.end())
        {
            // remove the entry from both map
            erase(key);
        }

        // insert the time and key to the map
        auto t = time(nullptr);
        mTimeKeyMap.emplace(t, key);

        KVPMapValue entry = KVPMapValue( value, mTimeKeyMap.find(t) );

        // insert the kvp to the map
        mKVPMap.emplace(key, move(entry));

        return t;
    }


    /**
     *
     * @return true if get is ok
     */
    bool get(K& key, const time_t t) const 
    {
        // check if the time is there
        TimeKeyMapConst_Iterator mapIter =  mTimeKeyMap.find(t);
        
        if (mapIter == mTimeKeyMap.end()) return false;

        key = mapIter->second;

        return true;
    }

    /**
     *
     * @return true if erase ok
     */
    bool erase(const K& key)
    {
        // check if the key is there
        KVPMapIterator mapIter =  mKVPMap.find(key);
    
        // just return if not found
        if (mapIter == mKVPMap.end()) return false;

        mTimeKeyMap.erase(mapIter->second.second);

        mKVPMap.erase(mapIter);

        return true;
    }

    using TimeKeyMap = unordered_map<time_t, K>;
    using TimeKeyMapIterator = typename TimeKeyMap::iterator;
    using TimeKeyMapConst_Iterator = typename TimeKeyMap::const_iterator;

    /**
     * a map of time and key
     */
    TimeKeyMap mTimeKeyMap;

    /**
     * a map of kvp
     */
    using KVPMapValue = pair<V, TimeKeyMapIterator>;
    using KVPMap = unordered_map<K, KVPMapValue>;
    using KVPMapIterator = typename KVPMap::iterator;

    KVPMap     mKVPMap;


};


#endif	// _TIMED_HASHMAP_HXX
