#pragma once
#include <vector>
#include <string>
#include <set>

using namespace std;

namespace Interview150
{
	class Matrix
	{
	protected:
		bool IsValid(char ch, const set<char>& cache);
		int checkBoarders(vector<vector<int>>& board, int x, int y);

	public:
		// 36. Valid Sudoku
		bool IsValidSudoku(const vector<vector<char>>& board);

		// 289. Game of Life
		void GameOfLife(vector<vector<int>>& board);
	};

}