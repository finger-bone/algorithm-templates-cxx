#include <vector>

using namespace std;

struct DS {
    vector<int> fa, rank;
    DS(int n) {
        fa.assign(n, 0); rank.assign(n, 1);
        for(int i = 0; i < n; ++i) fa[i] = i;
    }
    int find(int x) {
        int cur = x, next = fa[cur];
        while(cur != next) {
            cur = next; next = fa[cur];
        }
        return cur;
    }
    void unify(int x, int y) {
        if(rank[x] >= rank[y]) swap(x, y);
        rank[y] += rank[x]; fa[find(x)] = find(y);
    }
};

struct Edge {
    int from, to, weight;
    Edge(int from, int to, int weight) : from(from), to(to), weight(weight) {}
    bool operator<(const Edge& rhs) const {
        return weight < rhs.weight;
    }
};

// g is represented by edge list
vector<Edge> kruskal(vector<Edge> g, int n) {
    DS ds(n);
    vector<Edge> mst;
    
    // sort the edges by weight
    // from the least to the most
    sort(g.begin(), g.end());
    for(auto e: g) {
        // if the edge connects two different components
        // then it must be in the mst
        // since the edges are sorted by weight and it must be the smallest edge that complete this work
        if(ds.find(e.from) != ds.find(e.to)) {
            mst.push_back(e);
            ds.unify(e.from, e.to);
        }
    }
    return mst;
}

#ifdef DEBUG

#include <iostream>

int main() {
    vector<Edge> g;
    g.push_back(Edge(0, 1, 1));
    g.push_back(Edge(0, 2, 2));
    g.push_back(Edge(0, 3, 3));
    g.push_back(Edge(1, 2, 2));
    g.push_back(Edge(1, 3, 3));
    g.push_back(Edge(2, 3, 4));
    vector<Edge> mst = kruskal(g, 4);
    for(auto e: mst) {
        cout << e.from << " " << e.to << " " << e.weight << endl;
    }
}

#endif