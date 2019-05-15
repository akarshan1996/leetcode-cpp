#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

//////////

class Solution {
public:
    int subarraySum(vector<int> &nums, int k) {
        vector<int> sums = makeSums(nums);

        int count = 0;

        for (size_t begin = 0; begin < nums.size(); begin++) {
            for (size_t end = begin + 1; end < sums.size(); end++) {
                int sumOfSubarray = sums[end] - sums[begin];
                if (sumOfSubarray == k) {
                    count++;
                }
            }
        }

        return count;
    }

private:
    static vector<int> makeSums(const vector<int> &nums) {
        vector<int> sums(nums.size() + 1);

        int sum = 0;
        sums[0] = sum;

        for (size_t i = 0; i < nums.size(); i++) {
            int num = nums[i];
            sum += num;
            sums[i + 1] = sum;
        }

        return sums;
    }
};

//////////

static void runOne(vector<int> &&nums, int k, int expected) {
    Solution solution;
    int output = solution.subarraySum(nums, k);
    if (output != expected) {
        cerr << "  output: " << output << endl << "expected: " << expected << endl;
        exit(-1);
    }
}

void run0560() {
    runOne({1, 1, 1}, 2, 2);
}
