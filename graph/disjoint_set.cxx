#include <vector>
#include <algorithm>

using namespace std;

struct DS {
    vector<int> fa;
    // here we use size as the rank to make the tree more balanced
    // so as to improve performance
    // there are better ways to do this, but this is the simplest
    vector<int> rank;

    DS(int n) {
        fa.resize(n);
        rank.resize(n);
        for(int i = 0; i < n; i++) {
            fa[i] = i;
        }
        fill(rank.begin(), rank.end(), 1);
    }

    int find(int x) {
        // for root node, fa[x] == x
        int cur = x;
        int next = fa[cur];
        while(cur != next) {
            cur = next;
            next = fa[cur];
        }
        return cur;
    }

    void unify(int x, int y) {
        // we would like to make the tree more balanced
        // that is, we want fewer nodes at the deeper level
        if(rank[x] >= rank[y]) {
            swap(x, y);
        }
        fa[find(x)] = find(y);
        rank[y] += rank[x];
    }
};

#ifdef DEBUG

#include <iostream>

int main() {
    DS ds(5);
    ds.unify(0, 1);
    ds.unify(1, 2);
    ds.unify(3, 4);
    for(int i = 0; i < 5; i++) {
        cout << ds.find(i) << endl;
    }
}

#endif