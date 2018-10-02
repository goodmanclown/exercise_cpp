#include "GetRandomMap.hxx"

#include <iostream>
#include <utility>

using namespace std;

bool GetRandomMap::add(uint64_t min, uint64_t max)
{
    // make a temp 
    MdnEndpoint me(min, max);

    // check if there's any duplicate
    map<MdnEndpoint, std::size_t>::iterator iter = mMap.find(me);

    if (iter != mMap.end())
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
    MdnEndpoint me(min, max);

    cout << "me min " << me.mMin << " me max " << me.mMax << endl;

    // check if there's any duplicate
    map<MdnEndpoint, size_t>::iterator iter = mMap.begin();

    for (; iter != mMap.end(); ++iter)
    {   
        if (iter->first == me) break;
    }

    if (iter == mMap.end())
    {
        return false;
    }

    cout << "min " << iter->first.mMin << " max " << iter->first.mMax << endl;

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

    return true;
}


bool GetRandomMap::getRandom(uint64_t& min, uint64_t& max)
{
    if (mMap.empty() == true)
    {
        return false;
    }

    size_t pos = rand() % mMap.size();

    min = mVector[pos].mMin;
    max = mVector[pos].mMax;

    return true;
}
