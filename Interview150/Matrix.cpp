#pragma once
#include "Matrix.h"
#include <map>
#include <set>

namespace Interview150
{
    // 36. Valid Sudoku
    bool Matrix::IsValidSudoku(const vector<vector<char>>& board)
    {
        // Row check.
        for (int y = 0; y < board.size(); ++y)
        {
            set<char> buff;
            for (int x = 0; x < board[0].size(); ++x)
            {
                char cur = board[y][x];
                if (cur == '.')  continue;
                if (!IsValid(cur, buff))
                    return false;
                buff.insert(board[y][x]);
            }
        }

        // Col check.
        for (int x = 0; x < board[0].size(); ++x)
        {
            set<char> buff;
            for (int y = 0; y < board.size(); ++y)
            {
                char cur = board[y][x];
                if (cur == '.')  continue;
                if (!IsValid(cur, buff))
                    return false;
                buff.insert(board[y][x]);
            }
        }

        // 3x3 box check.
        for (int iY = 0; iY < 9; iY += 3)
        {
            for (int iX = 0; iX < 9; iX += 3)
            {
                set<char> buff;
                for (int y = 0; y < 3; ++y)
                {
                    for (int x = 0; x < 3; ++x)
                    {
                        char cur = board[y + iY][x + iX];
                        if (cur == '.')  continue;
                        // Console.WriteLine(cur);
                        if (!IsValid(cur, buff))
                            return false;
                        buff.insert(cur);
                    }
                }
            }
        }
        return true;
    }

    // 289. Game of Life
    void Matrix::GameOfLife(vector<vector<int>>& board)
    {
        for (int y = 0; y < board.size(); ++y)
        {
            for (int x = 0; x < board[0].size(); ++x)
            {
                int next = checkBoarders(board, x, y);

                switch (board[y][x])
                {
                case 0:     board[y][x] = next == 1 ? 2 : board[y][x];    break;  // 0 -> 1
                case 1:     board[y][x] = next == 0 ? 3 : board[y][x];    break;  // 1 -> 0
                default:    break;
                }
            }
        }

        for (int y = 0; y < board.size(); ++y)
        {
            for (int x = 0; x < board[0].size(); ++x)
            {
                if (board[y][x] == 2)
                    board[y][x] = 1;
                else if (board[y][x] == 3)
                    board[y][x] = 0;
            }
        }
    }





    // Helpers.
    bool Matrix::IsValid(char ch, const set<char>& cache)
    {
        if (ch < '0' || ch>'9')
            return false;
        if (cache.find(ch) != cache.end())
            return false;
        return true;
    }

    int Matrix::checkBoarders(vector<vector<int>>& board, int x, int y)
    {
        int live = 0;

        // up
        if (y > 0 && (board[y - 1][x] == 1 || board[y - 1][x] == 3))
            ++live;
        // down
        if (y < board.size() - 1 && (board[y + 1][x] == 1 || board[y + 1][x] == 3))
            ++live;
        // left 
        if (x > 0 && (board[y][x - 1] == 1 || board[y][x - 1] == 3))
            ++live;
        // right
        if (x < board[0].size() - 1 && (board[y][x + 1] == 1 || board[y][x + 1] == 3))
            ++live;

        // left up
        if (x > 0 && y > 0 && (board[y - 1][x - 1] == 1 || board[y - 1][x - 1] == 3))
            ++live;
        // right up
        if (x < board[0].size() - 1 && y>0 && (board[y - 1][x + 1] == 1 || board[y - 1][x + 1] == 3))
            ++live;
        // left down
        if (x > 0 && y < board.size() - 1 && (board[y + 1][x - 1] == 1 || board[y + 1][x - 1] == 3))
            ++live;
        // right down
        if (x < board[0].size() - 1 && y < board.size() - 1 && (board[y + 1][x + 1] == 1 || board[y + 1][x + 1] == 3))
            ++live;

        if (board[y][x] == 0)
        {
            if (live == 3)           return 1;
        }
        else if (board[y][x] == 1)
        {
            if (live < 2)            return 0;
            if (live == 2 || live == 3)  return 1;
            if (live > 3)              return 0;
        }
        return board[y][x];
    }
}