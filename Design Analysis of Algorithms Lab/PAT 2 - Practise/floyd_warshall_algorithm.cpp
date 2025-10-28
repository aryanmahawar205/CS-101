// Floyd Warshall Algorithm (All pair shortest path):

#include <bits/stdc++.h>

using namespace std;

int main()
{
    int vertex, edge;
    cout << "Enter the no. of vertices in the graph - ";
    cin >> vertex;
    cout << "Enter the no. of edges in the graph - ";
    cin >> edge;
    
    vector<vector<int>> graph(vertex, vector<int>(vertex, 0));
    
    // assign intially all weights as 1e9 (meaning not reachable) and diagonals cost as 0 due to self loop
    for (int i = 0; i < vertex; i++)
    {
        for (int j = 0; j < vertex; j++)
        {
            graph[i][j] = 1e9;
            
            if (i == j)
                graph[i][j] = 0;
        }
    }
    
    int u, v, weight; // edge relationships between vertices u and v with corresponding edge weight
    cout << "Enter the edge relationships with weight - \n";
    
    for (int i = 0; i < edge; i++)
    {
        cin >> u >> v >> weight;
        graph[u][v] = weight;
    }
    
    // actual floyd warshall starts
    for (int k = 0; k < vertex; k++)
    {
        for (int i = 0; i < vertex; i++)
        {
            for (int j = 0; j < vertex; j++)
                graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j]);
        }
    }
    
    // print the graph
    cout << endl << "The graph is - " << endl;
    for (int i = 0; i < vertex; i++)
    {
        for (int j = 0; j < vertex; j++)
            cout << graph[i][j] << " ";
        cout << endl;
    }
    
    return 0;
}