#include <bits/stdc++.h>

using namespace std;

// merge two sorted arrays
void merge(vector<int> &nums, int low, int mid, int high)
{
    vector<int> ans;
    
    int left = low;
    int right = mid+1;
    
    while (left <= mid && right <= high)
    {
        if (nums[left] <= nums[right])
        {
            ans.push_back(nums[left]);
            left++;
        }
        
        else
        {
            ans.push_back(nums[right]);
            right++;
        }
    }
    
    // remaining if any for left
    while (left <= mid)
    {
        ans.push_back(nums[left]);
        left++;
    }
    
    // remaining if any for right
    while (right <= high)
    {
        ans.push_back(nums[right]);
        right++;
    }
    
    // copy into original array
    for (int i = low; i <= high; i++)
        nums[i] = ans[i-low];
}

void mergeSort(vector<int> &nums, int low, int high)
{
    if (low >= high)
        return;
        
    int mid = (low+high)/2;
    
    mergeSort(nums, low, mid);
    mergeSort(nums, mid+1, high);
    merge(nums, low, mid, high);
}

int main()
{
    vector<int> nums = {31, 22, 43, 44, 56, 23, 5};
    
    int n = nums.size();
    
    mergeSort(nums, 0, n-1);
    
    for (int i = 0; i < nums.size(); i++)
        cout << nums[i] << " ";
    
    return 0;
}