#include <functional>

using namespace std;

// here are some theories about red-black tree
// every node is either red or black
// root is black
// nulls are black (here we treat null as a node, because it indicates the case where the target isn't in the tree)
// if a node is red, its children are black
// every path from a node to any sub-leaf has the same number of black nodes
// the last rule makes the tree more balanced
// so when we say balance the tree, we mean to follow the last rule

// operations
// left rotate a node
//  x is the node to be rotated
//  y is the right child of x
//  y's left child becomes x's right child
//  y's parent becomes x's parent
//  x's parent becomes y
//  x's right child becomes y's left child
// for example
//      x
//     / \
//    a   y
//       / \
//      b   c
// after left rotate
//      y
//     / \
//    x   c
//   / \
//  a   b
// a easy way to remember this is to draw a circle around x and y
// then rotate the circle
// make the original circle become a line
// then keep the order of their original children
// right rotate is the same as left rotate, but reversed
// rotate left or right doesn't change the binary search tree property
// for example
//     5
//    / \
//   3   7
// rotate right
//     3
//      \
//       5
//       \
//        7
// it can be deduced with the order of the numbers of the previous tree
// proof is omitted here

struct Node {
    bool black;
    int val;
    Node *left, *right, *parent;
    Node(int val, bool black = false, Node *left = nullptr, Node *right = nullptr, Node *parent = nullptr) : val(val), black(black), left(left), right(right), parent(parent) {}
};

// to avoid saying if(n != nullptr) every time
// we define a macro
#define NN(n) if((n) != (nullptr))
// we also don't want to handle color of nullptr every time
#define C(n) (((n) == nullptr) ? true : ((n)->black))
struct RBTree {
    Node* root;
    size_t size;
    RBTree() : root(nullptr), size(0) {}
    void rotate_left(Node *n) {
        if(n == nullptr) return;
        // consider the following tree
        //              p
        //             / \
        //            n   *
        //           / \
        //          a   b
        //         / \ / \
        //        c  d e  f
        // after left rotate
        //              p
        //             / \
        //            b   *
        //           / \
        //          n   f
        //         / \
        //        a   e
        //       / \
        //      c   d
        // the link between
        // b and f, a and c, a and d, a and n doesn't change
        // so we only need to change the nodes n, b, e, f, p
        // e, f stays as leaves
        Node *p = n->parent;
        Node *b = n->right;
        Node *e = b->left;
        Node *f = b->right;
        // we are only sure that n is not nullptr
        n->right = e;
        n->parent = b;
        NN(b) b->right = f;
        NN(b) b->left = n;
        NN(b) b->parent = p;
        NN(e) e->parent = n;
        NN(f) f->parent = b;
        // there maybe cases that such rotation changes the root
        if(p == nullptr) {
            root = b;
        }
        else {
            if(p->left == n) {
                p->left = b;
            }
            else {
                p->right = b;
            }
        }
    }
    void rotate_right(Node *n) {
        if(n == nullptr) return;
        // consider the following tree
        //              p
        //             / \
        //            *   n
        //               / \
        //              b   a
        //             / \ / \
        //            c  d e  f
        // after right rotate
        //              p
        //             / \
        //            *   b
        //               / \
        //              c   n
        //                 / \
        //                d   a
        //                   / \
        //                  e   f
        Node *p = n->parent;
        Node *b = n->left;
        Node *c = b != nullptr ? b->left : nullptr;
        Node *d = b != nullptr ? b->right : nullptr;
        // we are only sure that n is not nullptr
        n->parent = b;
        n->left = d;
        NN(b) b->parent = p;
        NN(b) b->right = n;
        NN(b) b->left = c;
        NN(d) d->parent = n;
        NN(c) c->parent = b;
        // there maybe cases that such rotation changes the root
        if(p == nullptr) {
            root = b;
        }
        else {
            if(p->left == n) {
                p->left = b;
            }
            else {
                p->right = b;
            }
        }
    }

    void insert(int val) {
        ++size;
        // first, insert the node the same way as binary search tree
        if(root == nullptr) {
            root = new Node(val, true);
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
        // now, we need to fix the red-black tree property
        // because fixing the red-black tree property would make sure that
        // for every path from a node to a leaf has the same number of black nodes
        // so the tree is balanced
        // we do so by rotating and recoloring
        // by default, the new node is red
        // because this doesn't hurts equal-black-nodes property
        // or else, we have more cases to cover
        // and now, we need to fix the tree
        // there are following cases that we need to fix
        // we move the fixing process to a function for convenience
        // because we'll need recursive calls
        function<void(Node*)> fix = [&](Node* n) {
            // n may be nullptr
            if(n == nullptr) return;
            // if the node is root
            // we just need to color it black, it's done
            if(n->parent == nullptr) {
                n->black = true;
                return;
            }
            // code below would use grandparent
            // so we need to handle the case where grandparent == nullptr manually
            // but since the root is black
            // we can assert that the new node must be red, which is out default setting
            // so no need to handle this case
            if(n->parent->parent == nullptr) return;

            // below
            // g stands for grandparent
            // u stands for uncle
            // p stands for parent
            // n stands for current node

            Node *p = n->parent;
            Node *g = p->parent;
            Node *u = g->left == p ? g->right : g->left;

            // there is an extra point to notice
            // when we re-balance a tree after inserting a new node
            // the count of the black nodes in the path from the root to the leaf
            // must stay the same or change by 1

            // now, consider a sub-tree whose root is g
            // first, we balance this tree as if it is the whole
            // after doing so, the blacks on path either stay or plus one
            // if it stays, well done, the tree is now balanced
            // because the count of the other paths doesn't change, and this one doesn't change as well
            // however, if it changes by one
            // we need to force it to balance
            // that is, we color the root red
            // now, if we take the g as the new n
            // this becomes a same problem, that is
            // there is a red-black tree
            // but there appears two adjacent red nodes, or different black nodes count,
            // balance the tree
            // so recursion would solve it.

            // the following cases are tricky
            // but bear the above in mind.

            // below we assume n is red

            // 1. p is red, u is red
            // for example
            //          g
            //         / \
            //        p   u
            //      / \
            //     n   *
            // in such case, inserting n does plus one on the count
            // so we color g red, thus p, u black
            // notice that if n is red, then this sub-tree is balanced
            // wether n is the left child or the right child of p doesn't matter
            // thus
            if(!C(p) && !C(u)) {
                NN(p) p->black = true;
                NN(u) u->black = true;
                NN(g) g->black = false;
                // now, we need to fix the tree
                // because g is red, and p is black
                // so we need to fix the tree as if p is the new node
                // and we do so by recursion
                fix(g);
                return;
            }
            // 2. p is red, u is black, n is left child
            // for example
            //          g
            //         / \
            //        p   u
            //      / \
            //     n   *
            // notice after balancing, g must be red, so p must be black
            // here to count the number of black nodes
            // we adds a number to the graph
            // x acts as a variable, originally, from g to any node, there was x black nodes(excluding g)
            //          g
            //         / \
            //        p   u
            //      / \
            //     n   *
            //    x+1 x+1 x
            // so, to make the sub-tree balanced, we rotate right the g
            // it comes
            //          p
            //         / \
            //        n   g
            //           / \
            //          *   u
            // count doesn't change and the root is black, done!
            if(!C(p) && C(u) && p->left == n) {
                rotate_right(g);
                NN(p) p->black = true;
                NN(g) g->black = false;
                return;
            }
            // 3. p is red, u is black, n is right child
            // for example
            //          g
            //         / \
            //        p   u
            //      / \
            //     *   n
            // now, g must become red, so p must be black
            //          g
            //         / \
            //        p   u
            //      / \
            //     *   n
            //    x-1 x-1 x
            // now, rotate left the g
            //          u
            //         / \
            //        g   *
            //      / \
            //     p   *
            //    / \
            //   *   n
            // the additional two stars are the original u's children
            // now, this is a balanced tree, because the count doesn't change, and the root is black
            if(!C(p) && C(u) && p->right == n) {
                rotate_left(g);
                NN(g) g->black = false;
                NN(u) u->black = true;
                return;
            }
        };
        fix(cur);
    }

    Node *get(int val) {
        // the same as binary search tree
        Node *cur = root;
        while(cur != nullptr) {
            if(cur->val == val) return cur;
            if(val < cur->val) cur = cur->left;
            else cur = cur->right;
        }
        return cur;
    }

    void remove(Node* n) {
        // first consider deleting the root
        if(n == root) {
            root = nullptr;
            delete n;
            return;
        }
        // now we divide the removing operation into to parts
        // first, find a node to replace n
        // then, remove the node
        // after doing so, maintain the red-black tree property
        // first, find the substituion: use sub as the substituion
        Node *sub = nullptr;
        // same as binary search tree
        if(n->left != nullptr ^ n->right != nullptr) sub = n->left == nullptr ? n->left : n->right;
        if(n->left != nullptr && n->right != nullptr) {
            // find the rightest node of the left tree of n
            sub = n->left;
            while(sub->right != nullptr) sub = sub->right;
        }
        // now, we have to consider the color of the sub and the n
        // 1. if sub is nullptr, n is red, just delete n, because n is a leaf
        if(sub == nullptr && !C(n)) {
            if(n->parent->left == n) n->parent->left = nullptr;
            else n->parent->right = nullptr;
            delete n;
            return;
        }
        // 2. if sub is red, n is whatever
        // just replace the value, then delete sub
        if(!C(sub)) {
            n->val = sub->val;
            if(sub->parent->left == sub) sub->parent->left = nullptr;
            else sub->parent->right = nullptr;
            delete sub;
            return;
        }
        // the cases below require extra balancing
        // still keep in mind that
        // root is black
        // if we can't balance, color the root red, the balance upwards
        // 3. if sub is black(maybe nullptr), n is red
        // for example, s for sub
        //          *
        //         / \
        //        n   * 
        //       / \
        //      *   *
        //     / \
        //    a   s
    }
};

#define DEBUG

#ifdef DEBUG

#include <iostream>
#include <vector>

using namespace std;

int main() {
    RBTree rot_test_tree;
    vector<int> test_data = {0, 1, 2, 3, 4, 5, 6, 7};
    for(auto i : test_data) {
        rot_test_tree.insert(i);
    }
    return 0;
}

#endif