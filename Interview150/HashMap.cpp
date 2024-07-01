#pragma once
#include "HashMap.h"
#include <map>
#include <set>
#include <iostream>
#include <algorithm>

namespace Interview150
{
    // 383. Ransom Note
    bool HashMap::CanConstruct(const string& ransomNote, const string& magazine)
    {
        map<char, int> mapFreq;
        for (int q = 0; q < magazine.size(); ++q)
        {
            char cur = magazine[q];
            if (mapFreq.find(cur) != mapFreq.end())
                ++mapFreq[cur];
            else
                mapFreq[cur] = 1;
        }

        for (int q = 0; q < ransomNote.size(); ++q)
        {
            char cur = ransomNote[q];
            if (mapFreq.find(cur) == mapFreq.end())
                return false;
            --mapFreq[cur];
            if (mapFreq[cur] == 0)
                mapFreq.erase(cur);
        }
        return true;
    }

    // 205. Isomorphic Strings
    bool HashMap::IsIsomorphic(const string& s, const string& t)
    {
        if (s.size() != t.size())
            return false;

        map<char, int> dictFreqS;
        for (int q = 0; q < s.size(); ++q)
        {
            char cur = s[q];
            if (dictFreqS.find(cur) != dictFreqS.end())
                ++dictFreqS[cur];
            else
                dictFreqS[cur] = 1;
        }

        map<char, int> dictFreqT;
        for (int q = 0; q < t.size(); ++q)
        {
            char cur = t[q];
            if (dictFreqT.find(cur) != dictFreqT.end())
                ++dictFreqT[cur];
            else
                dictFreqT[cur] = 1;
        }

        map<char, char> dictMap;
        for (int q = 0; q < t.size(); ++q)
        {
            char cur = s[q];
            if (dictMap.find(cur) == dictMap.end())
                dictMap[cur] = t[q];
            else
            {
                if (dictMap[cur] != t[q])
                    return false;
            }

            if (dictFreqS[s[q]] != dictFreqT[t[q]])
                return false;
        }
        return true;
    }

    // 290. Word Pattern
    bool HashMap::WordPattern(const string& pattern, const string& s)
    {
        vector<string> words = Split(s, ' ');
        if (pattern.size() != words.size())
            return false;

        set<string> hsWords;
        for (int q = 0; q < words.size(); ++q)
        {
            if (hsWords.find(words[q]) == hsWords.end())
                hsWords.insert(words[q]);
        }

        map<char, string> dictCache;
        for (int q = 0; q < pattern.size(); ++q)
        {
            char cur = pattern[q];
            if (dictCache.find(cur) != dictCache.end())
            {
                if (words[q] != dictCache[cur])
                    return false;
            }
            else dictCache[cur] = words[q];
        }
        return hsWords.size() == dictCache.size();
    }

    // 242. Valid Anagram
    bool HashMap::IsAnagram(const string& s, const string& t)
    {
        map<char, int> dictFreq;
        for (int q = 0; q < s.size(); ++q)
        {
            char cur = s[q];
            if (dictFreq.find(cur) != dictFreq.end())
                ++dictFreq[cur];
            else
                dictFreq[cur] = 1;
        }

        for (int q = 0; q < t.size(); ++q)
        {
            char cur = t[q];
            if (dictFreq.find(cur) == dictFreq.end())
                return false;

            --dictFreq[cur];
            if (dictFreq[cur] == 0)
                dictFreq.erase(cur);
        }
        return dictFreq.size() == 0;
    }


    // 49. Group Anagrams
    vector<vector<string>> HashMap::GroupAnagrams(const vector<string>& strs)
    {
        map<string, vector<int>> dictStrs;
        for (int q = 0; q < strs.size(); ++q)
        {
            string word = strs[q];
            sort(word.begin(), word.end());
            if (dictStrs.find(word) == dictStrs.end())
                dictStrs[word] = vector<int>{};
            dictStrs[word].push_back(q);
        }

        vector<vector<string>> ret;
        for(auto iter = dictStrs.begin() ; iter != dictStrs.end(); ++iter)
        {
            vector<string> vStr;
            for (int q = 0; q < dictStrs[iter->first].size(); ++q)
                vStr.push_back(strs[dictStrs[iter->first][q]]);
            ret.push_back(vStr);
        }
        return ret;
    }

    // 202. Happy Number
    bool HashMap::IsHappy(int number)
    {
        set<string> hashNums;
        hashNums.insert(to_string(number));
        int n = number;
        while (true)
        {
            vector<int> digits;
            while (n > 0)
            {
                int val = n % 10;
                digits.push_back(val);
                n /= 10;
            }
            int sum = 0;
            for (int q = 0; q < digits.size(); ++q)
                sum += (digits[q] * digits[q]);

            if (sum == 1)    return true;
            string strSorted = to_string(sum);
            sort(strSorted.begin(), strSorted.end());
            if (hashNums.find(strSorted) != hashNums.end())
                return false;

            hashNums.insert(strSorted);
            n = sum;
        }
        return false;
    }

    // 219. Contains Duplicate II
    bool HashMap::ContainsNearbyDuplicate(const vector<int>& nums, int k)
    {
        map<int, vector<int>> dictBuff;
        for (int q = 0; q < nums.size(); ++q)
        {
            int cur = nums[q];
            if (dictBuff.find(cur) == dictBuff.end())
                dictBuff[cur] = vector<int>{};
            else
            {
                for (int z = 0; z < dictBuff[cur].size(); ++z)
                {
                    if (q - dictBuff[cur][z] <= k)
                        return true;
                }
            }
            dictBuff[cur].push_back(q);
        }
        return false;
    }

    // Helper
    vector<string> HashMap::Split(const string& str, char divider)
    {
        vector<string> v;

        string cur = "";
        for (int q = 0; q < str.size(); ++q)
        {
            if (str[q] == divider)
            {
                if (cur.size() > 0)
                    v.push_back(cur);
                cur.clear();
                continue;
            }
            cur += str[q];
        }
        if (cur.size() > 0)
            v.push_back(cur);

        return v;
    }
}