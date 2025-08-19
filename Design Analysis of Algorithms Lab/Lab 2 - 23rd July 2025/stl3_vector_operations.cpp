#include <bits/stdc++.h>

using namespace std;

int main() {
    vector<int> v;

    // Add elements
    v.push_back(5);
    v.push_back(10);
    v.push_back(15);

    // Display
    cout << "After push_back: ";
    for (int x : v) {
        cout << x << " ";
    }
    cout << "\n";

    // Remove last element
    v.pop_back();

    // Display
    cout << "After pop_back:  ";
    for (int x : v) {
        cout << x << " ";
    }
    cout << "\n";

    // Insert at specific position (e.g., at begin)
    v.insert(v.begin(), 1);
    cout << "After insert:    ";
    for (int x : v) {
        cout << x << " ";
    }
    cout << "\n";

    // Erase first element
    v.erase(v.begin());
    cout << "After erase:     ";
    for (int x : v) {
        cout << x << " ";
    }
    cout << "\n";

    return 0;
}