// ----- Q1: Brute-force enumeration of all parenthesizations -----
#include <bits/stdc++.h>
using namespace std;

using Item = pair<long long,string>; // (cost, parenthesization)
vector<long long> P; // P[0..n], dims; Ai is P[i-1] x P[i]

vector<Item> enumerateAll(int i, int j){
    if(i == j) return { {0LL, "A" + to_string(i)} };
    vector<Item> ans;
    for(int k = i; k <= j-1; ++k){
        auto L = enumerateAll(i, k);
        auto R = enumerateAll(k+1, j);
        for(const auto &l : L){
            for(const auto &r : R){
                long long cost = l.first + r.first + P[i-1]*P[k]*P[j];
                string s = "(" + l.second + r.second + ")";
                ans.push_back({cost, s});
            }
        }
    }
    return ans;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cout << "Q1) Enter number of matrices n: ";
    if(!(cin >> n)) return 0;
    P.assign(n+1, 0);
    cout << "Enter dimensions array p[0..n] (n+1 integers): ";
    for(int i=0;i<=n;i++) cin >> P[i];

    auto all = enumerateAll(1, n);
    cout << "\nTotal parenthesizations: " << all.size() << "\n";
    for(const auto &e : all){
        cout << setw(10) << e.first << " : " << e.second << "\n";
    }
    return 0;
}