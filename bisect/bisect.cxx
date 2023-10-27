/*
binary searches
*/

// keep note of the principle of loop-invariant
// loop invariant is a condition that is true before and after each iteration of the loop
// for example, in the bisect, when we use closed interval
// the loop invariant is that the answer is always in [l, r]
// for example, in array {0, 1, 2, 3, 4, 5, 6}, searching for 2
// we first assume that the answer is in [0, 6]
// then we check the middle element, which is 3
// now we have mid, and we must keep the loop invariant
// that is, we must keep the answer in [l, r]
// so, r should be mid - 1, since we have checked mid
// now, the loop invariant is still true

#include <vector>
#include <functional>

using namespace std;

using validate = function<bool(int)>;

// here we assume function f uses only little resource, cache the result if it is efficiency-consuming

// find x where x is the max value that satisfies f(x)
// f returns true for some small values, false for some larger values
// that is, f is a monotonic decreasing function
int bisect_max_f(const vector<int>& vec, validate f) {
    // we need to find x is the max value that satisfies f(x)
    // here we use [l, r)
    // that is, x does not exist
    int l = 0;
    int r = vec.size();
    // loop invariant: the target value is always within [l, r)
    // when r - l == 1, the loop breaks
    while(r - l > 1) {
        int mid = (l + r) >> 1;
        // now, f(mid) is true, 
        if(f(mid)) {
            // we must keep the target value within [l, r)
            // f(mid) is true, so the target value should be within [mid, r)
            l = mid;
        }
        else {
            // still, keep the target value within [l, r)
            // f(mid) is false, so the target value should be within [l, mid)
            r = mid;
        }
    }
    // now, since the loop breaks, r = l + 1
    // the target value must be l
    // but there is also cases in which the target value does not exist
    return f(l) ? l : -1;
}

// find x where x is the min value that satisfies f(x)
// f is a monotonic increasing function
// for smaller values, f returns false, for larger values, f returns true
int bisect_min_f(const vector<int>& vec, validate f) {
    // x is the min value that satisfies f(x)
    // here we use [l, r]
    int l = 0;
    int r = vec.size() - 1;
    // loop invariant: the target value must be within [l, r]
    while(r - l > 0) {
        int mid = (l + r) >> 1;
        if(f(mid)) {
            // f(mid) is true, the target must be within [l, mid]
            r = mid;
        }
        else {
            // f(mid) is false, the target must be within [mid + 1, r]
            l = mid + 1;
        }
    }
    return f(l) ? l : -1;
}

#ifdef DEBUG

#include <iostream>

int main() {
    vector<int> vec = {1, 2, 3, 5, 6, 7};
    validate f = [&](int x) {
        return vec[x] > 10;
    };
    int target = bisect_min_f(vec, f);
    cout << target << endl;
    if (target != -1) {
        cout << vec[target] << endl;
    }
    return 0;
}

#endif