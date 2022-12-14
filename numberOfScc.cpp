#include <iostream>
#include <vector>
#include <stack>
#include "createGraph.h"
#define UNVISITED -1

using namespace std;

// Tarjan's Algorithm

/* ================================================================================================================
DFS para Algoritmo de Tarjan:


================================================================================================================ */
void dfs(int current, int &id, int &sccCount, const vector<vector<int>> &g, vector<bool> &visited, vector<int> &ids, vector<int> &low, stack<int> &stackG, vector<bool> &onStack)
{
    ids[current] = low[current] = ++id;
    stackG.push(current);
    onStack[current] = true;
    for (auto neighbor : g[current])
    {
        if (ids[neighbor] == UNVISITED)
        {
            dfs(neighbor, id, sccCount, g, visited, ids, low, stackG, onStack);
        }
        if (onStack[neighbor])
        {
            low[current] = min(low[current], low[neighbor]);
        }
    }
    if (ids[current] == low[current])
    {
        int node = stackG.top(); // new scc
        while (stackG.top() != current)
        {
            node = stackG.top();
            stackG.pop();
            onStack[node] = false;
            low[node] = ids[current];
        }
        node = stackG.top();
        onStack[node] = false;
        stackG.pop(); // remove current from stack
        sccCount++;
    }
}

pair<int, vector<int>> findSCCs(int N, const vector<vector<int>> &g)
{ // lista de adyacencia
    vector<bool> visited;
    vector<int> ids;
    vector<int> low;
    stack<int> stackG;
    vector<bool> onStack;

    visited = vector<bool>(g.size(), false);
    ids = vector<int>(g.size(), UNVISITED);
    low = vector<int>(g.size(), 0);
    onStack = vector<bool>(g.size(), false);
    stackG = stack<int>();
    int id = 0;
    int sccCount = 0;
    for (int i = 0; i < N; i++)
    {
        if (ids[i] == UNVISITED)
        {
            dfs(i, id, sccCount, g, visited, ids, low, stackG, onStack);
        }
    }
    return {sccCount, low};
}

int main()
{
    vector<vector<int>> g;
    g = createGraph();
    cout << endl
         << endl
         << "SCCs counting" << endl;
    auto sccResult = findSCCs(g.size(), g);
    cout << "La red tiene " << sccResult.first << " componentes fuertemente conexas" << endl;

    return 0;
}