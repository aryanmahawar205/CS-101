#include <bits/stdc++.h>
using namespace std;

vector<int> matchWithSpaces(string T, string P){
    string clean="";
    for(char c: P) if(c!='_') clean+=c;
    vector<int> shifts;
    for(int s=0;s+clean.size()<=T.size();s++){
        if(T.substr(s, clean.size())==clean)
            shifts.push_back(s);
    }
    return shifts;
}

int main(){
    string T="abbacabba";
    string P="ab_ba_c"; // interpreted as abbac
    auto res = matchWithSpaces(T,P);
    cout<<"Valid Shifts: ";
    for(int s: res) cout<<s<<" ";
    cout << endl;
}