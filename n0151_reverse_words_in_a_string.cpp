#include <iostream>
#include <stack>

using namespace std;

//////////

class Solution {
public:
    string reverseWords(string s) {
        return reverseWords(string_view(s));
    }

    static string reverseWords(const string_view &s) {

        stack<string_view> wordsStack;

        size_t wordBegin = -1;

        for (size_t i = 0; i < s.size(); i++) {
            if (wordBegin == -1) {
                if (s[i] != ' ') {
                    wordBegin = i;
                }
            } else {
                if (s[i] == ' ') {
                    wordsStack.emplace(s.substr(wordBegin, i - wordBegin));
                    wordBegin = -1;
                }
            }
        }

        if (wordBegin != -1) {
            wordsStack.emplace(s.substr(wordBegin, s.size() - wordBegin));
        }

        string reversed;

        while (!wordsStack.empty()) {
            reversed += wordsStack.top();
            reversed += " ";
            wordsStack.pop();
        }

        if (!reversed.empty()) {
            reversed.pop_back();
        }

        return reversed;
    }
};

//////////

static void runOne(string &&input, string &&expected) {
    Solution solution;
    string output = solution.reverseWords(input);
    if (output != expected) {
        cerr << "  output: " << output << endl << "expected: " << expected << endl;
        exit(-1);
    }
}

void run0151() {
    runOne("the sky is blue", "blue is sky the");
    runOne("  hello world!  ", "world! hello");
    runOne("a good   example", "example good a");
}
