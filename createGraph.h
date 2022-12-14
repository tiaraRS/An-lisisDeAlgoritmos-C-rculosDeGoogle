#include <iostream>
#include <fstream>
#include <dirent.h>
#include <sys/types.h>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <set>
using namespace std;

/* ================================================================================================================
mapNodes
Funcion que almacena genera un diccionario que mapea la representación original 
de los ids de los usuarios con un nuevo identificador int mas corto.
La representación la guarda sobre los parametros pasados por referencia:

unordered_map<string,int>& nodesMapStrToInt 
Ej: (110542479265736697332, 0)

unordered_map<int,string>& nodesMapIntToStr
Ej: (0, 110542479265736697332)

================================================================================================================ */

void mapNodes(string fileName, unordered_map<string,int>& nodesMapStrToInt, unordered_map<int,string>& nodesMapIntToStr, int& counter){
    ifstream infile;
    infile.open("gplus/"+fileName);
    printf("Reading %s ... \r",fileName.c_str());

    int dotPosition = fileName.find(".");
    string nodeId = fileName.substr(0,dotPosition);

    counter = nodesMapStrToInt.size();//nueva correccion
    nodesMapStrToInt.insert({ nodeId, counter });
    nodesMapIntToStr.insert({ counter, nodeId });
    
    string id1Str, id2Str;
    while(infile >> id1Str >> id2Str){
        // counter se actualiza cada que se añade un par
        counter = nodesMapStrToInt.size();
        int id1 = counter;
        
        nodesMapStrToInt.insert({ id1Str, id1});
        nodesMapIntToStr.insert({ id1, id1Str});
        
        counter = nodesMapStrToInt.size();
        int id2 = counter;
        
        nodesMapStrToInt.insert({ id2Str, id2 });
        nodesMapIntToStr.insert({ id2, id2Str });
    }
    infile.close();
}

void getSetOfNodes(string fileName, unordered_map<string,int>& nodesMapStrToInt, unordered_map<int,string>& nodesMapIntToStr, set<int>& setOfNodes, int& counter){
    ifstream infile;
    infile.open("gplus/"+fileName);
    printf("Reading %s ... \r",fileName.c_str());

    int dotPosition = fileName.find(".");
    string nodeId = fileName.substr(0,dotPosition);
    nodesMapStrToInt.insert({ nodeId, counter });
    nodesMapIntToStr.insert({ counter, nodeId });
    setOfNodes.insert(counter);

    string id1Str, id2Str;
    while(infile >> id1Str >> id2Str){

        counter = nodesMapStrToInt.size();
        int id1 = counter;
        
        setOfNodes.insert(id1);
        nodesMapStrToInt.insert({ id1Str, id1});
        nodesMapIntToStr.insert({ id1, id1Str});
        
        counter = nodesMapStrToInt.size();
        int id2 = counter;
        
        setOfNodes.insert(id2);
        nodesMapStrToInt.insert({ id2Str, id2 });
        nodesMapIntToStr.insert({ id2, id2Str });
    }
}

/* ================================================================================================================
getGraphSet
Funcion que almacena el grafo en forma de lista de adyacencias
en una estructura vector<unordered_set<int>> graph
Esta funcion sera llamada por cada archivo '.edges' de la carpeta gplus
Parametros
- string filename: (nodeId) el nombre del archivo '.edges' que abrira para obtener la 
  lista de los nodos a los conecta nodeId
- unordered_map<string,int> nodesMapStrToInt: diccionario que mapea la representación original 
  de los ids de los usuarios con un nuevo identificador int mas corto.
  Ej: (110542479265736697332, 0) <str,int>
================================================================================================================ */

void getGraphSet(string fileName, unordered_map<string,int>& nodesMapStrToInt, vector<unordered_set<int>>& graph){
    ifstream infile;
    infile.open("gplus/"+fileName);
    int dotPosition = fileName.find(".");
    
    string nodeIdStr = fileName.substr(0,dotPosition);
    int nodeId = nodesMapStrToInt[nodeIdStr];
    printf("Reading %s ... \r",fileName.c_str());
    string id1Str, id2Str;

    //set de usuarios con los que se conecta el el usuario nodeId (<nodeId>.edges)
    unordered_set<int> nodesInFile;
    while(infile >> id1Str >> id2Str){
        //mapeando los nodos a partir de la representacion original
        int id1 = nodesMapStrToInt[id1Str];
        int id2 = nodesMapStrToInt[id2Str];
        //creando arco de id1 -> id2
        graph[id1].insert(id2);
        
        nodesInFile.insert(id1);
        nodesInFile.insert(id2);
    }
    for(auto idx:nodesInFile){
        //creando arco de (fileName) nodeId -> idx  
        graph[nodeId].insert(idx);
    }
}

void getUndirectedGraphSet(string fileName, unordered_map<string,int>& nodesMapStrToInt, vector<unordered_set<int>>& graph){
    ifstream infile;
    infile.open("gplus/"+fileName);
    int dotPosition = fileName.find(".");
    string nodeIdStr = fileName.substr(0,dotPosition);
    int nodeId = nodesMapStrToInt[nodeIdStr];
    printf("Reading %s ... \r",fileName.c_str());
    string id1Str, id2Str;
    unordered_set<int> nodesInFile;
    while(infile >> id1Str >> id2Str){
        int id1 = nodesMapStrToInt[id1Str];
        int id2 = nodesMapStrToInt[id2Str];
        graph[id1].insert(id2);
        graph[id2].insert(id1);
        nodesInFile.insert(id1);
        nodesInFile.insert(id2);
    }
    for(auto it:nodesInFile){
        graph[nodeId].insert(it);
        graph[it].insert(nodeId);
    }
}

/* ================================================================================================================
getGraphAdjList
================================================================================================================ */

vector<vector<int>> getGraphAdjList(vector<unordered_set<int>>& graphSet){
    vector<vector<int>> graph;
    for(auto nodeAdj:graphSet){
        vector<int> adj = vector<int>(nodeAdj.begin(),nodeAdj.end()); 
        graph.push_back(adj);
    }
    return graph;
}

map<int,vector<int>> getGraphMapAdjList(vector<unordered_set<int>>& graphSet){
    map<int,vector<int>> graph;
    int i = 0;
    for(auto nodeAdj:graphSet){
        vector<int> adj = vector<int>(nodeAdj.begin(),nodeAdj.end()); 
        graph[i] = adj;
        i++;
    }
    return graph;
}

/* ================================================================================================================
createGraph
================================================================================================================ */

vector<vector<int>> createGraph(string edgeDirection = "directed"){
    bool undirected = edgeDirection == "undirected";
    unordered_map<string,int> nodesStrToInt;
    unordered_map<int,string> nodesIntToStr;
    vector<vector<int>> graph;

    // nodesId \in [0;102118]
    int counter = 0;
    DIR *dr;
    struct dirent *en;
    dr = opendir("./gplus"); //open all directory
    if (dr) {
        cout << endl<< "Mapping nodes"<<endl;
        while ((en = readdir(dr)) != NULL) {
            string fileName = en->d_name;
            int dotPosition = fileName.find(".");
            string extension = fileName.substr(dotPosition+1);
            if(extension=="edges"){
                mapNodes(fileName,nodesStrToInt,nodesIntToStr,counter);
            }
        }
        vector<unordered_set<int>> graphSet(nodesStrToInt.size(),unordered_set<int>());
        struct dirent *en;
        dr = opendir("./gplus");
        cout <<endl<<endl<< "Creating graph"<<endl;
        while ((en = readdir(dr)) != NULL) {
            string fileName = en->d_name;
            int dotPosition = fileName.find(".");
            string extension = fileName.substr(dotPosition+1);
            if(extension=="edges"){
                if ( undirected ){
                    getUndirectedGraphSet(fileName,nodesStrToInt,graphSet);
                }
                else {
                    getGraphSet(fileName,nodesStrToInt,graphSet);
                }
            }
        }
        cout <<endl;
        closedir(dr); //close all directory
        graph = getGraphAdjList(graphSet);
    }
    return graph;
}



map<int,vector<int>> createGraphMap(string edgeDirection = "directed"){
    bool undirected = edgeDirection == "undirected";
    unordered_map<string,int> nodesStrToInt;
    unordered_map<int,string> nodesIntToStr;
    map<int,vector<int>> graph;
    int counter = 0;
    DIR *dr;
    struct dirent *en;
    dr = opendir("./gplus"); //open all directory
    if (dr) {
        cout << endl<< "Mapping nodes"<<endl;
        while ((en = readdir(dr)) != NULL) {
            string fileName = en->d_name;
            int dotPosition = fileName.find(".");
            string extension = fileName.substr(dotPosition+1);
            if(extension=="edges"){
                mapNodes(fileName,nodesStrToInt,nodesIntToStr,counter);
            }
        }
        ofstream outfile;
        outfile.open("cliques/nodesMapIntStr.out");
        for (auto el:nodesIntToStr){
            outfile << " " << el.first << " " << el.second << endl;
            //cout << el.first << " " << el.second << endl;
        }
        outfile.close();
        vector<unordered_set<int>> graphSet(nodesStrToInt.size(),unordered_set<int>());
        struct dirent *en;
        dr = opendir("./gplus");
        cout <<endl<<endl<< "Creating graph"<<endl;
        while ((en = readdir(dr)) != NULL) {
            string fileName = en->d_name;
            int dotPosition = fileName.find(".");
            string extension = fileName.substr(dotPosition+1);
            if(extension=="edges"){
                if ( undirected ){
                    getUndirectedGraphSet(fileName,nodesStrToInt,graphSet);
                }
                else {
                    getGraphSet(fileName,nodesStrToInt,graphSet);
                }
            }
        }
        cout <<endl;
        closedir(dr); //close all directory
        graph = getGraphMapAdjList(graphSet);
    }
    return graph;
}