#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;

struct E {
    int from;
    int to;
    int cap;
    int cur;
    E(int f, int t, int c, int cur): from(f), to(t), cap(c), cur(cur) {}
    E(): from(-1), to(-1), cap(-1), cur(-1) {}
};

// O(E)
vector<E> get_residual(const vector<E> origin) {
    vector<E> residual;
    residual.reserve(2 * origin.size());
    for(E each: origin) {
        if(each.cap - each.cur > 0) {
            residual.push_back({each.from, each.to, each.cap - each.cur, 0});
        }
        if(each.cur > 0) {
            residual.push_back({each.to, each.from, each.cur, 0});
        }
    }
    return residual;
}

// O(E)
vector<vector<int>> get_cap_mtx(const vector<E> g, int n) {
    vector<vector<int>> cap(n, vector<int>(n, 0));
    for(E e: g) {
        cap[e.from][e.to] = e.cap;
    }
    return cap;
}

// O(V)
tuple<vector<E>, int> get_path_and_cap(const vector<E> g, int n) {
  // g is a residual network, find a path from 0 to n - 1
  // use bfs
    vector<int> prev(n, -1);
    queue<int> q;
    q.push(0);
    vector<vector<int>> cap = get_cap_mtx(g, n);
    while(!q.empty()) {
        int cur = q.front();
        q.pop();
        for(int i = 0; i < n; ++i) {
        if(cap[cur][i] > 0 && prev[i] == -1) {
            prev[i] = cur;
            q.push(i);
        }
        }
    }
    if(prev[n - 1] == -1) {
        return {vector<E>(), 0};
    }
    vector<E> path;
    int min_cap = 1e9;
    for(int i = n - 1; i != 0; i = prev[i]) {
        min_cap = min(min_cap, cap[prev[i]][i]);
        path.push_back({prev[i], i, 0, min_cap});
    }
    return {path, min_cap};
}

bool increase_flow(vector<E>& g, int n) {
    // O(E)
    vector<E> residual = get_residual(g);
    // O(V)
    vector<E> path;
    int min_cap;
    tie(path, min_cap) = get_path_and_cap(residual, n);
    if(min_cap == 0) {
        return false;
    }
    // O(E ** 2)
    for(E& e: g) {
        for(E& p: path) {
        if(e.from == p.from && e.to == p.to) {
            e.cur += min_cap;
        }
        if(e.from == p.to && e.to == p.from) {
            e.cur -= min_cap;
        }
        }
    }
    return true;
}

int main() {
    vector<E> flows;
    flows.push_back({0, 1, 16, 0});
    flows.push_back({0, 3, 13, 0});
    flows.push_back({1, 2, 12, 0});
    flows.push_back({2, 3, 9, 0});
    flows.push_back({3, 1, 4, 0});
    flows.push_back({3, 4, 14, 0});
    flows.push_back({4, 2, 7, 0});
    flows.push_back({4, 5, 4, 0});
    flows.push_back({2, 5, 20, 0});
    // O(V E ** 2)
    while (increase_flow(flows, 6)) {}
    for(E e: flows) {
        if(e.cur == 0) {
        continue;
        }
        cout << e.from << " " << e.to << " " << e.cur << endl;
    }
    int total = 0;
    for(E e: flows) {
        if(e.from == 0) {
        total += e.cur;
        }
    }
    cout << total << endl;
    return 0;
}
