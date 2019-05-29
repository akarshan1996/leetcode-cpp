#include <iostream>
#include <vector>

using namespace std;

//////////

class Solution {
public:
    vector<int> productExceptSelf(vector<int> &nums) {
        vector<int> result(nums.size());

        int productFromLeft = 1;
        for (size_t i = 0; i < nums.size(); i++) {
            result[i] = productFromLeft;
            productFromLeft *= nums[i];
        }

        int productFromRight = 1;
        for (size_t i = nums.size() - 1; i < nums.size(); i--) {
            result[i] *= productFromRight;
            productFromRight *= nums[i];
        }

        return result;
    }
};

//////////

static void runOne(vector<int> &&nums, vector<int> &&expected) {
    Solution solution;
    vector<int> output = solution.productExceptSelf(nums);
    if (output != expected) {
        cerr << "  output:";
        for (int n : output) {
            cerr << " " << n;
        }
        cerr << endl;
        cerr << "expected:";
        for (int n : expected) {
            cerr << " " << n;
        }
        cerr << endl;
        exit(-1);
    }
}

void run0238() {
    runOne({1, 2, 3, 4}, {24, 12, 8, 6});
}
