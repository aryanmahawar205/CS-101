#include <bits/stdc++.h>

using namespace std;

// Merge function that preserves stability
void mergeStable(vector<pair<int,int>>& A, int l, int m, int r, long long& cmp) {
    int n1 = m - l + 1, n2 = r - m;
    vector<pair<int,int>> L(A.begin() + l, A.begin() + m + 1);
    vector<pair<int,int>> R(A.begin() + m + 1, A.begin() + r + 1);
    
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        cmp++;
        // Key stability check: use <= for left array to maintain order
        if (L[i].first <= R[j].first) {
            A[k++] = L[i++];
        } else {
            A[k++] = R[j++];
        }
    }
    while (i < n1) A[k++] = L[i++];
    while (j < n2) A[k++] = R[j++];
}

void mergeSortStable(vector<pair<int,int>>& A, int l, int r, long long& cmp) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSortStable(A, l, m, cmp);
        mergeSortStable(A, m + 1, r, cmp);
        mergeStable(A, l, m, r, cmp);
    }
}

// Function to verify stability
bool verifyStability(const vector<pair<int,int>>& arr) {
    for (int i = 1; i < arr.size(); i++) {
        // If two adjacent elements have same key, their original indices should be in order
        if (arr[i].first == arr[i-1].first && arr[i].second < arr[i-1].second) {
            return false;
        }
    }
    return true;
}

// Create test dataset with duplicates
vector<pair<int,int>> createTestData(int size, int maxValue) {
    vector<pair<int,int>> data(size);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(1, maxValue);
    
    for (int i = 0; i < size; i++) {
        data[i] = {dis(gen), i}; // {value, original_index}
    }
    return data;
}

int main() {
    cout << "=== MERGE SORT STABILITY DEMONSTRATION ===" << endl;
    cout << "Testing with datasets containing duplicate elements" << endl;
    cout << string(60, '=') << endl;
    
    // Test with different array sizes and duplicate densities
    vector<int> sizes = {100, 500, 1000, 2000, 5000};
    vector<int> maxValues = {10, 20, 50}; // Lower values = more duplicates
    
    cout << setw(8) << "Size" 
         << setw(12) << "Max Value"
         << setw(15) << "Duplicates %"
         << setw(12) << "Stable?"
         << setw(15) << "Comparisons"
         << endl;
    cout << string(60, '-') << endl;
    
    for (int size : sizes) {
        for (int maxVal : maxValues) {
            // Create test data
            vector<pair<int,int>> testData = createTestData(size, maxVal);
            
            // Count duplicates before sorting
            int duplicateCount = 0;
            for (int i = 0; i < size; i++) {
                for (int j = i + 1; j < size; j++) {
                    if (testData[i].first == testData[j].first) {
                        duplicateCount++;
                        break;
                    }
                }
            }
            double duplicatePercent = (duplicateCount * 100.0) / size;
            
            // Sort and measure
            long long comparisons = 0;
            mergeSortStable(testData, 0, size - 1, comparisons);
            
            // Verify stability
            bool isStable = verifyStability(testData);
            
            cout << setw(8) << size
                 << setw(12) << maxVal
                 << setw(14) << fixed << setprecision(1) << duplicatePercent << "%"
                 << setw(12) << (isStable ? "YES" : "NO")
                 << setw(15) << comparisons
                 << endl;
        }
    }
    
    cout << string(60, '=') << endl;
    
    // Detailed example with small dataset
    cout << "\n=== DETAILED STABILITY EXAMPLE ===" << endl;
    vector<pair<int,int>> example = {{3,0}, {1,1}, {3,2}, {2,3}, {1,4}, {3,5}, {2,6}};
    
    cout << "Original array (value, original_index):" << endl;
    for (const auto& p : example) {
        cout << "(" << p.first << "," << p.second << ") ";
    }
    cout << endl;
    
    long long exampleComparisons = 0;
    mergeSortStable(example, 0, example.size() - 1, exampleComparisons);
    
    cout << "After stable merge sort:" << endl;
    for (const auto& p : example) {
        cout << "(" << p.first << "," << p.second << ") ";
    }
    cout << endl;
    
    cout << "Stability verification: " << (verifyStability(example) ? "PASSED" : "FAILED") << endl;
    cout << "Notice: Elements with value 1 maintain order (1,1) before (1,4)" << endl;
    cout << "        Elements with value 3 maintain order (3,0) before (3,2) before (3,5)" << endl;
    
    return 0;
}