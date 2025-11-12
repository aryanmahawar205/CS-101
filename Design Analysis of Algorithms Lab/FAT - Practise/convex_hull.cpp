#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

// Structure to represent a 2D point
struct Point {
    int x, y;
};

// Global variable to store the pivot point for sorting
Point p0;

// Function to find the orientation of three points (p, q, r)
// 0 --> Collinear
// 1 --> Clockwise
// 2 --> Counterclockwise
int orientation(Point p, Point q, Point r) {
    long long val = (long long)(q.y - p.y) * (r.x - q.x) -
                    (long long)(q.x - p.x) * (r.y - q.y);
    if (val == 0) return 0; // Collinear
    return (val > 0) ? 1 : 2; // Clockwise or Counterclockwise
}

// Function to calculate squared distance between two points
long long distSq(Point p1, Point p2) {
    return (long long)(p1.x - p2.x) * (p1.x - p2.x) +
           (long long)(p1.y - p2.y) * (p1.y - p2.y);
}

// Comparison function for sorting points by polar angle with respect to p0
bool compare(Point p1, Point p2) {
    int o = orientation(p0, p1, p2);
    if (o == 0) { // Collinear points, sort by distance from p0
        return distSq(p0, p1) < distSq(p0, p2);
    }
    return (o == 2); // Counterclockwise orientation
}

// Function to find the next-to-top point in the stack
Point nextToTop(std::stack<Point>& S) {
    Point p = S.top();
    S.pop();
    Point res = S.top();
    S.push(p);
    return res;
}

// Function to find the convex hull using Graham Scan
void grahamScan(std::vector<Point>& points) {
    int n = points.size();
    if (n < 3) {
        std::cout << "Convex hull not possible with less than 3 points.\n";
        return;
    }

    // Step 1: Find the bottom-most point (and left-most in case of tie)
    int minY = points[0].y, minIdx = 0;
    for (int i = 1; i < n; i++) {
        if ((points[i].y < minY) || (points[i].y == minY && points[i].x < points[minIdx].x)) {
            minY = points[i].y;
            minIdx = i;
        }
    }
    std::swap(points[0], points[minIdx]);
    p0 = points[0];

    // Step 2: Sort the remaining n-1 points by polar angle with respect to p0
    std::sort(points.begin() + 1, points.end(), compare);

    // Step 3: Remove collinear points that are not part of the hull
    // (keeping only the farthest one)
    int m = 1; // Current size of modified points array
    for (int i = 1; i < n; i++) {
        while (i < n - 1 && orientation(p0, points[i], points[i+1]) == 0) {
            i++;
        }
        points[m] = points[i];
        m++;
    }
    n = m; // Update n to the new size after removing collinear points

    if (n < 3) { // After removing collinear points, if less than 3 points remain
        std::cout << "Convex hull not possible with less than 3 non-collinear points.\n";
        for (int i = 0; i < n; ++i) {
            std::cout << "(" << points[i].x << ", " << points[i].y << ")\n";
        }
        return;
    }

    // Step 4: Use a stack to build the convex hull
    std::stack<Point> hull;
    hull.push(points[0]);
    hull.push(points[1]);
    hull.push(points[2]);

    for (int i = 3; i < n; i++) {
        while (hull.size() >= 2 && orientation(nextToTop(hull), hull.top(), points[i]) != 2) {
            hull.pop();
        }
        hull.push(points[i]);
    }

    // Print the points in the convex hull
    std::cout << "Points in Convex Hull:\n";
    std::vector<Point> result;
    while (!hull.empty()) {
        result.push_back(hull.top());
        hull.pop();
    }
    std::reverse(result.begin(), result.end()); // To print in counter-clockwise order
    for (const auto& p : result) {
        std::cout << "(" << p.x << ", " << p.y << ")\n";
    }
}

int main() {
    std::vector<Point> points = {
        {0, 3}, {1, 1}, {2, 2}, {4, 4},
        {0, 0}, {1, 2}, {3, 1}, {3, 3}
    };

    grahamScan(points);

    return 0;
}