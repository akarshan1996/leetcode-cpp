#include <iostream>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    explicit TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

//////////

class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode *root) {
        if (root == nullptr) {
            return "n";
        } else {
            return to_string(root->val) + "," + serialize(root->left) + "," + serialize(root->right);
        }
    }

    // Decodes your encoded data to tree.
    TreeNode *deserialize(string data) {
        size_t index = 0;
        return deserialize(data, index);
    }

private:
    static TreeNode *deserialize(const string &data, size_t &index) {
        if (data[index] == 'n') {
            index++;
            return nullptr;
        } else {
            int val = parseInt(data, index);
            auto *treeNode = new TreeNode(val);
            index++; // consume ","
            treeNode->left = deserialize(data, index);
            index++; // consume ","
            treeNode->right = deserialize(data, index);
            return treeNode;
        }
    }

    static int parseInt(const string &data, size_t &index) {
        int sign = 1;
        if (data[index] == '-') {
            sign = -1;
            index++;
        }

        int val = 0;
        for (; index < data.size(); index++) {
            if (data[index] >= '0' && data[index] <= '9') {
                val = val * 10 + (data[index] - '0');
            } else {
                break;
            }
        }

        return sign * val;
    }
};

//////////

static bool isEqual(TreeNode *a, TreeNode *b) {
    if (a == nullptr && b == nullptr) {
        return true;
    } else if (a == nullptr || b == nullptr) {
        return false;
    } else {
        return a->val == b->val
               && isEqual(a->left, b->left)
               && isEqual(a->right, b->right);
    }
}

static void runOne(TreeNode *root) {
    Codec codec;
    TreeNode *deserializedRoot = codec.deserialize(codec.serialize(root));
    if (!isEqual(root, deserializedRoot)) {
        std::cerr << "not equal" << std::endl;
    }
}

void run0297() {
    auto *root1 = new TreeNode(1);
    root1->left = new TreeNode(2);
    root1->right = new TreeNode(3);
    root1->right->left = new TreeNode(4);
    root1->right->right = new TreeNode(5);
    runOne(root1);

    auto *root2 = new TreeNode(-1);
    root2->left = new TreeNode(0);
    root2->right = new TreeNode(1);
    runOne(root2);
}
