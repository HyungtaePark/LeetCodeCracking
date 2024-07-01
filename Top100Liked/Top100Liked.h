#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <stack>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <concurrent_priority_queue.h>
#include <algorithm>

using namespace std;

namespace Top100Liked
{
	class BackTracking
	{
	public:

		// 22. Generate Parentheses
		void build_Parenthesis(vector<string>& vRet, string& strCombi, int n, int cntOpen, int cntClose)
		{
			if (strCombi.size() == n * 2)
			{
				if (cntOpen != cntClose)	return;

				string strOk = strCombi;
				vRet.push_back(strOk);
				cout << strCombi << endl;
				return;
			}

			strCombi += "(";
			build_Parenthesis(vRet, strCombi, n, cntOpen + 1, cntClose);
			strCombi.erase(strCombi.size()-1, 1);
			
			if (cntOpen > cntClose)
			{
				strCombi += ")";
				build_Parenthesis(vRet, strCombi, n, cntOpen, cntClose + 1);
				strCombi.erase(strCombi.size() - 1, 1);
			}
		}
		vector<string> generateParenthesis(int n)
		{
			// 주어진 n의 수 만큼 '()' 쌍이 규칙에 맞게 구성하라. 
			// 
			vector<string> vRet;
			string strCurrent = "(";
			build_Parenthesis(vRet, strCurrent, n, 1, 0);
			return vRet;
		}

		// 39. Combination Sum
		void combinationSum_BT(vector<vector<int>>& vRet, vector<int>& candidates, int target, vector<int>& cur, int idxStart)
		{
			int sum = 0;
			for (int q = 0; q < cur.size(); ++q)
			{
				sum += cur[q];
			}
			if (sum >= target)
			{
				if (sum == target)
					vRet.push_back(cur);
				return;
			}

			for (int k = idxStart; k < candidates.size(); ++k)
			{
				cur.push_back(candidates[k]);
				combinationSum_BT(vRet, candidates, target, cur, k);
				cur.pop_back();
			}
		}
		vector<vector<int>> combinationSum(vector<int>& candidates, int target)
		{
			// cadidates와 target이 주어질때, 그 합이 target이 되는 cadidates의 유일한 조합들을 찾아라.
			//
			vector<vector<int>> vRet;
			vector<int> cur;
			combinationSum_BT(vRet, candidates, target, cur, 0);
			return vRet;
		}

		// 46. Permutations
		void permute_BT(vector<vector<int>>& vRet, vector<int>& nums, unordered_set<int>& sCur)
		{
			if (sCur.size() == nums.size())
			{
				vector<int> temp;
				unordered_set<int>::iterator it = sCur.begin();
				for (; it != sCur.end(); ++it)
					temp.push_back( nums[*it] );
				vRet.push_back(temp);
				return;
			}

			for (int k = 0; k < nums.size(); ++k)
			{
				if (sCur.find(k) != sCur.end())
					continue;
				sCur.insert(k);
				permute_BT(vRet, nums, sCur);
				sCur.erase(k);
			}
		}
		
		void permute_swap(vector<int>& nums, int i, int j)
		{
			int t = nums[i];
			nums[i] = nums[j];
			nums[j] = t;
		}
		void permute_SwapBT(vector<vector<int>> vRet, vector<int>& nums, int idx)
		{
			if (idx + 1 >= nums.size())
			{
				vRet.push_back(nums);
				return;
			}

			for (int k = idx+1; k < nums.size(); ++k)
			{
				permute_swap(nums, k, idx);
				permute_SwapBT(vRet, nums, k);
				permute_swap(nums, k, idx);
			}
		}
		vector<vector<int>> permute(vector<int>& nums)
		{
			// 주어진 nums 배열로 만들 수 있는 모든 조합을 찾아라.
			//
			vector<vector<int>> vRet;
			unordered_set<int> sCur;
			//permute_BT(vRet, nums, sCur);
			permute_SwapBT(vRet, nums, 0);
			return vRet;
		}


		// 51. N-Queens
		void print_Queen(string& strCur, int n)
		{
			for (int y = 0; y < n; ++y)
			{
				cout << strCur.substr(y * n, n) << endl;
			}
			cout << endl;
		}
		bool IsValid_NQueens(string& strCur, int n)
		{
			//int idx = strCur.size();
			//int ix = idx % n;
			//int iy = idx / n;

			// x axis
			for (int y = 0; y < n; ++y)
			{
				bool hasQ = false;
				for (int x = 0; x < n; ++x)
				{
					int index = y * n + x;
					if (strCur[index] == 'Q')
					{
						if (hasQ)
						{
							//print_Queen(strCur, n);
							return false;
						}
						hasQ = true;
					}
				}
			}
			// y axis
			for (int x = 0; x < n; ++x)
			{
				bool hasQ = false;
				for (int y = 0; y < n; ++y)
				{
					int index = y * n + x;
					if (strCur[index] == 'Q')
					{
						if (hasQ)
						{
							//print_Queen(strCur, n);
							return false;
						}
						hasQ = true;
					}
				}
			}
			// dec
			for (int x = 0; x < n; ++x)
			{
				bool hasQ = false;
				int ix = x;
				for (int y = 0; y<n && ix<n; ++y, ++ix)
				{
					int index = y * n + ix;
					if (strCur[index] == 'Q')
					{
						if (hasQ)
						{
							//print_Queen(strCur, n);
							return false;
						}
						hasQ = true;
					}
				}
			}
			for (int y = 0; y < n; ++y)
			{
				bool hasQ = false;
				int iy = y;
				for (int x = 0; x<n && iy<n ; ++x, ++iy)
				{
					int index = iy * n + x;
					if (strCur[index] == 'Q')
					{
						if (hasQ)
						{
							//print_Queen(strCur, n);
							return false;
						}
						hasQ = true;
					}
				}
			}

			// inc
			for (int x = 0; x < n; ++x)
			{
				bool hasQ = false;
				int ix = x;
				for (int y = n-1; y>=0 && ix<n ; --y, ++ix)
				{
					int index = y * n + ix;
					if (strCur[index] == 'Q')
					{
						if (hasQ)
						{
							//print_Queen(strCur, n);
							return false;
						}
						hasQ = true;
					}
				}
			}
			for (int y = n-1; y >= 0; --y)
			{
				bool hasQ = false;
				int iy = y;
				for (int x = 0; x<n && iy>=0 ; ++x, --iy)
				{
					int index = iy * n + x;
					if (strCur[index] == 'Q')
					{
						if (hasQ)
						{
							//print_Queen(strCur, n);
							return false;
						}
						hasQ = true;
					}
				}
			}

			return true;
		}
		void NQueens_BT(vector<vector<string>>& vRet, string& strCur, int n, int cntQ)
		{
			if (strCur.size() >= n*n)
			{
				if (cntQ == n && IsValid_NQueens(strCur, n))
				{
					vector<string> vBuff;
					for (int q = 0; q < n; ++q)
					{
						string strTemp = strCur;
						strTemp = strTemp.substr(n * q, n);
						vBuff.push_back(strTemp);
						//cout << strTemp << endl;
					}
					vRet.push_back(vBuff);
					//cout << endl;
				}
				return;
			}

			strCur += ".";
			NQueens_BT(vRet, strCur, n, cntQ);
			strCur.erase(strCur.size() - 1, 1);

			//if (CanPlaceQ_NQueens(strCur, n))
			{
				strCur += "Q";
				NQueens_BT(vRet, strCur, n, cntQ+1);
				strCur.erase(strCur.size() - 1, 1);
			}
		}
		vector<vector<string>> solveNQueens(int n)
		{
			// n x x 타일이 주어진다고 할때, queen n개를 서로 공격할 수 없는 포지션에 배치하는 
			// 모든 경우를 찾아라.
			//
			vector<vector<string>> vRet;
			string strNow = "";
			NQueens_BT(vRet, strNow, n, 0);
			return vRet;
		}


		// 78. Subsets.
		void subsets_BT(vector<vector<int>>& vOut, vector<int>& nums, vector<int>& vCur, int idx)
		{
			vOut.push_back(vCur);
			if (idx >= nums.size())
				return;
			
			for (int q = idx; q < nums.size(); ++q)
			{
				vCur.push_back(nums[q]);
				subsets_BT(vOut, nums, vCur, q + 1);
				vCur.pop_back();
			}
		}
		vector<vector<int>> subsets(vector<int>& nums)
		{
			// nums 배열이 주어질때 가능한 모든 조합을 찾아라.
			//
			vector<vector<int>> vOut;
			vector<int> vCur;
			subsets_BT(vOut, nums, vCur, 0);
			return vOut;
		}

		// 79. Word Search
		bool exist_DP(vector<vector<char>>& board, string word, int x, int y, vector<bool>& vVisit, int cntHit)
		{
			if (cntHit >= word.size())
				return true;

			int height = board.size();
			int width = board[0].size();
			int idx = y * width + x;

			int wordIdx = cntHit;

			// left 
			if (x > 0 && !vVisit[idx - 1] && board[y][x - 1] == word[wordIdx])
			{
				vVisit[idx - 1] = true;
				if (exist_DP(board, word, x - 1, y, vVisit, cntHit+1))
					return true;
				vVisit[idx - 1] = false;
			}
			// right
			if (x < width-1 && !vVisit[idx + 1] && board[y][x + 1] == word[wordIdx])
			{
				vVisit[idx + 1] = true;
				if (exist_DP(board, word, x + 1, y, vVisit, cntHit + 1))
					return true;
				vVisit[idx + 1] = false;
			}

			// up 
			if (y > 0 && !vVisit[idx - width] && board[y-1][x] == word[wordIdx])
			{
				vVisit[idx - width] = true;
				if (exist_DP(board, word, x, y-1, vVisit, cntHit + 1))
					return true;
				vVisit[idx - width] = false;
			}

			// down
			if (y < height-1 && !vVisit[idx + width] && board[y + 1][x] == word[wordIdx])
			{
				vVisit[idx + width] = true;
				if (exist_DP(board, word, x, y + 1, vVisit, cntHit + 1))
					return true;
				vVisit[idx + width] = false;
			}

			return false;
		}
		bool exist(vector<vector<char>>& board, string word)
		{
			int height = board.size();
			int width = board[0].size();

			vector<bool> vVisit;
			vVisit.resize(width*height, false);

			for (int y = 0; y < height; ++y)
			{
				for (int x = 0; x < width; ++x)
				{
					if (board[y][x] != word[0])
						continue;

					vVisit[y * width + x] = true;
					if (exist_DP(board, word, x, y, vVisit, 1))
						return true;
					vVisit[y * width + x] = false;
				}
			}
			return false;
		}

		// 131. Palindrome Partitioning
		bool isPalindrome(string& strInput)
		{
			for (int k = 0; k <= strInput.size() / 2; ++k)
			{
				if (strInput[k] != strInput[strInput.size() - k - 1])
					return false;
			}
			return true;
		}
		void partition_BT(vector<vector<string>>& vOut, string& s, vector<string>& vCur, int idx)
		{
			if (idx >= s.size())
			{
				vOut.push_back(vCur);
				for (int q = 0; q < vCur.size(); ++q)
					cout << vCur[q] << endl;
				cout << endl;
				return;
			}

			for (int k = 1; k <= s.size()-idx; ++k)
			{
				string built = s.substr(idx, k);
				if (isPalindrome(built))
				{
					vCur.push_back(built);
					partition_BT(vOut, s, vCur, idx+k);
					vCur.pop_back();
				}
			}
		}
		vector<vector<string>> partition(string s)
		{
			// s를 분할하여 그 substring을 찾되, 결과가 palindrome(앞으로 읽어도 뒤로 읽어도 같은) 것을 찾아라.
			//
			vector<vector<string>> vOut;
			vector<string> vCur;
			partition_BT(vOut, s, vCur, 0);
			return vOut;
		}
	};

	class BinarySearch
	{
		struct TreeNode {
			int val;
			TreeNode* left;
			TreeNode* right;
			TreeNode() : val(0), left(nullptr), right(nullptr) {}
			TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
			TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
		};
		
	public:
		// 4. Median of Two Sorted Arrays
		double median_bs(vector<int>& nums1, vector<int>& nums2, int left, int right)
		{
			int num1Partition = left>=right ? left : 1 + (left + (right - left) / 2);// : nums1.size();
			int num2Partition = (nums1.size() + nums2.size()) / 2 - num1Partition;

			int idxNum1L = num1Partition - 1;
			int idxNum1R = num1Partition;
			int idxNum2L = num2Partition - 1;
			int idxNum2R = num2Partition;

			int N1Left  = idxNum1L >= 0 && idxNum1L < nums1.size() ? nums1[idxNum1L] : INT_MIN;
			int N1Right = idxNum1R >= 0 && idxNum1R < nums1.size() ? nums1[idxNum1R] : INT_MAX;
			int N2Left  = idxNum2L >= 0 && idxNum2L < nums2.size() ? nums2[idxNum2L] : INT_MIN;
			int N2Right = idxNum2R >= 0 && idxNum2R < nums2.size() ? nums2[idxNum2R] : INT_MAX;

			if (N1Left <= N2Right && N2Left <= N1Right)
			{
				if ((nums1.size() + nums2.size()) % 2 == 0)
					return (max(N1Left, N2Left) + min(N1Right, N2Right)) / 2.0;
				else
					return min(N1Right, N2Right);
			}
			else if (N1Left > N2Right)
				return median_bs(nums1, nums2, left, num1Partition - 1);
			
			else
				return median_bs(nums1, nums2, num1Partition+1, right);
		}
		double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2)
		{
			// 정렬된 배열 nums1과 nums2가 주어질때, 두 배열의 중간값을 구하라.
			// 이때 TC가 O(log(m+n)) 이 되도록 하라.
			//
			/*
			// 전체 값의 중간 값을 찾아본다. - 이는 아닌 듯 하다.
			double ret = 0;
			for (int k = 0; k < nums1.size(); ++k)
				ret += nums1[k];
			for (int k = 0; k < nums2.size(); ++k)
				ret += nums2[k];

			ret = ret / (nums1.size() + nums2.size());
			return ret;*/

			// 중간 '위치' 값을 찾아본다.
			/*vector<int> vRet;
			int idx1 = 0, idx2 = 0;
			for (int k = 0; k < nums1.size() + nums2.size(); ++k)
			{
				if (idx1 >= nums1.size() || idx2 >= nums2.size())
				{
					if (idx1 >= nums1.size())
						vRet.push_back(nums2[idx2++]);
					else
						vRet.push_back(nums1[idx1++]);
				}
				else
				{
					if (nums1[idx1] < nums2[idx2])
						vRet.push_back(nums1[idx1++]);
					else
						vRet.push_back(nums2[idx2++]);
				}
			}
			int mid = vRet.size() / 2;
			if (vRet.size()<=1 || vRet.size()%2==1)
				return vRet[mid];
			else
				return ( ((double)(vRet[mid - 1] + vRet[mid])) / 2.0);
			*/

			//if(nums1.size() >= nums2.size())
				return median_bs(nums1, nums2, 0, nums1.size() - 1);
			//else 
			//	return median_bs(nums2, nums1, 0, nums2.size() - 1);
		}


		// 33. Search in Rotated Sorted Array
		int searchRotated_bs(vector<int>& nums, int target, int left, int right)
		{
			if (left > right)	return -1;

			int mid = left + (right - left) / 2;

			int leftV = nums[left];
			int rightV = nums[right];
			int midV = nums[mid];

			if (midV == target)	return mid;

			if (leftV <= midV && midV <= rightV)
				return target < midV ? searchRotated_bs(nums, target, left, mid - 1) : searchRotated_bs(nums, target, mid + 1, right);
			else if (leftV >= midV && midV <= rightV)
				return target > midV && target <= rightV ? searchRotated_bs(nums, target, mid + 1, right) : searchRotated_bs(nums, target, left, mid - 1);
			else if (leftV <= midV && midV >= rightV)
				return target>=leftV && target<midV ? searchRotated_bs(nums, target, left, mid - 1) : searchRotated_bs(nums, target, mid + 1, right);
			else 
				return -1;
		}
		int search(vector<int>& nums, int target)
		{
			// 오름차순 정렬이 rotated 되어있는 nums 배열에 target이 있을 경우, 그 index를 찾아라.
			// 없으면 -1을 반환하라.
			//
			return searchRotated_bs(nums, target, 0, nums.size() - 1);
		}

		// 34. Find First and Last Position of Element in Sorted Array
		int searchRangeBS_Start(vector<int>& nums, int target, int left, int right)
		{
			if (left > right)	return -1;

			int mid = left + (right - left) / 2;

			if (nums[mid] < target)
				return searchRangeBS_Start(nums, target, mid + 1, right);
			else if (nums[mid] > target)
				return searchRangeBS_Start(nums, target, left, mid - 1);
			else
			{
				if (mid > left && nums[mid - 1] == nums[mid])
					return searchRangeBS_Start(nums, target, left, mid - 1);
				else
					return mid;
			}
		}
		int searchRangeBS_End(vector<int>& nums, int target, int left, int right)
		{
			if (left > right)	return -1;

			int mid = left + (right - left) / 2;

			if (nums[mid] < target)
				return searchRangeBS_End(nums, target, mid + 1, right);
			else if (nums[mid] > target)
				return searchRangeBS_End(nums, target, left, mid - 1);
			else
			{
				if (mid==right || (mid<right && nums[mid + 1] != nums[mid]))
					return mid;
				else
					return searchRangeBS_End(nums, target, mid + 1, right);
			}
		}
		vector<int> searchRange(vector<int>& nums, int target)
		{
			// 중복된 값이 있는 오름차순 정렬배열 nums가 있을때, 그 값중 target이 존재하면
			// 그 시작 위치와 끝 위치를 찾아라. 
			// 없다면 -1을 반환하라.
			//
			vector<int> vOut;
			vOut.resize(2, -1);
			vOut[0] = searchRangeBS_Start(nums, target, 0, nums.size() - 1);
			vOut[1] = searchRangeBS_End(nums, target, 0, nums.size() - 1);
			return vOut;
		}

		int searchCol(vector<vector<int>>& matrix, int target, int left, int right)
		{
			if (left > right) return clamp(right, 0, (int)matrix.size()-1);

			int mid = left + (right - left) / 2;

			if (matrix[mid][0] == target) return mid;
			else if (matrix[mid][0] > target) return searchCol(matrix, target, left, mid - 1);
			else return searchCol(matrix, target, mid + 1, right);
		}
		int searchValue(vector<int>& nums, int target, int left, int right)
		{
			if (left > right) return -1;

			int mid = left + (right - left) / 2;

			if (nums[mid] == target) return mid;
			else if (nums[mid] > target) return searchValue(nums, target, left, mid - 1);
			else return searchValue(nums, target, mid + 1, right);
		}
		bool searchMatrix(vector<vector<int>>& matrix, int target)
		{
			int col = searchCol(matrix, target, 0, matrix.size() - 1);
			return searchValue(matrix[col], target, 0, matrix[col].size() - 1) != -1;
		}

		// 124. Binary Tree Maximum Path Sum
		int maxPathSumBS(TreeNode* node, int& maxSum)
		{
			if (node == NULL)	return 0;

			int leftMax = 0;
			int rightMax = 0;
			
			if (node->left != NULL)
				leftMax = max(leftMax, maxPathSumBS(node->left, maxSum));
			if(node->right != NULL)
				rightMax = max(rightMax, maxPathSumBS(node->right, maxSum));
			
			maxSum = max(maxSum, leftMax + rightMax + node->val);
			
			return leftMax>rightMax ? leftMax+node->val : rightMax + node->val;

		}
		int maxPathSum(TreeNode* root)
		{
			int maxSum = INT_MIN;
			maxPathSumBS(root, maxSum);
			return maxSum;
		}

		// 153. Find Minumum in Rotated Sorted Array.
		int findMid_BS(vector<int>& nums, int left, int right)
		{
			if (left > right) return -1;
			int mid = left + (right - left) / 2;

			// 1, 2, 3, 4, 5
			if (nums[left] <= nums[mid] && nums[mid] <= nums[right])
				return nums[left];
			
			// 4, 5, 1, 2, 3
			if (nums[left] >= nums[mid] && nums[right] >= nums[mid])
			{
				// 5, 1, 2, 3, 4 
				if (mid > 0 && nums[mid - 1] < nums[mid])
					return findMid_BS(nums, left, mid - 1);

				return nums[mid];
			}

			// 2, 3, 4, 5, 1
			if (nums[left] >= nums[right] && nums[mid] >= nums[right])
			{
				// 3, 4, 5, 1, 2
				if (right<nums.size() - 1 && nums[right - 1]>nums[right])
					return findMid_BS(nums, mid + 1, right);

				return nums[right];
			}
			return -1;
		}
		int findMin(vector<int>& nums)
		{
			return findMid_BS(nums, 0, nums.size() - 1);
		}
	};

	class BinaryTree
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

	public:
		// 94. Binary Tree Inorder Traversal
		void inorderTraverseBT(vector<int>& vOut, TreeNode* node)
		{
			if (node == NULL)	return;

			inorderTraverseBT(vOut, node->left);
			vOut.push_back(node->val);
			inorderTraverseBT(vOut, node->right);
		}
		vector<int> inorderTraversal(TreeNode* root)
		{
			// tree를 inorder로 traverse 하고 그 값을 반환하라.
			vector<int> vRet;
			inorderTraverseBT(vRet, root);
			return vRet;
		}

		// 98. Validate Binary Search Tree
		int getLeftLeaf_BT(TreeNode* node)
		{
			return node->left == NULL ? node->val : getLeftLeaf_BT(node->left);
		}
		int getRightLeaf_BT(TreeNode* node)
		{
			return node->right == NULL ? node->val : getRightLeaf_BT(node->right);
		}
		bool isValidBST_BT(TreeNode* node)
		{
			if (node == NULL)	return true;

			if (node->left != NULL)
			{
				if (getRightLeaf_BT(node->left) > node->val)	return false;
			}
			if (node->right != NULL)
			{
				if (getLeftLeaf_BT(node->right) < node->val)	return false;
			}
			return true;
		}
		bool isValidBST(TreeNode* root)
		{
			return isValidBST_BT(root);
		}

		// 101. Symmetric Tree
		bool isSymmetric(TreeNode* root)
		{
			// root를 기준으로 mirror되는 tree인지 확인하라. 
			//
			queue<TreeNode*> qBuff;
			qBuff.push(root);

			while (!qBuff.empty())
			{
				int size = qBuff.size();
				vector<TreeNode*> vNodes;
				for (int q = 0; q < size; ++q)
				{
					TreeNode* node = qBuff.front(); 
					qBuff.pop();
					vNodes.push_back(node);
					if (node != NULL)
					{
						qBuff.push(node->left);
						qBuff.push(node->right);
					}
				}

				for (int q = 0; q < vNodes.size() / 2; ++q)
				{
					TreeNode* nodeA = vNodes[q];
					TreeNode* nodeB = vNodes[vNodes.size()-q-1];
					
					if ((nodeA == NULL || nodeB==NULL) && nodeA != nodeB)
						return false;
					if (nodeA->val != nodeB->val)
						return false;
				}
			}
			return true;
		}

		// 104. Maximum Depth of Binry Tree
		int maxDepth_BT(TreeNode* node, int maxDepth)
		{
			if (node == NULL)	
				return maxDepth;

			int maxL = INT_MIN, maxR = INT_MIN;
			if(node->left != NULL)
				maxL = maxDepth_BT(node->left, maxDepth + 1);
			if (node->right != NULL)
				maxR = maxDepth_BT(node->right, maxDepth + 1);

			return max(maxL, maxR);
		}
		int maxDepth(TreeNode* root)
		{
			int maxDepth = 0;
			maxDepth_BT(root, maxDepth);
			return maxDepth;
		}

		// 105. Contruct Binary Tree from Preorder and Inorder Traversal 
		TreeNode* buildTree_BT(vector<int>& preorder, map<int, int>& mapInorder, int& idx, int left, int right)
		{
			if (left > right)	return NULL;
			++idx;
			if (idx < 0 || idx >= preorder.size())
			{
				--idx;
				return NULL;
			}

			int value = preorder[idx];
			int mid = mapInorder[value];

			TreeNode* node = new TreeNode(value);
			node->left = buildTree_BT(preorder, mapInorder, idx, left, mid-1);
			node->right = buildTree_BT(preorder, mapInorder, idx, mid+1, right);
			return node;
		}
		TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder)
		{
			map<int, int> mapInorder;
			for (int q = 0; q < inorder.size(); ++q)
				mapInorder[inorder[q]] = q;

			int idx = 0;
			TreeNode* root = buildTree_BT(preorder, mapInorder, idx, 0, mapInorder.size()-1);
			return root;
		}

		// 114. Flatten Binary Tree to Linked List
		TreeNode* build_flatten(vector<TreeNode*>& vNodes, int& idx)
		{
			if (idx >= vNodes.size())
				return NULL;

			TreeNode* node = vNodes[idx++];
			node->left = NULL;
			node->right = build_flatten(vNodes, idx);
			return node;
		}
		void flatten_preorder(TreeNode* node, vector<TreeNode*>& vNodes)
		{
			if (node == NULL)	return;
			vNodes.push_back(node);
			if (node->left != NULL)		flatten_preorder(node->left, vNodes);
			if (node->right != NULL)	flatten_preorder(node->right, vNodes);
		}
		void flatten(TreeNode* root)
		{
			vector<TreeNode*> vNodes;
			flatten_preorder(root, vNodes);

			int idx = 0;
			build_flatten(vNodes, idx);
		}

		// 543. Diameter of Binary Tree
		int maxDOBT(TreeNode* node, int len)
		{
			if (node == NULL)	return len;

			++len;
			int left = maxDOBT(node->left, len);
			int right = maxDOBT(node->right, len);

			return max(left, right);
		}
		void maxDOBT_BFS(TreeNode* node, int& ret)
		{
			if (node == NULL)	return;

			int l = maxDOBT(node->left, 1);
			int r = maxDOBT(node->right, 1);

			ret = max(ret, l + r - 1);
			
			maxDOBT_BFS(node->left, ret);
			maxDOBT_BFS(node->right, ret);
		}
		int diameterOfBinaryTree(TreeNode* root)
		{
			// Tree에서 가장 긴 경로의 길이를 구하라. 
			int ret = 0;
			maxDOBT_BFS(root, ret);
			return ret;
		}
	};

	class DynamicProgramming
	{
	public:
		string longestPalindrome_helper(string& s, int left, int right)
		{
			string subPal = "";
			if (left < 0 || right >= s.size())
				return subPal;

			while (true)
			{
				if (left < 0 || right >= s.size() || s.at(left) != s.at(right))
				{
					++left; --right;
					subPal = s.substr(left, right - left + 1);
					break;
				}
				++right;
				--left;
			}
			return subPal;
		}

		// 5. Longest Palindromic Substring
		string longestPalindrome(string s)
		{
			string maxPal = "";
			for (int k = 0; k < s.size(); ++k)
			{
				string evenPal = longestPalindrome_helper(s, k, k + 1);
				string oddPal = longestPalindrome_helper(s, k, k);
				string longerPal = evenPal.size() > oddPal.size() ? evenPal : oddPal;
				maxPal = maxPal.size() > longerPal.size() ? maxPal : longerPal;
			}
			return maxPal;
		}

		// 32. Longest Valid Parentheses
		int longestValidParentheses(string s)
		{
			int maxLen = 0;
			stack<int> qBuff;
			qBuff.push(-1);
			for (int k = 0; k < s.size(); ++k)
			{
				if (s[k] == '(')		qBuff.push(k);
				else
				{
					qBuff.pop();
					if (qBuff.empty())
						qBuff.push(k);
					else
						maxLen = max(maxLen, k - qBuff.top());
				}

			}
			return maxLen;
		}

		// 72. Edit Distance
		int minD_helper(string& word1, string& word2, int idx1, int idx2)
		{
			if (idx1 >= word1.size())	
				return word2.size() - idx2;
			if (idx2 >= word2.size())	
				return word1.size() - idx1;

			if(word1[idx1] == word2[idx2])
				return minD_helper(word1, word2, idx1 + 1, idx2 + 1);

			int ins = 1 + minD_helper(word1, word2, idx1,     idx2 + 1);
			int del = 1 + minD_helper(word1, word2, idx1 + 1, idx2);
			int rep = 1 + minD_helper(word1, word2, idx1 + 1, idx2 + 1);

			del = min(ins, del);
			return min(rep, del);
		}
		int minDistance(string word1, string word2)
		{
			return minD_helper(word1, word2, 0, 0);
		}

		// 118. Pascal's Triangle
		vector<vector<int>> generate(int numRows)
		{
			vector<vector<int>> vRet;
			vRet.push_back({ 1 });

			for (int q = 1; q < numRows; ++q)
			{
				vector<int> line;
				for (int x = 0; x < q + 1; ++x)
				{
					if (x == 0 || x == q)
						line.push_back(1);
					else
						line.push_back(vRet[q - 1][x - 1] + vRet[q - 1][x]);
				}
				vRet.push_back(line);
			}
			return vRet;
		}

		// 139. Word Break
		bool wordBreak_dp(string s, vector<string>& wordDict)
		{
			bool bRet = false;
			for (int q = 0; q < wordDict.size(); ++q)
			{
				if (s.size() < wordDict[q].size())
					continue;

				string subStr = s.substr(0, wordDict[q].size());
				if (subStr == wordDict[q])
				{
					if (wordBreak_dp(s.substr(subStr.size()), wordDict))
						return true;
				}
			}
			return bRet;
		}
		bool wordBreak(string s, vector<string>& wordDict)
		{
			// 주어진 s를 wordDict에 있는 단어를 이용하여 분할 할수 있는지 여부를 반환하라. 
			// 이때 분할된 단어는 여러번 사용될 수 있다.
			//
			return wordBreak_dp(s, wordDict);
		}

		// 279. Perfect Squares
		int numSquaresdp(int n, vector<int>& vCache)
		{
			if (n == 0)	return 0;

			if (vCache[n - 1] >= 0)
				return vCache[n - 1];

			int minV = INT_MAX;
			for (int q = 1; q <= n ; ++q)
			{
				if (n - (q * q) < 0)	break;
				minV = min(minV, 1 + numSquaresdp(n-(q*q), vCache));
			}
			return vCache[n-1] = minV;
		}
		int numSquares(int n)
		{
			vector<int> vCache;
			vCache.resize(n, -1);
			return numSquaresdp(n, vCache);
		}

	};

	class Graph
	{
	public:
		// 207. Course Schedule
		bool canFinish_help(vector<vector<int>>& vCache, vector<bool>& vVisit, int idx)
		{
			for (int q = 0; q < vCache[idx].size(); ++q)
			{
				int nextIdx = vCache[idx][q];
				if (vVisit[nextIdx])		return false;

				vVisit[nextIdx] = true;
				canFinish_help(vCache, vVisit, nextIdx);
				vVisit[nextIdx] = false;
			}
			return true;
		}
		bool canFinish(int numCourses, vector<vector<int>>& prerequisites)
		{
			vector<vector<int>> vCache(numCourses, vector<int>());
			for (int q = 0; q < prerequisites.size(); ++q)
				vCache[prerequisites[q][0]].push_back(prerequisites[q][1]);

			for (int q = 0; q < prerequisites.size(); ++q)
			{
				vector<bool> vVisit(numCourses, false);
				if (!canFinish_help(vCache, vVisit, prerequisites[q][0]))
					return false;
			}
			return true;
		}

		// 994. 
		int orange_bfs(vector<bool>& vVisit, vector<vector<int>>& grid, queue<int>& qBuff)
		{
			int h = grid.size();
			int w = grid[0].size();

			int min = 0;
			while (!qBuff.empty())
			{
				int cnt = qBuff.size();

				for (int q = 0; q < cnt; ++q)
				{
					int idx = qBuff.front();
					qBuff.pop();
					if (vVisit[idx]) continue;
					vVisit[idx] = true;

					int iX = idx % w;
					int iY = idx / w;
					grid[iY][iX] = 2;

					// up
					if (iY > 0 && grid[iY - 1][iX] == 1)   qBuff.push(idx - w);
					// down
					if (iY < h - 1 && grid[iY + 1][iX] == 1) qBuff.push(idx + w);
					// left
					if (iX > 0 && grid[iY][iX - 1] == 1)    qBuff.push(idx - 1);
					// right
					if (iX < w - 1 && grid[iY][iX + 1] == 1)  qBuff.push(idx + 1);
				}
				++min;
			}
			return min - 1;
		}

		int orangesRotting(vector<vector<int>>& grid)
		{
			int h = grid.size();
			int w = grid[0].size();

			queue<int> qBuff;
			
			for (int y = 0; y < h; ++y)
			{
				for (int x = 0; x < w; ++x)
				{
					if (grid[y][x] == 2)
						qBuff.push(y * w + x);
				}
			}

			vector<bool> vVisit(w * h, false);
			int ret = orange_bfs(vVisit, grid, qBuff);
			
			// check if all is rotten.
			for (int y = 0; y < h; ++y)
			{
				for (int x = 0; x < w; ++x)
				{
					if (grid[y][x] == 1) return -1;
				}
			}
			return ret;
		}
	};

	void Run()
	{
		//BackTracking btSolver;
		//btSolver.generateParenthesis(6);
		//btSolver.solveNQueens(4);
		//vector<int> nums = { 1, 2, 3 };
		//btSolver.subsets(nums);

		//vector<vector<char>> board = { {'A','B','C','E'},{'S','F','C','S'},{'A','D','E','E'} };
		//cout << btSolver.exist(board, "SEE");

		//btSolver.partition("a");

		//BinarySearch bsSolver;
		vector<int> vNum1 = { 1, 3 };// , 5, 6, 7, 0, 1, 2
	//};
		//vector<int> vNum2 = { 1, 2, 3, 4, 5 };
		//cout << bsSolver.findMedianSortedArrays(vNum1, vNum2);
		//cout << bsSolver.search(vNum1, 3);

		//vector<vector<int>> nums = { {1} };// 5, 7, 7, 8, 8, 10
		//bsSolver.searchMatrix(nums, 0);

		BinaryTree btSolver;
		BinaryTree::TreeNode nodeL(1, NULL, NULL);
		BinaryTree::TreeNode nodeR(3, NULL, NULL);
		BinaryTree::TreeNode nodeRoot(2, &nodeL, &nodeR);
		//cout << btSolver.isValidBST(&nodeRoot);

		//DynamicProgramming dpSolver;
		//cout << dpSolver.longestValidParentheses("()(())");// ")(((((()())()()))()(()))(");
		//cout << dpSolver.minDistance("horse", "ros");
		//vector<string> vDict{ "car", "ca", "rs"};
		//cout << dpSolver.numSquares(13);// dpSolver.wordBreak("cars", vDict);

		Graph gpSolver;
		vector<vector<int>> grid({ {1,2} });
		gpSolver.orangesRotting(grid);

	}
}
