#include <set>
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>
#include <climits>
#include <chrono>
#include <stdio.h>
#include <string.h>
#include "createGraph.h"
using namespace std;
int INF  = INT_MAX;

//Optimización no exitosa
// int min(set<int>& u,map<int,vector<int>>& graph){
    // int minOrder = INF;
    // int nodeOfMinOrder;
    // for(auto node:u){
    //     int nodeOrder = graph[node].size();
    //     if (nodeOrder<minOrder){
    //         minOrder = nodeOrder;
    //         nodeOfMinOrder = node;
    //     }
    // }
    // return nodeOfMinOrder;
// }

int min(set<int>& u,map<int,vector<int>>& graph){
    return *u.begin();
}

map<int,string> nodesMapIntToStr;

set<int> maxClique;
set<int> currentClique;

void print(set<int> clique){
    for(auto el:clique){
        cout<<nodesMapIntToStr[el]<<" ";
    }
}

int maxCliqueSize = 0;//tamaño del clique mas grande
/*
set<int> u: lista de candidatos
*/
void clique(set<int> u,int size, map<int,vector<int>>& graph){
    if(u.size()==0){
        if(size > maxCliqueSize){
            maxCliqueSize = size;//Guardar el tamaño del clique mas grande encontrado hasta el momento
            maxClique = currentClique;//Guardar el clique
            cout << "---------------------------------"<<endl;
            cout << "maxClique size: " << maxCliqueSize<<endl;
            cout << "maxClique: " ;
            print(maxClique);
            cout << endl;
        }
        return;
    }
    while(!u.empty()){
        if(size+u.size() <= (unsigned)maxCliqueSize){
            return;
        }
        
        //asumiendo que el grafo esta ordenado de mayor a menor 
        //(segun el orden ded los vertices)
        int vi = min(u,graph); //vertice con menor cantidad de aristas en u
        auto viAdj = graph[vi]; //N(vi) - Adyacencias de vi

        currentClique.insert(vi);
        
        // U := U \ {vi}
        u.erase(vi);

        // U U N(vi)
        set<int> intersect;
        set<int> nvi(viAdj.begin(),viAdj.end());
        set_intersection(u.begin(), u.end(), nvi.begin(), nvi.end(),
        std::inserter(intersect, intersect.begin()));

        // recursividad hasta examinar todos los cliques
        clique(intersect,size+1,graph);
        currentClique.erase(vi);
    }
    return;
}

void resetGlobals(map<int,vector<int>>& graph){
    maxClique.clear();
    currentClique.clear();
    maxCliqueSize = 0;
    nodesMapIntToStr.clear();
    for(auto el:graph){
        nodesMapIntToStr[el.first] = to_string(el.first);
    }
}

void test1(){
    map<int,vector<int>> graph;
    graph[0] = {4,6};
    graph[1] = {3,7,8};
    graph[2] = {9,7,5,4};
    graph[3] = {1,8};
    graph[4] = {0,6,2};
    graph[5] = {9,2,7};
    graph[6] = {0,4};
    graph[7] = {5,9,2,1,8};
    graph[8] = {7,1,3};
    graph[9] = {7,5,2};
    set<int> u = {1,2,3,4,5,6,7,8,9};
    resetGlobals(graph);
    clique(u,0,graph);
    cout << endl << "-> Max clique size "<< maxCliqueSize <<endl;
    cout << "-> ";
    print(maxClique);
    cout << endl << endl << endl;
}

void test2(){
    map<int,vector<int>> graphWithComponents;
    graphWithComponents[0] = {};
    graphWithComponents[1] = {2,3,4};
    graphWithComponents[3] = {1,2,4,5};
    graphWithComponents[5] = {2,3,4};
    graphWithComponents[4] = {1,2,3,5};
    graphWithComponents[2] = {1,3,4,5};

    graphWithComponents[6] = {7,8,9,10};
    graphWithComponents[7] = {6,8,9,10};
    graphWithComponents[8] = {6,7,9,10};
    graphWithComponents[9] = {6,7,8,10};
    graphWithComponents[10] = {6,7,8,9};

    resetGlobals(graphWithComponents);
    set<int> u = {1,2,3,4,5,6,7,8,9,10};
    clique(u,0,graphWithComponents);
    cout << endl << "-> Max clique size "<< maxCliqueSize <<endl;
    cout << "-> ";
    print(maxClique);
    cout << endl << endl << endl;
}

void test3(){
    //grafo paper A fast algorithm for the maximum clique problem
    map<int,vector<int>> graph;
    graph[0] = {};
    graph[1] = {3,5,6,8};
    graph[3] = {1,6,7,8};
    graph[5] = {1,2,7,8};
    graph[6] = {1,2,3,4};
    graph[7] = {2,3,4,5};
    graph[8] = {1,3,4,5};
    graph[4] = {6,7,8};
    graph[2] = {5,6,7};
    set<int> u = {1,2,3,4,5,6,7,8};
    resetGlobals(graph);
    clique(u,0,graph);
    cout << endl << "-> Max clique size "<< maxCliqueSize <<endl;
    // maxCliqueSize expected : 3
    cout << "-> ";
    print(maxClique);
    cout << endl << endl << endl;
}

void testCliques(){
    cout << "TEST 1 (Grafo, Figura 1)"<<endl;
    cout << "================================="<<endl;
    test1();
    cout << "TEST 2 (Grafo, Figura 2)"<<endl;
    cout << "================================="<<endl;
    test2();
    cout << "TEST 3 (Grafo, Figura 3)"<<endl;
    cout << "================================="<<endl;
    test3();
}

int main(int argc, char* argv[]){
    if (argc > 1 && argv[1][1] == 't'){
        testCliques();
    }
    else{
        std::string outFilename = "cliques/nodesMapIntStr.out";
        if (argc == 3 && argv[1][1] == 'o'){
            outFilename = argv[2];
            outFilename = "cliques/" + outFilename;
            cout << "saving graph map in "<< outFilename << endl;
        }
        ofstream outfile;
        outfile.open("cliques/maxClique.out");
        const auto p1 = std::chrono::system_clock::now();
        outfile << "timestamp creating resources: "<< std::chrono::duration_cast<std::chrono::seconds>(p1.time_since_epoch()).count() << '\n';
        cout << "timestamp creating resources: "<< std::chrono::duration_cast<std::chrono::seconds>(p1.time_since_epoch()).count() << '\n';

        map<int,vector<int>> graph = createGraphMap("undirected",outFilename);
        ifstream infile;
        infile.open(outFilename);
        int idInt;
        string idStr;
        while(infile >> idInt >> idStr){
            nodesMapIntToStr[idInt] = idStr;
        }
        infile.close();
        
        set<int> setOfNodes;
        for(unsigned int counter = 0; counter < graph.size() ; counter++){
            setOfNodes.insert(counter);
        }
        
        cout << endl <<endl <<"Calculating the maximum clique ... "<<endl;

        const auto ps = std::chrono::system_clock::now();
        outfile << "timestamp start: "<< std::chrono::duration_cast<std::chrono::seconds>(ps.time_since_epoch()).count() << '\n';
        cout << "timestamp start: "<< std::chrono::duration_cast<std::chrono::seconds>(ps.time_since_epoch()).count() << '\n';

        // ==========================
        // Calculating the maximum clique ...
        clique(setOfNodes,0,graph);
        
        const auto p2 = std::chrono::system_clock::now();
        
        outfile << "timestamp end: "<< std::chrono::duration_cast<std::chrono::seconds>(p2.time_since_epoch()).count() << '\n';
        cout << "timestamp end: "<< std::chrono::duration_cast<std::chrono::seconds>(p2.time_since_epoch()).count() << '\n';
        
        cout << "Max clique size "<< maxCliqueSize <<endl;
        for(auto el:maxClique){
            outfile << nodesMapIntToStr[el]<<" ";
            cout<<nodesMapIntToStr[el]<<" ";
        }
        cout << endl;
        outfile << endl;
        outfile.close();
    }
}


