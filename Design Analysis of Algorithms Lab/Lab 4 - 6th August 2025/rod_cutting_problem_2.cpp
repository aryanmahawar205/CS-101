#include <bits/stdc++.h>

using namespace std;

int maxRevenue(int n, int k, vector<int>& price, vector<vector<int>>& memo) {
    if (k == 1) return price[n];
    if (memo[n][k] != -1) return memo[n][k];

    int maxRev = INT_MIN;

    for (int i = 1; i <= n - k + 1; i++) {
        int rev = price[i] + maxRevenue(n - i, k - 1, price, memo);
        maxRev = max(maxRev, rev);
    }

    return memo[n][k] = maxRev;
}

int main() {
    int n = 8, k = 3;
    vector<int> price = {0, 2, 5, 7, 8, 10, 13, 17, 20}; // price[i] = price of length i
    vector<vector<int>> memo(n + 1, vector<int>(k + 1, -1));

    int result = maxRevenue(n, k, price, memo);
    cout << "Maximum revenue for length " << n << " with " << k << " pieces: ₹" << result << endl;
    return 0;
}