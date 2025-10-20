#include <bits/stdc++.h>
using namespace std;

void dfs1(int u,vector<vector<int>>& adj,vector<bool>& vis,stack<int>& st){
    vis[u]=true;
    for(int v:adj[u]) if(!vis[v]) dfs1(v,adj,vis,st);
    st.push(u);
}
void dfs2(int u,vector<vector<int>>& radj,vector<int>& comp,int cid){
    comp[u]=cid;
    for(int v:radj[u]) if(comp[v]==-1) dfs2(v,radj,comp,cid);
}

bool isSemiconnected(vector<vector<int>>& adj){
    int n=adj.size();
    vector<vector<int>> radj(n);
    for(int u=0;u<n;u++) for(int v:adj[u]) radj[v].push_back(u);
    vector<bool> vis(n,false); stack<int> st;
    for(int i=0;i<n;i++) if(!vis[i]) dfs1(i,adj,vis,st);
    vector<int> comp(n,-1); int cid=0;
    while(!st.empty()){
        int u=st.top(); st.pop();
        if(comp[u]==-1) dfs2(u,radj,comp,cid++);
    }
    if(cid==1) return true;
    vector<set<int>> dag(cid);
    vector<int> indeg(cid,0);
    for(int u=0;u<n;u++)
        for(int v:adj[u])
            if(comp[u]!=comp[v]) dag[comp[u]].insert(comp[v]);
    vector<int> topo; vector<int> indegree(cid,0);
    for(int i=0;i<cid;i++) for(int v:dag[i]) indegree[v]++;
    queue<int> q; for(int i=0;i<cid;i++) if(!indegree[i]) q.push(i);
    while(!q.empty()){
        int x=q.front(); q.pop(); topo.push_back(x);
        for(int v:dag[x]) if(--indegree[v]==0) q.push(v);
    }
    for(int i=0;i<cid-1;i++)
        if(!dag[topo[i]].count(topo[i+1])) return false;
    return true;
}

int main(){
    vector<vector<int>> adj={{1},{2},{0,3},{4},{5},{3}};
    cout<<(isSemiconnected(adj)?"Semiconnected":"Not semiconnected");
}