#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <optional>

using namespace std;

//////////

static int indexOf(const vector<int> &nums, int target, function<bool(int, int)> &&compare) {
    auto it = lower_bound(nums.begin(), nums.end(), target, compare);
    if (it != nums.end() && *it == target) {
        return distance(nums.begin(), it);
    } else {
        return -1;
    }
}

class Solution {
public:
    int search(vector<int> &nums, int target) {
        if (nums.empty()) {
            return -1;
        }

        using checkFunc = function<optional<bool>(int)>;
        checkFunc check =
                target >= nums[0]
                ? checkFunc([&](int current) { return current < nums[0] ? optional<bool>{false} : nullopt; })
                : checkFunc([&](int current) { return current >= nums[0] ? optional<bool>{true} : nullopt; });

        return indexOf(nums, target, [&check](int current, int target) {
            return check(current).value_or(current < target);
        });
    }
};

//////////

static void runOne(vector<int> &&nums, int target, int expected) {
    Solution solution;
    int output = solution.search(nums, target);
    if (output != expected) {
        cerr << "  output: " << output << endl << "expected: " << expected << endl;
        exit(-1);
    }
}

void run0033() {
    runOne({4, 5, 6, 7, 0, 1, 2}, 0, 4);
    runOne({4, 5, 6, 7, 0, 1, 2}, 3, -1);
}
