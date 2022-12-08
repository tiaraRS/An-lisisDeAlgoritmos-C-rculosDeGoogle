#include <iostream>
#include <vector>
#include <stack>
#include "createGraph.h"
#define UNVISITED -1

using namespace std;

vector<bool> visited;
vector<int> ids;
vector<int> low;
stack<int> stackG;
vector<bool> onStack;
vector<vector<int>> g;
int id = 0;
int sccCount = 0;
void dfs(int current)
{
    // cout << "current " << current << endl;
    // cout << "g[current] size " << g[current].size() << endl;
    ids[current] = low[current] = ++id;
    stackG.push(current);
    // cout<<"stackG push pasa"<<endl;
    onStack[current] = true;
    //  cout<<"onstack pasa"<<endl;
    for (auto neighbor : g[current])
    {
        //  cout<<"neighbor = "<<neighbor<<endl;
        if (ids[neighbor] == UNVISITED)
        {
            dfs(neighbor);
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
void printGraph(const vector<vector<int>> &graph, int N)
{
    for (int i = 1; i <= N; i++)
    {
        cout << "i = " << i << endl;
        cout << i << " -> [ ";
        for (int j = 0; j < graph[i].size(); j++)
        {
            cout << graph[i][j] << ", ";
        }
        cout << " ]" << endl;
    }
}
vector<int> findSCCs(int N)
{ // lista de adyacencia
    // cout << "ids 0 " << ids[0] << endl;
    for (int i = 0; i < N; i++)
    {
        // cout << "ids "<< i << " "<< ids[i] << endl;
        if (ids[i] == UNVISITED)
        {
            dfs(i);
        }
    }
    return low;
}

int main()
{
    g = createGraph();
    cout << g.size();
    cout << g[0].size() << endl;
    vector<int> low1(g.size(), 0);
    vector<bool> visited1(g.size(), false);
    vector<int> ids1(g.size(), UNVISITED);
    vector<bool> onStack1(g.size(), false);
    visited = visited1;
    ids = ids1;
    low = low1;
    onStack = onStack1;
    stackG = stack<int>();
    id = 0;
    sccCount = 0;
    cout << "SCCs counting"<<endl;
    vector<int> lowVals = findSCCs(g.size());
    int s = sccCount;
    cout << "La red tiene " << sccCount << " componentes fuertemente conexas"<<endl;
}