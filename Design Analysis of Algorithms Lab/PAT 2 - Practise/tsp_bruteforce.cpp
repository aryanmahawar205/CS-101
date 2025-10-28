// TSP - Brute Force

#include <iostream>
using namespace std;

int n;
int cost[10][10], visited[10];
int minCost = 99999;

void tsp(int city, int count, int totalCost) {
    if (count == n && cost[city][0] > 0) {
        totalCost += cost[city][0];
        if (totalCost < minCost)
            minCost = totalCost;
        return;
    }

    for (int next = 0; next < n; next++) {
        if (!visited[next] && cost[city][next] > 0) {
            visited[next] = 1;
            tsp(next, count + 1, totalCost + cost[city][next]);
            visited[next] = 0; // backtrack
        }
    }
}

int main() {
    cout << "Enter number of cities: ";
    cin >> n;

    cout << "Enter cost matrix (" << n << "x" << n << "):\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> cost[i][j];

    for (int i = 0; i < n; i++)
        visited[i] = 0;

    visited[0] = 1; // start from city 0
    tsp(0, 1, 0);

    cout << "\nMinimum travelling cost: " << minCost << endl;
    return 0;
}