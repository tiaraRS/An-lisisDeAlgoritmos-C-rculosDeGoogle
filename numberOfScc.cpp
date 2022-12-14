#include <iostream>
#include <vector>
#include <stack>
#include "createGraph.h"
#define UNVISITED -1

using namespace std;

// Tarjan's Algorithm

/* ================================================================================================================
DFS para Algoritmo de Tarjan:

Este algoritmo hace uso de DFS para encontrar componentes fuertemente conexas.
Parámetros:
    - current: es el nodo actual
    - id: representa un identificador para cada nodo del grafo
    - sccCount: contador de componentes conexas del grafo
    - g: grafo como lista de adyacencias
    - visited: vector booleano que indica los nodos que han sido visitados y los que no
    - ids: vector que almacena los identificadores de cada nodo del grafo
    - low: vector que almacena low low-link values de los nodos del grafo, referidos como el menor id de nodo
           alcanzable desde ese nodo al realizar un DFS (incluyéndose a sí mismo)
    - stackG: pila para almacenar los nodos válidos para actualizar los low-link values
    - onStack: vector booleano que indica los nodos que se encuentran en la pila stackG
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
        if (onStack[neighbor]) // si se encuentra en la pila
        {
            low[current] = min(low[current], low[neighbor]); // actualizar el low-link value
        }
    }
    // después de visitar todos los vecinos
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

/* ================================================================================================================
findSCCs para Algoritmo de Tarjan:

Por cada nodo del grafo que no haya sido asignado un id, el algoritmo lanza un dfs desde el cual pretende encontrar
componentes fuertemente conexas.
================================================================================================================ */

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