#include <vector>
#include <functional>

using namespace std;

struct Node {
    Node* left;
    Node* right;
    int val;
    int l;
    int r;
    Node(int val, int l, int r, Node* left = nullptr, Node* right = nullptr) :
        val(val), l(l), r(r), left(left), right(right) {}
};

struct SegmentTree
{
    Node* root;
    int n;
    SegmentTree(vector<int> raw) {
        n = raw.size();
        function<Node*(int, int)> f = [&](int l, int r) -> Node* {
            if(l == r) {
                return new Node(l < n ? raw[l] : 0, l, r);
            }
            int mid = (l + r) / 2;
            Node* left = f(l, mid);
            Node* right = f(mid + 1, r);
            Node* ret = new Node(left->val + right->val, l, r, left, right);
            return ret;
        };
        root = f(0, n - 1);
    }
    int query(int l, int r) {
        function<int(Node*, int, int)> f = [&](Node* node, int l, int r) -> int {
            if(node == nullptr) return 0;
            if(node->l > r || node->r < l) return 0;
            if(node->l >= l && node->r <= r) return node->val;
            return f(node->left, l, r) + f(node->right, l, r);
        };
        return f(root, l, r);
    }
    void update(int idx, int val) {
        function<void(Node*, int, int)> f = [&](Node* node, int idx, int val) {
            if(node->l == node->r) {
                node->val = val;
                return;
            }
            int mid = (node->l + node->r) / 2;
            if(idx <= mid) {
                f(node->left, idx, val);
            } else {
                f(node->right, idx, val);
            }
            node->val = node->left->val + node->right->val;
        };
        f(root, idx, val);
    }
};

#ifdef DEBUG

#include <iostream>

int main() {
    vector<int> raw = {1, 2, 3, 4, 5};
    SegmentTree st(raw);
    function<void(Node*, int)> print = [&](Node* node, int depth) {
        if(node == nullptr) return;
        print(node->right, depth + 1);
        for(int i = 0; i < depth; i++) cout << "  ";
        cout << node->val << endl;
        print(node->left, depth + 1);
    };
    print(st.root, 0);
    cout << st.query(0, 2) << endl;
    st.update(1, 10);
    print(st.root, 0);
    cout << st.query(0, 2) << endl;
    return 0;
}

#endif