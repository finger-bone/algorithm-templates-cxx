// this implements the most ordinary binary search tree
#include <vector>
#include <functional>
using namespace std;

struct Node {
    int val;
    Node *left;
    Node *right;
    Node *parent;
    Node(int val, Node *left = nullptr, Node *right = nullptr, Node* parent = nullptr) : val(val), left(left), right(right), parent(parent) {}
    Node() : Node(0) {}
};

struct BinarySearchTree {
    Node *root;
    size_t size;

    BinarySearchTree() : root(nullptr), size(0) {}

    void insert(int val) {
        ++size;
        if(root == nullptr) {
            root = new Node(val);
            return;
        }
        Node *prev = nullptr;
        Node *cur = root;
        while(cur != nullptr) {
            prev = cur;
            if(val < cur->val) cur = cur->left;
            else cur = cur->right;
        }
        cur = new Node(val);
        cur->parent = prev;
        if(val < prev->val) prev->left = cur;
        else prev->right = cur;
    }

    Node* get(int val) {
        Node *cur = root;
        while(cur != nullptr) {
            if(cur->val == val) return cur;
            if(val < cur->val) cur = cur->left;
            else cur = cur->right;
        }
        return cur;
    }

    void remove(Node *n) {
        if(n == nullptr) return;
        --size;
        // there are 3 cases
        // 1. n has no child
        if(n->left == nullptr && n->right == nullptr) {
            if(n == root) root = nullptr;
            else {
                if(n->parent->left == n) n->parent->left = nullptr;
                else n->parent->right = nullptr;
            }
            delete n;
            return;
        }
        // 2. n has one child
        // an example of this case is
        //      *
        //     / \
        //    n   *
        //   /
        //  a
        // no matter n has left child or right child
        // we just need to replace n with its child
        if(n->left == nullptr ^ n->right == nullptr) {
            bool has_left = n->left != nullptr;
            Node* child = has_left ? n->left : n->right;
            // now just replace n with its child
            // however, practically, we replace the val then change the structure
            n->val = child->val;
            delete child;
            return;
        }
        // if n has two children
        // we need to find a node to substitute n
        // usually, we use the minimum value of the number that is greater than n
        // or the maximum value of the number that is smaller than n
        // here we use the maximum value of the number that is smaller than n
        // that is, the rightest node of the left tree of n
        // (alternatively, the leftest node of the right tree of n)
        // so that the tree is more balanced
        // then delete that node
        // then set correct links
        // for example
        //           *
        //          / \
        //         n   *
        //        / \
        //       3   9
        //      / \
        //     2   4
        // because the rightest node of a left tree is bound to be a leaf
        // and notice that after replacing the structure is still a binary search tree
        // so we can just delete that node
        if(n->left != nullptr && n->right != nullptr) {
            Node *cur = n->left;
            while(cur->right != nullptr) cur = cur->right;
            n->val = cur->val;
            if(cur->parent != nullptr) cur->parent->right = nullptr;
            delete cur;
            return;
        }
    }

    vector<int> sorted() {
        vector<int> ret;
        ret.reserve(size);
        // mid-order traversal
        function<void(Node*)> mid_order = [&](Node *n) {
            if(n == nullptr) return;
            mid_order(n->left);
            ret.push_back(n->val);
            mid_order(n->right);
        };
        mid_order(root);
        return ret;
    }
};

#ifdef DEBUG

#include <iostream>

int main() {
    BinarySearchTree bst = BinarySearchTree();
    vector<int> v = {5, 3, 7, 2, 4, 6, 8};
    for(int i = 0; i < v.size(); ++i) bst.insert(v[i]);
    vector<int> sorted = bst.sorted();
    for(int i = 0; i < sorted.size(); ++i) {
        cout << sorted[i] << " ";
    }
    cout << endl;
    bst.remove(bst.get(5));
    sorted = bst.sorted();
    for(int i = 0; i < sorted.size(); ++i) {
        cout << sorted[i] << " ";
    }
    cout << endl;
    return 0;
}

#endif