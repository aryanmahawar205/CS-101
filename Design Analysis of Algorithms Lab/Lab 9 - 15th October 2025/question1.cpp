#include <bits/stdc++.h>
using namespace std;

struct Point { double x, y; };

double cross(Point a, Point b, Point c) {
    return (b.x - a.x)*(c.y - a.y) - (b.y - a.y)*(c.x - a.x);
}

double dist2(Point a, Point b) {
    return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
}

int main() {
    int n; cout << "Enter number of points: "; cin >> n;
    vector<Point> pts(n);
    cout << "Enter points:\n";
    for(int i=0;i<n;i++) cin >> pts[i].x >> pts[i].y;
    Point p0 = pts[0];
    sort(pts.begin()+1, pts.end(), [&](Point a, Point b){
        double cr = cross(p0,a,b);
        if(fabs(cr)<1e-9) return dist2(p0,a) < dist2(p0,b);
        return cr > 0;
    });
    cout << "Sorted points by polar angle:\n";
    for(auto p:pts) cout << "("<<p.x<<","<<p.y<<") ";
}