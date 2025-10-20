#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    cout << "Enter number of statements in 3-address code: ";
    cin >> n;
    cin.ignore(); // to ignore newline after n

    vector<string> code(n);
    cout << "Enter the 3-address code statements line by line:\n";
    
    for (int i = 0; i < n; i++) 
        getline(cin, code[i]);

    set<int> leaders;

    // Rule 1: First statement is always a leader
    leaders.insert(1);

    for (int i = 0; i < n; i++) {
        string stmt = code[i];
        // Rule 2: Target of goto is a leader
        size_t pos = stmt.find("goto");
        if (pos != string::npos) {
            stringstream ss(stmt.substr(pos + 4));
            int target;
            ss >> target;
            if (target >= 1 && target <= n)
                leaders.insert(target);

            // Rule 3: Immediate next statement is also a leader
            if (i + 2 <= n)
                leaders.insert(i + 2);
        }
    }

    cout << "\nLeaders in the 3-address code are at statements: ";
    for (int leader : leaders)
        cout << leader << " ";
    cout << "\n";

    return 0;
}