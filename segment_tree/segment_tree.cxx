#include <stack>

using namespace std;

struct Node {
    Node* left;
    Node* right;
    int val;
};

struct SegmentTree
{
public:
    Node* root;
    bool modified;
    int n;

    SegmentTree(const vector<int> raw) {
        n = raw.size();
        root = new Node();

        // now, build up the tree
        build(root, 0, n - 1, raw);

        modified = false;
    }

    void build(Node* node, int l, int r, const vector<int> &raw) {
        // this indicates that the node is a leaf node
        if(l == r) {
            node->val = raw[l];
            return;
        }

        int mid = (l + r) / 2;
        node->left = new Node();
        node->right = new Node();
        build(node->left, l, mid, raw);
        build(node->right, mid + 1, r, raw);
        node->val = node->left->val + node->right->val;
    }

    // this modifies only the leaf
    // evaluation only happens in query to allow lazy propagation and large modification
    void update(int i, int val) {
        int l = 0;
        int r = n - 1;
        Node* node = root;
        
        // look for the i-th leaf
        // just like binary search
        while(l != r) {
            int mid = (l + r) / 2;
            if(i <= mid) {
                r = mid;
                node = node->left;
            } else {
                l = mid + 1;
                node = node->right;
            }
        }

        node->val = val;
    }
};
