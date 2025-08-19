#include <bits/stdc++.h>

using namespace std;

int main() {
    vector<int> v = {10, 20, 30, 40, 50};

    // 1. Iterator
    cout << "Iterator: ";
    for (auto it = v.begin(); it != v.end(); ++it) {
        cout << *it << " ";
    }
    cout << "\n";

    // 2. Const Iterator
    cout << "Const Iterator: ";
    for (auto it = v.cbegin(); it != v.cend(); ++it) {
        cout << *it << " ";
    }
    cout << "\n";

    // 3. Reverse Iterator
    cout << "Reverse Iterator: ";
    for (auto rit = v.rbegin(); rit != v.rend(); ++rit) {
        cout << *rit << " ";
    }
    cout << "\n";

    return 0;
}