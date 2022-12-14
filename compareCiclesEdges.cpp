#include <bits/stdc++.h>
#include <dirent.h>

using namespace std;

void getSetOfIdsEdge(string filename, set<string> &edgesIds)
{
    ifstream infile;
    infile.open("gplus/" + filename);

    int dotPosition = filename.find(".");
    string nodeId = filename.substr(0, dotPosition);

    edgesIds.insert(nodeId);

    string id1Str, id2Str;
    while (infile >> id1Str >> id2Str)
    {
        edgesIds.insert(id1Str);
        edgesIds.insert(id2Str);
    }
}

void getSetOfIdsCicrles(string filename, set<string> &circlesIds)
{
    ifstream infile;
    infile.open("gplus/" + filename);
    printf("Reading %s ... \r", filename.c_str());

    int dotPosition = filename.find(".");
    string nodeId = filename.substr(0, dotPosition);

    circlesIds.insert(nodeId);

    string idStr;
    while (infile >> idStr)
    {
        // Para distinguir los ids de los nodos "12325123541" de los identificadores de circulos "Afse42we2"
        if (idStr.size() > 11)
        {
            circlesIds.insert(idStr);
        }
    }
    infile.close();
}

bool checkIfSetIsSubset(set<string> subset, set<string> set)
{
    return includes(set.begin(), set.end(), subset.begin(), subset.end());
}

void getAllIds()
{
    set<string> edgesIds;
    set<string> circlesIds;
    DIR *dr;
    struct dirent *en;
    dr = opendir("./gplus");
    if (dr)
    {
        cout << endl
             << "Reading nodes" << endl;
        while ((en = readdir(dr)) != NULL)
        {
            string fileName = en->d_name;
            int dotPosition = fileName.find(".");
            string extension = fileName.substr(dotPosition + 1);
            if (extension == "edges")
            {
                getSetOfIdsEdge(fileName, edgesIds);
            }
            if (extension == "circles")
            {
                getSetOfIdsCicrles(fileName, circlesIds);
            }
        }
    }
    closedir(dr); // close all directory

    cout << "Hay " << circlesIds.size() << " nodos en los archivos .circles" << endl;
    cout << "Hay " << edgesIds.size() << " nodos en los archivos .edges" << endl;

    if (checkIfSetIsSubset(circlesIds, edgesIds))
    {
        cout << "todos los ids de nodos en los archivos .circles aparecen en los archivos .edges" << endl;
    }
    else
    {
        cout << "NO todos los ids de nodos en los archivos .circles aparecen en los archivos .edges" << endl;
    }
}

int main()
{
    getAllIds();
}