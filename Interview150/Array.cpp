#pragma once
#include "Array.h"
#include <map>

namespace Interview150
{
    // 26. Remove Duplicates from Sorted Array
    int Array::RemoveDuplicates(vector<int>& nums)    // [1, 1, 2]
    {
        if (nums.size() <= 1) return nums.size();

        int old = nums[0];
        int k = 1;
        int cnt = 1;
        for (; k < nums.size(); ++k)
        {
            int cur = nums[k];
            if (old != cur)
            {
                nums[cnt++] = cur;
            }
            old = cur;
        }
        nums.resize(cnt);
        return nums.size();
    }

    // 564. Best Time to Buy and Sell Stock II
    int Array::MaxProfit(const vector<int>& prices) 
    {
        if (prices.size() <= 1)
            return 0;
        int profit = 0;
        int idxBuy = -1;
        for (int k = 0; k < prices.size() - 1; ++k)
        {
            if (prices[k + 1] > prices[k])
            {
                if (idxBuy == -1)
                    idxBuy = k;
            }
            else if (prices[k + 1] < prices[k])
            {
                if (idxBuy >= 0)
                {
                    profit += (prices[k] - prices[idxBuy]);
                    idxBuy = -1;
                }
            }
            if (idxBuy >= 0 && prices[k + 1] > prices[idxBuy] && k + 2 == prices.size())
            {
                profit += (prices[k + 1] - prices[idxBuy]);
                break;
            }
        }
        return profit;
    }

    // 646. Rotate Array
    void Array::rotate(vector<int>& nums, int k) 
    {
        k = k % nums.size();
        // => 전체를 뒤집고, (0~k-1), (k~n-1)을 각각 뒤집는다.
        rotate_reverse(nums, 0, nums.size() - 1);
        rotate_reverse(nums, 0, k - 1);
        rotate_reverse(nums, k, nums.size() - 1);
    }

    // 578. Contains Duplicate
    bool Array::containsDuplicate(vector<int>& nums)
    {
        // using map.
        map<int, int> dicTemp;
        for (int k = 0; k < nums.size(); ++k)
        {
            if (dicTemp.find(nums[k]) != dicTemp.end())
                return true;
            dicTemp[nums[k]] = 0;
        }
        return false;
    }

    // 88. Merge Sorted Array
    void Array::merge(vector<int>& nums1, int m, vector<int>& nums2, int n) 
    {
        vector<int> ret;

        int size = max(m, n);
        int idx0 = 0;
        int idx1 = 0;
        for (int k = 0; k < (m + n); ++k)
        {
            int cur0 = INT_MAX;
            if (idx0 < m)
                cur0 = nums1[idx0];
            int cur1 = INT_MAX;
            if (idx1 < n)
                cur1 = nums2[idx1];

            int now;
            if (cur0 < cur1)
            {
                now = cur0;
                ++idx0;
            }
            else
            {
                now = cur1;
                ++idx1;
            }
            ret.push_back(now);
        }

        nums1.clear();
        for (int k = 0; k < ret.size(); ++k)
            nums1.push_back(ret[k]);
    }

    // 27. Remove Element
    int Array::removeElement(vector<int>& nums, int val) 
    {
        int hit = 0;
        int k = 0;
        for (; k < nums.size(); ++k)
        {
            if (k + hit >= nums.size()) break;

            if (nums[k] == val)
            {
                // shift.
                for (int q = k; q < nums.size() - 1; ++q)
                    nums[q] = nums[q + 1];

                --k;
                ++hit;
            }
        }
        return k;
    }

    // 80. Remove Duplicates from Sorted Array II
    int Array::removeDuplicates(vector<int>& nums)
    {
        if (nums.size() <= 1) return nums.size();

        int old = nums[0];
        int cnt = 1;
        int time = 0;
        for (int k = 1; k < nums.size(); ++k)
        {
            int cur = nums[k];
            if (old == cur)
            {
                ++time;
                if (1 == time)
                    nums[cnt++] = cur;
            }
            else if (old != cur)
            {
                nums[cnt++] = cur;
                time = 0;
            }
            old = cur;
        }

        nums.resize(cnt);
        return cnt;

    }

    // 13. Roman To Integer
    int Array::RomanToInt(string s)
    {
        map<string, int> mapValue;
        mapValue["I"] = 1;
        mapValue["V"] = 5;
        mapValue["X"] = 10;
        mapValue["L"] = 50;
        mapValue["C"] = 100;
        mapValue["D"] = 500;
        mapValue["M"] = 1000;

        mapValue["IV"] = 4;
        mapValue["IX"] = 9;
        mapValue["XL"] = 40;
        mapValue["XC"] = 90;
        mapValue["CD"] = 400;
        mapValue["CM"] = 900;


        int ret = 0;
        for (int q = 0; q < s.size(); ++q)
        {
            char cur = s[q];
            bool special = false;
            if (q + 1 < s.size() && (cur == 'I' || cur == 'X' || cur == 'C'))
            {
                string cut = s.substr(q, 2);
                if (mapValue.find(cut) != mapValue.end())
                {
                    special = true;
                    ret += mapValue[cut];
                    ++q;
                }
            }

            if (!special)
            {
                string curStr{ cur };// char.ToString(cur);
                if (mapValue.find(curStr) != mapValue.end())
                {
                    ret += mapValue[curStr];
                }
            }
        }
        return ret;
    }

    // 12. Integer to Roman
    string Array::IntToRoman(int num)
    {
        map<int, string> mapStr;

        mapStr[1] = "I";
        mapStr[5] = "V";
        mapStr[10] = "X";
        mapStr[50] = "L";
        mapStr[100] = "C";
        mapStr[500] = "D";
        mapStr[1000] = "M";

        mapStr[4] = "IV";
        mapStr[9] = "IX";
        mapStr[40] = "XL";
        mapStr[90] = "XC";
        mapStr[400] = "CD";
        mapStr[900] = "CM";

        string ret = "";

        int pos = 1;
        while (num > 0)
        {
            string strCur = "";
            int digit = num % 10;
            int val = digit * pos;

            if (mapStr.find(val) != mapStr.end())
            {
                strCur = mapStr[val];
            }
            else
            {
                string mul;
                if (val < 10)
                {
                    mul = "I";
                    if (val >= 5)
                    {
                        strCur += "V";
                        digit %= 5;
                    }
                }
                else if (val < 100)
                {
                    mul = "X";
                    if (val >= 50)
                    {
                        strCur += "L";
                        digit %= 5;
                    }
                }
                else if (val < 1000)
                {
                    mul = "C";
                    if (val >= 500)
                    {
                        strCur += "D";
                        digit %= 5;
                    }
                }
                else mul = "M";

                for (int j = 0; j < digit; ++j)
                    strCur += mul;
            }
            ret = strCur + ret;
            num /= 10;
            pos *= 10;
        }

        return ret;
    }

    // 58. Length of Last Word 
    int Array::LengthOfLastWord(string s)
    {
        int len = 0;
        bool started = false;
        for (int k = s.size() - 1; k >= 0; --k)
        {
            if (s[k] == ' ')
            {
                if (started) return len;
            }
            else
            {
                started = true;
                ++len;
            }
        }
        return len;
    }

    // 14. Longest Common Prefix
    string Array::LongestCommonPrefix(vector<string>& strs)
    {
        string ret = "";
        for (int k = 0; k < strs[0].size(); ++k)
        {
            char charPre = strs[0][k];
            for (int q = 1; q < strs.size(); ++q)
            {
                if (k >= strs[q].size() || strs[q][k] != charPre)
                    return ret;
            }
            ret += charPre;
        }
        return ret;
    }

    // 6. Zigzag Conversion.
    string Array::Convert(string s, int numRows)
    {
        vector<string> strings;
        strings.resize(numRows, "");

        int idx = 0;
        bool done = false;
        while (!done)
        {
            for (int q = 0; q < numRows; ++q)
            {
                if (idx >= s.size()) { done = true;    break; }
                strings[q] += s[idx++];
            }
            if (!done)
            {
                for (int q = 0; q < numRows - 2; ++q)
                {
                    if (idx >= s.size()) { done = true;    break; }
                    strings[numRows - 2 - q] += s[idx++];
                }
            }
        }

        string ret = "";
        for (int q = 0; q < numRows; ++q)
            ret += strings[q];

        return ret;
    }

    // 28. Find the Index of the First Occurrence in a String
    int Array::StrStr(string haystack, string needle)
    {
        if (haystack.size() < needle.size())
            return -1;

        for (int q = 0; q < haystack.size(); ++q)
        {
            char cur = haystack[q];
            if (cur != needle[0])    continue;
            bool match = true;
            for (int k = 0; k < needle.size(); ++k)
            {
                if (q + k >= haystack.size() || (q + k < haystack.size() && haystack[q + k] != needle[k]))
                {
                    match = false;
                    break;
                }
            }
            if (match) return q;
        }
        return -1;
    }

    // 68. Text Justification
    vector<string> Array::FullJustify(vector<string> words, int maxWidth)
    {
        vector<string> ret;
        int idx = 0;
        string line = getLine(words, idx, maxWidth);
        while (!line.empty())
        {
            ret.push_back(line);
            line = getLine(words, idx, maxWidth);
        }
        return ret;
    }

    //---------------------------------------------------------------------------//
    //
    // Helper
    //
    void Array::rotate_reverse(vector<int>& nums, int left, int right)
    {
        if (left < 0 || left >= nums.size() || right < 0 || right >= nums.size())
            return;
        while (left < right)
        {
            int temp = nums[left];
            nums[left] = nums[right];
            nums[right] = temp;
            ++left;	--right;
        }
    }

    string Array::getLine(const vector<string>& words, int& idxStart, int maxWidth)
    {
        int len = 0;
        int idx = idxStart;
        vector<int> spaces;
        for (; idx < words.size(); ++idx)
        {
            len += words[idx].size();
            if (len > maxWidth)
            {
                spaces.pop_back();  //.RemoveAt(spaces.Count - 1);
                len -= words[idx].size();
                len--;  // remove last space as well.
                break;
            }
            spaces.push_back(len < maxWidth ? 1 : 0);
            ++len;
        }
        if (len == 0)    return "";


        bool isLastLine = idx == words.size();
        // Console.WriteLine("Cut : " + spaces.Count + " , " + len + ", " + idx + " , " + isLastLine);

        if (!isLastLine && spaces.size() == 0)
            spaces.push_back(0);

        string line = "";

        int iSpace = 0;
        while (spaces.size() > 0 && len < maxWidth)
        {
            if (isLastLine)
                iSpace = spaces.size() - 1;
            else iSpace %= spaces.size();
            spaces[iSpace++]++;
            ++len;
        }

        //for(int q = 0; q < spaces.Count; ++q)
        //     Console.WriteLine("Spaces : " + spaces[q]);

        iSpace = 0;
        for (int q = idxStart; q < idx; ++q)
        {
            line += words[q];
            if (iSpace < spaces.size())
            {
                for (int z = 0; z < spaces[iSpace]; ++z)
                    line += " ";
                ++iSpace;
            }
        }
        idxStart = idx;
        return line;
    }
}