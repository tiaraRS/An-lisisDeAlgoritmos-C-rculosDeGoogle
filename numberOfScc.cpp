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

int id = -1;
int sccCount = 0;

//tarjans
void dfs(int current){
    ids[current] = low[current] = ++id;
    stackG.push(current);
    onStack[current] = true;
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
    
    visited = vector<bool>(g.size(), false);;
    ids = vector<int>(g.size(), UNVISITED);
    low = vector<int>(g.size(), 0);
    onStack = vector<bool>(g.size(), false);;
    stackG = stack<int>();
    
    id = 0;
    sccCount = 0;
    cout <<endl<<endl<< "SCCs counting"<<endl;
    vector<int> lowVals = findSCCs(g.size());
    cout << "La red tiene " << sccCount << " componentes fuertemente conexas"<<endl;

    return 0;
}