#include <iostream>
#include <fstream>
#include <dirent.h>
#include <sys/types.h>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;

void getGraph(string fileName, unordered_map<string,int>& nodesMapStrToInt, vector<vector<int>>& graph){
    ifstream infile;
    infile.open("gplus/"+fileName);
    int dotPosition = fileName.find(".");
    string nodeIdStr = fileName.substr(0,dotPosition);
    int nodeId = nodesMapStrToInt[nodeIdStr];
    cout << "Reading "+fileName<<"... "<<endl;
    string id1Str, id2Str;
    unordered_set<int> nodesInFile;
    while(infile >> id1Str >> id2Str){
        int id1 = nodesMapStrToInt[id1Str];
        int id2 = nodesMapStrToInt[id2Str];
        graph[id1].push_back(id2);
        nodesInFile.insert(id1);
        nodesInFile.insert(id2);
    }
    for(auto it:nodesInFile){
        graph[nodeId].push_back(it);
    }
}

void mapNodes(string fileName, unordered_map<string,int>& nodesMapStrToInt, unordered_map<int,string>& nodesMapIntToStr, int& counter){
    ifstream infile;
    infile.open("gplus/"+fileName);
    cout << "Reading "+fileName<<"... "<<endl;

    int dotPosition = fileName.find(".");
    string nodeId = fileName.substr(0,dotPosition);
    nodesMapStrToInt.insert({ nodeId, counter });
    nodesMapIntToStr.insert({ counter, nodeId });

    string id1Str, id2Str;
    while(infile >> id1Str >> id2Str){
        counter = nodesMapStrToInt.size();
        int id1 = counter;
        
        nodesMapStrToInt.insert({ id1Str, id1});
        nodesMapIntToStr.insert({ id1, id1Str});
        
        counter = nodesMapStrToInt.size();
        int id2 = counter;
        
        nodesMapStrToInt.insert({ id2Str, id2 });
        nodesMapIntToStr.insert({ id2, id2Str });
    }
}


int main(){
    unordered_map<string,int> nodesStrToInt;
    unordered_map<int,string> nodesIntToStr;
    vector<vector<int>> graph(102120,vector<int>());
    int counter = 0;
    DIR *dr;
    struct dirent *en;
    dr = opendir("./gplus"); //open all directory
    if (dr) {
        cout << endl<< "Mapping nodes"<<endl<<endl;
        while ((en = readdir(dr)) != NULL) {
            string fileName = en->d_name;
            int dotPosition = fileName.find(".");
            string extension = fileName.substr(dotPosition+1);
            if(extension=="edges"){
                mapNodes(fileName,nodesStrToInt,nodesIntToStr,counter);
            }
        }
        struct dirent *en;
        dr = opendir("./gplus");
        cout <<endl<< "Creating graph"<<endl<<endl;
        while ((en = readdir(dr)) != NULL) {
            string fileName = en->d_name;
            int dotPosition = fileName.find(".");
            string extension = fileName.substr(dotPosition+1);
            if(extension=="edges"){
                getGraph(fileName,nodesStrToInt,graph);
            }
        }
        closedir(dr); //close all directory
        cout << graph[0].size() << endl;
        cout << nodesIntToStr[0] << " " << nodesIntToStr[graph[0][0]]<<endl;
        cout << graph[1].size() << endl;
        cout << nodesIntToStr[1] << " " << nodesIntToStr[graph[1][0]]<<endl;
        cout << nodesIntToStr[1] << " " << nodesIntToStr[(graph[1].back())]<<endl;
        cout << "Node 1 "<<endl;
        for(auto n:graph[1]){
            cout << nodesIntToStr[1] << " " << nodesIntToStr[n]<<endl;
        }
    }
    // for(auto p:nodes){
    //     cout<<p.first<<endl;
    // }
    return 0;
}