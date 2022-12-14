#include <set>
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>
#include <climits>
#include <chrono>
#include "createGraph.h"
using namespace std;

struct classcomp {
  bool operator() (const pair<int,int>& lhs, const pair<int,int>& rhs) const
  {return lhs.second < rhs.second;}
  //{return (lhs.first < rhs.first || lhs.second < rhs.second);}
  //{return (lhs.first == rhs.first  && lhs.second > rhs.second) || (lhs.first != rhs.first && lhs.second <= rhs.second) ;}
  //insertar si son diferentes
}myobject;

// struct myclass {
//   bool operator() (const pair<int,vector<int>> &a, const pair<int,vector<int>> &b) 
//   { return (a.firs<b.first);}
// } myobject;

bool myfunction (const pair<int,int>& a, const pair<int,int>& b) { 
    bool ans = false;
    if ( a.second > b.second){
        ans = true;
    }
    return ans;
}


void checkMapSorted(){
    vector<pair<int,int>> u;
    u.push_back({1,9});
    u.push_back({3,3});
    u.push_back({2,2});
    u.push_back({5,2});
    u.push_back({1,2});
    sort(u.begin(),u.end(),myfunction);
    cout<<"min "<< u.back().first <<endl;
    u.pop_back();
    for(auto el:u){
        cout << el.first << " ";
    }
    cout << endl;
}

// void checkInsertSorted(){
//     set<pair<int,int>,classcomp> u;
//     u.insert({3,8});
//     u.insert({2,9});
//     u.insert({5,5});
//     u.insert({4,2});
//     u.insert({1,2});
//     pair<int,int> p = {6,2};
//     u.insert(p);
//     auto it = u.find(p);
//     u.erase(it);
//     for(auto el:u){
//         cout<<el.first<<" ";
//     }

//     set<int> v;
//     v.insert(3);
//     v.insert(2);
//     v.insert(5);
//     v.insert(4);
//     v.insert(1);
//     v.insert(6);
//     v.erase(6);
//     cout<<endl<<"v"<<endl;
//     for(auto el:v){
//         cout<<el<<" ";
//     }
//     //expected: 4 3 5 
//     //got: 4 5 3 2
// }

// void checkIntersection(){
//     vector<int> viAdj = {1,2,3,4,5};
//     set<int> intersect;
//     set<int> u = {3,4,5,6,8};
//     set<int> nvi(viAdj.begin(),viAdj.end());
//     set_intersection(u.begin(), u.end(), nvi.begin(), nvi.end(),
//         std::inserter(intersect, intersect.begin()));
//     for(auto el:intersect){
//         cout<<el<<" ";
//     }
// }
// void checkIntersectionFail(){
//     vector<int> viAdj = {1,2,3,4,5};
//     set<int> intersect;
//     set<int> u = {6,8};
//     set<int> nvi(viAdj.begin(),viAdj.end());
//     set_intersection(u.begin(), u.end(), nvi.begin(), nvi.end(),
//         std::inserter(intersect, intersect.begin()));
//     cout << intersect.empty() <<endl;
//     cout << intersect.size() <<endl;
//     for(auto el:intersect){
//         cout<<el<<" ";
//     }
// }

int main(){
    checkMapSorted();
    return 0;
}