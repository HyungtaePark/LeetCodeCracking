#pragma once
#include <list>
#include <unordered_map>

using namespace std;

class LRUCache
{
protected:
	
	int _capacity = 0;
	unordered_map<int, list<pair<int, int>>::iterator> _mapData;	// key, iterator to value.
	list<pair<int, int>> _listKeyValues;

public:
	LRUCache(int capacity);
	int Get(int key);
	void Put(int key, int value);
};

