// EJERCICIO 5: Indicar cuántas componentes fuertemente conexas tiene la red

#include <iostream>
#include <vector>
#include <stack>
#include <assert.h>
#include <stdio.h>
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

/*
==============================================================================================
    TESTS REALIZADOS:
    PRUEBAS REALIZADAS PARA PROBAR EL FUNCIONAMIENTO CORRECTO DEL ALGORITMO:
    Para correr las pruebas ejecutar numberOfSccTests.exe
==============================================================================================
*/

void print(vector<vector<int>> graph)
{
    int n = 0;
    for (auto adjList : graph)
    {
        cout << n << " -> ";
        for (auto node : adjList)
        {
            cout << node << " ";
        }
        cout << endl;
        n++;
    }
}

vector<vector<int>> proveGraph(int ver = 1)
{
    vector<vector<int>> graph;
    if (ver == 1)
    {
        graph.push_back(vector<int>({1, 2}));    // 0
        graph.push_back(vector<int>({0, 3}));    // 1
        graph.push_back(vector<int>({0, 3}));    // 2
        graph.push_back(vector<int>({4}));       // 3
        graph.push_back(vector<int>({3}));       // 4
        graph.push_back(vector<int>({2, 4, 7})); // 5
        graph.push_back(vector<int>({5}));       // 6
        graph.push_back(vector<int>({4, 6}));    // 7
        graph.push_back(vector<int>({7, 6, 8})); // 8
    }
    if (ver == 2)
    {
        graph.push_back(vector<int>({1, 2}));    // 0
        graph.push_back(vector<int>({0, 3}));    // 1
        graph.push_back(vector<int>({0, 3}));    // 2
        graph.push_back(vector<int>({4}));       // 3
        graph.push_back(vector<int>({3}));       // 4
        graph.push_back(vector<int>({2, 4, 7})); // 5
        graph.push_back(vector<int>({5}));       // 6
        graph.push_back(vector<int>({4, 6}));    // 7
    }
    if (ver == 3)
    {
        graph.push_back(vector<int>({1, 2}));    // 0
        graph.push_back(vector<int>({3}));       // 1
        graph.push_back(vector<int>({0, 3}));    // 2
        graph.push_back(vector<int>({}));        // 3
        graph.push_back(vector<int>({3}));       // 4
        graph.push_back(vector<int>({2, 4, 7})); // 5
        graph.push_back(vector<int>({5}));       // 6
        graph.push_back(vector<int>({4, 6}));    // 7
        graph.push_back(vector<int>({7, 6}));    // 8
    }
    if (ver == 4)
    {
        graph.push_back(vector<int>({})); // 0
        graph.push_back(vector<int>({})); // 1
        graph.push_back(vector<int>({})); // 2
        graph.push_back(vector<int>({})); // 3
        graph.push_back(vector<int>({})); // 4
        graph.push_back(vector<int>({})); // 5
        graph.push_back(vector<int>({})); // 6
        graph.push_back(vector<int>({})); // 7
    }
    return graph;
}

void runTest(int numTest, unordered_map<int, int> answers)
{
    cout << "------- TEST # " << numTest << "-------" << endl;
    vector<vector<int>> g = proveGraph(numTest);
    cout << "graph # " << numTest << " : " << endl;
    print(g);
    auto sccResult = findSCCs(g.size(), g);
    cout << "La red tiene " << sccResult.first << " componentes fuertemente conexas" << endl;
    cout << endl
         << endl;
    assert(sccResult.first == answers[numTest]);
}

void runTests()
{
    int numTests = 4;
    unordered_map<int, int> answers(numTests);
    answers.insert({1, 4});
    answers.insert({2, 3});
    answers.insert({3, 6});
    answers.insert({4, 8});
    for (int i = 1; i <= numTests; i++)
    {
        cout << "numTest = " << i << endl;
        runTest(i, answers);
    }
}

int main()
{
    // runTests();
    vector<vector<int>> g;
    g = createGraph();
    cout << endl
         << endl
         << "SCCs counting" << endl;
    auto sccResult = findSCCs(g.size(), g);
    cout << "La red tiene " << sccResult.first << " componentes fuertemente conexas" << endl;

    return 0;
}

// PARA COMPILAR: g++ -O2 -std=c++11 -Wall "-Wl,--stack=268435456" numberOfScc.cpp -o numberOfScc.exe
// PARA EJECUTAR LAS PRUEBAS: ejecutar archivo numberOfSccTests.exe
// El resultado de la ejecución de los testsy las imagenes de los grafos de prueba se pueden ver en la carpeta testGraphs/numberOfScc/numberOfSccTests.out

//  RESULTADO:
//  5. La red tiene 32308 componentes fuertemente conexas