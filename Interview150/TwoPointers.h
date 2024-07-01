#pragma once
#include <vector>
#include <string>
using namespace std;

namespace Interview150
{
	class TwoPointers
	{
	protected:
		bool isAlphabet(char cur);
		int findNum(const vector<int>& numbers, int target, int left, int right);
		bool IsStartWith(string s, int idxStart, string word);

	public:
		// 125. Valid Palindrome
		bool IsPalindrome(string s);

		// 167. Two Sum II - Input Array is Sorted.
		vector<int> TwoSum(vector<int> numbers, int target);
	
		// 209. Minimum Size Subarray Sum
		int MinSubArrayLen(int target, const vector<int>& nums);
	
		// 30. Substring with Concatenation of All Words
		vector<int> FindSubstring(string s, vector<string> words);
	};

}