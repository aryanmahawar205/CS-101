// ----- Q2: DP for optimal parenthesization -----
#include <bits/stdc++.h>
using namespace std;

void printOptimal(const vector<vector<int>> &s, int i, int j){
    if(i==j){ cout << "A" << i; return; }
    cout << "(";
    printOptimal(s, i, s[i][j]);
    printOptimal(s, s[i][j]+1, j);
    cout << ")";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cout << "Q2) Enter number of matrices n: ";
    if(!(cin >> n)) return 0;

    vector<long long> p(n+1);
    cout << "Enter dimensions array p[0..n] (n+1 integers): ";
    for(int i=0;i<=n;i++) cin >> p[i];

    const long long INF = (1LL<<62);
    vector<vector<long long>> m(n+1, vector<long long>(n+1, 0));
    vector<vector<int>> s(n+1, vector<int>(n+1, 0));

    for(int L=2; L<=n; ++L){
        for(int i=1; i<=n-L+1; ++i){
            int j = i + L - 1;
            m[i][j] = INF;
            for(int k=i; k<j; ++k){
                long long q = m[i][k] + m[k+1][j] + p[i-1]*p[k]*p[j];
                if(q < m[i][j]){
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }

    cout << "Minimum scalar multiplications: " << m[1][n] << "\n";
    cout << "Optimal Parenthesization: ";
    printOptimal(s, 1, n);
    cout << "\n";
    return 0;
}