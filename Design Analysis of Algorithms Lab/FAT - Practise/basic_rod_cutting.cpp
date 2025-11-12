#include <iostream>
#include <vector>
#include <algorithm> // For std::max

// Function to solve the rod cutting problem
int cutRod(const std::vector<int>& prices, int n) {
    // dp[i] stores the maximum obtainable price for a rod of length i
    std::vector<int> dp(n + 1);

    // Base case: a rod of length 0 has a price of 0
    dp[0] = 0;

    // Fill the dp table for rod lengths from 1 to n
    for (int i = 1; i <= n; ++i) {
        int max_val = 0;
        // Consider all possible first cuts for a rod of length i
        for (int j = 0; j < i; ++j) {
            // prices[j] is the price of a piece of length (j+1)
            // dp[i - (j + 1)] is the maximum price for the remaining rod
            max_val = std::max(max_val, prices[j] + dp[i - (j + 1)]);
        }
        dp[i] = max_val;
    }

    // The maximum obtainable price for a rod of length n is stored in dp[n]
    return dp[n];
}

int main() {
    // Example prices for pieces of length 1, 2, 3, ...
    // prices[0] is for length 1, prices[1] for length 2, and so on.
    std::vector<int> prices = {1, 5, 8, 9, 10, 17, 17, 20}; 
    int rodLength = prices.size(); // The total length of the rod

    // Calculate and print the maximum obtainable price
    std::cout << "Maximum obtainable value by cutting up the rod: " 
              << cutRod(prices, rodLength) << std::endl;

    return 0;
}