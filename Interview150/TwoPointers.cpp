#pragma once
#include "TwoPointers.h"
#include <map>
#include <set>

namespace Interview150
{
    // 125. Valid Palindrome
    bool TwoPointers::IsPalindrome(string s)
    {
        int left = 0;
        int right = s.size() - 1;

        while (left < s.size() && right >= 0 && left < right)
        {
            while (left < s.size() && !isAlphabet(s[left]))
                ++left;
            while (right >= 0 && !isAlphabet(s[right]))
                --right;

            if (left < s.size() && right >= 0 && tolower(s[left++]) != tolower(s[right--]))
                return false;
        }
        return true;
    }

    // 167. Two Sum II - Input Array is Sorted.
    vector<int> TwoPointers::TwoSum(vector<int> numbers, int target)
    {
        set<int> dataSet;
        for (int k = 0; k < numbers.size(); ++k)
        {
            int idx = findNum(numbers, target - numbers[k], k + 1, numbers.size() - 1);
            if (idx > -1)
                return vector<int>{k + 1, idx + 1};
        }
        return vector<int>{-1, -1};
    }
    
    // 209. Minimum Size Subarray Sum
    int TwoPointers::MinSubArrayLen(int target, const vector<int>& nums)
    {
        int left = 0;
        int right = 0;

        int sum = 0;
        int minLen = INT_MAX;
        for (; right < nums.size(); ++right)
        {
            sum += nums[right];
            while (sum >= target)
            {
                minLen = min(minLen, right - left + 1);
                sum -= nums[left++];
            }
        }
        return minLen == INT_MAX ? 0 : minLen;
    }

    
    // 30. Substring with Concatenation of All Words
    vector<int> TwoPointers::FindSubstring(string s, vector<string> words)
    {
        map<string, int> mapFreq;
        for (int k = 0; k < words.size(); ++k)
        {
            if (mapFreq.find(words[k]) != mapFreq.end())
                mapFreq[words[k]]++;
            else
                mapFreq[words[k]] = 1;
        }

        vector<int> listRet;

        map<string, int> curFreq;
        int left = 0, right = 0;
        for (; right < s.size(); )
        {
            bool found = false;
            for(auto iter = curFreq.begin(); iter != curFreq.end(); ++iter)
            {
                string key = iter->first;

                if (IsStartWith(s, right, key))
                {
                    if (left < 0)    left = right;

                    --curFreq[key];
                    if (curFreq[key] == 0)
                        curFreq.erase(key);

                    if (curFreq.size() == 0)
                    {
                        listRet.push_back(left);
                        found = false;
                    }
                    else
                    {
                        found = true;
                        right += key.size();
                    }
                    break;
                }
            }

            if (!found)
            {
                curFreq.clear();
                curFreq = mapFreq;

                right = left > -1 ? left : right;
                left = -1;
                ++right;
            }
        }
        return listRet;
    }



    //  Helpers
    bool TwoPointers::isAlphabet(char cur)
    {
        if (cur >= 'A' && cur <= 'Z')
            return true;
        if (cur >= 'a' && cur <= 'z')
            return true;
        if (cur >= '0' && cur <= '9')
            return true;
        return false;
    }

    int TwoPointers::findNum(const vector<int>& numbers, int target, int left, int right)
    {
        if (left > right)    return -1;

        int mid = left + (right - left) / 2;
        if (numbers[mid] == target)     return mid;
        else if (numbers[mid] > target)  return findNum(numbers, target, left, mid - 1);
        else return findNum(numbers, target, mid + 1, right);
    }


    bool TwoPointers::IsStartWith(string s, int idxStart, string word)
    {
        if (word.size() > s.size() - idxStart) return false;

        for (int c = 0; c < word.size(); ++c)
        {
            if (s[c + idxStart] != word[c])
                return false;
        }
        return true;
    }
}