#include <bits/stdc++.h>
using namespace std;

bool isRotation(string a,string b){
    return (a.size()==b.size() && (b+b).find(a)!=string::npos);
}

int main(){
    string a="car", b="arc";
    if(isRotation(a,b)) cout<<"Yes"<<endl;
    else cout<<"No"<<endl;
}