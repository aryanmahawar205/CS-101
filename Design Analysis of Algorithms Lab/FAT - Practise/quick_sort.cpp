#include <bits/stdc++.h>

using namespace std;

int generatePartitionIdx(vector<int> &nums, int low, int high)
{
    int i = low; int j = high;
    int pivot = nums[low];
    
    while (i < j)
    {
        while (nums[i] <= pivot && i <= high-1) // going good, happy case
            i++;
        
        while (nums[j] > pivot && j >= low+1)
            j--;
            
        if (i < j)
            swap(nums[i], nums[j]);
    }
    
    swap(nums[low], nums[j]);
    
    return j;
}

void quickSort(vector<int> &nums, int low, int high)
{
    if (low <= high)
    {
        int partition_idx = generatePartitionIdx(nums, low, high);
        quickSort(nums, low, partition_idx-1);
        quickSort(nums, partition_idx+1, high);
    }
}

int main()
{
    vector<int> nums = {31, 22, 43, 44, 56, 23, 5};
    
    int n = nums.size();
    
    quickSort(nums, 0, n-1);
    
    for (int i = 0; i < nums.size(); i++)
        cout << nums[i] << " ";
    
    return 0;
}