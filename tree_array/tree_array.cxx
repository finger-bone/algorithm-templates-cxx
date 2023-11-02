#include <vector>

#define LB(x) ((x) & (-(x)))

using namespace std;

struct TreeArray {
    vector<int> val;
    int n;
    TreeArray(const vector<int>& raw) {
        n = raw.size();
        val = vector<int>(n + 1);

        // first, copy the raw array to the val array
        for (int i = 0; i < n; ++i) val[i + 1] = raw[i];

        // then, update the val array
        for (int i = 1; i <= n; ++i)
        {

            // in val, val[i] should be the sum of raw whose index in binary is the prefix of i
            // so, if i + LB(i), it is the parent of i
            // all parents of i should add val[i]
            // however, because it is done in the loop, we shouldn't use while below
            // since the parent of i should adds val[i] only once,
            // so the grand parent of i adds val[i] only once, and so on
            int j = i + LB(i);
            if (j <= n) val[j] += val[i];
        }
    }

    // query the sum from 1..=i, starts from 1
    int query(int i)
    {
        int ret = 0;
        while (i > 0)
        {
            // add val[i] to the result, because val[i] is the sum of raw whose index in binary is the prefix of i
            // it is within the range of 1..=i
            ret += val[i];

            // i -= LB(i) is the parent of i
            i -= LB(i);
        }
        return ret;
    }

    // update the value of raw[i]
    void update(int i, int diff)
    {
        while (i <= n)
        {
            val[i] += diff;
            i += LB(i);
        }
    }
};

#ifdef DEBUG

#include <cstdio>

int main() {
    vector<int> raw = { 1, 1, 1, 1, 1 };
    TreeArray tree_array(raw);
    printf("%d\n", tree_array.query(5));
    tree_array.update(1, 1);
    printf("%d\n", tree_array.query(5));
}
#endif