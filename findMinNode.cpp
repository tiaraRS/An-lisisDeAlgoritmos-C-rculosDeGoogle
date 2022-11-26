#include <iostream>
#include <fstream>
#include <dirent.h>
#include <sys/types.h>
#include <string>
#include <unordered_map>
using namespace std;

void readNodesFile(string fileName, unordered_map<string,int>& nodes, int& counter){
    ifstream infile;
    infile.open("gplus/"+fileName);
    cout << "Reading "+fileName<<endl;
    string id1, id2;
    while(infile >> id1 >> id2){
        counter = nodes.size();
        nodes.insert({ id1, counter});
        counter = nodes.size();
        nodes.insert({ id2, counter });
    }
    counter++;
}


int main(){
    unordered_map<string,int> nodes;
    int counter = 0;
    DIR *dr;
    struct dirent *en;
    dr = opendir("./gplus"); //open all directory
    if (dr) {
        while ((en = readdir(dr)) != NULL) {
            string fileName = en->d_name;
            int dotPosition = fileName.find(".");
            string extension = fileName.substr(dotPosition+1);
            if(extension=="edges"){
                string nodeId = fileName.substr(0,dotPosition);
                nodes.insert({ nodeId, counter });
                readNodesFile(fileName,nodes,counter);
            }
        }
        closedir(dr); //close all directory
        cout << counter;
    }
    // for(auto p:nodes){
    //     cout<<p.first<<endl;
    // }
    return 0;
}