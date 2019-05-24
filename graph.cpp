/** @file graph.cpp
 * An adjacency list representation of an undirected weighted graph.
*/

#include "graph.h"
/*Do not add new libraries or files*/

class comparator
{
public:
    int operator() (const pair<string, int>& p1, const pair<string, int>& p2)
    {
        return p1.second > p2.second;
    }
};

Graph::Graph()
{
}  // end constructor

void Graph::addAirport(const string& airportName)
{  
    if (adjList.count(airportName) <= 0) {
        list<node> newList;
        adjList.insert(std::pair<string, list<node>>(airportName, newList));
    }
}  // end addPerformer

void Graph::addConnection(const string& airport1, const string& airport2, int numOfPassengers)
{   
    node n1;
    n1.airportName = airport2;
    n1.numOfPassengers = numOfPassengers;

    if (adjList.count(airport1) > 0) {
        adjList[airport1].push_back(n1);
    }

    node n2;
    n2.airportName = airport1;
    n2.numOfPassengers = numOfPassengers;

    if (adjList.count(airport2) > 0) {
        adjList[airport2].push_back(n2);
    }
}  // end addConnection

list<string> Graph::getAdjacentAirports(const string& airportName)
{  
    list<string> li;

    if (adjList.count(airportName) > 0) {
        list<node> nodeList = adjList[airportName];
        while (!nodeList.empty()) {
            node n = nodeList.front();
            nodeList.pop_front();
            li.push_back(n.airportName);
        }
    }
    return li;

}  // end getAdjacentAirports

int Graph::getTotalPassengers(const string& airportName)
{  
    int passNum = 0;

    if (adjList.count(airportName) > 0) {
        list<node> nodeList = adjList[airportName];
        while (!nodeList.empty()) {
            node n = nodeList.front();
            nodeList.pop_front();
            passNum += n.numOfPassengers;
        }
    }
    return passNum;
}  // end getTotalPassengers


list<string> Graph::findShortestPath(const string& airport1, const string& airport2)
{   
    list<string> li;
    
    queue<string> q;
    map<string,bool> visited;
    map<string, string> predec;
    
    for (auto const& x: adjList){
        visited[x.first] = false;
        predec[x.first] = "";
    }

    visited[airport1] = true;
    q.push(airport1);

    while (!q.empty()) {
        string temp = q.front();
        q.pop();

        for (auto const& y : adjList[temp]) {
            if (visited[y.airportName] == false) {
                visited[y.airportName] = true;
                predec[y.airportName] = temp;
                q.push(y.airportName);

                if (y.airportName == airport2) {
                    break;
                }
            }
        }
    }

    string begin = predec[airport2];
    li.push_front(airport2);
   while (begin != airport1) {
        li.push_front(begin);
        begin = predec[begin];
    }
   li.push_front(airport1);

    return li;
}  // end findShortestPath

list< pair<string, string> > Graph::findMST()
{   
    list<pair<string,string>> li;

    map<string, string> parent;
    map<string, int> key;
    map<string, bool> inMST;

    priority_queue <pair<string,int>, vector<pair<string, int>>, comparator> pq;

    string src = adjList.begin()->first;
    pair<string, int> temp;
    temp.first = src;
    temp.second = 0;
    pq.push(temp);

    string prev = src;
    key[src] = 2147483647;
    while (!pq.empty()) {
        string u = pq.top().first;
        pq.pop();

        inMST[u] = true;
        if (adjList[u].size() < 0) {
            u = prev;
        }
        prev = u;
        
        int min = 2147483647;
        string next = "";

        for (auto& v: adjList[u]) {
            string name = v.airportName;
            int weight = v.numOfPassengers;
            if (inMST[name] == false && weight < min) {
                min = weight;
                next = name;

                key[name] = weight;
                pair<string, int> loopTemp;
                loopTemp.first = name;
                loopTemp.second = key[name];
                pq.push(loopTemp);

                parent[name] = u;

            }
        }
    }

    for (auto &x: parent) {
        pair<string, string> temp;
        temp.first = x.second;
        temp.second = x.first;
        li.push_back(temp);
    }

    return li;
}  // end findMST

void Graph::deleteAirport(const string& airportName)
{  
    adjList.erase(airportName);
    for (auto& i : adjList) {
        list<node> temp = i.second;
        list<node> newList;
        for (auto const& x : temp){
            if (x.airportName != airportName) {
                newList.push_back(x);
            }
        }
        i.second = newList;
    }
}  // end deleteAirport

