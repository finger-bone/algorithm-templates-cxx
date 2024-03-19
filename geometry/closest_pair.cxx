#include <vector>
#include <algorithm>

using namespace std;

struct Point {
    double x;
    double y;
};

double distance(Point a, Point b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

vector<Point> closest_pair_of_points(vector<Point> points) {
    if(points.size() <= 3) {
        double min_dist = 0x3f3f3f3f;
        vector<Point> ans;
        for(size_t i = 0; i < points.size(); i++) {
            for(size_t j = i + 1; j < points.size(); j++) {
                double dist = distance(points[i], points[j]);
                if(dist < min_dist) {
                    min_dist = dist;
                    ans = {points[i], points[j]};
                }
            }
        }
        return ans;
    } else {
        sort(points.begin(), points.end(), [](Point a, Point b) {
            return a.x < b.x;
        });
        vector<Point> left(points.begin(), points.begin() + points.size() / 2);
        vector<Point> right(points.begin() + points.size() / 2, points.end());
        vector<Point> left_ans = closest_pair_of_points(left);
        vector<Point> right_ans = closest_pair_of_points(right);
        double left_dist = distance(left_ans[0], left_ans[1]);
        double right_dist = distance(right_ans[0], right_ans[1]);
        double min_dist = min(left_dist, right_dist);
        double mid = (left.back().x + right.front().x) / 2;
        vector<Point> mid_points;
        for(size_t i = 0; i < points.size(); i++) {
            if((points[i].x - mid) * (points[i].x - mid) < min_dist) {
                mid_points.push_back(points[i]);
            }
        }
        sort(mid_points.begin(), mid_points.end(), [](Point a, Point b) {
            return a.y < b.y;
        });
        for(size_t i = 0; i < mid_points.size(); i++) {
            for(size_t j = i + 1; j < mid_points.size() && (mid_points[j].y - mid_points[i].y) * (mid_points[j].y - mid_points[i].y) < min_dist; j++) {
                double dist = distance(mid_points[i], mid_points[j]);
                if(dist < min_dist) {
                    min_dist = dist;
                    left_ans = {mid_points[i], mid_points[j]};
                }
            }
        }
        return left_dist < right_dist ? left_ans : right_ans;
    }
}

#ifdef DEBUG

#include <iostream>
#include <chrono>
#include <utility>
#include <unordered_set>

void print_points(vector<Point> points, vector<Point> markers, size_t n, size_t m) {
    vector<vector<char>> g(n, vector<char>(m, '.'));
    for(auto each: points) {
        g[(size_t)(each.x * n)][(size_t)(each.y * m)] = '*';
    }
    for(auto each: markers) {
        g[(size_t)(each.x * n)][(size_t)(each.y * m)] = 'o';
    }
    for (size_t i = 0; i < g.size(); ++i) {
        for (size_t j = 0; j < g[i].size(); ++j) {
            cout << g[i][j];
        }
        cout << endl;
    }
}

int main() {
    size_t n = 100;
    size_t m = 100;
    vector<Point> points;
    // set seed
    srand(chrono::high_resolution_clock::now().time_since_epoch().count());
    for(size_t i = 0; i < 20; i++) {
        points.push_back({(double)rand() / RAND_MAX, (double)rand() / RAND_MAX});
    }
    auto start = chrono::high_resolution_clock::now();
    vector<Point> ans = closest_pair_of_points(points);
    auto end = chrono::high_resolution_clock::now();
    cout << "Time: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << "ms" << endl;
    print_points(points, ans, n, m);
}

#endif