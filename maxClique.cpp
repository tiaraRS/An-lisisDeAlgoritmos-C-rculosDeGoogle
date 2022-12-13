#include <set>
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>
using namespace std;

int min(set<int> u){
    int min = 10000000;
    for(auto el:u){
        if (el<min){
            min = el;
        } 
    }
    return min;
}

int maxCliqueSize = 0;//tamaño del clique mas grande
void clique(set<int> u,int size, map<int,vector<int>>& graph){
    // cout << "size: "<< size << endl;
    // cout << "u size: "<< u.size() << endl;
    if(u.size()==0){
        if(size > maxCliqueSize){
            maxCliqueSize = size;
            //Guardar el clique
        }
        return;
    }
    while(!u.empty()){
        if(size+u.size() <= maxCliqueSize){
            // for(auto el:u){
            //     cout<<el<<" ";
            // }
            // cout <<endl;
            return;
        }
        //asumiendo que el grafo esta ordenado de mayor a menor
        int vi = min(u);
        cout << "vi " << vi <<endl;
        auto viAdj = graph[vi];//N(vi)
        // cout << "vi adj " << viAdj[0] <<endl;
        u.erase(vi);
        set<int> intersect;
        //to do sort
        set<int> nvi(viAdj.begin(),viAdj.end());
        set_intersection(u.begin(), u.end(), nvi.begin(), nvi.end(),
        std::inserter(intersect, intersect.begin()));
        // cout << "intersect pass " <<endl;
        clique(intersect,size+1,graph);
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

int main(){
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
    // map<int,vector<int>> graph2;
    // graph2[0] = {};
    // graph2[1] = {2,3,4,5};
    // graph2[3] = {1,2,4,5};
    // graph2[5] = {1,2,3,4};
    // graph2[4] = {1,2,3,5};
    // graph2[2] = {1,3,4,5};
    // set<int> u = {1,2,3,4,5};
    set<int> u = {1,2,3,4,5,6,7,8};
    clique(u,0,graph);
    cout << "Max clique size "<< maxCliqueSize <<endl;
}