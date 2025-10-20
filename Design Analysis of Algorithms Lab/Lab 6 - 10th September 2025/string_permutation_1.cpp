#include <bits/stdc++.h>
using namespace std;

int main(){
    string s="abc";
    vector<string> perms;
    sort(s.begin(), s.end());
    do{
        perms.push_back(s);
    }while(next_permutation(s.begin(),s.end()));
    for(auto &str: perms) cout<<str<<"\n";
}