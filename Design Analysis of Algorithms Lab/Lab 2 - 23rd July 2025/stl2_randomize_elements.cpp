#include <bits/stdc++.h>

using namespace std;

int main() {
    vector<int> v = {1, 2, 3, 4, 5};

    // Obtain a random number generator
    random_device rd;
    mt19937 g(rd());

    // Shuffle the vector
    shuffle(v.begin(), v.end(), g);

    cout << "Shuffled sequence: ";
    for (int x : v) {
        cout << x << " ";
    }
    cout << "\n";

    return 0;
}