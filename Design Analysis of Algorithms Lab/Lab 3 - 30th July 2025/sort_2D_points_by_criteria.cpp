#include <bits/stdc++.h>

using namespace std;

struct Point {
    int x, y;
};

bool compareX(Point a, Point b) { return a.x < b.x; }
bool compareY(Point a, Point b) { return a.y < b.y; }
bool compareAvg(Point a, Point b) { return (a.x + a.y) < (b.x + b.y); }

void print(const vector<Point>& points) {
    for (auto p : points)
        cout << "(" << p.x << ", " << p.y << ") ";
    cout << endl;
}

int main() {
    vector<Point> points = {{2, 3}, {1, 5}, {4, 1}, {3, 3}};

    vector<Point> xSorted = points, ySorted = points, avgSorted = points;
    sort(xSorted.begin(), xSorted.end(), compareX);
    sort(ySorted.begin(), ySorted.end(), compareY);
    sort(avgSorted.begin(), avgSorted.end(), compareAvg);

    cout << "Sorted by X: "; print(xSorted);
    cout << "Sorted by Y: "; print(ySorted);
    cout << "Sorted by Avg: "; print(avgSorted);

    return 0;
}