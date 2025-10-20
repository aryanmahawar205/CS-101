#include <bits/stdc++.h>

using namespace std;

int main(){
    string T="abcxabcdabxabcdabcdabcy";
    vector<string> P={"abcd","bcd","dab"};
    int m=P[0].size();
    unordered_set<string> st(P.begin(),P.end());
    for(int i=0;i+m<=T.size();i++){
        string sub=T.substr(i,m);
        if(st.count(sub)) cout<<"Pattern at "<<i<<": "<<sub<<"\n";
    }
}