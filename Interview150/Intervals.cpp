#pragma once
#include "Intervals.h"
#include <map>
#include <set>
#include <iostream>
#include <algorithm>

namespace Interview150
{
    vector<string> Intervals::SummaryRanges(const vector<int>& nums)
    {
        vector<string> ret;
        if (nums.size() == 0)  return ret;

        int start = nums[0];
        int cur = start;
        for (int q = 1; q < nums.size(); ++q)
        {
            if (nums[q] == cur + 1)
                cur = nums[q];
            else
            {
                if (start < cur)    ret.push_back(to_string(start) + "->" + to_string(cur));
                else                ret.push_back(to_string(cur));
                start = nums[q];
                cur = start;
            }
        }
        if (start < cur)   ret.push_back(to_string(start) + "->" + to_string(cur));
        else               ret.push_back(to_string(cur));
        return ret;
    }
}