//Indicar cuál es la distancia máxima que se puede encontrar 
// entre dos usuarios cualquiera de la red (asumiendo un grafo no-dirigido)
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <climits>
#include "createGraph.h"
#define UNVISITED -1
using namespace std;

int maxDistance = 0;
int INF  = INT_MAX;

vector<int> bfs(int s, vector<vector<int>>& graph){
    // inside int main()---no recursion
    vector<int> d(graph.size(), INF);
    d[s] = 0; // distance from source s to s is 0
    queue<int> q; 
    q.push(s); // start from source
    while (!q.empty()) {
        int u = q.front(); q.pop(); // queue: layer by layer!
        if (d[u] > maxDistance){
            maxDistance = d[u];
        }
        for (auto neighbor:graph[u]){
            if (d[neighbor] == INF) { // if v.first is unvisited + reachable
                d[neighbor] = d[u] + 1; // make d[v.first] != INF to flag it
                q.push(neighbor); // enqueue v.first for the next iteration
            }
        }
    }
    return d;
}



int main(){
    cout << INF << endl;
    vector<vector<int>> g = createGraph();
    vector<vector<int>> distance;
    int gsize = g.size() ;
    for(int node = 0; node < gsize; node++){
        cout << node << endl;
        bfs(node,g);
    }
    cout << "La distancia máxima entre dos usuarios cualquiera de la red es " << maxDistance << endl;
    return 0;
}
//g++ -O2 -std=c++11 -Wall "-Wl,--stack=268435456" numberOfScc.cpp -o scc2.exe