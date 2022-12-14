#include <set>
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>
#include <climits>
#include <chrono>
#include "createGraph.h"
using namespace std;
int INF  = INT_MAX;

//set esta ordenado
int min(set<int>& u){
    return *u.begin();
}

map<int,string> nodesMapIntToStr;

set<int> maxClique;
set<int> currentClique;

void print(set<int> clique){
    for(auto el:clique){
        cout<<nodesMapIntToStr[el]<<" ";
    }//TO DO print for tests
}

int maxCliqueSize = 0;//tamaño del clique mas grande
void clique(set<int> u,int size, map<int,vector<int>>& graph){
    // cout << "size: "<< size << endl;
    // cout << "u size: "<< u.size() << endl;
    if(u.size()==0){
        if(size > maxCliqueSize){
            maxCliqueSize = size;
            maxClique = currentClique;
            //Guardar el clique
            cout << "==============================="<<endl;
            cout << "maxClique size: " << maxCliqueSize<<endl;
            cout << "maxClique: " ;
            print(maxClique);
            cout << endl;
        }
        return;
    }
    while(!u.empty()){
        if(size+u.size() <= (unsigned)maxCliqueSize){
            // for(auto el:u){
            //     cout<<el<<" ";
            // }
            // cout <<endl;
            return;
        }
        //asumiendo que el grafo esta ordenado de mayor a menor
        int vi = min(u);
        // cout << "vi " << vi <<endl;
        auto viAdj = graph[vi];//N(vi)
        // cout << "vi adj " << viAdj[0] <<endl;
        currentClique.insert(vi);
        u.erase(vi);
        set<int> intersect;
        //to do sort
        set<int> nvi(viAdj.begin(),viAdj.end());
        set_intersection(u.begin(), u.end(), nvi.begin(), nvi.end(),
        std::inserter(intersect, intersect.begin()));
        // cout << "intersect pass " <<endl;
        // for(auto el:u){
        //     cout<<el<<" ";
        // }
        // cout <<endl;
        clique(intersect,size+1,graph);
        currentClique.erase(vi);
    }
    return;
}

void checkIntersection(){
    vector<int> viAdj = {1,2,3,4,5};
    set<int> intersect;
    set<int> u = {3,4,5,6,8};
    set<int> nvi(viAdj.begin(),viAdj.end());
    set_intersection(u.begin(), u.end(), nvi.begin(), nvi.end(),
        std::inserter(intersect, intersect.begin()));
    for(auto el:intersect){
        cout<<el<<" ";
    }
}
void checkIntersectionFail(){
    vector<int> viAdj = {1,2,3,4,5};
    set<int> intersect;
    set<int> u = {6,8};
    set<int> nvi(viAdj.begin(),viAdj.end());
    set_intersection(u.begin(), u.end(), nvi.begin(), nvi.end(),
        std::inserter(intersect, intersect.begin()));
    cout << intersect.empty() <<endl;
    cout << intersect.size() <<endl;
    for(auto el:intersect){
        cout<<el<<" ";
    }
}

void test1(){
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

    set<int> u = {1,2,3,4,5,6,7,8,9,10};
    clique(u,0,graphWithComponents);
    cout << endl << "-> Max clique size "<< maxCliqueSize <<endl;
    cout << "-> ";
    print(maxClique);
    cout << endl;
}

void test2(){
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
    clique(u,0,graph);
    cout << endl << "-> Max clique size "<< maxCliqueSize <<endl;
    cout << "-> ";
    print(maxClique);
    cout << endl;
}

void test0(){
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
    clique(u,0,graph);
    cout << endl << "-> Max clique size "<< maxCliqueSize <<endl;
    cout << "-> ";
    print(maxClique);
    cout << endl;
}

void resetGlobals(){
    maxClique.clear();
    currentClique.clear();
    maxCliqueSize = 0;
}

void testCliques(){
    test0();
    resetGlobals();
    test1();
    resetGlobals();
    test2();
    // map<int,vector<int>> graph;
    // graph[0] = {};
    // graph[1] = {3,5,8};
    // graph[3] = {1,6,7,8};
    // graph[5] = {1,2,7,8};
    // graph[6] = {2,3,4};
    // graph[7] = {2,3,4,5};
    // graph[8] = {1,3,4,5};
    // graph[4] = {6,7,8};
    // graph[2] = {5,6,7};
    // set<int> u = {1,2,3,4,5,6,7,8};
    // map<int,vector<int>> graph;
    // graph[0] = {};
    // graph[1] = {5,8};
    // graph[3] = {6,7,8};
    // graph[5] = {1,2,7,8};
    // graph[6] = {2,3,4};
    // graph[7] = {2,3,4,5};
    // graph[8] = {1,3,4,5};
    // graph[4] = {6,7,8};
    // graph[2] = {5,6,7};
    // set<int> u = {1,2,3,4,5,6,7,8};
    // map<int,vector<int>> graph;
    // graph[0] = {};
    // graph[1] = {5};
    // graph[3] = {6,7,8};
    // graph[5] = {1,2,7,8};
    // graph[6] = {2,3,4};
    // graph[7] = {2,3,4,5};
    // graph[8] = {3,4,5};
    // graph[4] = {6,7,8};
    // graph[2] = {5,6,7};
    // set<int> u = {1,2,3,4,5,6,7,8};
    // map<int,vector<int>> graph2;
    // graph2[0] = {};
    // graph2[1] = {2,3,4,5};
    // graph2[3] = {1,2,4,5};
    // graph2[5] = {1,2,3,4};
    // graph2[4] = {1,2,3,5};
    // graph2[2] = {1,3,4,5};
    // set<int> u = {1,2,3,4,5};
    // map<int,vector<int>> graph2;//3
    // graph2[0] = {};
    // graph2[3] = {1,2,4,5};
    // graph2[4] = {1,2,3,5};
    // graph2[2] = {1,3,4,5};
    // graph2[5] = {2,3,4};
    // graph2[1] = {2,3,4};
    // set<int> u = {1,2,3,4,5};
    
}

int main(){
    ofstream outfile;
    outfile.open("cliques/maxClique.out");
    const auto p1 = std::chrono::system_clock::now();
    outfile << "timestamp creating resources: "<< std::chrono::duration_cast<std::chrono::seconds>(p1.time_since_epoch()).count() << '\n';
    cout << "timestamp creating resources: "<< std::chrono::duration_cast<std::chrono::seconds>(p1.time_since_epoch()).count() << '\n';

    map<int,vector<int>> graph = createGraphMap();
    ifstream infile;
    infile.open("cliques/nodesMapIntStr.out");
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
    // testCliques();
}