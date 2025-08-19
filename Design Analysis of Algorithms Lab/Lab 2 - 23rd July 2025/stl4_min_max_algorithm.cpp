#include <bits/stdc++.h>

using namespace std;

int main() {
    vector<int> v = {7, 2, 10, 4, 6};

    // Find max and min elements
    auto itMax = max_element(v.begin(), v.end());
    auto itMin = min_element(v.begin(), v.end());

    if (itMax != v.end() && itMin != v.end()) {
        cout << "Maximum element: " << *itMax << "\n";
        cout << "Minimum element: " << *itMin << "\n";
    }

    return 0;
}