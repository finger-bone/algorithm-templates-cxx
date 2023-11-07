#include <vector>
#include <tuple>

using namespace std;

tuple<int,int> get_min_max_ind(vector<int>& nums, int l, int r) {
    int min_ind = l;
    int max_ind = r;
    for(int i = l; i <= r; ++i) {
        if(nums[i] < nums[min_ind]) min_ind = i;
        if(nums[i] > nums[max_ind]) max_ind = i;
    }
    return make_tuple(min_ind, max_ind);
}

// for smaller data sets, insertion sort is faster than quicksort
// here we use two-way insertion sort
void insertion_sort(vector<int>& nums) {
    int n = nums.size();
    int l = 0;
    int r = n - 1;
    // invariants [0, l) and (r, n - 1] are sorted
    while(l <= r) {
        auto [min_ind, max_ind] = get_min_max_ind(nums, l, r);
        swap(nums[l], nums[min_ind]);
        swap(nums[r], nums[max_ind]);
        ++l;
        --r;
    }
}

void buckle_sort(vector<int>& nums) {
    int n = nums.size();
    auto [min_ind, max_ind] = get_min_max_ind(nums, 0, n - 1);
    // we assume the data are evenly distributed
    int bucket_size = (nums[max_ind] - nums[min_ind]) / n + 1;
    int bucket_num = (nums[max_ind] - nums[min_ind]) / bucket_size + 1;
    vector<vector<int>> buckets(bucket_num);
    for(int i = 0; i < n; ++i) {
        int bucket_ind = (nums[i] - nums[min_ind]) / bucket_size;
        buckets[bucket_ind].push_back(nums[i]);
    }
    for(int i = 0; i < bucket_num; ++i) insertion_sort(buckets[i]);
    int ind = 0;
    for(int i = 0; i < bucket_num; ++i) {
        for(int j = 0; j < buckets[i].size(); ++j) {
            nums[ind] = buckets[i][j];
            ++ind;
        }
    }
}

#ifdef DEBUG

#include <iostream>

int main() {
    vector<int> vec = {0, 1, 2, 8, 4, 3, 7, 6, 5, 9};
    buckle_sort(vec);
    for(auto& x : vec) cout << x << " ";
    cout << endl;
    return 0;
}

#endif