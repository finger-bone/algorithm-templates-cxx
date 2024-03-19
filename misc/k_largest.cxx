#include <vector>

using namespace std;

constexpr int BITE = 5;

int get_approx_median(vector<int> nums)
{
    vector<array<int, BITE>> bites(ceil(nums.size() / BITE));
    for (size_t i = 0; i < nums.size(); i++)
    {
        bites[i / BITE][i % BITE] = nums[i];
    }
    vector<int> medians;
    for (auto bite : bites)
    {
        sort(bite.begin(), bite.end());
        medians.push_back(bite[bite.size() / 2]);
    }
    sort(medians.begin(), medians.end());
    return medians[medians.size() / 2];
}

int k_largest(vector<int> nums, size_t k)
{
    int med = get_approx_median(nums);
    vector<int> left, equal, right;
    for (auto num : nums)
    {
        if (num < med)
        {
            left.push_back(num);
        }
        else if (num == med)
        {
            equal.push_back(num);
        }
        else
        {
            right.push_back(num);
        }
    }
    if (right.size() >= k)
    {
        return k_largest(right, k);
    }
    else if (right.size() + equal.size() >= k)
    {
        return med;
    }
    else
    {
        return k_largest(left, k - right.size() - equal.size());
    }
}

#define DEBUG

#ifdef DEBUG

#include <iostream>

int main()
{
    cout << k_largest(
        {1, 6, 123, 34, 24, 6, 123, 89, 132, 54, 47, 58, 7, 213, 6, 5, 765, 643, 123}
        , 5) << endl; 
    return 0;
}

#endif
