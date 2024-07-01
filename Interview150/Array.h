#pragma once
#include <vector>
#include <string>
using namespace std;

namespace Interview150
{
	class Array
	{
	protected:
		void rotate_reverse(vector<int>& nums, int left, int right);
		string getLine(const vector<string>& words, int& idxStart, int maxWidth);

	public:
		// 26. Remove Duplicates from Sorted Array
        int RemoveDuplicates(vector<int>& nums);
		
		// 564. Best Time to Buy and Sell Stock II
		int MaxProfit(const vector<int>& prices);

		// 646. Rotate Array
		void rotate(vector<int>& nums, int k);

		// 578. Contains Duplicate
		bool containsDuplicate(vector<int>& nums);

		// 88. Merge Sorted Array
		void merge(vector<int>& nums1, int m, vector<int>& nums2, int n);
	
	    // 27. Remove Element
		int removeElement(vector<int>& nums, int val);

		// 80. Remove Duplicates from Sorted Array II
		int removeDuplicates(vector<int>& nums);

		// 13. Roman To Integer
		int RomanToInt(string s);

		// 12. Integer to Roman
		string IntToRoman(int num);

		// 58. Length of Last Word
		int LengthOfLastWord(string s);

		// 14. Longest Common Prefix
		string LongestCommonPrefix(vector<string>& strs);

		// 6. Zigzag Conversion.
		string Convert(string s, int numRows);

		// 28. Find the Index of the First Occurrence in a String
		int StrStr(string haystack, string needle);

		// 68. Text Justification
		vector<string> FullJustify(vector<string> words, int maxWidth);

	};

}