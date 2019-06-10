#include <iostream>
#include <vector>
#include <utility>

using namespace std;

class Node {
public:
    bool val;
    bool isLeaf;
    Node *topLeft;
    Node *topRight;
    Node *bottomLeft;
    Node *bottomRight;

    Node() = default;

    Node(bool _val, bool _isLeaf, Node *_topLeft, Node *_topRight, Node *_bottomLeft, Node *_bottomRight) {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = _topLeft;
        topRight = _topRight;
        bottomLeft = _bottomLeft;
        bottomRight = _bottomRight;
    }
};

//////////

static Node *makeLeaf(bool val) {
    return new Node(val, true, nullptr, nullptr, nullptr, nullptr);
}

struct LeafOrNode {
    bool val;
    Node *node;

    bool isLeaf() {
        return node == nullptr;
    }

    Node *toNode() {
        return isLeaf() ? makeLeaf(val) : node;
    }

    static LeafOrNode createLeaf(bool val) {
        return {val, nullptr};
    }

    static LeafOrNode createNode(Node *node) {
        return {false, node};
    }
};

class Solution {
public:
    Node *construct(vector<vector<int>> &grid) {
        if (grid.empty()) {
            return nullptr;
        }
        return construct(grid, 0, grid.size(), 0, grid[0].size()).toNode();
    }

private:
    static LeafOrNode construct(vector<vector<int>> &grid, size_t top, size_t bottom, size_t left, size_t right) {
        if (bottom - top == 1) {
            return LeafOrNode::createLeaf(grid[top][left]);
        }

        size_t verticalMiddle = (top + bottom) / 2;
        size_t horizontalMiddle = (left + right) / 2;

        LeafOrNode topLeft = construct(grid, top, verticalMiddle, left, horizontalMiddle);
        LeafOrNode topRight = construct(grid, top, verticalMiddle, horizontalMiddle, right);
        LeafOrNode bottomLeft = construct(grid, verticalMiddle, bottom, left, horizontalMiddle);
        LeafOrNode bottomRight = construct(grid, verticalMiddle, bottom, horizontalMiddle, right);

        if (topLeft.isLeaf()
            && topRight.isLeaf()
            && bottomLeft.isLeaf()
            && bottomRight.isLeaf()
            && topLeft.val == topRight.val
            && topRight.val == bottomLeft.val
            && bottomLeft.val == bottomRight.val) {

            return LeafOrNode::createLeaf(topLeft.val);
        }

        return LeafOrNode::createNode(
                new Node(false,
                         false,
                         topLeft.toNode(),
                         topRight.toNode(),
                         bottomLeft.toNode(),
                         bottomRight.toNode()));
    }
};

//////////

static bool isEqual(Node *a, Node *b) {
    if (a == nullptr && b == nullptr) {
        return true;
    } else if (a == nullptr || b == nullptr) {
        return false;
    } else {
        return a->val == b->val
               && a->isLeaf == b->isLeaf
               && isEqual(a->topLeft, b->topLeft)
               && isEqual(a->topRight, b->topRight)
               && isEqual(a->bottomLeft, b->bottomLeft)
               && isEqual(a->bottomRight, b->bottomRight);
    }
}

static void printNode(Node *node, int indent, ostream &os) {
    if (node == nullptr) {
        return;
    }

    for (int i = 0; i < indent; i++) {
        os << "   ";
    }

    os << node->isLeaf << " " << node->val << endl;
    printNode(node->topLeft, indent + 1, os);
    printNode(node->topRight, indent + 1, os);
    printNode(node->bottomLeft, indent + 1, os);
    printNode(node->bottomRight, indent + 1, os);
}

static void printNode(Node *node, ostream &os) {
    printNode(node, 0, os);
}

static void runOne(vector<vector<int>> &&grid, Node *expected) {
    Solution solution;
    Node *output = solution.construct(grid);
    if (!isEqual(expected, output)) {
        cerr << "  output:" << endl;
        printNode(output, cerr);
        cerr << "expected:" << endl;
        printNode(expected, cerr);
    }
}

void run0427() {
    Node *root1 =
            new Node(false, false,
                     makeLeaf(true),
                     new Node(false, false,
                              makeLeaf(false),
                              makeLeaf(false),
                              makeLeaf(true),
                              makeLeaf(true)),
                     new Node(true, true, nullptr, nullptr, nullptr, nullptr),
                     new Node(false, true, nullptr, nullptr, nullptr, nullptr)
            );
    runOne({
                   {1, 1, 1, 1, 0, 0, 0, 0},
                   {1, 1, 1, 1, 0, 0, 0, 0},
                   {1, 1, 1, 1, 1, 1, 1, 1},
                   {1, 1, 1, 1, 1, 1, 1, 1},
                   {1, 1, 1, 1, 0, 0, 0, 0},
                   {1, 1, 1, 1, 0, 0, 0, 0},
                   {1, 1, 1, 1, 0, 0, 0, 0},
                   {1, 1, 1, 1, 0, 0, 0, 0},
           },
           root1);
}
