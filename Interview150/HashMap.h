#pragma once
#include <vector>
#include <string>
#include <set>

using namespace std;

namespace Interview150
{
	class HashMap
	{
	protected:

		vector<string> Split(const string& in, char divider);

	public:

		// 383. Ransom Note
		bool CanConstruct(const string& ransomNote, const string& magazine);

		// 205. Isomorphic Strings
		bool IsIsomorphic(const string& s, const string& t);

		// 290. Word Pattern
		bool WordPattern(const string& pattern, const string& s);

		// 242. Valid Anagram
		bool IsAnagram(const string& s, const string& t);

		// 49. Group Anagrams
		vector<vector<string>> GroupAnagrams(const vector<string>& strs);

		// 202. Happy Number
		bool IsHappy(int number);

		// 219. Contains Duplicate II
		bool ContainsNearbyDuplicate(const vector<int>& nums, int k);
	};

}