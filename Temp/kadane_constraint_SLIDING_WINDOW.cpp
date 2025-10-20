#include <bits/stdc++.h>

using namespace std;

int main()
{
    vector<int> nums = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    int k = 2;
    int n = nums.size();

    // calculate the sum of the first windows of size 2
    int window_sum = 0;
    
    for (int i = 0; i < k; i++)
        window_sum += nums[i];

    int maxi_sum = window_sum; // maanlo ek hi window rahi tho yehi return karunga

    // use sliding window of fixed length k to detect where we get max sum
    for (int i = k; i < n; i++)
    {
        window_sum = window_sum + nums[i] - nums[i-k]; // add new element to existing sum and consequently subtract the first element
        maxi_sum = max(maxi_sum, window_sum);
    }

    cout << maxi_sum << " ";

    return 0;
}