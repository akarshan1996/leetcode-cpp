#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

//////////

static inline string_view getPalindromeCommon(const string_view &s, size_t front, size_t rear) {
    for (; front < s.size() && rear < s.size(); front--, rear++) {
        if (s[front] != s[rear]) {
            break;
        }
    }
    return s.substr(front + 1, rear - front - 1);
}

static inline string_view getOddPalindrome(const string_view &s, const size_t centerIndex) {
    size_t front = centerIndex - 1, rear = centerIndex + 1;
    return getPalindromeCommon(s, front, rear);
}

static inline string_view getEvenPalindrome(const string_view &s, const size_t centerIndex) {
    size_t front = centerIndex, rear = centerIndex + 1;
    if (s[front] != s[rear]) {
        return s.substr(0, 0);
    }
    return getPalindromeCommon(s, front, rear);
}

static inline string_view getPalindrome(const string_view &s, const size_t centerIndex) {
    string_view palindrome1 = getOddPalindrome(s, centerIndex);
    string_view palindrome2 = getEvenPalindrome(s, centerIndex);
    return palindrome1.size() > palindrome2.size() ? palindrome1 : palindrome2;
}

class Solution {
    string_view longestPalindrome(string_view s) {
        if (s.empty()) {
            return "";
        }

        string_view longest = s.substr(0, 1);

        for (size_t i = 0; i < s.size() - 1; i++) {
            if (s.size() - i < longest.size() / 2) {
                break;
            }

            string_view palindrome = getPalindrome(s, i);
            if (palindrome.size() > longest.size()) {
                longest = palindrome;
            }
        }

        return longest;
    }

public:
    string longestPalindrome(string s) { // NOLINT(performance-unnecessary-value-param)
        return string(longestPalindrome(string_view(s)));
    }
};

//////////

static void runOne(string &&input, vector<string> &&expectedList) {
    Solution solution;
    const string output = solution.longestPalindrome(std::move(input));
    if (std::find(expectedList.begin(), expectedList.end(), output) == expectedList.end()) {
        cerr << "output: " << output << endl << "expected: " << expectedList[0];
        for (int i = 1; i < expectedList.size(); i++) {
            cerr << " or " << expectedList[i];
        }
        cerr << endl;
        exit(-1);
    }
}

void run0005() {
    runOne("babad", {"bab", "aba"});
    runOne("cbbd", {"bb"});
}
