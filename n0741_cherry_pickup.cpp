#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//////////

class Solution {
public:
    int cherryPickup(vector<vector<int>> &grid) {
        if (grid.empty()) {
            return 0;
        }


        vector<int> maximumsGrid[grid.size()][grid[0].size()];

        size_t n = grid.size();
        size_t iEnd = 2 * n - 1;

        for (size_t i = 0; i < iEnd; i++) {
            size_t jEnd = i < n ? i + 1 : 2 * n - 1 - i;
            size_t rBegin = i < n ? 0 : i - n + 1;

            vector<int> cellsOnI;
            for (size_t j = 0; j < jEnd; j++) {
                size_t r = rBegin + j;
                size_t c = i - r;
                int cell = grid[r][c];
                cellsOnI.push_back(cell);
            }

            for (size_t j = 0; j < jEnd; j++) {
                size_t r = rBegin + j;
                size_t c = i - r;
                int cell = grid[r][c];

                vector<int> &newMaximums = maximumsGrid[r][c];
                newMaximums.resize(jEnd, -1);

                if (cell == -1) {
                    continue;
                }

                vector<int> &cellsOnIAfterPickup = cellsOnI;
                if (cell == 1) {
                    cellsOnIAfterPickup[j] = 0;
                }

                if (r == 0 && c == 0) {
                    newMaximums[0] = 0;
                }
                if (r > 0) {
                    mergeNewMaximums(newMaximums, maximumsGrid[r - 1][c], cellsOnIAfterPickup);
                }
                if (c > 0) {
                    mergeNewMaximums(newMaximums, maximumsGrid[r][c - 1], cellsOnIAfterPickup);
                }

                if (cell == 1) {
                    cellsOnIAfterPickup[j] = 1;
                    for (int &newMaximum : newMaximums) {
                        if (newMaximum != -1) {
                            newMaximum++;
                        }
                    }
                }
            }
        }

        int maximum = maximumsGrid[n - 1][n - 1][0];
        return maximum == -1 ? 0 : maximum;
    }

private:
    static void
    mergeNewMaximums(vector<int> &newMaximums, const vector<int> &oldMaximums, const vector<int> &cellsOnIAfterPickup) {
        if (newMaximums.size() > oldMaximums.size()) {
            for (size_t jOldM = 0; jOldM < oldMaximums.size(); jOldM++) {
                int newMaximum;
                newMaximum = makeNewMaximum(oldMaximums[jOldM], cellsOnIAfterPickup[jOldM]);
                if (newMaximum > newMaximums[jOldM]) {
                    newMaximums[jOldM] = newMaximum;
                }
                newMaximum = makeNewMaximum(oldMaximums[jOldM], cellsOnIAfterPickup[jOldM + 1]);
                if (newMaximum > newMaximums[jOldM + 1]) {
                    newMaximums[jOldM + 1] = newMaximum;
                }
            }
        } else {
            for (size_t jNewM = 0; jNewM < newMaximums.size(); jNewM++) {
                int newMaximum;
                newMaximum = makeNewMaximum(oldMaximums[jNewM], cellsOnIAfterPickup[jNewM]);
                if (newMaximum > newMaximums[jNewM]) {
                    newMaximums[jNewM] = newMaximum;
                }
                newMaximum = makeNewMaximum(oldMaximums[jNewM + 1], cellsOnIAfterPickup[jNewM]);
                if (newMaximum > newMaximums[jNewM]) {
                    newMaximums[jNewM] = newMaximum;
                }
            }
        }
    }

    static int makeNewMaximum(int oldMaximum, int cell) {
        return (oldMaximum == -1 || cell == -1) ? -1 : oldMaximum + cell;
    }
};

//////////

static void runOne(vector<vector<int>> &&grid, int expected) {
    Solution solution;
    int output = solution.cherryPickup(grid);
    if (output != expected) {
        cerr << "  output: " << output << endl << "expected: " << expected << endl;
        exit(-1);
    }
}

void run0741() {
    runOne({
                   {0, 1, -1},
                   {1, 0, -1},
                   {1, 1, 1},
           },
           5);

    runOne({{1}},
           1);

    runOne({
                   {1,  1,  -1},
                   {1,  -1, 1},
                   {-1, 1,  1},
           }, 0);

    runOne({
                   {1,  1, -1, 1,  1},
                   {1,  1, 1,  1,  1},
                   {-1, 1, 1,  -1, -1},
                   {0,  1, 1,  -1, 0},
                   {1,  0, -1, 1,  0},
           },
           0);

    runOne({
                   {1, 1,  1,  1, 1},
                   {1, 1,  1,  1, 1},
                   {1, 1,  -1, 1, 1},
                   {0, -1, -1, 1, 1},
                   {1, 1,  1,  1, 1},
           },
           16);

    runOne({
                   {1, 1, 1, 1, 0, 0, 0},
                   {0, 0, 0, 1, 0, 0, 0},
                   {0, 0, 0, 1, 0, 0, 1},
                   {1, 0, 0, 1, 0, 0, 0},
                   {0, 0, 0, 1, 0, 0, 0},
                   {0, 0, 0, 1, 0, 0, 0},
                   {0, 0, 0, 1, 1, 1, 1},
           },
           15);
}
