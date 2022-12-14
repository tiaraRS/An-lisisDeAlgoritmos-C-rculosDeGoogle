// EJERCICIO 3: Indicar cuál es la distancia máxima que se puede encontrar entre dos usuarios cualquiera de la red (asumiendo un grafo no-dirigido)
// EJERCICIO 4: Indiar cuál es la distancia promedio entre dos usuarios de la red (asumiendo un grafo no-dirigido)

#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <climits>
#include <assert.h>
#include <stdio.h>
#include <cmath>
#include "createGraph.h"
#define UNVISITED -1
#define epsilon 10e-4
using namespace std;
int INF = INT_MAX;

long long maxDistance = 0;
long double avgDistance = 0;
long double paths = 0;

/* ================================================================================================================
BFS para APSP (All-Pairs Shortest Path):

Se utilizó BFS para encontrar el camino más corto entre cada par de nodos del grafo.

Parámetros:
    - s: nodo inicial
    - graph: grafo como lista de adyacencias

================================================================================================================ */

vector<int> bfs(int s, const vector<vector<int>> &graph)
{
    vector<int> d(graph.size(), INF); // almacena la distancia desde el nodo fuente (s) hasta cada nodo
    d[s] = 0;
    queue<int> q; // almacena el orden de visitas
    q.push(s);    // comenzar en el primer nodo
    while (!q.empty())
    {
        int u = q.front();
        q.pop(); // queue: capa por capa

        // en esta etapa tenemos almacenado en d[u] la distancia mínima entre s y u
        if (d[u] > maxDistance)
        {
            maxDistance = d[u]; // actualizar valor de distancia máxima
        }

        // considerar solo distancias > 0 para el calculo de la distancia promedio
        if (d[u] > 0)
        {
            avgDistance += d[u];
            paths++;
        }

        for (auto neighbor : graph[u])
        {
            if (d[neighbor] == INF) // si no ha sido visitado
            {
                d[neighbor] = d[u] + 1; // visitar - actualizar distancia de nodo actual
                q.push(neighbor);       // encolar vecino
            }
        }
    }
    return d;
}

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
/*
==============================================================================================
    TESTS REALIZADOS:
    PRUEBAS REALIZADAS PARA PROBAR EL FUNCIONAMIENTO CORRECTO DEL ALGORITMO:
    Para correr las pruebas descomentar la línea 69 que llama a la función runTests() y volver a compilar y ejecutar,
    o ejecutar maxAndAvgDistanceTests.exe
==============================================================================================
*/

vector<vector<int>> proveGraph(int ver = 1)
{
    vector<vector<int>> graph;
    if (ver == 1)
    {
        graph.push_back(vector<int>({1, 2, 3}));          // 0
        graph.push_back(vector<int>({0, 3}));             // 1
        graph.push_back(vector<int>({0, 3, 5}));          // 2
        graph.push_back(vector<int>({0, 1, 2, 4, 6, 7})); // 3
        graph.push_back(vector<int>({3, 7}));             // 4
        graph.push_back(vector<int>({2, 6}));             // 5
        graph.push_back(vector<int>({5, 3, 7}));          // 6
        graph.push_back(vector<int>({6, 4, 3}));          // 7
    }
    if (ver == 2)
    {
        graph.push_back(vector<int>({1, 2}));       // 0
        graph.push_back(vector<int>({0, 3}));       // 1
        graph.push_back(vector<int>({0, 3, 5}));    // 2
        graph.push_back(vector<int>({1, 2, 4, 6})); // 3
        graph.push_back(vector<int>({3, 7}));       // 4
        graph.push_back(vector<int>({2, 6}));       // 5
        graph.push_back(vector<int>({5, 3, 7}));    // 6
        graph.push_back(vector<int>({6, 4}));       // 7
    }
    if (ver == 3) // igual que graph 2 pero con nodos 3 no conectados agregados
    {
        graph.push_back(vector<int>({1, 2}));       // 0
        graph.push_back(vector<int>({0, 3}));       // 1
        graph.push_back(vector<int>({0, 3, 5}));    // 2
        graph.push_back(vector<int>({1, 2, 4, 6})); // 3
        graph.push_back(vector<int>({3, 7}));       // 4
        graph.push_back(vector<int>({2, 6}));       // 5
        graph.push_back(vector<int>({5, 3, 7}));    // 6
        graph.push_back(vector<int>({6, 4}));       // 7
        graph.push_back(vector<int>({}));           // 8
        graph.push_back(vector<int>({}));           // 9
        graph.push_back(vector<int>({}));           // 10
    }
    if (ver == 4)
    {
        graph.push_back(vector<int>({1, 2}));       // 0
        graph.push_back(vector<int>({0, 3}));       // 1
        graph.push_back(vector<int>({0, 3, 5}));    // 2
        graph.push_back(vector<int>({1, 2, 4, 6})); // 3
        graph.push_back(vector<int>({3, 7}));       // 4
        graph.push_back(vector<int>({2, 6}));       // 5
        graph.push_back(vector<int>({5, 3, 7}));    // 6
        graph.push_back(vector<int>({6, 4}));       // 7
        graph.push_back(vector<int>({9}));          // 8
        graph.push_back(vector<int>({8, 10}));      // 9
        graph.push_back(vector<int>({9}));          // 10
    }
    return graph;
}

void runTest(int numTest, unordered_map<int, pair<double, int>> answers)
{
    maxDistance = 0;
    avgDistance = 0;
    paths = 0;
    cout << "------- TEST # " << numTest << "-------" << endl;
    vector<vector<int>> g = proveGraph(numTest);
    cout << "graph # " << numTest << " : " << endl;
    print(g);
    cout << endl
         << endl;
    vector<vector<int>> distance;
    int gsize = g.size();
    for (int node = 0; node < gsize; node++) // lanzar bfs desde cada nodo para calcular la distancia mínima de ese nodo a cada uno de los demás nodos
    {
        bfs(node, g);
    }
    cout << "La distancia maxima entre dos usuarios cualquiera de la red es " << maxDistance << endl;
    avgDistance = avgDistance / paths;
    cout << "La distancia promedio entre dos usuarios cualquiera de la red es " << avgDistance << endl;
    assert(abs(avgDistance - answers[numTest].first) <= epsilon);
    assert(maxDistance == answers[numTest].second);
}

void runTests()
{
    int numTests = 4;
    unordered_map<int, pair<double, int>> answers(numTests);
    answers.insert({1, {1.64286, 3}});
    answers.insert({2, {1.92857, 4}});
    answers.insert({3, {1.92857, 4}});
    answers.insert({4, {1.870968, 4}});
    for (int i = 1; i <= numTests; i++)
    {
        runTest(i, answers);
    }
}

int main()
{
    // runTests();
    vector<vector<int>> graph = createGraph("undirected");
    vector<vector<int>> distance;
    int gsize = graph.size();
    int lastNodeId = gsize - 1;
    for (int node = 0; node < gsize; node++) // lanzar bfs desde cada nodo para calcular la distancia mínima de ese nodo a cada uno de los demás nodos
    {
        printf("-> BFS at [ %d / %d ]\r", node, lastNodeId);
        bfs(node, graph);
    }
    cout << "La distancia máxima entre dos usuarios cualquiera de la red es " << maxDistance << endl;
    avgDistance = avgDistance / paths;
    cout << "La distancia promedio entre dos usuarios cualquiera de la red es " << avgDistance << endl;
    return 0;
}

// PARA COMPILAR: g++ -O2 -std=c++11 -Wall "-Wl,--stack=268435456" maxAndAvgDistance.cpp -o maxAndAvgDistance.exe
// PARA EJECUTAR LAS PRUEBAS: ejecutar archivo maxAndAvgDistanceTests.exe
// El resultado de la ejecución de los tests y las imagenes de los grafos de prueba se pueden ver en la carpeta testGraphs/maxAndAvgDistanceTests/maxAndAvgDistanceTests.out

//  RESULTADOS:
// 3. La distancia máxima entre dos usuarios cualquiera de la red es 6
// 4. La distancia promedio entre dos usuarios cualquiera de la red es 2.82836