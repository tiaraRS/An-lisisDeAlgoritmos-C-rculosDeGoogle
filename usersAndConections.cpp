#include <iostream>
#include <sys/types.h>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "createGraph.h"

using namespace std;

int numberOfNodes(vector<vector<int>> graph){
    return graph.size();
}

int numberOfEdges(vector<vector<int>> graph){
    int nEdges = 0;
    for(auto nodeAdj:graph){
        nEdges+=nodeAdj.size();
    }
    return nEdges;
}

int main(){
    vector<vector<int>> graph = createGraph();
    cout << endl << "El número total de usuarios en la red " << numberOfNodes(graph) << endl;
    cout << "El número total de conexiones en la red " << numberOfEdges(graph) << endl;
    return 0;
}

// El número total de usuarios en la red 102119
// El número total de conexiones en la red 13667810