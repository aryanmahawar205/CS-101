#include <bits/stdc++.h>
using namespace std;

bool match2D(vector<string>& T, vector<string>& P, int x, int y){
    int m=P.size();
    for(int i=0;i<m;i++)
        for(int j=0;j<m;j++)
            if(T[x+i][y+j]!=P[i][j]) return false;
    return true;
}

int main(){
    vector<string> T={"abcd","efgh","ijkl","mnop"};
    vector<string> P={"fg","jk"};
    int n=T.size(), m=P.size();
    for(int i=0;i<=n-m;i++){
        for(int j=0;j<=n-m;j++){
            if(match2D(T,P,i,j))
                cout<<"Pattern at ("<<i<<","<<j<<")\n";
        }
    }
}