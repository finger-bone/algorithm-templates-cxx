#include <vector>

using namespace std;

struct SegmentTree
{
    vector<int> val;
    int n;

    SegmentTree(const vector<int> &raw)
    {
        n = raw.size();

        // val starts from 1 so as to prevent -1 to appear in the query function
        // the count of total nodes is 2 * n - 1
        // so we allocate 2 * n + 1 space, + 1 for the 0th element that isn't used
        // however, this is the case when n is a power of 2, so we allocate 4 * n space, just in case
        val = vector<int>(4 * n, 0);

        // init the leaf nodes
        for (int i = 0; i < n; ++i) val[i + n] = raw[i];

        // calculate the internal nodes
        // because the upper nodes has lower index, we calculate from the bottom to the top
        for (int i = n - 1; i > 0; --i) val[i] = val[2 * i] + val[2 * i + 1];
    }

    // query the sum of l..=r, l r all starts from 0
    int query(int l, int r)
    {
        int ret = 0;

        // l += n so that it is located to the leaf node, same for r
        // when l > r, all calculations are done
        // every run of the loop will add the value of the needed node of a layer
        // and then move to the upper layer, so l /= 2, r /= 2
        for (l += n, r += n; l <= r; l /= 2, r /= 2)
        {
            /*
                an example tree for better explanation
                n = 4
                10
                6   4
                3 3 2 2
                index for the leaf
                4 5 6 7
                in the array
                {not used, 10, 6, 4, 3, 3, 2, 2}
                query(3, 6)
            */

            // for a certain layer, if l is odd, it points to the right child
            // so, l..=r doesn't contain the left child of l
            // thus, we add the value of l, and move l to the right
            // so it points to a left child
            // after l /= 2, it moves to the upper layer
            if (l % 2 == 1)
            {
                ret += val[l];
                ++l;
            }

            // same for r
            // but if r is even, it points to the left child
            // so l..=r doesn't contain the right child of r
            // so the value is added, then r moves to the left
            if (r % 2 == 0)
            {
                ret += val[r];
                --r;
            }
        }
        return ret;
    }

    // update the value of the i-th element to v, i starts from 0
    void update(int i, int v)
    {
        val[i + n] = v;
        // the affected nodes are the nodes on the path from the leaf to the root
        // that is, all nodes whose index is i or i's ancestor
        // the first should be i + n, but it's modified to v
        // so we start from (i + n) / 2
        for (i = (i + n) / 2; i > 0; i /= 2) val[i] = val[2 * i] + val[2 * i + 1];
    }
};

#ifdef DEBUG
int main()
{
    vector<int> raw = {1, 1, 1, 1, 1};
    SegmentTree st(raw);
    printf("%d\n", st.query(0, 4));
    st.update(1, 10);
    printf("%d\n", st.query(0, 4));
    return 0;
}
#endif