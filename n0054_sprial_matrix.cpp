#include <iostream>
#include <vector>

using namespace std;

//////////

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>> &matrix) {
        if (matrix.empty()) {
            return vector<int>();
        }

        vector<int> result;
        result.reserve(matrix.size() * matrix[0].size());

        spiralOrder(result, matrix, 0, matrix.size(), 0, matrix[0].size());

        return result;
    }

private:
    static void spiralOrder(vector<int> &result,
                            vector<vector<int>> &matrix,
                            size_t rBegin, size_t rEnd, size_t cBegin, size_t cEnd) {

        if (rEnd <= rBegin || cEnd <= cBegin) {
            return;
        }

        if (rEnd - rBegin == 1) {
            for (size_t c = cBegin; c < cEnd; c++) {
                result.push_back(matrix[rBegin][c]);
            }
        } else if (cEnd - cBegin == 1) {
            for (size_t r = rBegin; r < rEnd; r++) {
                result.push_back(matrix[r][cBegin]);
            }
        } else {
            for (size_t c = cBegin; c < cEnd; c++) {
                result.push_back(matrix[rBegin][c]);
            }
            for (size_t r = rBegin + 1; r < rEnd; r++) {
                result.push_back(matrix[r][cEnd - 1]);
            }
            for (size_t c = cEnd - 2; c >= cBegin && c < cEnd; c--) {
                result.push_back(matrix[rEnd - 1][c]);
            }
            for (size_t r = rEnd - 2; r >= rBegin + 1 && r < rEnd; r--) {
                result.push_back(matrix[r][cBegin]);
            }
        }

        spiralOrder(result, matrix, rBegin + 1, rEnd - 1, cBegin + 1, cEnd - 1);
    }
};

//////////

static void runOne(vector<vector<int>> &&matrix, vector<int> &&expected) {
    vector<int> output = Solution().spiralOrder(matrix);
    if (output != expected) {
        cerr << "output:" << endl;
        for (int &e : output) {
            cerr << " " << e;
        }
        cerr << endl;
        cerr << "expected:" << endl;
        for (int &e : expected) {
            cerr << " " << e;
        }
        cerr << endl;
        exit(-1);
    }
}

void run0054() {
    runOne(
            {
                    {1, 2, 3},
                    {4, 5, 6},
                    {7, 8, 9},
            },
            {1, 2, 3, 6, 9, 8, 7, 4, 5}
    );

    runOne(
            {
                    {1, 2,  3,  4},
                    {5, 6,  7,  8},
                    {9, 10, 11, 12},
            },
            {1, 2, 3, 4, 8, 12, 11, 10, 9, 5, 6, 7}
    );
}
