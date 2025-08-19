#include <bits/stdc++.h>

using namespace std;

int maxRevenue(int n, vector<int>& price, unordered_map<int, int>& memo) {
    if (n < 3) return -n; // Penalty for leftover

    if (memo.find(n) != memo.end()) return memo[n];

    int rev = INT_MIN;

    if (n >= 3)
        rev = max(rev, price[3] + maxRevenue(n - 3, price, memo));
    if (n >= 5)
        rev = max(rev, price[5] + maxRevenue(n - 5, price, memo));

    memo[n] = rev;
    return rev;
}

int main() {
    int n = 8;
    vector<int> price(n + 1, 0);

    // Example prices
    price[3] = 5;
    price[5] = 8;
    price[6] = 10;
    price[8] = 15;

    unordered_map<int, int> memo;
    int result = maxRevenue(n, price, memo);

    cout << "Maximum revenue: ₹" << result << endl;

    return 0;
}