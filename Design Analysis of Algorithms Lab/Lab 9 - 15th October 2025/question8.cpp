#include <bits/stdc++.h>
using namespace std;
struct Point{ double x,y; };
double cross(Point a, Point b, Point c){
    return (b.x-a.x)*(c.y-a.y)-(b.y-a.y)*(c.x-a.x);
}
vector<Point> convexHull(vector<Point>& pts){
    sort(pts.begin(), pts.end(), [](Point a, Point b){
        return a.x<b.x || (a.x==b.x && a.y<b.y);
    });
    vector<Point> lower,upper;
    for(auto p:pts){
        while(lower.size()>=2 && cross(lower[lower.size()-2],lower.back(),p)<=0)
            lower.pop_back();
        lower.push_back(p);
    }
    for(int i=pts.size()-1;i>=0;i--){
        Point p=pts[i];
        while(upper.size()>=2 && cross(upper[upper.size()-2],upper.back(),p)<=0)
            upper.pop_back();
        upper.push_back(p);
    }
    lower.pop_back(); upper.pop_back();
    lower.insert(lower.end(),upper.begin(),upper.end());
    return lower;
}
int main(){
    vector<Point> pts={{0,3},{1,1},{2,2},{4,4},{0,0},{1,2},{3,1},{3,3}};
    auto hull=convexHull(pts);
    cout<<"Convex Hull:\n";
    for(auto p:hull) cout<<"("<<p.x<<","<<p.y<<") ";
}