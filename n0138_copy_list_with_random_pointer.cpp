#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

class Node {
public:
    int val;
    Node *next;
    Node *random;

    Node() {} // NOLINT

    Node(int _val, Node *_next, Node *_random) {
        val = _val;
        next = _next;
        random = _random;
    }
};

//////////

/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;

    Node() {}

    Node(int _val, Node* _next, Node* _random) {
        val = _val;
        next = _next;
        random = _random;
    }
};
*/

class Solution {
public:
    Node *copyRandomList(Node *head) {
        if (head == nullptr) {
            return nullptr;
        }

        for (Node *node = head; node != nullptr; node = node->next) {
            Node *newNode = new Node();
            newNode->val = node->val;
            newNode->next = node->random;
            node->random = newNode;
        }

        Node *newHead = head->random;

        for (Node *node = head; node != nullptr; node = node->next) {
            Node *newNode = node->random;
            newNode->random = newNode->next != nullptr ? newNode->next->random : nullptr;
        }

        for (Node *node = head; node != nullptr; node = node->next) {
            Node *newNode = node->random;
            Node *nodeRandom = newNode->next;
            newNode->next = node->next != nullptr ? node->next->random : nullptr;
            node->random = nodeRandom;
        }

        return newHead;
    }
};

//////////

static void runOne(Node *head) {
    Solution solution;
    Node *output = solution.copyRandomList(head);

    unordered_map<Node *, Node *> nodeMap;

    Node *oldNode, *newNode;

    for (oldNode = head, newNode = output;
         oldNode != nullptr && newNode != nullptr;
         oldNode = oldNode->next, newNode = newNode->next) {

        nodeMap[oldNode] = newNode;

        if (oldNode == newNode) {
            cerr << "identical: " << oldNode->val << endl;
            exit(-1);
        }

        if (oldNode->val != newNode->val) {
            cerr << "val is different: " << oldNode->val << " " << newNode->val << endl;
            exit(-1);
        }
    }

    if (oldNode != nullptr || newNode != nullptr) {
        cerr << "end without nullptr" << endl;
        exit(-1);
    }

    for (oldNode = head, newNode = output;
         oldNode != nullptr && newNode != nullptr;
         oldNode = oldNode->next, newNode = newNode->next) {

        if (oldNode->random == nullptr && newNode->random == nullptr) {
            continue;
        }

        if (newNode->random != nodeMap[oldNode->random]) {
            cerr << "random is different" << endl;
            exit(-1);
        }
    }
}

void run0138() {
    Node *node1 = new Node(1, nullptr, nullptr);
    Node *node2 = new Node(2, nullptr, nullptr);
    node1->next = node2;
    node1->random = node2;
    node2->random = node2;

    runOne(node1);
}
