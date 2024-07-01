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
			// str1가 str2로 나눠지는 최대 string을 찾아라.
			if (str1 + str2 != str2 + str1)
				return "";

			int iGCD = gcd(str1.length(), str2.length());
			return str1.substr(0, iGCD);
		}

		// 1431. Kids With the Greatest Number of Candies
		vector<bool> kidsWithCandies(vector<int>& candies, int extraCandies)
		{
			// input array가 각 아이들이 가지고 있는 사탕의 수다. 이때 extranCadies를 각 수에 더하면, 
			// 각 해당 아이가 전체 에서 최대의 사탕수를 가지는지 여부를 반환하라.
			// 이때 여러 아이가 동시에 최대의 캔디수를 가질 수 있다.
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
			// 각 자리가 1일때 flow가 planted되어 있고, 0이면 그렇지 않다.
			// flower는 연속해서 plant할 수 없다.
			// 이때 n의 flowers를 더 심으려고 한다면, 가능하지 여부를 반환하라.
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
			// s에서 모음 문자만 reverse해서 반환하라.
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
			// 단어가 space 캐릭터가 아닌 연속된 캐릭터 집합이라고 하면, 
			// s에 대해 이 단어들를 뒤집은 s를 출력하라.
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
			// nums의 배열값에서 해당 자신의 값을 제외한 다른값들의 곱을 반환하라.
			// O(N) time complexity and O(1) space complexity로 구현하고, 나누기 연산을 사용하지 말라.
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
			// 세개의 증가하는 배열 구간에 대해 해당 값이 역시 오름차순이 되는 구간이 있는지 여부를 반환하라.
			// -> TC O(N), SC O(1)에 풀수 있겠는가?
			// 
			// 
			// Brute Force - 3중 for문을 돌면서 조건을 만족하나 확인한다. 
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
			// 해당 chars를 압축하라.
			// - 나오는 문자수를 문자후에 출력하라.
			// - 문자가 하나라면, 문자후에 숫자를 생략하라.
			// constant extra space만을 사용하라.
			// 압축한 문자를 input된 buffer에 update하라.
			// 완료되면 이 최종 buffer의 size를 반환하라.
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
			// 배열에서 등장하는 0을 뒤로 밀고, in place로 처리하라.
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
			// t의 일부 문자를 제거해서(순서는 변경하지 말고) s를 만들수 있는지 여부를 반환하라.
			// 이때 s와 t는 소문자로만 구성되어 있다.
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
			// 각 height에 해당하는 높이에 물을 채운다고 할때, 
			// 최대 면적을 구하라.
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
			// nums 배열에서 두 수의 합이 sum이 되면 두 수를 제거한다.
			// 이 연산의 최대 수를 구하라.
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
			// nums에서 연속된 sub array 중에 길이가 k가 되는 것중에 가장 큰 평균값을 반환하라.
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
			// s 안에서 길이가 k인 모든 substring 안에서 
			// 최대 모음의 개수를 반환하라.
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
			// 1과 0으로 구성된, nums array가 있을때, k의 길이만큼의 subarray에서 
			// k수 만큼의 0을 1로 바꿀 수 있다고 하면, 최대 연속된 1의 길이를 찾아라.
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
			// 1과 0으로 구성된 nums배열이 주어질 경우, 0을 1번 제거할 수 있다면
			// 얻을 수 있는 1로만 구성된 sub array의 최대 길이를 구하라.
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
			// 입력된 배열값은 n과 n+1 위치와의 차이 값이다. 
			// 이때, 절대값의 가장 큰 값을 찾아라.
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
			// 우측과 좌측의 합의 값이 같은 기준 index를 피봇 인덱스라고 할때
			// 이 index를 구하라.
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
			// 주어진 입력에 대해 2개의 배열을 출력하되, 각각
			// 첫번째는 nums1에는 나오지만 2에는 안나오는 값들을, 
			// 두번째는 nums2에는 나오지만 1에는 안나오는 값들을 찾아라.
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
			// 주어진 입력 arr의 원소의 출현 빈도가 유일한지 여부를 반환하라. 
			// 즉, [1,2] 는 각 1회씩 출현하였으므로, false가 된다. 
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
			// 두개의 string word1과 word2가 비슷한지 판단하라. 
			// - 문자의 순서를 바꿔서 같은 문자가 되면 비슷하다 할수 있다.
			// - 출현하는 문자가 달라도 빈도수가 같으면 비슷하다 할 수 있다. 
			//
			if (word1.size() != word2.size())
				return false;

			// a. 출현하는 문자 종류는 같아야 한다.
			// b. 빈도수로 정렬했을때 같아야 한다.

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
			// 해당 모든 행의 값들 순서와 해당 모든 열의 순서가 같을때, 이 열과 행을 같다라고 한다.
			// input grid에서 같은 열과 행의 조합의 수를 반환하라.
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
			// 입력문자 s에서 *와 *의 바로 왼쪽 문자를 제거하고 출력하라.
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
			// input array ast에서 각 값은 
			// 운석의 크기를, 부호는 방향을 의미한다. 
			// + right, - left.
			// 서로 만나면 크기가 작은것이 없어진다.(같으면 둘다 사라짐)
			// 방향이 같으면 만나지 않는다.
			// 모두 속도가 같다고 할때, 충돌 이후 결과를 출력하라.
			//
			// ex) [5,10,-5] 
			// => 두번째와 세번째가 만나게 되고, 두번째가 크기가 더 크므로 
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
			// k[string] 꼴의 입력이 들어올때, string을 k번 출력하게 디코딩 하라.
			
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
			// t는 현재 data의 input 시간이라고 할때, 여지껏 data의 (t-3000, t) 구간내의 
			// 데이터 수를 출력하라.
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
			// 리스트의 중앙 노드를 제거하라. 노드수가 짝수라면, 두 노드중 나중 노드를 삭제하라.
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
			// 입력된 list를 홀수끼리 연결하고, 다음 짝수끼리 연결하라. 
			// O(1) extra space에 O(N) TC 가 되도록 하라.
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
			// 주어진 리스트를 뒤집고, 그 head를 반환하라.
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
			// 앞에서부터의 순서가 같은 node와 뒤에서 부터 순서가 같은 노드를 한 pair라고 할때, 
			// 이 pair 중에 그 합의 최대 값을 반환하라.
			// 
			// 중간 부분을 찾는다. 
			// 중간 바로 앞까지 list를 역전 시킨다. 
			// 중간부터 직진, 
			// 역전된 노드를 직진
			// 하면 두 노드가 pair가 된다. 
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
			// 주어진 binary tree의 max depth를 반환하라.
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
			// 두 노드의 leaf를 한쪽 방향으로 읽었을때 같은 길이와 같이면, 리프가 비슷하다고 한다.
			// 두 노드의 리프가 비슷한지 여부를 반환하라.
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
			// root에서 특정 노드 x 까지 과정을 포함한 모든 노드에서 x보다 큰 값이 없으면, good 노드라 한다.
			// 주어진 tree에서 good 노드의 수를 반환하라.
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
			mapFreq[0] = 1;         // 처음부터의 구간합일 경우 고려. 
			for (int q = 0; q < nums.size(); ++q)
			{
				sum += nums[q];
				if (mapFreq.find(sum - target) != mapFreq.end())
					ret += mapFreq[sum - target];

				mapFreq[sum]++;     // 현재 위치 구간합은 검색에서 제외 필요. 따라서 search후에 map에 더한다.
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
			// 주어진 노드 root에서 특정 Path의 합을 구했을때 targetSum과 같아지는 path의 수를 반환하라.
			// 이때 path는 아래 방향으로만 향할 수 있다.
			// 
			// 위 560. 문제를 tree에 가져온 문제일 뿐.
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
			// 주어진 tree 에서 최대 길이의 zig zag 노드수를 구하라.
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
			// 주어진 root노드에서 p와 q에 동시에 부모가 되는 가장 가까운(낮은) 노드를 반환하라.
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
			// root node의 level이 1이라고 할때(이하 차례대로 1씩 증가한다.)
			// 이때, 각 level의 합이 최대인 레벨중 최소 레벨을 반환하라.
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
			// 주어진 Binary Tree(2진 트리)에서 해당 값을 가진 node를 찾아라. 
			//
			if (node == NULL)	return NULL;

			if (node->val < val)	return searchBST(node->right, val);
			if (node->val > val)	return searchBST(node->left, val);
			return node;
		}

		// 450. Delete Node in a BST 
		TreeNode* deleteNode(TreeNode* root, int key)
		{
			// 대상 key를 가진 노드를 찾고 BST가 유지되도록 대상 노드를 삭제 하라.
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
			// 길이가 같은 두개의 배열과 양수 k가 주어질 때, 
			// nums1과 nums2에서 길이 k의 부분열을 취한다. 
			// nums1에서는 부분열의 합을,          => Sum(n1, ...)
			// nums2에서는 부분열의 최소값을 얻고  => Min(n1... )
			// 이를 곱했을때 가능한 최대값을 구하라.
			//

			// 첫 배열의 내림차순 정리를, 
			// 둘째 배열의 오름차순으로 재정리 하고 
			// 로직 재시도.


			// nums1을 정렬하여, 합의 최대를 찾고 상응하는 nums2의 최소값으로 결과를 도출하는 방식.
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
			
			// nums2를 정렬하여, 최소값을 정렬 & 적용하면서 상응하는 nums1의 합으로 결과를 도출 하는 방식.
			
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
			// k수의 worker를 고용한다고 할때, costs는 각 worker의 비용이다.
			// 아래와 같은 규칙으로 worker를 고용한다고 할때, k회의 세션 이후 최종 고용비용을 반환하라.
			// - 총 k 세션을 돌면서 각 세션당 1명씩 고용하며, 고용된 노동자는 리스트에서 제거된다.
			// - 목록의 앞에서 candidates만큼 후보군을 정하고, 뒤로도 해당 후보군을 정한다.
			// - 위 두 후보군 중에 최소비용의 노동자를 고용한다.
			// - 후보군보다 적은 수의 노동자만이 있다면, 그 중에서 최소비용의 노동자를 고용한다.
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
			// spells와 potions의 2개의 array input이 있을때, 원소 각기의 곱이 success 보다 크거나 같으면 성공으로 친다.
			// 이 성공한 spells의 각 원소에 대해 성공의 수를 array로 out 하라.
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
			// 주어진 nums vector에서 주변 값보다 값이 큰 원소를 peak 원소라 한다. 
			// 어떤 peak원소든 찾아서 그 index를 반환하라.
			// 이때 배열의 첫과 끝은 배열 밖의 값보다 크다고 간주한다.
			// TC가 O(logN) 이 되도록 하라. 
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
			// 주어진 piles 배열은 바나나더미를 의미하고, h는 시간이다. 
			// 코코가 주어진 시간에 바나나 더미를 다 먹는 시간당 최소 개수를 찾아라.
			// 이때, 주어진 개수보다 바나나더미의 바나나가 더 많으면, 그 더미만 먹는다.
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
			// input string digit은 2~9까지의 전화번호 숫자의 string이다.
			// 이를 입력할시, 이로 출력가능한 모든 문자 조합을 찾아라.
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
			// 1~9까지의 k개수의 수를 중복 없이 1회씩 사용하여 그 합이 n이 되는 모든 집합을 찾아라.
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
			// 위와 같은 조건일때 주어진 n 에 대한 결과 값을 찾아라.
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
			// 한번에 하나 혹은 두개의 계단을 밟아 나갈 수 있으며, 그때 비용이 cost이다. 
			// top 에 도달하기 위한 최소 비용을 찾아라.
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
			// nums 배열에 접근하되, 인접해서 접근은 불가하다. 얻을 수 있는 최대 값을 구하라.
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
			// mxn의 grid가 있고 robot이 left top에 있다. 
			// 이때 robot은 우측으로 한칸, 혹은 아래로 한칸만 갈수 있다.
			// 이때 right, bottom으로 가는 모든 유일한 경로의 수를 구하라.
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
			// mxn의 grid가 있고 robot이 left top에 있다. 
			// 이때 robot은 우측으로 한칸, 혹은 아래로 한칸만 갈수 있다.
			// 이때 right, bottom으로 가는 모든 유일한 경로의 수를 구하라.
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
			// 두개의 string text1, text2가 주어질때 두 string에서의 가장 긴 공통 sub-string의 길이를 반환하라.
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

			if (boughtIndex < 0)							// 안샀을 때.
			{
				vCache[idxCache] = max(
					maxProfit_dp(vCache, prices, idx + 1, idx, fee),	// 지금 산다.
					maxProfit_dp(vCache, prices, idx + 1, -1, fee));	// 그냥 지나친다.
			}
			else
			{
															// 샀다.
				idxCache += prices.size();
				
				vCache[idxCache] = max(
					prices[idx] - prices[boughtIndex] - fee + 
					maxProfit_dp(vCache, prices, idx + 1, -1, fee),	// 지금 판다.
																	// 그냥 지나친다.
					maxProfit_dp(vCache, prices, idx + 1, boughtIndex, fee));
			}
			return vCache[idxCache];
		}
		int maxProfit(vector<int>& prices, int fee)
		{
			// vector prices를 각 날의 stock의 가격을 의미한다.
			// 사고 팔때 fee를 지불한다면, 
			// 최대 이익을 구하라.
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
			// word1과 word2 두개의 string이 주어질때 word1을 word2로 바꾸기 위한 
			// 최소의 연산 수를 구하라.
			// 연산은 문자를 넣거나, 빼거나, 교체할 수 있다.
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
			// 주어진 input은 2개의 interval을 의미한다.
			// 겹치지 않게 하기위해 최소한의 input을 제거한다면
			// 몇개를 제거할수 있겠는가.
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
			// 주어진 배열은 풍선의 2차원 좌표를 의미한다. 
			// 모든 풍선을 떠뜨리기 위한 최소의 화살수를 찾아라.
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
				// 공통으로 터뜨릴수 있는 풍선이면, 더 작은 끝으로 갱신. 
				// arrow 감소.
				if (lastEnd >= points[k][0])
				{
					--cntArrow;
					lastEnd = min(lastEnd, points[k][1]);
				}
				// 공통으로 터뜨릴수 없으면 정리하고, 끝을 update.
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
			// 주어진 input array가 각 날짜의 온도 라고 할때, 
			// 각 날에서 더 따뜻한 날이 되기까지 며칠을 기다려야 하는지
			// 출력하라.
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
			// 0 index 방을 제외하고 각 vector안의 index의 방에만 접근 할 수 있다. 
			// 모든 방에 접근 가능한지 여부를 반환하라.
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
			// 주어진 vector는 각 노드들의 연결 여부를 의미한다.
			// 이때 서로 연결되지 않는 덩어리의 수를 구하라.
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

			// 양방향 데이터 구성. - 뒤집힌 곳 정보 기록 필요
			for (int k = 0; k < connections.size(); ++k)
			{
				vLink[connections[k][0]].push_back(make_pair(connections[k][1], true));
				vLink[connections[k][1]].push_back(make_pair(connections[k][0], false));
			}

			 // 0 기준으로 BFS하면서 뒤집힌 곳 reverse하서 count
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
			// 주어진 input equations은 수식, values는 eq1 / eq2 를 의미한다고 할때
			// queries에 대한 결과를 구하라.
			//
			// 각 셈을 노드라고 생각하면, 
			// 정방향 진행은 주어진 경로값의 곱이 되고, 
			// 역방향 진행은 주어진 경로값으로 나누면 됨을 알 수 있다. 
			// 논리대로 진행 해 본다. 
			//
			// 검색을 위해 출발 노드 기준으로 data 재정리.
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
			// 주어진 배열 maze에서 . 는 빈 공간을, + 는 벽을 의미한다.
			// 외부 경계에 있는 빈 공간을 exit이라고 정의하며, 입구는 exit에서 제외한다.
			// 입구에서 exit에 도달하기 위한 최소 경로 이동 수를 반환하라.
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
			// 주어진 grid의 0 은 빈칸, 1은 fresh 오렌지, 2는 rotten 오렌지를 말한다.
			// 분당 rotten한 오렌지가 근처의 fresh한 오렌지를 rotten하게 할 수 있다면, 
			// 모든 오렌지를 rotten하게 만들 수 있는 시간을 찾아라.
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
			// search word를 입력함에 따라 products의 목록중에서 최대 3개의 제시어를 보여주도록 
			// 함수를 디자인 하라.
			// 이때 string은 lexicographically 하게 sort 하라.

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
			// n이 주어질때, 0 ~ n 까지의 수를 2진수로 변환하여 그 1의 개수를 vector로 출력하라.
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
			// 주어진 배열 nums에서 모든 요소는 각 2번씩 나오되, 단 하나가 1번만 나온다. 
			// 1번만 나오는 값을 찾아라.
			// 이때 O(N)의 TC에 추가 메모리를 사용하지 말아라.
			//
			int ret = nums[0];
			for (int q = 1; q < nums.size(); ++q)
				ret = ret ^ nums[q];

			return ret;
		}

		// 1318. Minimum Flips to Make a OR b Equal to c
		int minFlips(int a, int b, int c)
		{
			// a or b 를 해서 c가 되게 하려면 
			// 바꿔야 할 a와 b의 총 수의 최소값을 구하라.
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