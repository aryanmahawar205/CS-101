#include <bits/stdc++.h>

using namespace std;

int mergeAndCount(vector<int>& arr, int l, int m, int r) {
    int leftSize = m - l + 1, rightSize = r - m;
    vector<int> L(arr.begin() + l, arr.begin() + m + 1);
    vector<int> R(arr.begin() + m + 1, arr.begin() + r + 1);

    int i = 0, j = 0, k = l, invCount = 0;
    while (i < leftSize && j < rightSize) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
            invCount += (leftSize - i); // Count inversions
        }
    }

    while (i < leftSize) arr[k++] = L[i++];
    while (j < rightSize) arr[k++] = R[j++];

    return invCount;
}

int countInversions(vector<int>& arr, int l, int r) {
    if (l >= r) return 0;
    int m = (l + r) / 2;
    int left = countInversions(arr, l, m);
    int right = countInversions(arr, m + 1, r);
    int cross = mergeAndCount(arr, l, m, r);
    return left + right + cross;
}

int main() {
    vector<int> arr = {2, 3, 8, 6, 1};
    int inversions = countInversions(arr, 0, arr.size() - 1);
    cout << "Total Inversions: " << inversions << endl;
    return 0;
}