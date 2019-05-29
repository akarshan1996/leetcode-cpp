#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;

    explicit ListNode(int x) : val(x), next(nullptr) {}
};

//////////

class Solution {
public:
    ListNode *mergeKLists(vector<ListNode *> &lists) {
        ListNode outputPointer(0);

        auto compare = [](ListNode *a, ListNode *b) { return a->val > b->val; };
        priority_queue<ListNode *, vector<ListNode *>, decltype(compare)> heads(compare);
        for (auto head : lists) {
            if (head != nullptr) {
                heads.push(head);
            }
        }

        ListNode *outputPrev = &outputPointer;

        while (!heads.empty()) {
            ListNode *top = heads.top();
            heads.pop();

            if (top->next != nullptr) {
                heads.push(top->next);
                top->next = nullptr;
            }

            outputPrev->next = top;
            outputPrev = top;
        }

        return outputPointer.next;
    }
};

//////////

static void runOne(vector<ListNode *> &&lists, ListNode *expected) {
    Solution solution;
    ListNode *output = solution.mergeKLists(lists);

    bool failed = false;

    ListNode *outputIt = output;
    ListNode *expectedIt = expected;
    for (; outputIt != nullptr && expectedIt != nullptr; outputIt = outputIt->next, expectedIt = expectedIt->next) {
        if (outputIt->val != expectedIt->val) {
            failed = true;
        }
    }
    if (!(outputIt == nullptr && expectedIt == nullptr)) {
        failed = true;
    }

    if (failed) {
        cerr << "output:";
        for (outputIt = output; outputIt != nullptr; outputIt = outputIt->next) {
            cerr << " " << outputIt->val;
        }
        cerr << endl;
        cerr << "expected:";
        for (expectedIt = expected; expectedIt != nullptr; expectedIt = expectedIt->next) {
            cerr << " " << expectedIt->val;
        }
        cerr << endl;
        exit(-1);
    }
}

static ListNode *toList(vector<int> &&v) {
    ListNode headPointer(0);
    ListNode *prev = &headPointer;
    for (int i : v) {
        prev->next = new ListNode(i);
        prev = prev->next;
    }
    return headPointer.next;
}

void run0023() {
    runOne({
                   toList({1, 4, 5}),
                   toList({1, 3, 4}),
                   toList({2, 6}),
           },
           toList({1, 1, 2, 3, 4, 4, 5, 6}));
}
