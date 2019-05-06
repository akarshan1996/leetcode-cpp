#include <iostream>

using namespace std;

//////////

class Solution {
public:
    int compareVersion(string version1, string version2) {

        size_t it1 = 0;
        size_t it2 = 0;

        while (it1 < version1.size() || it2 < version2.size()) {

            int versionFragment1 = getVersionFragment(version1, it1);
            int versionFragment2 = getVersionFragment(version2, it2);

            if (versionFragment1 < versionFragment2) {
                return -1;
            } else if (versionFragment1 > versionFragment2) {
                return 1;
            }
        }

        return 0;
    }

private:
    static int getVersionFragment(const string &version, size_t &it) {
        if (it >= version.size()) {
            return 0;
        }

        int versionFragment = 0;

        for (; it < version.size(); it++) {
            if (version[it] == '.') {
                it++;
                break;
            }

            versionFragment = versionFragment * 10 + (version[it] - '0');
        }

        return versionFragment;
    }
};

//////////

static void runOne(string &&version1, string &&version2, int expected) {
    Solution solution;
    int output = solution.compareVersion(version1, version2);
    if (output != expected) {
        cerr << "  output: " << output << endl << "expected: " << expected << endl;
        exit(-1);
    }
}

void run0165() {
    runOne("0.1", "1.1", -1);
    runOne("1.0.1", "1", 1);
    runOne("7.5.2.4", "7.5.3", -1);
    runOne("1.01", "1.001", 0);
    runOne("1.0", "1.0.0", 0);
}
