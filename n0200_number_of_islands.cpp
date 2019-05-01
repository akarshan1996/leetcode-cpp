#include <vector>
#include <iostream>
#include <stack>

using namespace std;

//////////

typedef uint8_t CellType;

struct Coord {
    int r;
    int c;

    Coord(int r, int c) : r(r), c(c) {}
};

static void fill(vector<vector<CellType>> &field, size_t startRow, size_t startColumn, int filler) {
    const CellType starter = field[startRow][startColumn];
    if (starter == filler) {
        return;
    }

    stack<Coord> targetStack;
    targetStack.emplace(Coord(startRow, startColumn));

    while (!targetStack.empty()) {
        Coord target = targetStack.top();
        targetStack.pop();

        field[target.r][target.c] = filler;

        if (target.r >= 1 && field[target.r - 1][target.c] == starter) {
            targetStack.emplace(Coord(target.r - 1, target.c));
        }
        if (target.r < field.size() - 1 && field[target.r + 1][target.c] == starter) {
            targetStack.emplace(Coord(target.r + 1, target.c));
        }
        if (target.c >= 1 && field[target.r][target.c - 1] == starter) {
            targetStack.emplace(Coord(target.r, target.c - 1));
        }
        if (target.c < field[target.r].size() - 1 && field[target.r][target.c + 1] == starter) {
            targetStack.emplace(Coord(target.r, target.c + 1));
        }
    }
}

class Solution {
public:
    int numIslands(vector<vector<char>> &grid) {
        if (grid.empty() || grid[0].empty()) {
            return 0;
        }

        const size_t rowSize = grid.size();
        const size_t columnSize = grid[0].size();

        const CellType water = 0;
        const CellType ownerlessLand = 1;
        const CellType ownerIdBegin = 2;

        vector<vector<CellType>> field(rowSize, vector<CellType>(columnSize, water));
        for (size_t r = 0; r < rowSize; r++) {
            for (size_t c = 0; c < columnSize; c++) {
                if (grid[r][c] == '1') {
                    field[r][c] = ownerlessLand;
                }
            }
        }

        CellType nextOwnerId = ownerIdBegin;

        for (size_t r = 0; r < rowSize; r++) {
            for (size_t c = 0; c < columnSize; c++) {
                if (field[r][c] == ownerlessLand) {
                    fill(field, r, c, nextOwnerId++);
                }
            }
        }

        return nextOwnerId - ownerIdBegin;
    }
};

//////////

static void runOne(vector<vector<char>> &grid, const int expected) {
    Solution solution;
    const int result = solution.numIslands(grid);
    if (result != expected) {
        cerr << "result: " << result << endl << "expected: " << expected << endl;
        exit(-1);
    }
}

void run0200() {
    vector<vector<char>> grid;

    grid = {
            {'1', '1', '1', '1', '0'},
            {'1', '1', '0', '1', '0'},
            {'1', '1', '0', '0', '0'},
            {'0', '0', '0', '0', '0'},
    };
    runOne(grid, 1);

    grid = {
            {'1', '1', '0', '0', '0'},
            {'1', '1', '0', '0', '0'},
            {'0', '0', '1', '0', '0'},
            {'0', '0', '0', '1', '1'},
    };
    runOne(grid, 3);
}
