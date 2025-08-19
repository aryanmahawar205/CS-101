#include <bits/stdc++.h>

using namespace std;

int findMax(const vector<int>& arr, int low, int high) {
    if (low == high)
        return arr[low];
    int mid = (low + high) / 2;
    int leftMax = findMax(arr, low, mid);
    int rightMax = findMax(arr, mid + 1, high);
    return max(leftMax, rightMax);
}

int main() {
    vector<int> arr = {4, 7, 2, 9, 1};
    cout << "Maximum: " << findMax(arr, 0, arr.size() - 1) << endl;
    return 0;
}