#include <bits/stdc++.h>

using namespace std;

// Merge function: merges two sorted subarrays A[l..m] and A[m+1r]
void merge(vector<int>& A, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    vector<int> L(A.begin() + l, A.begin() + m + 1);
    vector<int> R(A.begin() + m + 1, A.begin() + r + 1);

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            A[k++] = L[i++];
        } else {
            A[k++] = R[j++];
        }
    }
    while (i < n1) A[k++] = L[i++];
    while (j < n2) A[k++] = R[j++];
}

// Recursive Merge Sort
void mergeSort(vector<int>& A, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(A, l, m);
        mergeSort(A, m + 1, r);
        merge(A, l, m, r);
    }
}

int main() {
    vector<int> arr = {64, 34, 25, 12, 22, 11, 90};

    cout << "Original array (Merge Sort): ";
    for (int x : arr) cout << x << " ";
    cout << endl;

    mergeSort(arr, 0, arr.size() - 1);

    cout << "Sorted array (Merge Sort):   ";
    for (int x : arr) cout << x << " ";
    cout << endl;

    return 0;
}