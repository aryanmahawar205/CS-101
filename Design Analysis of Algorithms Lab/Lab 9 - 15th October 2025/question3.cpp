#include <bits/stdc++.h>
using namespace std;

struct Point { double x, y; };

int orientation(Point a, Point b, Point c){
    double v = (b.y - a.y)*(c.x - b.x) - (b.x - a.x)*(c.y - b.y);
    if(fabs(v) < 1e-9) return 0;
    return (v > 0) ? 1 : 2;
}

bool onSegment(Point a, Point b, Point c){
    return min(a.x,c.x)<=b.x && b.x<=max(a.x,c.x) &&
           min(a.y,c.y)<=b.y && b.y<=max(a.y,c.y);
}

bool intersect(Point p1, Point q1, Point p2, Point q2){
    int o1=orientation(p1,q1,p2), o2=orientation(p1,q1,q2);
    int o3=orientation(p2,q2,p1), o4=orientation(p2,q2,q1);
    if(o1!=o2 && o3!=o4) return true;
    if(o1==0 && onSegment(p1,p2,q1)) return true;
    if(o2==0 && onSegment(p1,q2,q1)) return true;
    if(o3==0 && onSegment(p2,p1,q2)) return true;
    if(o4==0 && onSegment(p2,q1,q2)) return true;
    return false;
}

int main(){
    int n; cin>>n;
    vector<pair<Point,Point>> seg(n);
    for(int i=0;i<n;i++)
        cin>>seg[i].first.x>>seg[i].first.y>>seg[i].second.x>>seg[i].second.y;
    for(int i=0;i<n;i++)
        for(int j=i+1;j<n;j++)
            if(intersect(seg[i].first,seg[i].second,seg[j].first,seg[j].second))
                cout<<"Segment "<<i<<" intersects "<<j<<"\n";
}