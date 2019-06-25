#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    explicit TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

//////////

class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode *root) {
        vector<vector<int>> levelOrderValues;
        levelOrder(levelOrderValues, root, 0);

        vector<vector<int>> zigzagLevelOrderValues = move(levelOrderValues);
        for (size_t i = 0; i < zigzagLevelOrderValues.size(); i++) {
            if (i % 2 == 1) {
                reverse(zigzagLevelOrderValues[i].begin(), zigzagLevelOrderValues[i].end());
            }
        }
        return zigzagLevelOrderValues;
    }

private:
    static void levelOrder(vector<vector<int>> &levelOrderValues, TreeNode *node, int level) {
        if (node == nullptr) {
            return;
        }

        if (levelOrderValues.size() < level + 1) {
            levelOrderValues.resize(level + 1);
        }
        vector<int> &valuesOfCurrentLevel = levelOrderValues[level];
        valuesOfCurrentLevel.push_back(node->val);

        levelOrder(levelOrderValues, node->left, level + 1);
        levelOrder(levelOrderValues, node->right, level + 1);
    }
};

//////////

static void runOne(TreeNode *root, vector<vector<int>> &&expected) {
    vector<vector<int>> output = Solution().zigzagLevelOrder(root);
    if (output != expected) {
        cerr << "output:" << endl;
        for (vector<int> &row : output) {
            for (int val : row) {
                cerr << " " << val;
            }
            cerr << endl;
        }
        cerr << "expected:" << endl;
        for (vector<int> &row : expected) {
            for (int val : row) {
                cerr << " " << val;
            }
            cerr << endl;
        }
        exit(-1);
    }
}

static TreeNode *newNode(int val, TreeNode *left, TreeNode *right) {
    auto treeNode = new TreeNode(val);
    treeNode->left = left;
    treeNode->right = right;
    return treeNode;
}

static TreeNode *newLeaf(int val) {
    return new TreeNode(val);
}

void run0103() {
    runOne(
            newNode(3,
                    newLeaf(9),
                    newNode(20,
                            newLeaf(15),
                            newLeaf(7)
                    )),
            {
                    {3},
                    {20, 9},
                    {15, 7},
            });
}
