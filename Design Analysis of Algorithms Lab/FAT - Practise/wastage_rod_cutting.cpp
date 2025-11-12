#include <iostream>
#include <vector>
#include <algorithm> // For std::max

int rodCuttingWithWaste(const std::vector<int>& prices, int rodLength, int cutCost) {
    // dp[i] stores the maximum profit for a rod of length i
    std::vector<int> dp(rodLength + 1, 0);

    // Iterate through all possible rod lengths from 1 to rodLength
    for (int i = 1; i <= rodLength; ++i) {
        int max_val = -1; // Initialize with a value lower than any possible profit

        // Consider all possible first cuts for a rod of length i
        for (int j = 1; j <= i; ++j) {
            // Option 1: Don't cut the current piece (length j) further
            // Profit = price of piece j + profit from remaining rod (length i - j)
            // If i - j > 0, we incur a cutCost
            int current_profit = prices[j - 1] + dp[i - j];
            if (i - j > 0) { // If a cut was actually made to get a piece of length j
                current_profit -= cutCost;
            }
            max_val = std::max(max_val, current_profit);
        }
        dp[i] = max_val;
    }
    return dp[rodLength];
}

int main() {
    // Example: prices[i] is the price of a rod piece of length i+1
    // So, prices[0] is for length 1, prices[1] for length 2, etc.
    std::vector<int> prices = {1, 5, 8, 9, 10, 17, 17, 20}; 
    int rodLength = prices.size(); // Length of the original rod
    int cutCost = 2; // Cost incurred for each cut

    int maxProfit = rodCuttingWithWaste(prices, rodLength, cutCost);
    std::cout << "Maximum profit with cuts and waste: " << maxProfit << std::endl;

    // Example 2: No cut cost
    int cutCost_no_waste = 0;
    int maxProfit_no_waste = rodCuttingWithWaste(prices, rodLength, cutCost_no_waste);
    std::cout << "Maximum profit without cut cost: " << maxProfit_no_waste << std::endl;

    return 0;
}