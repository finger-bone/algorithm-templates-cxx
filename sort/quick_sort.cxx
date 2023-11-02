#include <vector>

using namespace std;

// two pointers based
void quick_sort(vector<int>& nums, int l, int r) {
    // sort [l, r]
    if(r <= l) return;
    // similar to binary search, focus on the loop invariant
    // pivot can be any number within the range
    int pivot = nums[(l + r) >> 1];
    // i moves from l to r, j moves from r to l
    int i = l;
    int j = r;
    // invariance: [l, i) <= pivot, (j, r] >= pivot
    // i is the maximum possible number and j is the minimum possible number
    // when maximum/minimum index meet, break it
    while(i < j) {
        while(nums[i] <= pivot) ++i;
        while(nums[j] >= pivot) --j;
        if(i > j) break;
        swap(nums[i], nums[j]);
        // i, j are the maximum and minimum possible numbers
        // so to keep the invariant, we need to move them
        ++i;
        --j;
    }
    // i < j is broken, so i == j
    // so [l, i] <= pivot, [j, r] >= pivot
    // so [l, j] and [i, r] are two sub-arrays
    // so we need to sort them recursively
    quick_sort(nums, l, j);
    quick_sort(nums, i, r);
}

#ifdef DEBUG

#include <iostream>

int main() {
    vector<int> nums = {3, 2, 4, 1, 6, 2};
    quick_sort(nums, 0, nums.size() - 1);
    for(auto& num : nums) {
        cout << num << " ";
    }
    cout << endl;
    return 0;
}

#endif