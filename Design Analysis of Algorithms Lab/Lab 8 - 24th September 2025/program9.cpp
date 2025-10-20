#include <bits/stdc++.h>
using namespace std;

vector<int> eulerTour(vector<vector<int>>& adj){
    int n=adj.size();
    vector<int> indeg(n,0), outdeg(n,0);
    for(int u=0;u<n;u++) for(int v:adj[u]) { outdeg[u]++; indeg[v]++; }
    for(int i=0;i<n;i++) if(indeg[i]!=outdeg[i]) return {};
    vector<stack<int>> g(n);
    for(int u=0;u<n;u++) for(int v:adj[u]) g[u].push(v);
    vector<int> path; stack<int> st; st.push(0);
    while(!st.empty()){
        int v=st.top();
        if(!g[v].empty()){
            int u=g[v].top(); g[v].pop();
            st.push(u);
        } else {
            path.push_back(v);
            st.pop();
        }
    }
    reverse(path.begin(),path.end());
    return path;
}

int main(){
    vector<vector<int>> adj={{1},{2},{0}};
    auto tour=eulerTour(adj);
    if(tour.empty()) cout<<"No Euler Tour\n";
    else{
        cout<<"Euler Tour: ";
        for(int x:tour) cout<<x<<" ";
    }
}