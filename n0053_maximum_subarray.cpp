#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

//////////

class Solution {
public:
    int maxSubArray(vector<int> &nums) {
        if (nums.empty()) {
            return 0;
        }

        int max = nums[0];
        int largeContiguousSum = nums[0];

        for (size_t i = 1; i < nums.size(); i++) {
            const int num = nums[i];

            if (largeContiguousSum + num > num) {
                largeContiguousSum += num;
            } else {
                largeContiguousSum = num;
            }

            if (largeContiguousSum > max) {
                max = largeContiguousSum;
            }
        }

        return max;
    }
};

//////////

static void runOne(vector<int> &&nums, int expected) {
    Solution solution;
    int output = solution.maxSubArray(nums);
    if (output != expected) {
        cerr << "  output: " << output << endl << "expected: " << expected << endl;
        exit(-1);
    }
}

void run0053() {
    runOne({-2, 1, -3, 4, -1, 2, 1, -5, 4}, 6);
}
