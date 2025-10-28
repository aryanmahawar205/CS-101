// Sum of subsets

#include <iostream>
#include <vector>
using namespace std;

void printSubset(const vector<int>& subset) {
    cout << "{ ";
    for (int x : subset) {
        cout << x << " ";
    }
    cout << "}" << endl;
}

// backtracking helper
void sumOfSubsetsHelper(const vector<int>& arr,
                        int target,
                        int currentSum,
                        int index,
                        vector<int>& subset) {
    int n = arr.size();

    // If current sum becomes equal to target, we found a subset
    if (currentSum == target) {
        printSubset(subset);
        // Note: not returning here allows finding further subsets
    }

    // If we reach end or currentSum exceeds target, stop
    if (index >= n || currentSum > target) {
        return;
    }

    // Include arr[index]
    subset.push_back(arr[index]);
    sumOfSubsetsHelper(arr, target, currentSum + arr[index], index + 1, subset);

    // Backtrack: exclude arr[index]
    subset.pop_back();
    sumOfSubsetsHelper(arr, target, currentSum, index + 1, subset);
}

void sumOfSubsets(const vector<int>& arr, int target) {
    vector<int> subset;
    sumOfSubsetsHelper(arr, target, 0, 0, subset);
}

int main() {
    vector<int> arr;
    int n, target;

    cout << "Enter number of elements: ";
    cin >> n;
    arr.resize(n);

    cout << "Enter the elements: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    cout << "Enter target sum: ";
    cin >> target;

    cout << "Subsets of given set that sum to " << target << " :" << endl;
    sumOfSubsets(arr, target);

    return 0;
}