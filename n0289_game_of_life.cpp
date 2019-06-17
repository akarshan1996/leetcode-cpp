#include <iostream>
#include <vector>

using namespace std;

//////////

class Solution {
public:
    void gameOfLife(vector<vector<int>> &board) {
        if (board.empty()) {
            return;
        }

        vector<vector<int>> nextGeneration(board.size(), vector<int>(board[0].size()));

        for (size_t i = 0; i < board.size(); i++) {
            for (size_t j = 0; j < board[i].size(); j++) {
                nextGeneration[i][j] = getNext(board, i, j);
            }
        }

        board = nextGeneration;
    }

private:
    static int getNext(vector<vector<int>> &board, size_t i, size_t j) {
        int count = 0;
        count += getCurrent(board, i - 1, j - 1);
        count += getCurrent(board, i - 1, j);
        count += getCurrent(board, i - 1, j + 1);
        count += getCurrent(board, i, j - 1);
        count += getCurrent(board, i, j + 1);
        count += getCurrent(board, i + 1, j - 1);
        count += getCurrent(board, i + 1, j);
        count += getCurrent(board, i + 1, j + 1);

        return board[i][j] == 0
               ? count == 3
               : (count == 2 || count == 3);
    }

    static int getCurrent(vector<vector<int>> &board, size_t i, size_t j) {
        if (i < board.size() && j < board[i].size()) {
            return board[i][j];
        }
        return 0;
    }
};

//////////

static void runOne(vector<vector<int>> &&board, vector<vector<int>> &&expected) {
    Solution solution;
    solution.gameOfLife(board);
    if (board != expected) {
        cerr << "output:" << endl;
        for (auto &row : board) {
            for (int cell : row) {
                cerr << " " << cell;
            }
            cerr << endl;
        }
        cerr << "expected:" << endl;
        for (auto &row : expected) {
            for (int cell : row) {
                cerr << " " << cell;
            }
            cerr << endl;
        }
        exit(-1);
    }
}

void run0289() {
    runOne({
                   {0, 1, 0},
                   {0, 0, 1},
                   {1, 1, 1},
                   {0, 0, 0},
           },
           {
                   {0, 0, 0},
                   {1, 0, 1},
                   {0, 1, 1},
                   {0, 1, 0},
           });
}
