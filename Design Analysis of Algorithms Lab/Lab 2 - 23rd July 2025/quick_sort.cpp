#include <bits/stdc++.h>

using namespace std;

// Partition function: places pivot at correct position
int partitionQS(vector<int>& A, int low, int high) {
    int pivot = A[high];
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (A[j] <= pivot) {
            swap(A[++i], A[j]);
        }
    }
    swap(A[i + 1], A[high]);
    return i + 1;
}

// Recursive Quick Sort
void quickSort(vector<int>& A, int low, int high) {
    if (low < high) {
        int pi = partitionQS(A, low, high);
        quickSort(A, low, pi - 1);
        quickSort(A, pi + 1, high);
    }
}

int main() {
    vector<int> arr = {64, 34, 25, 12, 22, 11, 90};

    cout << "Original array (Quick Sort): ";
    for (int x : arr) cout << x << " ";
    cout << endl;

    quickSort(arr, 0, arr.size() - 1);

    cout << "Sorted array (Quick Sort):   ";
    for (int x : arr) cout << x << " ";
    cout << endl;

    return 0;
}