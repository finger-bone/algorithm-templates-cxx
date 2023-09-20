#include <vector>

using namespace std;

#ifdef CLEAR_VERSION
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
        for (int i = 0; i < n; ++i)
        {
            val[i + n] = raw[i];
        }

        // calculate the internal nodes
        // because the upper nodes has lower index, we calculate from the bottom to the top
        for (int i = n - 1; i > 0; --i)
        {
            val[i] = val[2 * i] + val[2 * i + 1];
        }
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
        // i += n + 1 so that it is located to the leaf node
        i += n + 1;

        // update the value of the leaf node
        val[i] = v;

        // update the value of the internal nodes
        // because the upper nodes has lower index, we calculate from the bottom to the top
        // the same as the init function
        for (i /= 2; i > 0; i /= 2)
        {
            val[i] = val[2 * i] + val[2 * i + 1];
        }
    }
};
#endif

#ifdef QUICK_VERSION
// the updates are cached into the lazy array
// when calling query, the cached updates are applied to the val array
// also uses bits operations and memcpy to speed up

#include <cstdlib>

struct SegmentTree
{
    vector<int> val;
    vector<int> lazy;
    bool modified;
    int n;

    SegmentTree(const vector<int> &raw)
    {
        n = raw.size();
        val = vector<int>(n << 2);
        memcpy(&val[n], &raw[0], n * sizeof(int));
        for (int i = n - 1; i > 0; --i)
        {
            val[i] = val[i << 1] + val[i << 1 | 1];
        }
        lazy = vector<int>(n << 2);
        memcpy(&lazy[0], &val[0], lazy.size() * sizeof(int));
        modified = false;
    }

    int query(int l, int r)
    {
        if (modified)
        {
            memcpy(&val[0], &lazy[0], lazy.size() * sizeof(int));
            modified = false;
        }
        int ret = 0;
        for (l += n, r += n; l <= r; l >>= 1, r >>= 1)
        {
            if (l & 1)
            {
                ret += val[l];
                ++l;
            }
            if (!(r & 1))
            {
                ret += val[r];
                --r;
            }
        }
        return ret;
    }

    void update(int i, int v)
    {
        i += n;
        lazy[i] = v;
        for (i >>= 1; i > 0; i >>= 1)
        {
            lazy[i] = lazy[i << 1] + lazy[i << 1 | 1];
        }
        modified = true;
    }
};
#endif

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