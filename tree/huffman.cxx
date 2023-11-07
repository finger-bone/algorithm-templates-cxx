#include <queue>
#include <vector>
#include <utility>
#include <functional>
#include <unordered_map>

using namespace std;

struct Node {
    Node *left, *right;
    char val;
    int freq;
    Node() : left(nullptr), right(nullptr), val('\0'), freq(0) {}
    Node(char val, int freq) : left(nullptr), right(nullptr), val(val), freq(freq) {}
    Node(Node *left, Node *right) : left(left), right(right), val('\0'), freq(left->freq + right->freq) {}
};

Node *construct(const vector<pair<char, int>> &freq) {
    auto cmp = [](Node *a, Node *b) { return a->freq > b->freq; };
    priority_queue<Node*, vector<Node*>, decltype(cmp)> pq(cmp);
    for (auto &[val, freq] : freq) pq.push(new Node(val, freq));
    while (pq.size() > 1) {
        Node *left = pq.top(); pq.pop();
        Node *right = pq.top(); pq.pop();
        pq.push(new Node(left, right));
    }
    return pq.top();
}

unordered_map<char, int> get_encoding(Node *root) {
    unordered_map<char, int> res;
    function<void(Node*, int)> dfs = [&](Node *cur, int code) {
        if (cur->left == nullptr && cur->right == nullptr) {
            res[cur->val] = code;
            return;
        }
        dfs(cur->left, code << 1);
        dfs(cur->right, (code << 1) | 1);
    };
    dfs(root, 0);
    return res;
}

#ifdef DEBUG

#include <iostream>
#include <bitset>

int main() {
    vector<pair<char, int>> freq = {
        {'a', 45},
        {'b', 13},
        {'c', 12},
        {'d', 16},
        {'e', 9},
        {'f', 5}
    };
    Node *root = construct(freq);
    auto encoding = get_encoding(root);
    for (auto &[val, code] : encoding) {
        cout << val << " " << code << endl;
        // convert code to binary without prefix 0
        auto b = bitset<8>(code);
        bool prefix = true;
        for (int i = 7; i >= 0; --i) {
            if (b[i] == 1) prefix = false;
            if (!prefix) cout << b[i];
        }
        cout << endl;
    }
    return 0;
}

#endif