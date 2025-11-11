#include <bits/stdc++.h>

using namespace std;

void insertionSort(vector<int> &nums)
{
    int n = nums.size();
    
    for (int i = 0; i <= n-1; i++)
    {
        int j = i;
        
        while (j > 0 && nums[j-1] > nums[j])
            {
                swap(nums[j-1], nums[j]);
                j--;
            }
    }
}

int main()
{
    vector<int> nums = {31, 22, 43, 44, 56, 23, 5};
    
    insertionSort(nums);
    
    for (int i = 0; i < nums.size(); i++)
        cout << nums[i] << " ";
    
    return 0;
}