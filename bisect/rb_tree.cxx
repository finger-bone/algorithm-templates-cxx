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

// we define some macros to simplify repeating codes
// null
#define N(n) ((n) == (nullptr))
// if null
#define IN(n) if((n) == (nullptr))
// not null
#define NN(n) ((n) != (nullptr))
// if not null
#define INN(n) if((n) != (nullptr))
// set null
#define SN(n) ((n) = (nullptr))
// we also don't want to handle color of nullptr every time
// is_black
#define B(n) (((n) == nullptr) ? true : ((n)->black))
struct RBTree {
    Node* root;
    size_t size;
    RBTree() : root(nullptr), size(0) {}
    void left_rotate(Node *n) {
        IN(n) return;
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
        INN(b) b->right = f;
        INN(b) b->left = n;
        INN(b) b->parent = p;
        INN(e) e->parent = n;
        INN(f) f->parent = b;
        // there maybe cases that such rotation changes the root
        IN(p) {
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
    void right_rotate(Node *n) {
        IN(n) return;
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
        Node *c = NN(b) ? b->left : nullptr;
        Node *d = NN(b) ? b->right : nullptr;
        // we are only sure that n is not nullptr
        n->parent = b;
        n->left = d;
        INN(b) b->parent = p;
        INN(b) b->right = n;
        INN(b) b->left = c;
        INN(d) d->parent = n;
        INN(c) c->parent = b;
        // there maybe cases that such rotation changes the root
        IN(p) {
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

    void rotate(Node *n, bool left) {
        if(left) left_rotate(n);
        else right_rotate(n);
    }

    void insert(int val) {
        ++size;
        // first, insert the node the same way as binary search tree
        IN(root) {
            root = new Node(val, true);
            return;
        }
        Node *prev = nullptr;
        Node *cur = root;
        while(NN(cur)) {
            prev = cur;
            if(val < cur->val) cur = cur->left;
            else cur = cur->right;
        }
        cur = new Node(val);
        cur->parent = prev;
        if(val < prev->val) prev->left = cur;
        else prev->right = cur;
        // now, we need to fix the tree
        // the tree looks like this now
        //          g
        //         / \
        //        p   u
        //       / \
        //      n   *
        // the only problem here is that, n and p could be both red
        // we need to fix this
        function<void(Node*, bool)> fix = [&](Node* n, bool p_is_left) {
            // n can be null
            IN(n) return;
            // first we find p, u, g
            // however, g maybe nullptr
            // in this case, since p is root, root is black, we just leave the tree as it is
            Node *p = n->parent;
            Node *g = p->parent;
            IN(g) return;
            Node *u = p_is_left ? g->right : g->left;
            bool n_is_left = p->left == n;
            // 1. p is black
            // we don't need to do anything, it's already balanced
            // 2. p is red, n-p is of same direction as p-g
            // the reason why n position matters is that
            // we need to rotate g, and after rotation
            // the new position of n depends on it,
            // now n and p are now both red
            // the way to fix depends on u, because p is red, g must be black
            // when p is the left child of g
            // the tree is like this
            //          g
            //         / \
            //        p   u
            //       / \
            //      n   *
            // to do the following operations, we color p black, g red, n stays red
            // because, in this way, all paths through p has x black nodes
            // and g-u has x-1 black nodes, which is simpler to deal with
            // however, if u is red, we can't do this
            // 2.1. p is red, n-p is of same direction as p-g, u is black
            // then we need to get rid of the extra black node in n
            // we can do this by rotating g right
            // after rotation, the tree becomes
            //          p
            //         / \
            //        n   g
            //           / \
            //          *   u
            // similarly, if p is the right child of g
            // we rotate g left, color p black, g red, n stays red
            if(!B(p) && B(u) && n_is_left == p_is_left) {
                INN(p) p->black = true;
                INN(g) g->black = false;
                rotate(g, !p_is_left);
                return;
            }
            // 2.2. p is red, n-p is of same direction as p-g, u is red
            // in other cases, we want the root to be black
            // so that it won't violate the rule after taking the whole tree into consideration
            // but now, we need to move up, since the sub-tree can't balance itself
            // now we color g red, p and u black
            // this is a balanced tree, but the root is red
            // we just need to fix upwards, taking g as the new n
            if(!B(p) && !B(u)) {
                INN(g) g->black = false;
                INN(p) p->black = true;
                INN(u) u->black = true;
                // g maybe root, so we need to do null check
                // don't worry- if g is root, coloring g black won't violate the rule
                // it's just there may be null pointer exceptions
                IN(g->parent) {
                    g->black = true;
                    return;
                }
                fix(g, g->parent->left == g);
                return;
            }

            // 3. p is red, n-p is of opposite direction as p-g
            // the tree is like this, if p is the left child of g
            //          g
            //         / \
            //        p   u
            //       / \
            //      *   n
            // now previous operations won't work, because n won't be in the right position
            // we want n-p to be of same direction as p-g
            // so we rotate p left
            //          g
            //         / \
            //        n   u
            //       /
            //      p
            //     /
            //    *
            // now, the tree is still balanced, but n-p are of same color
            // now, treat p as n, and n as p, we can apply fix function again
            if(!B(p) && n_is_left != p_is_left) {
                rotate(p, p_is_left);
                fix(p, !n_is_left);
                return;
            }
        };
        fix(cur, cur->parent->left == cur);
    }

    Node *get(int val) {
        // the same as binary search tree
        Node *cur = root;
        while(NN(cur)) {
            if(cur->val == val) return cur;
            if(val < cur->val) cur = cur->left;
            else cur = cur->right;
        }
        return cur;
    }

    void remove(Node* n) {
        // n maybe null
        IN(n) return;
        // first, reduce the size
        --size;
        // now, here we start the real deletion
        // we classify the cases by the number of children, and the color
        int num_children = NN(n->left) + NN(n->right);
        bool is_n_black = n->black;
        bool has_left = NN(n->left);
        // we take the following view at this problem
        // we always remove a leaf node
        // when we aren't removing a leaf node
        // we can convert it
        // just like how we did in bst
        // when n has children
        // we replace n with the left-sub-tree rightest or right-sub-tree leftest node, called sub
        // then we remove the sub
        // this will always end up with a leaf node
        // so first, we consider cases in which n has children
        if(num_children != 0) {
            if(has_left) {
                Node *sub = n->left;
                while(NN(sub->right)) sub = sub->right;
                n->val = sub->val;
                remove(sub);
            }
            else {
                Node *sub = n->right;
                while(NN(sub->left)) sub = sub->left;
                n->val = sub->val;
                remove(sub);
            }
            return;
        }
        // now, we deal with leaf node, num_children == 0
        // there are only two cases, from the surface
        // now, if n is red
        // this is simple, obviously, we can just delete it
        if(!is_n_black) {
            // we need to handle the case where n is root
            INN(n->parent) {
                if(n->parent->left == n) {
                    SN(n->parent->left);
                }
                else {
                    SN(n->parent->right);
                }
            }
            else {
                SN(root);
            }
            // delete n
            delete n;
            return;
        }



        // now, n is black and has no children
        // this is hard
        // following good coding styles
        // we should have another if here
        // but I don't want an extra indent and braces and everything
        // so, if(num_children == 0 && is_n_black) is omitted
        // first, deal with the case where n is root
        if(root == n) {
            SN(root);
            delete n;
            return;
        }
        // now, n is black and has no children, and it is not a root
        // we first apply the deletion
        // we will need following vars for later
        bool is_n_left = n->parent->left == n;
        Node *p = n->parent;
        Node *s = is_n_left ? p->right : p->left;
        if(is_n_left) {
            SN(n->parent->left);
        }
        else {
            SN(n->parent->right);
        }
        delete n;
        // now, we need to separate the cases by the color of n's sibling
        // to better illustrate the reason
        // we draw a tree
        //          p
        //         / \
        //        n   s
        // p for parent, s for sibling
        // after we delete n
        // the tree is imbalanced
        // to balance it, we must add an extra black node to p-n path
        // the source of this extra black node could be
        // sibling's left child, sibling's right child, or sibling itself
        // or the parent
        // if there can't borrow an extra black node from this sub-tree
        // we move up to look for it
        // if we can't find it, we add an extra black node to the whole tree
        // and this node becomes the new root
        // now, we separate the cases by the color of sibling
        // since we may need to move up, and we don't want to repeat the code
        // we define a function
        // the names are fully spelt to avoid variable name conflicts and provides better clarity
        // when calling fix(p, n)
        // it fixes the sub-tree whose root is p
        // that is,
        //          p
        //         / \
        //        *   s
        //  in which, compared with the paths from p to s, paths from p to * lacks a black node
        function<void(Node*, Node*, bool)> fix = [&](Node *parent, Node* sibling, bool lack_in_left) {
            // 1. sibling is black
            // this then specifies into following ones
            // 1.1. sibling is black and has a red child that is of the same direction as n
            // for example
            //          p
            //         / \
            //        n   s
            //           / \
            //          * [R]
            //      x-1 x  x
            // we want an extra black node into p-n, so s would be it
            // so rotate left p
            //          s
            //         / \
            //        p   [R]
            //      / \
            //     n   *
            //     x   x   ?
            // because we hadn't consider the color of p, [R] is a ?
            // if p is black, ? is x, we are done.
            // tragically, if p is red, ? is x-1
            // however, if we color s the original p's color
            // and color p black
            // this would solve both cases
            // if s was the left child of p, we rotate right p
            // so we define some functions to simplify the code
            function<Node*(Node*,bool)> get_child = [&](Node *n, bool left) {
                if(left) return n->left;
                else return n->right;
            };
            if(B(sibling) && !B(get_child(sibling, !lack_in_left))) {
                // first color, then rotate
                sibling->black = parent->black;
                parent->black = true;
                rotate(parent, lack_in_left);
                return;
            }
            // 1.2. sibling is black and has a red child that is of the opposite direction as n
            // for example
            //          p
            //         / \
            //        n   s
            //           / \
            //         [R]  *
            // now if we rotate right s
            //          p
            //         / \
            //        n   [R]
            //           / \
            //          *   s
            //      x-1 ?   x
            // now, we color [R] as the original color of s, and color s red
            // this becomes case 1.1
            if(B(sibling) && !B(get_child(sibling, lack_in_left))) {
                sibling->black = false;
                get_child(sibling, lack_in_left)->black = true;
                rotate(sibling, !lack_in_left);
                fix(p, get_child(p, lack_in_left), lack_in_left);
                return;
            }
            // 1.3. sibling is black and has no red child
            // this depends on the color of parent, if parent is red, we can borrow the black from parent
            // however, if it is not, we need extra operations
            // 1.3.1. sibling is black and has no red child, parent is red
            if(B(sibling) && !B(parent)) {
                sibling->black = false;
                parent->black = true;
                return;
            }
            // 1.3.2 sibling is black and has no red child, parent is black
            // this is bad, but also, surprisingly, simple
            // there can't find a black node to borrow from this sub-tree
            // so we search up, make the whole tree lack a black node
            if(B(sibling) && B(parent)) {
                // after coloring sibling red, every path from current root lacks a black node
                sibling->black = false;
                // now, fix up
                fix(parent->parent, parent, parent->parent->left == parent);
                return;
            }
        };
        fix(p, s, is_n_left);
    }
};

#ifdef DEBUG

#include <iostream>
#include <vector>

using namespace std;

int main() {
    RBTree rot_test_tree;
    vector<int> test_data = {0, 1, 2, 3, 4, 5, 6};
    for(auto i : test_data) {
        rot_test_tree.insert(i);
    }
    for(auto i : test_data) {
        rot_test_tree.remove(rot_test_tree.get(i));
        cout << "after removing " << i << endl;
        cout << "mid order: ";
        function<void(Node*)> mid_order = [&](Node *n) {
            IN(n) return;
            mid_order(n->left);
            cout << n->val << " ";
            mid_order(n->right);
        };
        mid_order(rot_test_tree.root);
        cout << endl;
        cout << endl;
    }
    return 0;
}

#endif