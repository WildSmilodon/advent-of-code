
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

bool isCapital(string xx)
{
    char x = xx[0];
    int storeAscii=x;
    if (storeAscii>=65 && storeAscii<=90) { return true; } else { return false; }
}


class Node {
public:
    string name;
    vector<int> links;
    bool onlyOnce;
    bool done;
    int nVisits;

    Node(string n) {
        name = n;
        links.clear();
        done = false;
        nVisits = 0;
        if (isCapital(name.substr(0,1))) {
            onlyOnce = false;
        } else { onlyOnce = true;}
    }

};

class Tree {
public:
    vector<Node> nodes;

    void addLink(string n1, string n2) {
        int i1;
        int i2;
        for (int i = 0; i<nodes.size(); i++) {
            if (nodes[i].name == n1) { i1=i; }
            if (nodes[i].name == n2) { i2=i; }
        }
        nodes[i1].links.push_back(i2);
        nodes[i2].links.push_back(i1);
    }

    void addNode(Node node) {
        bool isNew = true;
        for (Node n: nodes) {
            if (n.name == node.name) { isNew = false;}
        }
        if (isNew) { nodes.push_back(node); }
    }

    void print() {
        int i = 0;
        for (Node n : nodes) {
              cout << n.name << " " << n.onlyOnce << " links: ";
            for (int l : n.links) {   cout << nodes[l].name << " "; }
              cout << endl;
            i++;
        }        
    }

};


void  countPaths(vector<Node> nodes, int current, string end, int &nPaths, int limit, vector<string> path) {
    
    nodes[current].nVisits++;
    path.push_back(nodes[current].name);

    if (nodes[current].onlyOnce & nodes[current].nVisits > limit ) { 
        nodes[current].done = true; 
        limit = 0; 
        for (Node &n : nodes) {
            if (n.onlyOnce & n.nVisits > limit ) {  n.done = true; } 
        }
    }

    if (nodes[current].name == end ) {
        nPaths++;
        cout << nPaths<<" ";

        for (string s : path) {
            cout << s << " ";
        }
        cout << endl;
    } else {
        for (int l : nodes[current].links) {      
            if (!nodes[l].done & nodes[l].name != "start" ) {
                 countPaths(nodes,l,end,nPaths,limit,path); 
            }               
        }
    }
    
}

int main()
{

    int nLines = 24; //18; //S10; //7;
    Tree tree;

    for (int r = 0; r<nLines; r++) {
        string s;
        string e;
        cin >> s >> e;  cin.ignore();
        tree.addNode(Node(s));
        tree.addNode(Node(e));
        tree.addLink(s,e);
    }

    tree.print();

    vector<string> path;
    int nPaths = 0;
    int i = 0;
    int limit = 1;
    for (Node n : tree.nodes) {
       if (n.name == "start") {  countPaths(tree.nodes,i,"end",nPaths,limit,path); }
       i++;
    }


}
