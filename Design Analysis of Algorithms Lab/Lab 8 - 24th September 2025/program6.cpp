#include <bits/stdc++.h>
using namespace std;

bool dfsCycle(int u,int p,vector<vector<int>>& adj,vector<bool>& vis){
    vis[u]=true;
    for(int v:adj[u]){
        if(!vis[v]){
            if(dfsCycle(v,u,adj,vis)) return true;
        } else if(v!=p) return true;
    }
    return false;
}

bool isCyclic(vector<vector<int>>& adj){
    int n=adj.size();
    vector<bool> vis(n,false);
    for(int i=0;i<n;i++)
        if(!vis[i] && dfsCycle(i,-1,adj,vis)) return true;
    return false;
}

int main(){
    vector<vector<int>> adj={{1},{0,2},{1,3},{2}};
    cout<<(isCyclic(adj)?"Cyclic":"Acyclic");
}