// TSP - DP

#include <iostream>
#include <cstring>
using namespace std;

int n;
int cost[20][20];
int dp[1 << 20][20]; // dp[mask][i]
const int INF = 1e9;

int tsp(int mask, int pos) {
    if (mask == (1 << n) - 1)  // all cities visited
        return cost[pos][0];   // return to starting city

    if (dp[mask][pos] != -1)
        return dp[mask][pos];

    int ans = INF;

    for (int city = 0; city < n; city++) {
        if ((mask & (1 << city)) == 0) { // if city not visited
            int newCost = cost[pos][city] + tsp(mask | (1 << city), city);
            if (newCost < ans)
                ans = newCost;
        }
    }

    return dp[mask][pos] = ans;
}

int main() {
    cout << "Enter number of cities: ";
    cin >> n;

    cout << "Enter cost matrix (" << n << "x" << n << "):\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> cost[i][j];

    memset(dp, -1, sizeof(dp));

    int result = tsp(1, 0); // starting from city 0, mask=1 means only city 0 visited
    cout << "\nMinimum travelling cost: " << result << endl;

    return 0;
}