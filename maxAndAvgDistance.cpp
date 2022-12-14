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
int INF  = INT_MAX;

int maxDistance = 0;
long double avgDistance = 0;
long double paths = 0;

vector<int> bfs(int s, vector<vector<int>>& graph){
    vector<int> d(graph.size(), INF);
    d[s] = 0; // distance from source s to s is 0
    queue<int> q;
    q.push(s); // start from source
    while (!q.empty()) {
        
        int u = q.front(); q.pop(); // queue: layer by layer!
        if (d[u] > maxDistance){
            maxDistance = d[u];
        }

        //considerar solo distancias > 0 para el calculo de la distancia promedio
        if (d[u] > 0){
            avgDistance += d[u];
            paths++;
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

//TODO refactorizar como pruebas + figuras en drawio o mermaid
vector<vector<int>> proveGraph(int ver = 1){
    vector<vector<int>> graph;
    if (ver == 1 ){
        graph.push_back(vector<int>({1,2,3}));//0
        graph.push_back(vector<int>({0,3}));//1
        graph.push_back(vector<int>({0,3,5}));//2
        graph.push_back(vector<int>({0,1,2,4,6,7}));//3
        graph.push_back(vector<int>({3,7}));//4
        graph.push_back(vector<int>({2,6}));//5
        graph.push_back(vector<int>({5,3,7}));//6
        graph.push_back(vector<int>({6,4,3}));//7
    }
    if(ver == 2){
        graph.push_back(vector<int>({1,2}));//0
        graph.push_back(vector<int>({0,3}));//1
        graph.push_back(vector<int>({0,3,5}));//2
        graph.push_back(vector<int>({1,2,4,6}));//3
        graph.push_back(vector<int>({3,7}));//4
        graph.push_back(vector<int>({2,6}));//5
        graph.push_back(vector<int>({5,3,7}));//6
        graph.push_back(vector<int>({6,4}));//7
    }
    if(ver == 3){
        graph.push_back(vector<int>({1,2}));//0
        graph.push_back(vector<int>({0,3}));//1
        graph.push_back(vector<int>({0,3,5}));//2
        graph.push_back(vector<int>({1,2,4,6}));//3
        graph.push_back(vector<int>({3,7}));//4
        graph.push_back(vector<int>({2,6}));//5
        graph.push_back(vector<int>({5,3,7}));//6
        graph.push_back(vector<int>({6,4}));//7
        graph.push_back(vector<int>({9}));//8
        graph.push_back(vector<int>({8}));//9
    }
    if(ver == 4){
        graph.push_back(vector<int>({1,2}));//0
        graph.push_back(vector<int>({0,3}));//1
        graph.push_back(vector<int>({0,3,5}));//2
        graph.push_back(vector<int>({1,2,4,6}));//3
        graph.push_back(vector<int>({3,7}));//4
        graph.push_back(vector<int>({2,6}));//5
        graph.push_back(vector<int>({5,3,7}));//6
        graph.push_back(vector<int>({6,4}));//7
        graph.push_back(vector<int>({9}));//8
        graph.push_back(vector<int>({8,10}));//9
        graph.push_back(vector<int>({11,9}));//10
        graph.push_back(vector<int>({10,12}));//11
        graph.push_back(vector<int>({11,13}));//12
        graph.push_back(vector<int>({12}));//13
    }
    
    return graph;
}

void print(vector<vector<int>> graph){
    int n = 0;
    for(auto adjList:graph){
        cout << n << " -> ";
        for(auto node:adjList){
            cout << node << " ";
        }
        cout << endl;
        n++;
    }
}

int main(){
    vector<vector<int>> graph = createGraph("undirected");
    // vector<vector<int>> g = proveGraph(4);
    // print(g);
    vector<vector<int>> distance;
    int gsize = graph.size();
    int lastNodeId = gsize - 1;
    for(int node = 0; node < gsize; node++){
        printf("-> BFS at [ %d / %d ]\r",node,lastNodeId);
        bfs(node,graph);
    }
    cout << "La distancia máxima entre dos usuarios cualquiera de la red es " << maxDistance << endl;
    avgDistance = avgDistance / paths;
    cout << "La distancia promedio entre dos usuarios cualquiera de la red es " << avgDistance << endl;
    return 0;
}
//g++ -O2 -std=c++11 -Wall "-Wl,--stack=268435456" numberOfScc.cpp -o scc2.exe
// La distancia m├íxima entre dos usuarios cualquiera de la red es 6
// La distancia promedio entre dos usuarios cualquiera de la red es 2.82836