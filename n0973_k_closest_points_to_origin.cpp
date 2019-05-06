#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//////////

class Solution {
public:
    vector<vector<int>> kClosest(vector<vector<int>> &points, int K) {
        if (points.empty() || K == 0) {
            return {};
        }

        vector<Point> heap;
        heap.reserve(K);

        heap.emplace_back(Point{&points[0], getDistanceSquare(points[0])});

        for (size_t i = 1; i < points.size(); i++) {
            const vector<int> &point = points[i];

            if (heap.size() < K) {
                heap.emplace_back(Point{&point, getDistanceSquare(point)});
                push_heap(heap.begin(), heap.end());
            } else {
                const int distanceSquare = getDistanceSquare(point);
                if (distanceSquare < heap.front().distanceSquare) {
                    pop_heap(heap.begin(), heap.end());
                    heap.back() = Point{&point, distanceSquare};
                    push_heap(heap.begin(), heap.end());
                }
            }
        }

        vector<vector<int>> result;
        result.reserve(K);

        for (const Point &point : heap) {
            result.push_back(*point.raw);
        }

        return result;
    }

private:
    static inline int getDistanceSquare(const vector<int> &point) {
        return point[0] * point[0] + point[1] * point[1];
    }

    struct Point {
        const vector<int> *raw;
        int distanceSquare;

        bool operator<(const Point &other) {
            return distanceSquare < other.distanceSquare;
        }
    };
};

//////////

static void runOne(vector<vector<int>> &&points, int K, vector<vector<int>> &&expected) {
    Solution solution;
    vector<vector<int>> output = solution.kClosest(points, K);

    bool containsAll = true;
    for (const auto &o : output) {
        if (find(expected.begin(), expected.end(), o) == expected.end()) {
            containsAll = false;
            break;
        }
    }

    if (output.size() != expected.size() || !containsAll) {
        cerr << "  output:";
        for (auto o : output) {
            cerr << " " << o[0] << ',' << o[1];
        }
        cerr << endl;
        cerr << "expected:";
        for (auto e : expected) {
            cerr << " " << e[0] << ',' << e[1];
        }
        exit(-1);
    }
}

void run0973() {
    runOne(
            {{1,  3},
             {-2, 2}},
            1,
            {{-2, 2}}
    );
    runOne(
            {{3,  3},
             {5,  -1},
             {-2, 4}},
            2,
            {{3,  3},
             {-2, 4}}
    );
    runOne(
            {{1,  3},
             {-2, 2},
             {2,  -2}},
            2,
            {{-2, 2},
             {2,  -2}}
    );
}
