#include "LRUCache.h"


LRUCache::LRUCache(int capacity) :
	_capacity(capacity)
{
	_mapData.clear();
	_listKeyValues.clear();
}


int LRUCache::Get(int key)
{
	unordered_map<int, list<pair<int, int>>::iterator>::iterator itr = _mapData.find(key);
	if (itr != _mapData.end())
	{
		// Move to front. 
		list<pair<int, int>>::iterator target = itr->second;
		_listKeyValues.erase(target);
		_listKeyValues.push_front(*target);
		_mapData[key] = _listKeyValues.begin();

		return (*target).second;
	}
	return -1;
}

void LRUCache::Put(int key, int val)
{
	unordered_map<int, list<pair<int, int>>::iterator>::iterator itr = _mapData.find(key);
	if (itr == _mapData.end())
	{
		if (_mapData.size() >= _capacity)
		{
			// delete the last one. 
			list<pair<int, int>>::iterator toDel = _listKeyValues.end();
			--toDel;
			int keyToDelete = (*toDel).first;
			_listKeyValues.pop_back();		// delete the last data.
			_mapData.erase(keyToDelete);	// delete it from map.
		}

		_listKeyValues.push_front(make_pair(key, val));
		_mapData[key] = _listKeyValues.begin();
	}
	else
	{
		list<pair<int, int>>::iterator target = itr->second;
		_listKeyValues.erase(target);
		_listKeyValues.push_front(*target);
		_mapData[key] = _listKeyValues.begin();
	}
}
