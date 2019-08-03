#include "GetRandomMap.hxx"

#include <algorithm>
#include <iostream>
#include <utility>

using namespace std;

bool GetRandomMap::add(uint64_t min, uint64_t max)
{
    // make a temp 
    const MdnEndpoint me(min, max);

    // check if there's any duplicate
    map<MdnEndpoint, std::size_t>::const_iterator iter = mMap.find(me);

    if (iter != mMap.cend())
    {   // already in the map
        return false;
    }

    // keep track of the index
    mMap[me] = mVector.size();

    // push it to the vector
    mVector.push_back(move(me));

    return true;
}


bool GetRandomMap::remove(uint64_t min, uint64_t max)
{
    if (mMap.empty() == true)
    {
        return false;
    }

    // make a temp 
    const MdnEndpoint me(min, max);

    cout << "me min " << me.first << " me max " << me.second << endl;

    // check if the pair is in the map
    map<MdnEndpoint, size_t>::const_iterator iter = mMap.find(me);

    if (iter == mMap.cend())
    {
        return false;
    }

    cout << "min " << iter->first.first << " max " << iter->first.second << endl;

    // keep track of the index
    size_t pos = iter->second;

    // remove it from the map
    mMap.erase(iter);

    // put the last element in the vector to replace the removed element
    // if there're more than 1
    if (mVector.size() > 1)
    {
        mVector[pos] = move(mVector[mVector.size()-1]); 
    }

    // reduce the vector by 1 element
    mVector.resize(mVector.size()-1);

    // update the index of the moved value in the map
    const MdnEndpoint& elem = mVector[pos];

    mMap[elem] = pos;

    return true;
}


bool GetRandomMap::find(uint64_t min, uint64_t max) const
{
    if (mMap.empty() == true)
    {
        return false;
    }

    // make a temp 
    const MdnEndpoint me(min, max);

    cout << "me min " << me.first << " me max " << me.second << endl;

    // check if the pair is in the map
    map<MdnEndpoint, size_t>::const_iterator mCIter = mMap.find(me);

    if (mCIter != mMap.cend())
    {   // this is an exact match
        return true;
    }

    // how about within the range of a pair
    const vector<MdnEndpoint>::const_iterator vCIter = 
            find_if(mVector.begin(), mVector.end(),
                       [&](const MdnEndpoint& value) 
                       {
                           if (value.first <= min && value.second >= max)
                           {
                               return true;
                           }
                           else
                           {
                               return false;
                           }
                       }
                   );

    if (vCIter != mVector.cend())
    {   // this is a match
        return true;
    }

    return false;
}


bool GetRandomMap::getRandom(MdnEndpoint& out) const
{
    if (mMap.empty() == true)
    {
        return false;
    }

    size_t pos = rand() % mMap.size();

    out.first = mVector[pos].first;
    out.second = mVector[pos].second;

    return true;
}
