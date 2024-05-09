#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

struct Point {
    double x, y;
    Point() : x(0), y(0) {};
    Point(double x, double y) : x(x), y(y) {};
};

bool cmp(const Point &a, const Point &b) {
    return a.x < b.x || (a.x == b.x && a.y < b.y);
}

double cross_product(Point a, Point b, Point c) {
    double y1 = a.y - b.y;
    double y2 = a.y - c.y;
    double x1 = a.x - b.x;
    double x2 = a.x - c.x;
    return y2 * x1 - y1 * x2;
}

vector<Point> get_convex_hull(vector<Point> points) {
    stack<Point> hull;
    vector<char> used(points.size(), false);
    
    vector<Point> res;
    while(!hull.empty()) {
        res.push_back(hull.top());
        hull.pop();
    }
    return res;
}

#define DEBUG
#ifdef DEBUG

#include <iostream>

void print_points(vector<Point> points, vector<Point> hull, int n, int m) {
    vector<vector<char>> field(n, vector<char>(m, '.'));
    for(auto p : points) {
        field[p.x][p.y] = 'o';
    }
    for(auto p : hull) {
        field[p.x][p.y] = 'x';
    }
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            cout << field[i][j];
        }
        cout << endl;
    }
}

int main() {
    vector<Point> ps = {
        Point(1, 4),
        Point(2, 3),
        Point(2, 3),
        Point(4, 2),
        Point(1, 4),
        Point(3, 1),
        Point(4, 9),
        Point(5, 6),
        Point(3, 4),
        Point(7, 2),
        Point(8, 4),
        Point(9, 3),
        Point(6, 5),
        Point(7, 7),
        Point(8, 8),
    };
    vector<Point> hull = get_convex_hull(ps);
    print_points(ps, hull, 10, 10);
    return 0;
}

#endif