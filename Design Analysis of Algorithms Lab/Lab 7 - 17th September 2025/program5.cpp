#include <bits/stdc++.h>
using namespace std;

vector<int> prefix_function(string s){
    int n=s.size();
    vector<int> pi(n);
    for(int i=1;i<n;i++){
        int j=pi[i-1];
        while(j>0 && s[i]!=s[j]) j=pi[j-1];
        if(s[i]==s[j]) j++;
        pi[i]=j;
    }
    return pi;
}

int main(){
    string P="aba", T="abacaba";
    string S=P+"#"+T;
    auto pi=prefix_function(S);
    for(int i=0;i<S.size();i++){
        if(pi[i]==P.size())
            cout<<"Match at "<<i-2*P.size()<<"\n";
    }
}