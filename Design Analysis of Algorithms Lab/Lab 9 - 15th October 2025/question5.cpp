#include <bits/stdc++.h>
using namespace std;

struct Point{ double x,y; };

double cross(Point a, Point b, Point c){
    return (b.x-a.x)*(c.y-a.y) - (b.y-a.y)*(c.x-a.x);
}

bool isConvex(vector<Point>& p){
    int n=p.size(); if(n<3) return false;
    int dir=0;
    for(int i=0;i<n;i++){
        double z=cross(p[i],p[(i+1)%n],p[(i+2)%n]);
        if(z!=0){
            if(dir==0) dir=(z>0)?1:-1;
            else if((z>0 && dir<0)||(z<0 && dir>0))
                return false;
        }
    }
    return true;
}

int main(){
    vector<Point> poly={{0,0},{4,0},{4,3},{0,3}};
    cout<<(isConvex(poly)?"Convex":"Not Convex");
}