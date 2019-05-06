#include <vector>
#include <iostream>

using namespace std;

//////////

struct Node {
    static const size_t indexForEmpty = -1;

    int value;

    size_t leftIndex;
    size_t rightIndex;

    int leftSize;
    int sameValueCount;

    Node() = default;

    explicit Node(int value) :
            value(value),
            leftIndex(indexForEmpty),
            rightIndex(indexForEmpty),
            leftSize(0),
            sameValueCount(1) {}
};

static int insertAndGetCount(vector<Node> &tree, int value) {
    if (tree.empty()) {
        tree.emplace_back(Node(value));
        return 0;
    }

    int count = 0;

    Node *currentNode = &tree[0];
    while (true) {
        if (currentNode->value > value) {
            // left
            currentNode->leftSize++;
            if (currentNode->leftIndex == Node::indexForEmpty) {
                tree.emplace_back(Node(value));
                currentNode->leftIndex = tree.size() - 1;
                break;
            } else {
                currentNode = &tree[currentNode->leftIndex];
            }
        } else if (currentNode->value < value) {
            // right
            count += currentNode->leftSize + currentNode->sameValueCount;
            if (currentNode->rightIndex == Node::indexForEmpty) {
                tree.emplace_back(Node(value));
                currentNode->rightIndex = tree.size() - 1;
                break;
            } else {
                currentNode = &tree[currentNode->rightIndex];
            }
        } else {
            // currentNode.value == value
            // duplicate
            currentNode->sameValueCount++;
            count += currentNode->leftSize;
            break;
        }
    }

    return count;
}

class Solution {
public:
    vector<int> countSmaller(vector<int> &nums) {
        vector<int> counts(nums.size());

        vector<Node> tree;
        tree.reserve(nums.size());

        for (size_t i = nums.size() - 1; i < nums.size(); i--) {
            counts[i] = insertAndGetCount(tree, nums[i]);
        }

        return counts;
    }
};

//////////

static void runOne(vector<int> &&input, vector<int> &&expected) {
    Solution solution;
    const vector<int> output = solution.countSmaller(input);
    if (output != expected) {
        cerr << "  output:";
        for (auto o : output) {
            cerr << " " << o;
        }
        cerr << endl;
        cerr << "expected:";
        for (auto e : expected) {
            cerr << " " << e;
        }
        exit(-1);
    }
}

void run0315() {
    runOne({5, 2, 6, 1}, {2, 1, 1, 0});
}
