#include <bits/stdc++.h>
using namespace std;

void dfs(int u,vector<vector<int>>& adj,vector<bool>& vis){
    vis[u]=true;
    for(int v:adj[u]) if(!vis[v]) dfs(v,adj,vis);
}

bool isConnected(vector<vector<int>>& adj){
    int n=adj.size();
    vector<bool> vis(n,false);
    dfs(0,adj,vis);
    if(count(vis.begin(),vis.end(),true)!=n) return false;
    vector<vector<int>> radj(n);
    for(int u=0;u<n;u++) for(int v:adj[u]) radj[v].push_back(u);
    fill(vis.begin(),vis.end(),false);
    dfs(0,radj,vis);
    return count(vis.begin(),vis.end(),true)==n;
}

int main(){
    vector<vector<int>> adj={{1},{2},{0}};
    cout<<(isConnected(adj)?"Connected":"Not connected");
}