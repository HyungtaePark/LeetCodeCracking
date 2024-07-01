#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <stack>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <concurrent_priority_queue.h>
#include <algorithm>
#include <numeric>

using namespace std;

namespace LeetCode75
{
	class ArrayString
	{
	public:
		// 1768. Merge String Alternately
		string mergeAlternately(string word1, string word2)
		{
			int p1 = 0, p2 = 0;
			string ret = "";
			while (p1 < word1.length() || p2 < word2.length())
			{
				if (p1 < word1.length())
					ret += word1.at(p1++);
				if (p2 < word2.length())
					ret += word2.at(p2++);
			}
			return ret;
		}

		// [ALGORITHM]
		// 1071. Greatest Commom Divisor of Strings
		string gcdOfStrings(string str1, string str2)
		{
			// str1�� str2�� �������� �ִ� string�� ã�ƶ�.
			if (str1 + str2 != str2 + str1)
				return "";

			int iGCD = gcd(str1.length(), str2.length());
			return str1.substr(0, iGCD);
		}

		// 1431. Kids With the Greatest Number of Candies
		vector<bool> kidsWithCandies(vector<int>& candies, int extraCandies)
		{
			// input array�� �� ���̵��� ������ �ִ� ������ ����. �̶� extranCadies�� �� ���� ���ϸ�, 
			// �� �ش� ���̰� ��ü ���� �ִ��� �������� �������� ���θ� ��ȯ�϶�.
			// �̶� ���� ���̰� ���ÿ� �ִ��� ĵ����� ���� �� �ִ�.
			//
			int maxC = 0;
			for (int k = 0; k < candies.size(); ++k)
				maxC = max(maxC, candies[k]);
				
			vector<bool> vRet;
			for (int k = 0; k < candies.size(); ++k)
			{
				vRet.push_back(candies[k] + extraCandies >= maxC);
			}
			return vRet;
		}

		// 605. Can Place Flowers
		bool canPlaceFlowers(vector<int>& flowerbed, int n)
		{
			// �� �ڸ��� 1�϶� flow�� planted�Ǿ� �ְ�, 0�̸� �׷��� �ʴ�.
			// flower�� �����ؼ� plant�� �� ����.
			// �̶� n�� flowers�� �� �������� �Ѵٸ�, �������� ���θ� ��ȯ�϶�.
			//
			if (n == 0)	return true;
			if (flowerbed.size() == 1)
				return flowerbed[0]==0 && n==1;

			for (int k = 0; k < flowerbed.size(); ++k)
			{
				bool plant = false;
				if (k == 0)
				{
					if (flowerbed[k]==0 && flowerbed[k+1]==0)
						plant = true;
				}
				else if (k == flowerbed.size() - 1)
				{
					if (flowerbed[k] == 0 && flowerbed[k - 1] == 0)
						plant = true;
				}
				else
				{
					if (flowerbed[k - 1] == 0 && flowerbed[k] == 0 && flowerbed[k + 1] == 0)
						plant = true;
				}
				if (plant)
				{
					--n;
					flowerbed[k] = 1;
				}
				if (n <= 0)	return true;
			}
			return false;
		}

		// 345. Reverse Vowels of a String
		string reverseVowels(string s)
		{
			// s���� ���� ���ڸ� reverse�ؼ� ��ȯ�϶�.
			// 
			string vowls = "";
			for (int k = 0; k < s.length(); ++k)
			{
				char cur = s[k];
				cur = tolower(cur);
				if (cur == 'a' || cur == 'e' || cur == 'i' || cur == 'o' || cur == 'u')
					vowls += s[k];
			}
			string ret = "";
			int q = 0;
			for (int k = 0; k < s.length(); ++k)
			{
				char cur = s[k];
				cur = tolower(cur);
				if (cur == 'a' || cur == 'e' || cur == 'i' || cur == 'o' || cur == 'u')
				{
					ret += vowls[vowls.length() - 1 - q];
					++q;
				}
				else ret += s[k];
			}
			return ret;
		}

		// 151. Reverse Words in a String
		string reverseWords(string s)
		{
			// �ܾ space ĳ���Ͱ� �ƴ� ���ӵ� ĳ���� �����̶�� �ϸ�, 
			// s�� ���� �� �ܾ�鸦 ������ s�� ����϶�.
			vector<string> vWords;
			string cur = "";
			for (int k = 0; k < s.length(); ++k)
			{
				char now = s[k];
				if (now == ' ')
				{
					if (!cur.empty())
					{
						vWords.push_back(cur);
						cur = "";
					}
				}
				else cur += now;
			}
			if (!cur.empty())
				vWords.push_back(cur);

			reverse(vWords.begin(), vWords.end());

			string ret = "";
			for (int k = 0; k < vWords.size(); ++k)
			{
				ret += vWords[k];
				if (k < vWords.size() - 1) ret += " ";
			}
			return ret;
		}

		// 238. Product of Array Except Self
		vector<int> productExceptSelf(vector<int>& nums)
		{
			// nums�� �迭������ �ش� �ڽ��� ���� ������ �ٸ������� ���� ��ȯ�϶�.
			// O(N) time complexity and O(1) space complexity�� �����ϰ�, ������ ������ ������� ����.
			//
			vector<int> vRet;
			int totalMultiply = 1;
			for (int k = 0; k < nums.size(); ++k)
			{
				vRet.push_back(totalMultiply);
				totalMultiply *= nums[k];
			}

			totalMultiply = 1;
			for (int k = 0; k < nums.size(); ++k)
			{
				int idx = nums.size() - 1 - k;
				vRet[idx] = totalMultiply * vRet[idx];
				totalMultiply *= nums[idx];
			}
			return vRet;
		}

		// 334. Increasing Triplet Subsequence
		bool increasingTriplet(vector<int>& nums)
		{
			// ������ �����ϴ� �迭 ������ ���� �ش� ���� ���� ���������� �Ǵ� ������ �ִ��� ���θ� ��ȯ�϶�.
			// -> TC O(N), SC O(1)�� Ǯ�� �ְڴ°�?
			// 
			// 
			// Brute Force - 3�� for���� ���鼭 ������ �����ϳ� Ȯ���Ѵ�. 
			//
			int left = INT_MAX;
			int mid = INT_MAX;
			for (int k = 0; k < nums.size(); ++k)
			{
				if (nums[k] <= left)
					left = nums[k];
				else if (nums[k] <= mid)
					mid = nums[k];
				else return true;
			}
			return false;
		}

		// 443. String Compression
		int compress(vector<char>& chars)
		{
			// �ش� chars�� �����϶�.
			// - ������ ���ڼ��� �����Ŀ� ����϶�.
			// - ���ڰ� �ϳ����, �����Ŀ� ���ڸ� �����϶�.
			// constant extra space���� ����϶�.
			// ������ ���ڸ� input�� buffer�� update�϶�.
			// �Ϸ�Ǹ� �� ���� buffer�� size�� ��ȯ�϶�.
			//
			//
			char target = -1;
			int counter = 0;
			int idx = 0;
			for (int k = 0; k <= chars.size(); ++k)
			{
				char cur = k==chars.size() ? -1 : chars[k];
				if (target < 0)
				{
					target = cur;
					counter = 1;
					++idx;
				}
				else
				{
					if(target == cur)
						++counter;
					else
					{
						if (counter > 1)
						{
							vector<char> vNum;
							while (counter > 0)
							{
								vNum.push_back(counter % 10 + '0');
								counter /= 10;
							}
							for (int q = 0; q < vNum.size(); ++q)
								chars[idx+q] = vNum[ vNum.size()-1-q ];
							idx += vNum.size();
						}
						
						if (k < chars.size())
						{
							target = cur;
							chars[idx++] = target;
							counter = 1;
						}
					}
				}
			}
			return idx;
		}
	};

	class TwoPointers
	{
	public:

		// 283. Move Zeroes
		void moveZeroes(vector<int>& nums)
		{
			// �迭���� �����ϴ� 0�� �ڷ� �а�, in place�� ó���϶�.
			//
			int zero = 0;
			for (int k = 0; k < nums.size(); ++k)
			{
				if (nums[k] == 0)
				{
					++zero;
					continue;
				}
				nums[k - zero] = nums[k];
			}
			for (int k = nums.size() - 1 - zero; k < nums.size(); ++k)
				nums[k] = 0;
		}

		// 392. Is Subsequence
		bool isSubsequence(string s, string t)
		{
			// t�� �Ϻ� ���ڸ� �����ؼ�(������ �������� ����) s�� ����� �ִ��� ���θ� ��ȯ�϶�.
			// �̶� s�� t�� �ҹ��ڷθ� �����Ǿ� �ִ�.
			// 
			int idxS = 0;
			for (int k = 0; k < t.size(); ++k)
			{
				if (t[k] == s[idxS])
				{
					++idxS;
					if (idxS >= s.size())	return true;
				}
			}
			return idxS==s.size();
		}

		// 11. Container With Most Water
		int maxArea(vector<int>& height)
		{
			// �� height�� �ش��ϴ� ���̿� ���� ä��ٰ� �Ҷ�, 
			// �ִ� ������ ���϶�.
			//
			int left = 0;
			int right = height.size() - 1;
			int maxArea = 0;
			while (left < right)
			{
				int h = min(height[left], height[right]);
				maxArea = max(maxArea, h * (right - left));
				if (height[left] > height[right])
					--right;
				else if (height[left] < height[right])
					++left;
				else
				{
					++left; --right;
				}
			}
			return maxArea;
		}

		// 1679. Max Number of K-Sum Pairs
		int maxOperations(vector<int>& nums, int sum)
		{
			// nums �迭���� �� ���� ���� sum�� �Ǹ� �� ���� �����Ѵ�.
			// �� ������ �ִ� ���� ���϶�.
			// 
			int ret = 0;
			unordered_map<int, int> freqMap;
			for (int k = 0; k < nums.size(); ++k)
			{
				if (freqMap.find(nums[k]) == freqMap.end())
					freqMap[sum - nums[k]]++;
				else
				{
					--freqMap[nums[k]];
					if (freqMap[nums[k]] == 0)
						freqMap.erase(nums[k]);
					++ret;
				}
			}
			return ret;
		}
	};

	class SlidingWindow
	{
	public:

		// 643. Maximum Average Subarray I
		double findMaxAverage(vector<int>& nums, int k)
		{
			// nums���� ���ӵ� sub array �߿� ���̰� k�� �Ǵ� ���߿� ���� ū ��հ��� ��ȯ�϶�.
			//
			double ret = -DBL_MAX;
			int sum = 0;
			int left = 0;
			for (int right = 0; right < nums.size(); ++right)
			{
				sum += nums[right];

				if (right - left + 1 == k)
				{
					ret = max(ret, ((double)sum) / ((double)k));
					sum -= nums[left++];
				}
			}
			return ret;
		}

		// 1456. Maximum Number of Vowels in a Substring of Given Length
		int maxVowels(string s, int k)
		{
			// s �ȿ��� ���̰� k�� ��� substring �ȿ��� 
			// �ִ� ������ ������ ��ȯ�϶�.
			int left = 0;
			int cntVowl = 0;
			int ret = 0;
			for (int right = 0; right < s.length(); ++right)
			{
				char cur = s[right];
				if (cur == 'a' || cur == 'e' || cur == 'i' || cur == 'o' || cur == 'u')
					++cntVowl;

				if (right - left + 1 == k)
				{
					ret = max(ret, cntVowl);
					cur = s[left++];
					if (cur == 'a' || cur == 'e' || cur == 'i' || cur == 'o' || cur == 'u')
						--cntVowl;
				}
			}
			return ret;
		}

		// 1004. Max Consecutive Ones III
		int longestOnes(vector<int>& nums, int k)
		{
			// 1�� 0���� ������, nums array�� ������, k�� ���̸�ŭ�� subarray���� 
			// k�� ��ŭ�� 0�� 1�� �ٲ� �� �ִٰ� �ϸ�, �ִ� ���ӵ� 1�� ���̸� ã�ƶ�.
			int left = 0;
			int flip = k;
			int ret = 0;
			for (int right = 0; right < nums.size(); ++right)
			{
				int cur = nums[right];
				if (cur == 0)
					--flip;
				
				while(flip < 0)
				{
					cur = nums[left++];
					if (cur == 0)
						++flip;
				}

				if (flip >= 0)				
					ret = max(ret, right - left + 1);
			}
			return ret;
		}

		// 1493. Longest Subarray of 1's After Deleting One Element
		int longestSubarray(vector<int>& nums)
		{
			// 1�� 0���� ������ nums�迭�� �־��� ���, 0�� 1�� ������ �� �ִٸ�
			// ���� �� �ִ� 1�θ� ������ sub array�� �ִ� ���̸� ���϶�.
			//
			int left = 0;	int left_with_0 = -1;
			int flip = 1;
			int ret = 0;
			for (int right = 0; right < nums.size(); ++right)
			{
				int cur = nums[right];
				if (cur == 0)
				{
					--flip;
					if (left_with_0 < 0)	left_with_0 = right;
				}

				if (flip < 0)
				{
					flip = 0;
					left = left_with_0 + 1;
					left_with_0 = right;
				}
				ret = max(ret, right - left);
			}
			return ret;
		}
	};

	class PrefixSum
	{
	public:
		// 1732. Find the Highest Altitude
		int largestAltitude(vector<int>& gain)
		{
			// �Էµ� �迭���� n�� n+1 ��ġ���� ���� ���̴�. 
			// �̶�, ���밪�� ���� ū ���� ã�ƶ�.
			//
			if (gain.size() < 1)
				return 0;
			int elapsed = gain[0];
			int ret = max(0, elapsed);
			for (int k = 1; k < gain.size(); ++k)
			{
				elapsed += gain[k];
				ret = max(ret, elapsed);
			}
			return ret;
		}

		// 724. Find Pivot Index
		int pivotIndex(vector<int>& nums)
		{
			// ������ ������ ���� ���� ���� ���� index�� �Ǻ� �ε������ �Ҷ�
			// �� index�� ���϶�.
			//
			vector<int> leftSum, rightSum;
			for (int k = 0; k < nums.size(); ++k)
			{
				if (leftSum.size() == 0)	leftSum.push_back(0);
				else leftSum.push_back(leftSum[leftSum.size() - 1] + nums[k - 1]);

				int r = nums.size() - 1 - k;
				if (rightSum.size() == 0)	rightSum.push_back(0);
				else rightSum.push_back(rightSum[rightSum.size() - 1] + nums[r + 1]);
			}

			for (int k = 0; k < nums.size(); ++k)
			{
				if (leftSum[k] == rightSum[nums.size()-1-k])
					return k;
			}
			return -1;
		}
	};


	class HashMapSet
	{
	public:
		// 2215. Find the Difference of Two Arrays
		vector<vector<int>> findDifference(vector<int>& nums1, vector<int>& nums2)
		{
			// �־��� �Է¿� ���� 2���� �迭�� ����ϵ�, ����
			// ù��°�� nums1���� �������� 2���� �ȳ����� ������, 
			// �ι�°�� nums2���� �������� 1���� �ȳ����� ������ ã�ƶ�.
			//
			vector<vector<int>> vRet;
			unordered_set<int> present, sRet;
			for (int k = 0; k < nums2.size(); ++k)
			{
				if (present.find(nums2[k]) == present.end())
					present.insert(nums2[k]);
			}
			for (int k = 0; k < nums1.size(); ++k)
			{
				if (present.find(nums1[k]) == present.end())
				{
					if (sRet.find(nums1[k]) == sRet.end())
						sRet.insert(nums1[k]);
				}
			}
			vRet.push_back(vector<int>(sRet.begin(), sRet.end()));

			present.clear();
			sRet.clear();
			for (int k = 0; k < nums1.size(); ++k)
			{
				if (present.find(nums1[k]) == present.end())
					present.insert(nums1[k]);
			}
			for (int k = 0; k < nums2.size(); ++k)
			{
				if (present.find(nums2[k]) == present.end())
				{
					if (sRet.find(nums2[k]) == sRet.end())
						sRet.insert(nums2[k]);
				}
			}
			vRet.push_back(vector<int>(sRet.begin(), sRet.end()));
			return vRet;
		}

		// 1207. Unique Number of Occurrences
		bool uniqueOccurrences(vector<int>& arr)
		{
			// �־��� �Է� arr�� ������ ���� �󵵰� �������� ���θ� ��ȯ�϶�. 
			// ��, [1,2] �� �� 1ȸ�� �����Ͽ����Ƿ�, false�� �ȴ�. 
			//
			unordered_map<int, int> freqMap;
			for (int k = 0; k < arr.size(); ++k)
				freqMap[arr[k]]++;

			unordered_set<int> check;
			for (unordered_map<int, int>::iterator it = freqMap.begin(); it != freqMap.end(); ++it)
			{
				if (check.find(it->second) == check.end())
					check.insert(it->second);
				else
					return false;
			}
			return true;
		}

		// 1657. Determine if Two Strings Are Close
		bool closeStrings(string word1, string word2)
		{
			// �ΰ��� string word1�� word2�� ������� �Ǵ��϶�. 
			// - ������ ������ �ٲ㼭 ���� ���ڰ� �Ǹ� ����ϴ� �Ҽ� �ִ�.
			// - �����ϴ� ���ڰ� �޶� �󵵼��� ������ ����ϴ� �� �� �ִ�. 
			//
			if (word1.size() != word2.size())
				return false;

			// a. �����ϴ� ���� ������ ���ƾ� �Ѵ�.
			// b. �󵵼��� ���������� ���ƾ� �Ѵ�.

			map<char, int> freqMap1, freqMap2;
			for (int k = 0; k < word1.size(); ++k)
			{
				freqMap1[word1[k]]++;
				freqMap2[word2[k]]++;
			}
			map<char, int>::iterator it1 = freqMap1.begin();
			map<char, int>::iterator it2 = freqMap2.begin();
			vector<int> vFreq1, vFreq2;
			for (; it1 != freqMap1.end(); ++it1, ++it2)
			{
				if (it1->first != it2->first)
					return false;

				vFreq1.push_back(it1->second);
				vFreq2.push_back(it2->second);
			}
			sort(vFreq1.begin(), vFreq1.end());
			sort(vFreq2.begin(), vFreq2.end());

			for (int k = 0; k < vFreq1.size(); ++k)
			{
				if (vFreq1[k] != vFreq2[k])
					return false;
			}
			return true;
		}

		// 2352. Equal Row and Column Pairs
		int equalPairs(vector<vector<int>>& grid)
		{
			// �ش� ��� ���� ���� ������ �ش� ��� ���� ������ ������, �� ���� ���� ���ٶ�� �Ѵ�.
			// input grid���� ���� ���� ���� ������ ���� ��ȯ�϶�.
			//
			map<string, int> mapFreq;
			for (int k = 0; k < grid.size(); ++k)
			{
				string line = "";
				for (int x = 0; x < grid[0].size(); ++x)
				{
					line += to_string(grid[k][x]);
					line += "_";
				}

				mapFreq[line]++;
			}

			int ret = 0;
			for (int k = 0; k < grid[0].size(); ++k)
			{
				string line = "";
				for (int x = 0; x < grid.size(); ++x)
				{
					line += to_string(grid[x][k]);
					line += "_";
				}

				if (mapFreq.find(line) != mapFreq.end())
					ret += mapFreq[line];
			}
			return ret;
		}
	};

	class StackRT
	{
	public:
		// 2390. Removing Stars From a String
		string removeStars(string s)
		{
			// �Է¹��� s���� *�� *�� �ٷ� ���� ���ڸ� �����ϰ� ����϶�.
			// a*b => b
			//
			stack<char> sBuff;
			for (int k = 0; k < s.size(); ++k)
			{
				if (s[k] == '*')
				{
					if (sBuff.size())
						sBuff.pop();
				}
				else sBuff.push(s[k]);
			}

			string ret;
			ret.resize(sBuff.size());
			int stackSize = sBuff.size();
			for(int k = 0; k < stackSize; ++k)
			{
				ret[stackSize - 1 - k] = sBuff.top();
				sBuff.pop();
			}
			return ret;
		}

		// 735. Asteroid Collision
		vector<int> asteroidCollision(vector<int>& ast)
		{
			// input array ast���� �� ���� 
			// ��� ũ�⸦, ��ȣ�� ������ �ǹ��Ѵ�. 
			// + right, - left.
			// ���� ������ ũ�Ⱑ �������� ��������.(������ �Ѵ� �����)
			// ������ ������ ������ �ʴ´�.
			// ��� �ӵ��� ���ٰ� �Ҷ�, �浹 ���� ����� ����϶�.
			//
			// ex) [5,10,-5] 
			// => �ι�°�� ����°�� ������ �ǰ�, �ι�°�� ũ�Ⱑ �� ũ�Ƿ� 
			// => [5,10]
			//
			vector<int> ret;
			stack<int> sBuff;
			for (int k = 0; k < ast.size(); ++k)
			{
				if (ast[k] < 0)
				{
					if (sBuff.empty())
						sBuff.push(ast[k]);
					else
					{
						while (true)
						{
							int last = sBuff.top();
							if (last < 0)
							{
								sBuff.push(ast[k]);
								break;
							}
							if (abs(last) < abs(ast[k]))
								sBuff.pop();
							else if (abs(last) == abs(ast[k]))
							{
								sBuff.pop();
								break;
							}
							else break;

							if (sBuff.empty())
							{
								sBuff.push(ast[k]);
								break;
							}
						}
					}
				}
				else sBuff.push(ast[k]);
			}
			ret.resize(sBuff.size());
			for(int k = 0; k < ret.size(); ++k)
			{
				ret[ret.size() - 1 - k] = sBuff.top();
				sBuff.pop();
			}
			return ret;
		}

		// 394. Decode String
		string decodeString(string s)
		{
			// k[string] ���� �Է��� ���ö�, string�� k�� ����ϰ� ���ڵ� �϶�.
			
			stack<char> sBuff;
			for (int k = 0; k < s.size(); ++k)
			{
				char cur = s[k];
				if (cur == ']')
				{
					string src = "";
					string num = "";
					while (true)
					{
						if (sBuff.empty())
							break;
						else
						{
							char last = sBuff.top();
							if (last >= '0' && last <= '9')
							{
								num += last;
								sBuff.pop();
							}
							else
							{
								if (num.size() > 0)
									break;
								else
								{
									src = last!='[' ? src + last : src;
									sBuff.pop();
								}
							}
						}
					}

					reverse(num.begin(), num.end());
					int times = num.size()>0 ? atoi(num.c_str()) : 0;

					reverse(src.begin(), src.end());
					for (int z = 0; z < times; ++z)
					{
						for (int q = 0; q < src.size(); ++q)
							sBuff.push(src[q]);
					}
				}
				else sBuff.push(cur);
			}

			string ret = "";
			while (!sBuff.empty())
			{
				ret += sBuff.top();
				sBuff.pop();
			}
			reverse(ret.begin(), ret.end());
			return ret;
		}
	};

	class QueueRT
	{
	public:
		
		// 933. Number of Recent Calls
		vector<int> mVect;
		int ping(int t)
		{
			// t�� ���� data�� input �ð��̶�� �Ҷ�, ������ data�� (t-3000, t) �������� 
			// ������ ���� ����϶�.
			//
			mVect.push_back(t);
			int ret = 0;
			for (int q = mVect.size() - 1; q >= 0; --q)
			{
				if (mVect[q] >= t - 3000)
					++ret;
				else break;
			}
			return ret;
		}
	};

	class LinkedList
	{
	public:
		struct ListNode {
			int val;
			ListNode* next;
			ListNode() : val(0), next(nullptr) {}
			ListNode(int x) : val(x), next(nullptr) {}
			ListNode(int x, ListNode* next) : val(x), next(next) {}
		};

		// 2095. Delete the Middle Node of a Linked List
		ListNode* deleteMiddle(ListNode* head)
		{
			// ����Ʈ�� �߾� ��带 �����϶�. ������ ¦�����, �� ����� ���� ��带 �����϶�.
			//
			if (head == NULL)	return NULL;

			ListNode* fast = head;
			ListNode* slow = head;
			ListNode* prev = NULL;
			while (fast != NULL && fast->next != NULL)
			{
				prev = slow;
				slow = slow->next;
				fast = fast->next->next;
			}

			// delete. 
			if (slow != NULL)
			{
				if (prev == NULL)	head = NULL;
				else prev->next = slow->next;
			}
			else
				prev->next = NULL;
			return head;
		}

		// 328. Odd Even Linked List.
		ListNode* oddEvenList(ListNode* head)
		{
			// �Էµ� list�� Ȧ������ �����ϰ�, ���� ¦������ �����϶�. 
			// O(1) extra space�� O(N) TC �� �ǵ��� �϶�.
			//
			if (head == NULL || head->next == NULL)
				return head;

			ListNode* odd = head;
			ListNode* even = head->next;
			ListNode* evenHead = even;
			while (even!=NULL && even->next!=NULL)
			{
				odd->next = even->next;
				odd = even->next;
				even->next = odd->next;
				even = odd->next;
			}
			odd->next = evenHead;
			return head;
		}

		// 206. Reverse Linked List.
		ListNode* reverseList(ListNode* head)
		{
			// �־��� ����Ʈ�� ������, �� head�� ��ȯ�϶�.
			// 
			ListNode* node = head;
			ListNode* prev = NULL;
			while (node != NULL)
			{
				ListNode* next = node->next;
				node->next = prev;
				prev = node;
				node = next;
			}
			return prev;
		}

		// 2130. Maximum Twin Sum of a Linked List
		int pairSum(ListNode* head)
		{
			// �տ��������� ������ ���� node�� �ڿ��� ���� ������ ���� ��带 �� pair��� �Ҷ�, 
			// �� pair �߿� �� ���� �ִ� ���� ��ȯ�϶�.
			// 
			// �߰� �κ��� ã�´�. 
			// �߰� �ٷ� �ձ��� list�� ���� ��Ų��. 
			// �߰����� ����, 
			// ������ ��带 ����
			// �ϸ� �� ��尡 pair�� �ȴ�. 
			ListNode* fast = head;
			ListNode* slow = head;
			ListNode* prevSlow = NULL;
			while (fast != NULL && fast->next != NULL)
			{
				prevSlow = slow;
				slow = slow->next;
				fast = fast->next->next;
			}

			ListNode* rightHead = slow;
			ListNode* leftHead = prevSlow;
			ListNode* prev = NULL;
			slow = head;
			while (slow != rightHead)
			{
				ListNode* next = slow->next;
				slow->next = prev;
				prev = slow;
				slow = next;
			}

			int ret = 0;
			ListNode* right = rightHead;
			ListNode* left = leftHead;
			while (right != NULL)
			{
				ret = max(ret, right->val + left->val);
				right = right->next;
				left = left->next;
			}
			return ret;
		}
	};

	class BinaryTree_DFS
	{
	public:
		struct TreeNode {
			int val;
			TreeNode* left;
			TreeNode* right;
			TreeNode() : val(0), left(nullptr), right(nullptr) {}
			TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
			TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}			
		};

		// 104. Maximum Depth of Binary Tree
		int maxDepthHelper(TreeNode* node, int depth)
		{
			if (node == NULL)	return depth;
			++depth;

			int leftD = maxDepthHelper(node->left, depth);
			int rightD = maxDepthHelper(node->right, depth);
			
			return max(leftD, rightD);
		}
		int maxDepth(TreeNode* root)
		{
			// �־��� binary tree�� max depth�� ��ȯ�϶�.
			//
			//int ret = maxDepthHelper(root, 0);
			//return ret;

			if (root == NULL)	return 0;
			queue<TreeNode*> qBuff;
			qBuff.push(root);
			int ret = 0;
			while (!qBuff.empty())
			{
				int cnt = qBuff.size();
				for (int k = 0; k < cnt; ++k)
				{
					TreeNode* cur = qBuff.front();
					qBuff.pop();

					if (cur->left != NULL)	qBuff.push(cur->left);
					if (cur->right != NULL)	qBuff.push(cur->right);
				}
				++ret;
			}
			return ret;
		}

		// 872. Leaf-Similar Trees
		void leafSimilar_helper(TreeNode* node, vector<int>& vectBuff)
		{
			if (node == NULL)	return;

			if (node->left != NULL)		leafSimilar_helper(node->left, vectBuff);
			if (node->right != NULL)	leafSimilar_helper(node->right, vectBuff);
			if (node->left == NULL && node->right == NULL)
				vectBuff.push_back(node->val);
		}
		bool leafSimilar(TreeNode* root1, TreeNode* root2)
		{
			// �� ����� leaf�� ���� �������� �о����� ���� ���̿� ���̸�, ������ ����ϴٰ� �Ѵ�.
			// �� ����� ������ ������� ���θ� ��ȯ�϶�.
			//
			vector<int> v1, v2;
			leafSimilar_helper(root1, v1);
			leafSimilar_helper(root2, v2);

			if (v1.size() != v2.size())	return false;
			for (int k = 0; k < v1.size(); ++k)
			{
				if (v1[k] != v2[k])	return false;
			}
			return true;
		}

		// 1448. Count Good Nodes in Binary Tree
		void goodNodes_Helper(TreeNode* node, int &count, int maxV)
		{
			if (node == NULL)	return;

			if (node->val >= maxV)
				++count;

			maxV = max(maxV, node->val);

			if (node->left != NULL)		goodNodes_Helper(node->left, count, maxV);
			if (node->right != NULL)	goodNodes_Helper(node->right, count, maxV);
		}
		int goodNodes(TreeNode* root)
		{
			// root���� Ư�� ��� x ���� ������ ������ ��� ��忡�� x���� ū ���� ������, good ���� �Ѵ�.
			// �־��� tree���� good ����� ���� ��ȯ�϶�.
			//
			int ret = 0, max = INT_MIN;
			goodNodes_Helper(root, ret, max);
			return ret;
		}

		// 560. Subarray Sum Equals K
		int subarraySum(vector<int>& nums, int k)
		{
			int sum = 0;
			int target = k;
			int ret = 0;
			map<int, int> mapFreq;
			mapFreq[0] = 1;         // ó�������� �������� ��� ���. 
			for (int q = 0; q < nums.size(); ++q)
			{
				sum += nums[q];
				if (mapFreq.find(sum - target) != mapFreq.end())
					ret += mapFreq[sum - target];

				mapFreq[sum]++;     // ���� ��ġ �������� �˻����� ���� �ʿ�. ���� search�Ŀ� map�� ���Ѵ�.
			}
			return ret;

			/*
			int target = k;
			int ret = 0;
			vector<int> areaSum;
			int sum = 0;
			for (int q = 0; q < nums.size(); ++q)
			{
				sum += nums[q];
				areaSum.push_back( sum );
			}
			
			for (int q = 0; q < areaSum.size(); ++q)
			{
				if (areaSum[q] == target)
					++ret;
				for (int j = 0; j < q; ++j)
				{
					if (areaSum[q] - areaSum[j] == target)
						++ret;
				}
			}
			*/
			return ret;
		}

		// 437. Path Sum III
		void pathSum_helper(TreeNode* node, long sum, int& ret, unordered_map<long, int>& mapFreq, const int targetSum)
		{
			if (node == NULL)	return;

			// Calculate Sum.
			sum += node->val;
			
			// Search.
			if (mapFreq.find(sum - targetSum) != mapFreq.end())
				ret += mapFreq[sum - targetSum];

			// Add to Buffer. 
			mapFreq[sum]++;

			// Keep Looping.
			pathSum_helper(node->left, sum, ret, mapFreq, targetSum);
			pathSum_helper(node->right, sum, ret, mapFreq, targetSum);

			mapFreq[sum]--;
			if (mapFreq[sum] == 0)
				mapFreq.erase(sum);
		}
		int pathSum(TreeNode* root, int targetSum)
		{
			// �־��� ��� root���� Ư�� Path�� ���� �������� targetSum�� �������� path�� ���� ��ȯ�϶�.
			// �̶� path�� �Ʒ� �������θ� ���� �� �ִ�.
			// 
			// �� 560. ������ tree�� ������ ������ ��.
			int ret = 0;
			unordered_map<long, int> mapFreq;
			mapFreq[0] = 1;
			pathSum_helper(root, 0, ret, mapFreq, targetSum);
			return ret;
		}

		// 1372. Longest ZigZag Path in a Binary Tree
		int longestZigZag_dfs(TreeNode* node, int count, bool isLeft)
		{
			if (node == NULL)	return count;

			int left = 0, right = 0;
			if (isLeft)
			{
				right = longestZigZag_dfs(node->right, count + 1, false);
				left = longestZigZag_dfs(node->left, 0, true);
			}
			else
			{
				right = longestZigZag_dfs(node->right, 0, false);
				left = longestZigZag_dfs(node->left, count + 1, true);
			}
			return max(left, right);
		}
		int longestZigZag(TreeNode* root)
		{
			// �־��� tree ���� �ִ� ������ zig zag ������ ���϶�.
			//
			if (root == NULL)	return 0;

			int retLeft = longestZigZag_dfs(root->left, 0, true);
			int retRight = longestZigZag_dfs(root->right, 0, false);
			return max(retLeft, retRight);
		}

		// 236. Lowest Common Ancestor of a Binary Tree
		bool LCA_dfs(TreeNode* node, TreeNode* target, vector<TreeNode*>& vBuff)
		{
			if (node == NULL)	return false;

			vBuff.push_back(node);
			if (node == target)
				return true;

			if (LCA_dfs(node->left, target, vBuff) || LCA_dfs(node->right, target, vBuff))
				return true;

			vBuff.pop_back();
			return false;
		}
		TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q)
		{
			// �־��� root��忡�� p�� q�� ���ÿ� �θ� �Ǵ� ���� �����(����) ��带 ��ȯ�϶�.
			//
			vector<TreeNode*> vP, vQ;
			LCA_dfs(root, p, vP);
			LCA_dfs(root, q, vQ);

			int len = min(vP.size(), vQ.size());
			TreeNode* lastMatch = NULL;
			for (int q = 0; q < len; ++q)
			{
				if (vP[q] != vQ[q])
					return lastMatch;
				lastMatch = vP[q];
			}
			return lastMatch;
		}

		
	};

	class BinaryTree_BFS
	{
	public:
		struct TreeNode {
			int val;
			TreeNode* left;
			TreeNode* right;
			TreeNode() : val(0), left(nullptr), right(nullptr) {}
			TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
			TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
		};

		// 199. Binary Tree Right Side View. 
		vector<int> rightSideView(TreeNode* root)
		{
			vector<int> vRet;
			if (root == NULL)    return vRet;

			queue<TreeNode*> qBuff;
			qBuff.push(root);

			while (!qBuff.empty())
			{
				int size = qBuff.size();
				for (int q = 0; q < size; ++q)
				{
					TreeNode* cur = qBuff.front();
					qBuff.pop();

					if (q == size - 1)
						vRet.push_back(cur->val);

					if (cur->left != NULL)	qBuff.push(cur->left);
					if (cur->right != NULL)	qBuff.push(cur->right);
				}
			}
			return vRet;
		}

		// 1161. Maximum Level Sum of a Binary Tree
		int maxLevelSum(TreeNode* root)
		{
			// root node�� level�� 1�̶�� �Ҷ�(���� ���ʴ�� 1�� �����Ѵ�.)
			// �̶�, �� level�� ���� �ִ��� ������ �ּ� ������ ��ȯ�϶�.
			//
			if (root == NULL)	return 0;

			queue<TreeNode*> qBuff;
			qBuff.push(root);
			int level = 0;
			long maxSum = LONG_MIN;
			int ret = 0;
			while (!qBuff.empty())
			{
				++level;
				int count = qBuff.size();
				long sum = 0;
				for (int q = 0; q < count; ++q)
				{
					TreeNode* cur = qBuff.front();
					qBuff.pop();

					sum += cur->val;
					if (cur->left != NULL)	qBuff.push(cur->left);
					if (cur->right != NULL)	qBuff.push(cur->right);
				}

				if (maxSum < sum)
				{
					maxSum = sum;
					ret = level;
				}
			}
			return ret;
		}
	};


	class BinarySearchTree
	{
	public:
		struct TreeNode {
			int val;
			TreeNode* left;
			TreeNode* right;
			TreeNode() : val(0), left(nullptr), right(nullptr) {}
			TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
			TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
		};

		// 700. Search in a Binary Search Tree
		TreeNode* searchBST(TreeNode* node, int val)
		{
			// �־��� Binary Tree(2�� Ʈ��)���� �ش� ���� ���� node�� ã�ƶ�. 
			//
			if (node == NULL)	return NULL;

			if (node->val < val)	return searchBST(node->right, val);
			if (node->val > val)	return searchBST(node->left, val);
			return node;
		}

		// 450. Delete Node in a BST 
		TreeNode* deleteNode(TreeNode* root, int key)
		{
			// ��� key�� ���� ��带 ã�� BST�� �����ǵ��� ��� ��带 ���� �϶�.
			//
			if (root == NULL)	return root;

			TreeNode* target = root;
			TreeNode* parent = NULL;
			
			// Search Target.
			while (target != NULL)
			{
				if (target->val == key)
					break;
				
				parent = target;
				if (target->val > key)	target = target->left;
				else target = target->right;
			}

			// Search Smallest Node from the right Child.
			TreeNode* smallest = NULL;
			TreeNode* parent_smallest = NULL;
			if (target!=NULL && target->right!=NULL)
			{
				smallest = target->right;
				parent_smallest = target;
				while (true)
				{
					if (smallest->left == NULL)
						break;
					parent_smallest = smallest;
					smallest = smallest->left;
				}
			}

			// Search Biggest Node from the left Child.
			TreeNode* biggest = NULL;
			TreeNode* parent_biggest = NULL;
			if (target != NULL && target->left != NULL)
			{
				biggest = target->left;
				parent_biggest = target;
				while (true)
				{
					if (biggest->right == NULL)
						break;
					parent_biggest = biggest;
					biggest = biggest->right;
				}
			}

			// Remove target. 
			if (target != NULL)
			{
				TreeNode* replaced = NULL;
				// Replacing with either side is fine.
				if (smallest != NULL)
				{
					if (target->right == smallest)	target->right = smallest->right;
					else parent_smallest->left = smallest->right;
					smallest->left = target->left;
					smallest->right = target->right;
					replaced = smallest;
				}
				else if (biggest != NULL)
				{
					if (target->left == biggest)	target->left = biggest->left;
					else parent_biggest->right = biggest->left;
					biggest->right = target->right;
					biggest->left = target->left;
					replaced = biggest;
				}

				if (parent != NULL)
				{
					if (parent->left == target) parent->left = replaced;
					else parent->right = replaced;
				}
				else
					root = replaced;
			}
			return root;
		}

	};


	class Graph_DFS
	{
	public:
		
		// 841. Keys and Rooms
		bool canVisitAllRooms(vector<vector<int>>& rooms)
		{

		}
	};

	class Heap_PriorityQueue
	{
	public:
		
		// 512. Kth Largest Element in an Array.
		int findKthLargest(vector<int>& nums, int k)
		{
			priority_queue<int> pqBuff;

			for (int k = 0; k < nums.size(); ++k)
			{
				pqBuff.push(nums[k]);
			}

			while (!pqBuff.empty())
			{
				int top = pqBuff.top();
				--k;

				if (k == 0)
					return top;

				pqBuff.pop();
			}
			return -1;
		}

		// 2336. Smallest Number in infinite Set.
		class SmallestInfiniteSet 
		{
			unsigned int mMin;
			//priority_queue<int, vector<int>, greater<int>> mPQBuff;
			set<int> mSet;
		public:
			SmallestInfiniteSet() 
			{
				mMin = 1;
			}
			int popSmallest() 
			{
				//if (!mPQBuff.empty())
				if(mSet.size() > 0)
				{
					//int ret = mPQBuff.top();
					//mPQBuff.pop();
					int ret = *mSet.begin();
					mSet.erase(ret);
					return ret;
				}
				++mMin;
				return mMin - 1;
			}
			void addBack(int num) 
			{
				if (mMin > num)
				{
					if (mSet.find(num) == mSet.end())
					{
						//mPQBuff.push(num);
						mSet.insert(num);
					}
				}
			}
		};

		// 2542. Maximum Subsequence Score.
		long long maxScore(vector<int>& nums1, vector<int>& nums2, int k)
		{
			// ���̰� ���� �ΰ��� �迭�� ��� k�� �־��� ��, 
			// nums1�� nums2���� ���� k�� �κп��� ���Ѵ�. 
			// nums1������ �κп��� ����,          => Sum(n1, ...)
			// nums2������ �κп��� �ּҰ��� ���  => Min(n1... )
			// �̸� �������� ������ �ִ밪�� ���϶�.
			//

			// ù �迭�� �������� ������, 
			// ��° �迭�� ������������ ������ �ϰ� 
			// ���� ��õ�.


			// nums1�� �����Ͽ�, ���� �ִ븦 ã�� �����ϴ� nums2�� �ּҰ����� ����� �����ϴ� ���.
			map<int, vector<int>, greater<int>> mapBuff;	// Decending order.
			for (int q = 0; q < nums1.size(); ++q)
			{
				if (mapBuff.find(nums1[q]) == mapBuff.end())
				{
					vector<int> vTemp{ q };
					mapBuff[nums1[q]] = vTemp;
				}
				else
					mapBuff[nums1[q]].push_back(q);
			}

			unordered_map<int, vector<int>> mapNums2;
			for (int q = 0; q < nums2.size(); ++q)
			{
				if (mapNums2.find(nums2[q]) == mapNums2.end())
				{
					vector<int> vTemp{ q };
					mapNums2[nums2[q]] = vTemp;
				}
				else
					mapNums2[nums2[q]].push_back(q);
			}


			long long ret = 0;
			long long sum = 0;
			priority_queue <int, vector<int>, greater<int> > minHeap;	// min heap.
			int cnt = 0;
			for (map<int, vector<int>>::iterator it = mapBuff.begin(); it != mapBuff.end(); ++it)
			{
				for (int q = 0; q < it->second.size(); ++q)
				{
					//cout << it->first << endl;
					//cout << it->second[q] << endl;

					sum += it->first;			// nums1. 10, 9, 8...

					int idx = it->second[q];
					minHeap.push(nums2[idx]);

					++cnt;



					if (cnt == k)
					{
						int min = minHeap.top();
						minHeap.pop();

						ret = max(ret, sum * min);

						idx = (mapNums2[min])[ mapNums2[min].size() - 1];
						

						
						sum -= nums1[idx];
						
						mapNums2[min].pop_back();
						if (mapNums2[min].size() <= 0)
							mapNums2.erase(min);

						--cnt;
					}
				}
			}
			return ret;

			/*
			
			// nums2�� �����Ͽ�, �ּҰ��� ���� & �����ϸ鼭 �����ϴ� nums1�� ������ ����� ���� �ϴ� ���.
			
			map<int, vector<int>, greater<int>> mapBuff;	// Decending order.
			for (int q = 0; q < nums2.size(); ++q)
			{
				if (mapBuff.find(nums2[q]) == mapBuff.end())
				{
					vector<int> vTemp{ q };
					mapBuff[nums2[q]] = vTemp;
				}
				else
					mapBuff[nums2[q]].push_back(q);
			}

			long long ret = 0;
			long long sum = 0;
			priority_queue <int, vector<int>, greater<int> > qBuff;	// min heap.
			for (map<int, vector<int>>::iterator it = mapBuff.begin(); it != mapBuff.end(); ++it)
			{
				for (int q = 0; q < it->second.size(); ++q)
				{
					cout << it->first << endl;
					cout << it->second[q] << endl;

					int idx = it->second[q];
					sum += nums1[idx];
					qBuff.push(nums1[idx]);

					if (qBuff.size() == k)
					{
						int min = it->first;
						ret = max(ret, sum * min);
						
						sum -= qBuff.top();
						qBuff.pop();
					}
				}
			}
			return ret;
			*/
		}

		// 2462. Total Cost to Hire K Workders
		long long totalCost(vector<int>& costs, int k, int candidates)
		{
			//
			// k���� worker�� ����Ѵٰ� �Ҷ�, costs�� �� worker�� ����̴�.
			// �Ʒ��� ���� ��Ģ���� worker�� ����Ѵٰ� �Ҷ�, kȸ�� ���� ���� ���� ������� ��ȯ�϶�.
			// - �� k ������ ���鼭 �� ���Ǵ� 1�� ����ϸ�, ���� �뵿�ڴ� ����Ʈ���� ���ŵȴ�.
			// - ����� �տ��� candidates��ŭ �ĺ����� ���ϰ�, �ڷε� �ش� �ĺ����� ���Ѵ�.
			// - �� �� �ĺ��� �߿� �ּҺ���� �뵿�ڸ� ����Ѵ�.
			// - �ĺ������� ���� ���� �뵿�ڸ��� �ִٸ�, �� �߿��� �ּҺ���� �뵿�ڸ� ����Ѵ�.
			//  
			vector<bool> vHired;
			vHired.resize(costs.size(), false);

			priority_queue<pair<int, pair<int, bool>>, vector<pair<int, pair<int, bool>>>, greater<pair<int, pair<int, bool>>> > qBuff;
			// value, (index, IsDirectionTail)

			int idxHead = 0;
			int idxTail = costs.size() - 1;
			int cntHead = 0, cntTail = 0;
			for (int q = 0; q < costs.size(); ++q)
			{
				if (cntHead < candidates)
				{
					qBuff.push(make_pair(costs[q], make_pair(q, true)));
					idxHead = q;
					++cntHead;
				}
				if (qBuff.size() >= costs.size())   break;
				int idxBack = costs.size() - q - 1;
				if (cntTail < candidates)
				{
					qBuff.push(make_pair(costs[idxBack], make_pair(idxBack, false)));
					idxTail = idxBack;
					++cntTail;
				}
				if (qBuff.size() >= costs.size())   break;
				if (cntHead >= candidates && cntTail >= candidates)
					break;
			}

			long long total = 0;
			for (int q = 0; q < k; ++q)
			{
				total += ((long long)qBuff.top().first);
				vHired[qBuff.top().second.first] = true;
				cout << "value : " << qBuff.top().first << ", total : " << total << endl;
				bool isDirBack = qBuff.top().second.second;
				qBuff.pop();

				if (idxHead+1 >= idxTail)   continue;

				if (isDirBack)
				{
					++idxHead;
					while (idxHead < costs.size() && vHired[idxHead])
						idxHead++;
					if (idxHead < costs.size())
						qBuff.push(make_pair(costs[idxHead], make_pair(idxHead, true)));
				}
				else
				{
					--idxTail;
					while (idxTail >= 0 && vHired[idxTail])
						idxTail--;
					if (idxTail >= 0)
						qBuff.push(make_pair(costs[idxTail], make_pair(idxTail, false)));
				}
			}
			return total;
		}
	};


	class BinarySearchLC
	{
	public:
		// 2300. Successful Pairs of Spells and Potions
		int pairs_helper(vector<int>& vBuff, int left, int right, long long target)
		{
			if (left > right) return vBuff.size()-left;

			int mid = left + (right - left) / 2;
			int cur = vBuff[mid];

			if (cur < target)   return pairs_helper(vBuff, mid + 1, right, target);
			else return pairs_helper(vBuff, left, mid - 1, target);
		}
		vector<int> successfulPairs(vector<int>& spells, vector<int>& potions, long long success)
		{
			// spells�� potions�� 2���� array input�� ������, ���� ������ ���� success ���� ũ�ų� ������ �������� ģ��.
			// �� ������ spells�� �� ���ҿ� ���� ������ ���� array�� out �϶�.
			//
			sort(potions.begin(), potions.end());

			vector<int> vRet;

			for (int k = 0; k < spells.size(); ++k)
			{
				int div = (success % spells[k]) == 0 ? success / spells[k] : 1 + (success / spells[k]);
				cout << spells[k] << " : " << div << endl;
				vRet.push_back(pairs_helper(potions, 0, potions.size() - 1, div ));
			}
			return vRet;
		}


		// 162. Find Peak Element
		int peak_helper(vector<int>& nums, int left, int right)
		{
			if (left > right)	// No Peak Found ?
				return -1;

			int mid = left + (right - left) / 2;

			long prev = mid - 1 < 0 ? ((long)nums[mid]) - 1 : nums[mid - 1];
			long next = mid + 1 >= nums.size() ? ((long)nums[mid] - 1) : nums[mid + 1];

			if (nums[mid] > prev && nums[mid] > next)
				return mid;

			if (nums[mid] < prev)
				return peak_helper(nums, left, mid - 1);

			return peak_helper(nums, mid + 1, right);
		}
		int findPeakElement(vector<int>& nums)
		{
			// �־��� nums vector���� �ֺ� ������ ���� ū ���Ҹ� peak ���Ҷ� �Ѵ�. 
			// � peak���ҵ� ã�Ƽ� �� index�� ��ȯ�϶�.
			// �̶� �迭�� ù�� ���� �迭 ���� ������ ũ�ٰ� �����Ѵ�.
			// TC�� O(logN) �� �ǵ��� �϶�. 
			// 
			// O(N)
			/*
			if (nums.size() == 0)	return -1;

			long prev = ((long)nums[0]) - 1;
			for (int q = 0; q < nums.size(); ++q)
			{
				long next = q < nums.size() - 1 ? nums[q + 1] : ((long)nums[q]) - 1;
				if (nums[q] > prev && nums[q] > next)
					return q;
				prev = nums[q];
			}
			return -1;*/

			// O(log N)
			return peak_helper(nums, 0, nums.size() - 1);
		}


		// 875. Koko Eating Bananas
		int koko_help(vector<int>& nums, long left, long right, int h)
		{
			if (left > right) return left;

			long mid = left + (right - left) / 2;

			long long totalTime = 0;
			for (int q = 0; q < nums.size(); ++q)
				totalTime += (nums[q] % mid) == 0 ? ((long)nums[q])/mid : 1 + (((long)nums[q])/mid);

			if (totalTime > h)
				return koko_help(nums, mid + 1, right, h);

			return koko_help(nums, left, mid - 1, h);
		}
		int minEatingSpeed(vector<int>& piles, int h)
		{
			// �־��� piles �迭�� �ٳ������̸� �ǹ��ϰ�, h�� �ð��̴�. 
			// ���ڰ� �־��� �ð��� �ٳ��� ���̸� �� �Դ� �ð��� �ּ� ������ ã�ƶ�.
			// �̶�, �־��� �������� �ٳ��������� �ٳ����� �� ������, �� ���̸� �Դ´�.
			//

			long maxV = 0;
			for (int q = 0; q < piles.size(); ++q)
				maxV = max((int)maxV, piles[q]);

			return koko_help(piles, 1, maxV, h);
		}
	};

	class BackTracking
	{
	public:
		// 
		void letter_helper(map<char, string>& mapData, string digits, string curStr, vector<string>& vOut)
		{
			if (curStr.size() == digits.size())
			{
				if(digits.size() > 0)
					vOut.push_back(curStr);
				return;
			}

			int idx = curStr.size();
			string strTarget = mapData[digits.at(idx)];
			for (int k = 0; k < strTarget.size(); ++k)
			{
				curStr += strTarget[k];
				letter_helper(mapData, digits, curStr, vOut);
				curStr.erase(curStr.end()-1);
			}
		}
		vector<string> letterCombinations(string digits)
		{
			// input string digit�� 2~9������ ��ȭ��ȣ ������ string�̴�.
			// �̸� �Է��ҽ�, �̷� ��°����� ��� ���� ������ ã�ƶ�.
			//
			map<char, string> mapData;
			mapData['2'] = "abc";
			mapData['3'] = "def";
			mapData['4'] = "ghi";
			mapData['5'] = "jkl";
			mapData['6'] = "mno";
			mapData['7'] = "pqrs";
			mapData['8'] = "tuv";
			mapData['9'] = "wxyz";

			
			vector<string> vOut;
			letter_helper(mapData, digits, "", vOut);
			return vOut;
		}

		// 216. Combination SumIII
		void combi_help(vector<vector<int>>& vRet, vector<int>& vCur, const int targetSize, const int targetSum, const int start)
		{
			if (vCur.size() == targetSize)
			{
				int sum = 0;
				for (int q = 0; q < vCur.size(); ++q)
					sum += vCur[q];
				if (sum == targetSum)
					vRet.push_back(vCur);
				return;
			}

			for (int k = start; k <= 9; ++k)
			{
				vCur.push_back(k);
				combi_help(vRet, vCur, targetSize, targetSum, k + 1);
				vCur.pop_back();
			}
		}
		vector<vector<int>> combinationSum3(int k, int n)
		{
			// 1~9������ k������ ���� �ߺ� ���� 1ȸ�� ����Ͽ� �� ���� n�� �Ǵ� ��� ������ ã�ƶ�.
			//
			

			vector<vector<int>> vRet;
			vector<int> vCur;
			combi_help(vRet, vCur, k, n, 1);
			return vRet;
		}
	};

	class DP_1D
	{
	public:
		// 1137. N-th Tribonacci Number
		int tribonacci_help(map<int, int>& mapBuff, int n)
		{
			map<int, int>::iterator itRet = mapBuff.find(n);
			if (itRet != mapBuff.end())
				return itRet->second;

			int nRet = tribonacci_help(mapBuff, n - 1) + tribonacci_help(mapBuff, n - 2) + tribonacci_help(mapBuff, n - 3);
			mapBuff[n] = nRet;
			return nRet;
		}
		int tribonacci(int n)
		{
			// T0 = 0, T1 = 1, T2 = 1, and Tn+3 = Tn + Tn+1 + Tn+2 for n >= 0.
			// ���� ���� �����϶� �־��� n �� ���� ��� ���� ã�ƶ�.
			//
			if (n == 0)	return 0;
			if (n <= 2) return 1;

			map<int, int> mapBuff;
			mapBuff[0] = 0;
			mapBuff[1] = 1;
			mapBuff[2] = 1;

			return tribonacci_help(mapBuff, n - 1) + tribonacci_help(mapBuff, n - 2) + tribonacci_help(mapBuff, n - 3);
		}

		// 746. Min Cost Climbing Stairs.
		int climb_helper(vector<int>& cache, vector<int>& cost, int idx)
		{
			if (idx >= cost.size())
				return 0;

			if (cache[idx] >= 0)	return cache[idx];

			int cost1 = climb_helper(cache, cost, idx + 1);
			int cost2 = climb_helper(cache, cost, idx + 2);

			cache[idx] = cost[idx] + min(cost1, cost2);
			return cache[idx];
		}
		int minCostClimbingStairs(vector<int>& cost)
		{
			// �ѹ��� �ϳ� Ȥ�� �ΰ��� ����� ��� ���� �� ������, �׶� ����� cost�̴�. 
			// top �� �����ϱ� ���� �ּ� ����� ã�ƶ�.
			//
			vector<int> vCache;
			vCache.resize(cost.size(), -1);
			int cost1 = climb_helper(vCache, cost, 0);
			int cost2 = climb_helper(vCache, cost, 1);
			return min(cost1, cost2);
		}

		// 198. House Robber
		int rob_helper(vector<int>& cache, vector<int>& nums, int idx)
		{
			if (idx >= nums.size())
				return 0;

			if (cache[idx] >= 0)
				return cache[idx];

			int val1 = rob_helper(cache, nums, idx + 2);
			int val2 = rob_helper(cache, nums, idx + 3);

			cache[idx] = nums[idx] + max(val1, val2);
			return cache[idx];
		}
		int rob(vector<int>& nums)
		{
			// nums �迭�� �����ϵ�, �����ؼ� ������ �Ұ��ϴ�. ���� �� �ִ� �ִ� ���� ���϶�.
			//
			vector<int> cache;
			cache.resize(nums.size(), -1);
			return max(rob_helper(cache, nums, 0), rob_helper(cache, nums, 1));
		}

		// 790. Domino and Tromino Tiling
		/*int tiling_help(int idx)
		{
			if (idx == 0)		return 1;
			else if (idx == 1)	return 2;
			else if (idx == 2)  return 5;

			const long mod = 1000000007;
			long sum = 0;
			for (int q = idx - 3; q >= 0; --q)
			{
				sum += tiling_help(q);
				sum %= mod;
			}

			return (tiling_help(idx - 1) + tiling_help(idx - 2) + sum * 2 + 2) % mod;
		}
		int numTilings(int n)
		{
			return tiling_help(n - 1);
		}*/
		int tiling_help(vector<int>& vCache, int idx)
		{
			if (idx == 0)		return 1;
			else if (idx == 1)	return 2;
			else if (idx == 2)  return 5;

			if (vCache[idx] >= 0)
				return vCache[idx];

			const long mod = 1000000007;
			long sum = 0;
			for (int q = idx - 3; q >= 0; --q)
			{
				sum += tiling_help(vCache, q);
				sum %= mod;
			}

			vCache[idx ] = (tiling_help(vCache, idx - 1) + tiling_help(vCache, idx - 2) + sum * 2 + 2) % mod;
			return vCache[idx];
		}
		int numTilings(int n)
		{
			vector<int> vCache;
			vCache.resize(n, -1);
			return tiling_help(vCache, n - 1);
		}
	};

	class DP_2D
	{
	public:
		// 62. Unique Paths
	/*
		int path_dp(int x, int y, const int m, const int n)
		{
			if (x >= m - 1)
			{
				if (y >= n - 1)
					return 1;
				return path_dp(x, y + 1, m, n);
			}
			if (y >= n - 1)
			{
				if (x >= m - 1)
					return 1;
				return path_dp(x + 1, y, m, n);
			}

			int cnt = 0;
			cnt += path_dp(x, y + 1, m, n);
			cnt += path_dp(x + 1, y, m, n);
			return cnt;
		}
		int uniquePaths(int m, int n)
		{
			// mxn�� grid�� �ְ� robot�� left top�� �ִ�. 
			// �̶� robot�� �������� ��ĭ, Ȥ�� �Ʒ��� ��ĭ�� ���� �ִ�.
			// �̶� right, bottom���� ���� ��� ������ ����� ���� ���϶�.
			//
			int ret = 0;
			if (m == 1 && n == 1)	return 1;
			if (n > 1)	ret += path_dp(0, 1, m, n);
			if (m > 1)	ret += path_dp(1, 0, m, n);
			return ret;
		}
		*/
		int path_dp(vector<int>& cache, int x, int y, const int m, const int n)
		{
			int idx = y * m + x;
			if (idx < cache.size() && cache[idx] >= 0)
				return cache[idx];

			if (x >= m - 1)
			{
				if (y >= n - 1)
					return 1;
				cache[idx] = path_dp(cache, x, y + 1, m, n);
				return cache[idx];
			}
			if (y >= n - 1)
			{
				if (x >= m - 1)
					return 1;
				cache[idx] = path_dp(cache, x + 1, y, m, n);
				return cache[idx];
			}

			int cnt = 0;
			cnt += path_dp(cache, x, y + 1, m, n);
			cnt += path_dp(cache, x + 1, y, m, n);
			cache[idx] = cnt;
			return cnt;
		}
		int uniquePaths(int m, int n)
		{
			// mxn�� grid�� �ְ� robot�� left top�� �ִ�. 
			// �̶� robot�� �������� ��ĭ, Ȥ�� �Ʒ��� ��ĭ�� ���� �ִ�.
			// �̶� right, bottom���� ���� ��� ������ ����� ���� ���϶�.
			//
			int ret = 0;
			if (m == 1 && n == 1)	return 1;
			vector<int> cache;
			cache.resize(m * n, -1);
			if (n > 1)	ret += path_dp(cache, 0, 1, m, n);
			if (m > 1)	ret += path_dp(cache, 1, 0, m, n);
			return ret;
		}

		// 1143. Longest Common Subsequence
		int longest_dp(vector<int>& vCache, int idx1, int idx2, string& text1, string& text2)
		{
			if (idx1 >= text1.size() || idx2 >= text2.size())
				return 0;

			int idx = idx2 * text1.size() + idx1;
			if (vCache[idx] >= 0)
				return vCache[idx];

			if (text1[idx1] == text2[idx2])
				vCache[idx] = 1 + longest_dp(vCache, idx1 + 1, idx2 + 1, text1, text2);
			else
				vCache[idx] = max(longest_dp(vCache, idx1+1, idx2, text1, text2), longest_dp(vCache, idx1, idx2+1, text1, text2));

			return vCache[idx];
		}
		int longestCommonSubsequence(string text1, string text2)
		{
			// �ΰ��� string text1, text2�� �־����� �� string������ ���� �� ���� sub-string�� ���̸� ��ȯ�϶�.
			//
			vector<int> vCache;
			vCache.resize(text1.size() * text2.size(), -1);
			return longest_dp(vCache, 0, 0, text1, text2);
		}		

		// 714. Best Time to Buy and Sell Stock With Transaction Fee
		int maxProfit_dp(vector<int>& vCache, vector<int>& prices, int idx, int boughtIndex, const int fee)
		{
			if (idx >= prices.size())
				return 0;

			string key = to_string(boughtIndex) + "-" + to_string(idx);
			int idxCache = idx;

			if (boughtIndex < 0)							// �Ȼ��� ��.
			{
				vCache[idxCache] = max(
					maxProfit_dp(vCache, prices, idx + 1, idx, fee),	// ���� ���.
					maxProfit_dp(vCache, prices, idx + 1, -1, fee));	// �׳� ����ģ��.
			}
			else
			{
															// ���.
				idxCache += prices.size();
				
				vCache[idxCache] = max(
					prices[idx] - prices[boughtIndex] - fee + 
					maxProfit_dp(vCache, prices, idx + 1, -1, fee),	// ���� �Ǵ�.
																	// �׳� ����ģ��.
					maxProfit_dp(vCache, prices, idx + 1, boughtIndex, fee));
			}
			return vCache[idxCache];
		}
		int maxProfit(vector<int>& prices, int fee)
		{
			// vector prices�� �� ���� stock�� ������ �ǹ��Ѵ�.
			// ��� �ȶ� fee�� �����Ѵٸ�, 
			// �ִ� ������ ���϶�.
			vector<int> vCache;
			vCache.resize(prices.size()*2, -1);
			return maxProfit_dp(vCache, prices, 0, -1, fee);
		}


		// 72. Edit Distance
		int minDist_dp(vector<int>& vCache, int idx1, int idx2, string word1, string word2)
		{
			if (idx1 >= word1.size())
				return word2.size() - idx2;
			if (idx2 >= word2.size())
				return word1.size() - idx1;

			int idxCache = idx2 * word1.size() + idx1;
			if (vCache[idxCache] >= 0)
				return vCache[idxCache];

			if (word1[idx1] == word2[idx2])
				vCache[idxCache] = minDist_dp(vCache, idx1 + 1, idx2 + 1, word1, word2);
			else
			{
				int insert_op = 1 + minDist_dp(vCache, idx1, idx2+1, word1, word2);
				int delete_op = 1 + minDist_dp(vCache, idx1+1, idx2, word1, word2);
				int replace_op = 1 + minDist_dp(vCache, idx1+1, idx2+1, word1, word2);

				vCache[idxCache] = min(insert_op, min(delete_op, replace_op));
			}
			return vCache[idxCache];
		}
		int minDistance(string word1, string word2)
		{
			// word1�� word2 �ΰ��� string�� �־����� word1�� word2�� �ٲٱ� ���� 
			// �ּ��� ���� ���� ���϶�.
			// ������ ���ڸ� �ְų�, ���ų�, ��ü�� �� �ִ�.
			if (word1.size() == 0)	return word2.size();
			if (word2.size() == 0)  return word1.size();

			vector<int> vCache;
			vCache.resize(word1.size() * word2.size(), -1);
			return minDist_dp(vCache, 0, 0, word1, word2);
		}
	};

	class Intervals
	{
	public:
		// 435. Non0overlapping Intervals
		static bool interval_sort(vector<int>& v1, vector<int>& v2)
		{
			return v1[0] < v2[0];
		}
		int eraseOverlapIntervals(vector<vector<int>>& in)
		{
			// �־��� input�� 2���� interval�� �ǹ��Ѵ�.
			// ��ġ�� �ʰ� �ϱ����� �ּ����� input�� �����Ѵٸ�
			// ��� �����Ҽ� �ְڴ°�.
			//
			if (in.size() <= 1)	return 0;

			sort(in.begin(), in.end(), interval_sort);

			int minRet = 0;
			int preEnd = in[0][1];
			for (int k = 1; k < in.size(); ++k)
			{
				if (in[k][0] < preEnd)
				{
					++minRet;
					preEnd = in[k][1] < preEnd ? in[k][1] : preEnd;
				}
				else preEnd = in[k][1];
			}
			return minRet;
		}

		// 452. Mininum Number of Arrows to Burst Ballons
		static bool arrow_sort(vector<int>& v1, vector<int>& v2)
		{
			return v1[0] < v2[0];
		}
		int findMinArrowShots(vector<vector<int>>& points)
		{
			// �־��� �迭�� ǳ���� 2���� ��ǥ�� �ǹ��Ѵ�. 
			// ��� ǳ���� ���߸��� ���� �ּ��� ȭ����� ã�ƶ�.
			// 
			if (points.size() <= 1)
				return points.size();

			// sort.
			sort(points.begin(), points.end(), arrow_sort);

			int cntArrow = 0;
			int lastEnd = points[0][1];
			int idxStart = 0;
			for (int k = 1; k < points.size(); ++k)
			{
				// �������� �Ͷ߸��� �ִ� ǳ���̸�, �� ���� ������ ����. 
				// arrow ����.
				if (lastEnd >= points[k][0])
				{
					--cntArrow;
					lastEnd = min(lastEnd, points[k][1]);
				}
				// �������� �Ͷ߸��� ������ �����ϰ�, ���� update.
				else
				{
					cntArrow += (k - idxStart);
					idxStart = k;
					lastEnd = points[k][1];
				}
			}
			cntArrow += (points.size() - idxStart);
			return cntArrow;
		}
	};

	class MonotonicStack
	{
	public:
		// 739. Daily Tempreatures
		vector<int> dailyTemperatures(vector<int>& temp)
		{
			// �־��� input array�� �� ��¥�� �µ� ��� �Ҷ�, 
			// �� ������ �� ������ ���� �Ǳ���� ��ĥ�� ��ٷ��� �ϴ���
			// ����϶�.
			//
			vector<int> vRet;
			vRet.resize(temp.size(), 0);

			stack<pair<int, int>> sBuff;
			sBuff.push(make_pair(temp[0], 0));

			for (int k = 1; k < temp.size(); ++k)
			{
				int curTemp = temp[k];
				while (!sBuff.empty())
				{
					if (sBuff.top().first < curTemp)
					{
						vRet[sBuff.top().second] = k - sBuff.top().second;
						sBuff.pop();
					}
					else break;
				}
				sBuff.push(make_pair(curTemp, k));
			}
			return vRet;
		}

		// 901. Online Stock Span

		stack<pair<int, int>> sPrices;
		int next(int price)
		{
			int cnt = 1;
			while (!sPrices.empty())
			{
				if (price >= sPrices.top().first)
				{
					cnt += sPrices.top().second;
					sPrices.pop();
				}
				else
					break;
			}
			sPrices.push(make_pair(price, cnt));
			
			return cnt;
		}
	};
	
	class Graphs_DFS
	{
	public:
		// 841. Keys and Rooms
		void canVisit(vector<bool>& vVisit, int idx, vector<vector<int>>& rooms)
		{
			if (vVisit[idx])	return;

			vVisit[idx] = true;

			for (int q = 0; q < rooms[idx].size(); ++q)
			{
				int curIdx = rooms[idx][q];
				canVisit(vVisit, curIdx, rooms);
			}
		}
		bool canVisitAllRooms(vector<vector<int>>& rooms)
		{
			// 0 index ���� �����ϰ� �� vector���� index�� �濡�� ���� �� �� �ִ�. 
			// ��� �濡 ���� �������� ���θ� ��ȯ�϶�.
			//
			if (rooms.size() <= 0)	return false;

			vector<bool> vVisit;
			vVisit.resize(rooms.size(), false);
			vVisit[0] = true;

			canVisit(vVisit, 0, rooms);
			
			

			/*
			queue<int> qBuff;
			for (int k = 0; k < rooms[0].size(); ++k)
				qBuff.push(rooms[0][k]);

			while (!qBuff.empty())
			{
				int idx = qBuff.front();
				qBuff.pop();
				if (vVisit[idx])
					continue;

				vVisit[idx] = true;
				for (int k = 0; k < rooms[idx].size(); ++k)
					qBuff.push(rooms[idx][k]);
			}*/

			for (int k = 0; k < vVisit.size(); ++k)
			{
				if (!vVisit[k])	return false;
			}
			return true;
		}

		// 547. Number of Provinces
		int findCircle_help(int idx, vector<vector<int>>& isConnected)
		{
			int minIdx = idx;

			vector<bool> vVisit;
			vVisit.resize(isConnected.size(), false);
			queue<int> qBuff;
			for (int q = 1; q < isConnected[idx].size(); ++q)
			{
				if (isConnected[idx][q] == 1)
				{
					minIdx = min(minIdx, q);
					qBuff.push(q);
					vVisit[q] = true;
				}
			}

			while (!qBuff.empty())
			{
				int curIdx = qBuff.front();
				qBuff.pop();
				if (vVisit[curIdx])
					continue;

				vVisit[curIdx] = true;
				for (int q = 0; q < isConnected[curIdx].size(); ++q)
				{
					if (curIdx!=q && isConnected[idx][q]==1)
					{
						minIdx = min(minIdx, q);
						qBuff.push(q);
					}
				}
			}
			return minIdx;
		}
		int findCircleNum(vector<vector<int>>& isConnected)
		{
			// �־��� vector�� �� ������ ���� ���θ� �ǹ��Ѵ�.
			// �̶� ���� ������� �ʴ� ����� ���� ���϶�.
			//
			set<int> smallests;

			// squash linked nodes into smallest ones.
			for (int k = 0; k < isConnected.size(); ++k)
			{
				int idxSmallest = findCircle_help(k, isConnected);
				if (smallests.find(idxSmallest) == smallests.end())
					smallests.insert(idxSmallest);
			}

			// count how many is that.
			return smallests.size();
		}

		// 1466. Reorder Routes to Make All Paths Lead to the City Zero
		int minReorder(int n, vector<vector<int>>& connections)
		{
			vector<vector<pair<int, bool>>> vLink;	// node id, to 
			vLink.resize(n);

			// ����� ������ ����. - ������ �� ���� ��� �ʿ�
			for (int k = 0; k < connections.size(); ++k)
			{
				vLink[connections[k][0]].push_back(make_pair(connections[k][1], true));
				vLink[connections[k][1]].push_back(make_pair(connections[k][0], false));
			}

			 // 0 �������� BFS�ϸ鼭 ������ �� reverse�ϼ� count
			queue<pair<int, bool>> qBuff;
			for (int k = 0; k < vLink[0].size(); ++k)
				qBuff.push(make_pair(vLink[0][k].first, vLink[0][k].second));

			vector<bool> vVisit;
			vVisit.resize(n, false);
			vVisit[0] = true;

			int retCnt = 0;
			while (!qBuff.empty())
			{
				int id = qBuff.front().first;
				bool toNode = qBuff.front().second;
				qBuff.pop();
				if (vVisit[id])	continue;

				vVisit[id] = true;

				retCnt = toNode ? retCnt + 1 : retCnt;

				for (int k = 0; k < vLink[id].size(); ++k)
					qBuff.push(make_pair(vLink[id][k].first, vLink[id][k].second));
			}

			// 
			return retCnt;
		}

		// 399. Evaluate Division
		void AddDataToNode(unordered_map<string, vector<pair<string, double>>>& mapNode, string idFrom, string idTo, double value)
		{
			if (mapNode.find(idFrom) == mapNode.end())
			{
				vector<pair<string, double>> vData;
				vData.push_back(make_pair(idTo, value));

				mapNode[idFrom] = vData;
			}
			else
				mapNode[idFrom].push_back(make_pair(idTo, value));
		}
		vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) 
		{
			// �־��� input equations�� ����, values�� eq1 / eq2 �� �ǹ��Ѵٰ� �Ҷ�
			// queries�� ���� ����� ���϶�.
			//
			// �� ���� ����� �����ϸ�, 
			// ������ ������ �־��� ��ΰ��� ���� �ǰ�, 
			// ������ ������ �־��� ��ΰ����� ������ ���� �� �� �ִ�. 
			// ����� ���� �� ����. 
			//
			// �˻��� ���� ��� ��� �������� data ������.
			unordered_map<string, vector<pair<string, double>>> mapNodes;
			for (int q = 0; q < equations.size(); ++q)
			{
				string idFrom = equations[q][0];
				string idTo = equations[q][1];

				AddDataToNode(mapNodes, idFrom, idTo, values[q]);
				AddDataToNode(mapNodes, idTo, idFrom, 1.0/values[q]);
			}

			vector<double> vOut;
			for (int q = 0; q < queries.size(); ++q)
			{
				string start = queries[q][0];
				string dest = queries[q][1];
				set<string> setVisit;

				queue<pair<string, double>> qBuff;
				qBuff.push(make_pair(start, 1));
				double ret = -1.0;
				while (!qBuff.empty())
				{
					string cur = qBuff.front().first;
					double curValue = qBuff.front().second;
					qBuff.pop();
					if (mapNodes.find(cur) == mapNodes.end())
					{
						ret = -1.0;
						break;
					}
					if (cur == dest)
					{
						ret = curValue;
						break;
					}
					if (setVisit.find(cur) != setVisit.end())
						continue;
					setVisit.insert(cur);

					for (int z = 0; z < mapNodes[cur].size(); ++z)
						qBuff.push(make_pair(mapNodes[cur][z].first, curValue * mapNodes[cur][z].second));
				}
				vOut.push_back(ret);
			}
			return vOut;
		}
	};

	class Graphs_BFS
	{
	public:
		// 1926. Nearest Exit from Enterance in Maze
		int nearestExit(vector<vector<char>>& maze, vector<int>& entrance) 
		{
			// �־��� �迭 maze���� . �� �� ������, + �� ���� �ǹ��Ѵ�.
			// �ܺ� ��迡 �ִ� �� ������ exit�̶�� �����ϸ�, �Ա��� exit���� �����Ѵ�.
			// �Ա����� exit�� �����ϱ� ���� �ּ� ��� �̵� ���� ��ȯ�϶�.
			//
			int mazeWidth = maze[0].size();
			int mazeHeight = maze.size();
			vector<bool> vVisit;
			vVisit.resize(mazeHeight * mazeWidth, false);
			
			queue<pair<int, int>> qBuff;	// idx, move count
			int idx = entrance[0] * mazeWidth + entrance[1];
			qBuff.push(make_pair(idx, 0));

			int minCount = INT_MAX;
			while (!qBuff.empty())
			{
				idx = qBuff.front().first;
				int moveCnt = qBuff.front().second;
				qBuff.pop();
				
				if (vVisit[idx])  continue;
				vVisit[idx] = true;

				int ix = idx % mazeWidth;
				int iy = idx / mazeWidth;
				if (maze[iy][ix] == '+')	continue;
				
				if (ix == 0 || ix == mazeWidth - 1 || iy == 0 || iy == mazeHeight - 1)
				{
					if (ix != entrance[1] || iy != entrance[0])
					{
						minCount = min(minCount, moveCnt);
						continue;
					}
				}

				// left
				if (ix > 0)	
					qBuff.push(make_pair(idx - 1, moveCnt + 1));

				// right
				if (ix < mazeWidth - 1)
					qBuff.push(make_pair(idx + 1, moveCnt + 1));

				// up
				if (iy > 0)
					qBuff.push(make_pair(idx - mazeWidth, moveCnt + 1));

				// down
				if (iy < mazeHeight-1)
					qBuff.push(make_pair(idx + mazeWidth, moveCnt + 1));
			}
			return minCount;
		}

		// 994. Rotting Oranges
		bool orange_canMove(vector<vector<int>>& grid, vector<bool>& vVisit, int idx)
		{
			if (vVisit[idx])	return false;

			int W = grid[0].size();
			int iX = idx % W;
			int iY = idx / W;

			return grid[iY][iX] == 1;
		}
		int orangesRotting(vector<vector<int>>& grid)
		{
			// �־��� grid�� 0 �� ��ĭ, 1�� fresh ������, 2�� rotten �������� ���Ѵ�.
			// �д� rotten�� �������� ��ó�� fresh�� �������� rotten�ϰ� �� �� �ִٸ�, 
			// ��� �������� rotten�ϰ� ���� �� �ִ� �ð��� ã�ƶ�.
			// 
			int totalCount = 0;
			int H = grid.size();
			int W = grid[0].size();
			queue<int> qBuff;	// idx
			for (int k = 0; k < grid.size(); ++k)
			{
				for (int q = 0; q < grid[0].size(); ++q)
				{
					if (grid[k][q] != 0)		++totalCount;
					if (grid[k][q] == 2)
						qBuff.push(k * W + q);
				}
			}

			vector<bool> vVisit;
			vVisit.resize(W * H, false);

			int time = 0;
			int visitCnt = 0;
			while (qBuff.size() > 0)
			{
				int size = qBuff.size();
				bool processed = false;
				for (int k = 0; k < size; ++k)
				{
					int curIdx = qBuff.front();
					qBuff.pop();
					int iX = curIdx % W;
					int iY = curIdx / W;
					if (vVisit[curIdx]) continue;

					vVisit[curIdx] = true;
					++visitCnt;
					processed = true;

					// up
					if (iY>0 && orange_canMove(grid, vVisit, curIdx-W))		
						qBuff.push(curIdx - W);

					// down
					if (iY < H - 1 && orange_canMove(grid, vVisit, curIdx+W))	
						qBuff.push(curIdx + W);

					// left 
					if (iX > 0 && orange_canMove(grid, vVisit, curIdx-1))
						qBuff.push(curIdx - 1);

					// right
					if (iX < W - 1 && orange_canMove(grid, vVisit, curIdx+1)) 
						qBuff.push(curIdx + 1);

					cout << iX << ", " << iY << endl;
				}
				if(processed)
					++time;
				cout << endl;
			}
			
			return (visitCnt==totalCount) ? time-1 : -1;
		}
	};

	// Design class.
	class Trie
	{
	public:
		struct Node
		{
			char key;
			bool fin;
			vector<Node*> children;
			Node(char inKey, bool inFin)
			{
				key = inKey;	fin = inFin;
			}
		};

		Node* mRoot;

		Trie() {
			mRoot = new Node(' ', false);
		}

		Node* FindNode(char key, Node* target)
		{
			for (int q = 0; q < target->children.size(); ++q)
			{
				if (target->children[q]->key == key)
					return target->children[q];
			}
			return NULL;
		}

		void insert(string word) 
		{
			Node* cur = mRoot;
			for (int idx = 0; idx < word.size(); ++idx)
			{
				Node* found = FindNode(word[idx], cur);
				bool isLastChar = idx == word.size() - 1;
				if (found == NULL)
				{
					found = new Node(word[idx], isLastChar);
					cur->children.push_back(found);
				}
				else
					found->fin = isLastChar ? true : found->fin;

				cur = found;
			}
		}

		bool search(string word) 
		{
			Node* cur = mRoot;
			for (int idx = 0; idx < word.size(); ++idx)
			{
				Node* found = FindNode(word[idx], cur);
				if (found == NULL)	return false;
				
				bool isLastChar = idx == word.size() - 1;
				if (isLastChar && found->fin)
					return true;

				cur = found;
			}
			return false;
		}

		bool startsWith(string prefix) 
		{
			Node* cur = mRoot;
			for (int idx = 0; idx < prefix.size(); ++idx)
			{
				Node* found = FindNode(prefix[idx], cur);
				if (found == NULL)	return false;

				if (idx == prefix.size() - 1)
					return true;

				cur = found;
			}
			return false;
		}
	};

	class Trie75
	{
	public:
		// 1268. Search Suggestions System
		vector<vector<string>> suggestedProducts(vector<string>& products, string searchWord) 
		{
			// search word�� �Է��Կ� ���� products�� ����߿��� �ִ� 3���� ���þ �����ֵ��� 
			// �Լ��� ������ �϶�.
			// �̶� string�� lexicographically �ϰ� sort �϶�.

			vector<vector<string>> vRet;

			sort(products.begin(), products.end());
			for (int k = 0; k < searchWord.size(); ++k)
			{
				vector<string> vOut;
				vector<string>::iterator it = products.begin(); 
				for ( ; it != products.end(); )
				{
					if ((*it)[k] != searchWord[k])
						it = products.erase(it);
					else
					{
						if(vOut.size() < 3) vOut.push_back(*it);
						++it;
					}
				}
				vRet.push_back(vOut);
			}
			return vRet;
		}

	};

	class BitManipulation
	{
	public:
		// 338. Counting Bits
		vector<int> countBits(int n)
		{
			// n�� �־�����, 0 ~ n ������ ���� 2������ ��ȯ�Ͽ� �� 1�� ������ vector�� ����϶�.
			vector<int> vRet;
			/*for (int k = 0; k <= n; ++k)
			{
				int value = k;
				int count = 0;
				while (value)
				{
					if (value & 1)	++count;
					value = value >> 1;
				}
				vRet.push_back(count);
			}
			return vRet;*/

			vRet.resize(n + 1, 0);
			for (int q = 1; q <= n; ++q)
				vRet[q] = vRet[q / 2] + q%2;

			return vRet;
		}

		// 136. Single Number
		int singleNumber(vector<int>& nums)
		{
			// �־��� �迭 nums���� ��� ��Ҵ� �� 2���� ������, �� �ϳ��� 1���� ���´�. 
			// 1���� ������ ���� ã�ƶ�.
			// �̶� O(N)�� TC�� �߰� �޸𸮸� ������� ���ƶ�.
			//
			int ret = nums[0];
			for (int q = 1; q < nums.size(); ++q)
				ret = ret ^ nums[q];

			return ret;
		}

		// 1318. Minimum Flips to Make a OR b Equal to c
		int minFlips(int a, int b, int c)
		{
			// a or b �� �ؼ� c�� �ǰ� �Ϸ��� 
			// �ٲ�� �� a�� b�� �� ���� �ּҰ��� ���϶�.
			// 
			int ret = 0;
			while (a!=0 || b!=0 || c!=0)
			{
				int cc = c & 1;
				int aa = a & 1;
				int bb = b & 1;
				if (cc == 0)
				{
					if (aa == 1 && bb == 0)			++ret;
					else if (aa == 0 && bb == 1)	++ret;
					else if (aa == 1 && bb == 1)    ret += 2;
				}
				else
				{
					if (aa == 0 && bb == 0) ++ret;
				}
				c >>= 1;
				a >>= 1;
				b >>= 1;
			}
			return ret;
		}
	};

	void Run()
	{
		ArrayString solution;

		//cout << solution.mergeAlternately("abc", "pqr");
		//vector<int> in{ 20,100,10,12,5,13 };// 2, 1, 5, 0, 4, 6
		//cout << solution.increasingTriplet(in);
		//vector<char> vIn{ 'a','a','b','c','c','c' };
		//cout << solution.compress(vIn);

		//TwoPointers tpSolver;
		//vector<int> nums{ 0, 1, 0, 3, 12 };
		//tpSolver.moveZeroes(nums);

		SlidingWindow swSolver;
		//vector<int> nums{ 0,1,1,1,0,1,1,0,1 };
		//swSolver.findMaxAverage(nums, 1);
		//cout << swSolver.maxVowels("weallloveyou", 7);
		//cout << swSolver.longestSubarray(nums);

		PrefixSum pfSolver;
		vector<int> nums{ 1,7,3,6,5,6 };
		//cout << pfSolver.largestAltitude(nums);
		// cout << pfSolver.pivotIndex(nums);

		HashMapSet hmSolver;
		vector<vector<int>> grid{ {250,78,253},{334,252,253},{250,253,253} };
		// cout << hmSolver.equalPairs(grid);

		StackRT stackSolver;
		//cout << stackSolver.decodeString("3[z]2[2[y]pq4[2[jk]e1[f]]]ef");

		// [1,2,3,4]
		LinkedList listSolver;
		LinkedList::ListNode n5{ 5, NULL };
		LinkedList::ListNode n4{ 4, &n5 };
		LinkedList::ListNode n3{ 3, &n4 };
		LinkedList::ListNode n2{ 2, &n3 };
		LinkedList::ListNode n1{ 1, &n2 };
		//listSolver.deleteMiddle(&n4);
		//listSolver.oddEvenList(&n1);

		BinaryTree_DFS dfsSolver;
		//BinaryTree_DFS::TreeNode node5{ 5, NULL, NULL };
		//BinaryTree_DFS::TreeNode node4{ 4, NULL, &node5 };
		//BinaryTree_DFS::TreeNode node3{ 3, NULL, &node4 };
		//BinaryTree_DFS::TreeNode node2{ 2, NULL, &node3 };
		//BinaryTree_DFS::TreeNode node1{ 1, NULL, &node2 };
		//cout << dfsSolver.pathSum(&node1, 3);

		//vector<int> vIn2{ -1, -1, 1 };
		//cout << dfsSolver.subarraySum(vIn2, 0);

		BinarySearchTree bst_solver;
		BinarySearchTree::TreeNode node6{ 80, NULL, NULL };
		BinarySearchTree::TreeNode node5{ 60, NULL, NULL };
		BinarySearchTree::TreeNode node4{ 40, NULL, NULL };
		BinarySearchTree::TreeNode node3{ 70, &node5, &node6 };
		BinarySearchTree::TreeNode node2{ 30, NULL, &node4 };
		BinarySearchTree::TreeNode node1{ 50, &node2, &node3 };
		//bst_solver.deleteNode(&node1, 50);

		Heap_PriorityQueue pqSolver;
		vector<int> vv1{ 57,39,48,5,7,56,34,29 };// 44, 10, 25, 0, 25, 49, 0// 1, 3, 3, 2
		vector<int> vv2{ 28,12,16,48,11,54,28,22 };// 18, 39, 15, 31, 43, 20, 45
		//cout << pqSolver.maxScore(vv1, vv2, 1);// 6);

		vector<int> costs//{ 31,25,72,79,74,65,84,91,18,59,27,9,81,33,17,58 };
		//{ 1,2,4,1 };
		//{ 17,12,10,2,7,2,11,20,8 };
		{ 18,64,12,21,21,78,36,58,88,58,99,26,92,91,53,10,24,25,20,92,73,63,51,65,87,6,17,32,14,42,46,65,43,9,75 };
		cout << pqSolver.totalCost(costs, 13, 23);// 3, 3);// 11, 2);

		BinarySearchLC bspSolver;
		vector<int> spells{ 14 };
		vector<int> potions{ 25,19,30,37,14,30,38,22,38,38,26,33,34,23,40,28,15,29,36,39,39,37,32,38,8,17,39,20,4,39,39,7,30,35,29,23 };
		//bspSolver.successfulPairs(spells, potions, 317);

		//vector<int> peaks{ 0, 1, 0, 5, 6, 7, 8 };
		//cout << bspSolver.findPeakElement(peaks);
		//vector<int> piles{ 805306368,805306368,805306368 };
		//cout << bspSolver.minEatingSpeed(piles, 1000000000);

		//BackTracking btSolver;
		//btSolver.letterCombinations("23");

		DP_1D dpSover;
		//vector<int> cost{ 1,100,1,1,1,100,1,1,100,1 };// 
		//{ 10, 15, 20 };
	    //cout << dpSover.minCostClimbingStairs(cost);

		//cout << dpSover.numTilings(5);

		DP_2D dp2Sover;
		// cout << dp2Sover.uniquePaths(1, 2);

		//cout << dp2Sover.longestCommonSubsequence(//"abcde", "ace");
		//	"mhunuzqrkzsnidwbun", "szulspmhwpazoxijwbq");

		vector<int> vPrices{ 1, 3, 2, 8, 4, 9 };
		//cout << dp2Sover.maxProfit(vPrices, 2);
		//cout << dp2Sover.minDistance("horse", "ros");

		//BitManipulation bitSolver;
		//cout << bitSolver.minFlips(8, 3, 5);

		Graphs_DFS graphSolver;
		vector<vector<string>> equations = { {"a","b"}, {"b","c"} };
		vector<double> values = { 2.0, 3.0 };
		vector<vector<string>> query = { {"a","c"},{"b","a"},{"a","e"},{"a","a"},{"x","x"} };
		//graphSolver.calcEquation(equations, values, query);

		Graphs_BFS bfsSolver;
		vector<vector<char>> maze = { {'+','+','.','+'}, {'.','.','.','+'}, {'+','+','+','.'} };
		vector<int> entrance2 = {1, 2 };
		//cout << bfsSolver.nearestExit(maze, entrance2);

		//vector<vector<int>> grid22 = { {2,1,1} ,{1,1,0},{0,1,1} };
		vector<vector<int>> grid22 = { {2,2} ,{1,1},{0,0}, {2,0}};
		//cout << bfsSolver.orangesRotting(grid22);
	}
};