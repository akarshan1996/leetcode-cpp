#include <vector>
#include <iostream>

using namespace std;

//////////

class Solution {
public:
    int trap(vector<int> &height) {
        const int heightSize = height.size();
        if (heightSize <= 2) {
            return 0;
        }

        int maxHeightFromLeft[heightSize];
        maxHeightFromLeft[0] = height[0];
        for (size_t i = 1; i < heightSize; i++) {
            maxHeightFromLeft[i] = max(maxHeightFromLeft[i - 1], height[i]);
        }

        int maxHeightFromRight[heightSize];
        maxHeightFromRight[heightSize - 1] = height[heightSize - 1];
        for (size_t i = heightSize - 2; i < heightSize; i--) {
            maxHeightFromRight[i] = max(maxHeightFromRight[i + 1], height[i]);
        }

        int waterLevel[heightSize];
        for (size_t i = 0; i < heightSize; i++) {
            waterLevel[i] = min(maxHeightFromLeft[i], maxHeightFromRight[i]);
        }

        int waterCapacity = 0;
        for (size_t i = 0; i < heightSize; i++) {
            waterCapacity += waterLevel[i] - height[i];
        }

        return waterCapacity;
    }
};

//////////

static void runOne(vector<int> &height, const int expected) {
    Solution solution;
    const int result = solution.trap(height);
    if (result != expected) {
        cerr << "result: " << result << endl << "expected: " << expected << endl;
        exit(-1);
    }
}

void run0042() {
    vector<int> height;

    height = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
    runOne(height, 6);
}
