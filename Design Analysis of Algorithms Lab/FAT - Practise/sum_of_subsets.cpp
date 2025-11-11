#include <bits/stdc++.h>

using namespace std;

void printSubset(vector<int> &subset)
{
    cout << "{";
    for (auto it : subset)
        cout << " " << it << " ";
    cout << "}" << endl;
}

void sumOfSubsetsHelper(vector<int> &array, int target, int current_sum, int idx, vector<int> &subset)
{
    int n = array.size();
    
    if (current_sum == target)
        printSubset(subset); // not returning to explore more possibilities
        
    if (idx >= n || current_sum > target)
        return;
        
    // nahi tho consider karo and update subset
    subset.push_back(array[idx]);
    // recursively check for the next element at idx+1
    sumOfSubsetsHelper(array, target, current_sum+array[idx], idx+1, subset);
    // backtrack
    subset.pop_back();
    // if popped, gotta clear its entry as well and call helper again 
    sumOfSubsetsHelper(array, target, current_sum, idx+1, subset);
}

void sumOfSubsets(vector<int> &array, int target)
{
    vector<int> subset;
    sumOfSubsetsHelper(array, target, 0, 0, subset);
}

int main()
{
    int n; cout << "Enter the number of elements you want in the array - "; cin >> n;
    
    vector<int> array(n);
    
    cout << "Enter the array elements - " << endl;
    
    for (int i = 0; i < n; i++)
        cin >> array[i];
    
    int target; cout << "Enter the target sum - "; cin >> target;
        
    cout << "The subsets which sum up to " << target << " are - " << endl;
    
    sumOfSubsets(array, target);
    
    return 0;
}