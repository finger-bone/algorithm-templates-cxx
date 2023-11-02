#include <vector>
#include <algorithm>

using namespace std;

// in addition to merge sort
// this also counts reverse pairs
// that is, the number of ordered pairs (i, j) such that i < j and nums[i] > nums[j]
// the reason why we can count reverse pairs in merge sort is that
// the reverse pairs are accumulative when merging
// for example, [1, 3, 5] and [2, 4, 6]
// the total reverse pairs equals to that of the two halves plus the reverse pairs between the two halves
// the reverse pairs in the two halves are independent from each other
// so we can count them separately
int merge_sort(vector<int>& nums, int l, int r) {
    // sort [l, r], when l == r or l > r, no need to sort
    if(l >= r) return 0;
    // now split the array into two halves
    int mid = (l + r) >> 1;
    // sort two halves
    int reverse_left = merge_sort(nums, l, mid);
    int reverse_right = merge_sort(nums, mid + 1, r);
    // here uses extra space to store the sorted array
    // in-place algorithm is also possible, but it hurts the performance
    vector<int> sorted(r - l + 1);
    // merge two halves
    // within the process, we can count the reverse pairs across the two halves
    int reverse_across = 0;
    int i = l;
    int j = mid + 1;
    int k = 0;
    for(
        ;
        i <= mid && j <= r;
        ++k
    ) {
        if(nums[i] <= nums[j]) {
            // left is smaller than right
            // no reverse pair
            sorted[k] = nums[i];
            ++i;
        }
        else {
            // now, nums[i] > nums[j]
            // notice that [i, mid] is sorted
            // so every number comes after nums[i] (including nums[i]) is greater than nums[j]
            // so for nums[j], there are mid - i + 1 reverse pairs
            reverse_across += mid - i + 1;
            sorted[k] = nums[j];
            ++j;
        }
    }
    // now, the merging is done or one of the two halves is done
    // only one of the two loops below will be executed
    for(; i <= mid; ++k, ++i) sorted[i - l + r - mid] = nums[i];
    for(; j <= r; ++k, ++j) sorted[j - l + r - mid] = nums[j];
    // copy the sorted array back to nums
    copy(sorted.begin(), sorted.end(), nums.begin() + l);
    // return the total number of reverse pairs
    return reverse_left + reverse_right + reverse_across;
}

#ifdef DEBUG

int main() {
    vector<int> nums = {7, 5, 6, 4};
    int reverse_pairs = merge_sort(nums, 0, nums.size() - 1);
    printf("reverse pairs: %d\n", reverse_pairs);
    for(int i = 0; i < nums.size(); ++i) {
        printf("%d ", nums[i]);
    }
    printf("\n");
    return 0;
}

#endif