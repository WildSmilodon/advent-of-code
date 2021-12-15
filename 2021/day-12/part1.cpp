
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

    Node(string n) {
        name = n;
        links.clear();
        done = false;
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
            cerr << n.name << " " << n.onlyOnce << " links: ";
            for (int l : n.links) { cerr << nodes[l].name << " "; }
            cerr << endl;
            i++;
        }        
    }

};


void countPaths(vector<Node> nodes, int current, string previous, string end, int &nPaths) {
    
    cerr << "curr " << nodes[current].name << endl;
    if (nodes[current].onlyOnce) { nodes[current].done = true; }

    if (nodes[current].name == end ) {
        nPaths++;
        cerr << nPaths << endl;
    } else {
        for (int l : nodes[current].links) {              // lahko gre nazaj, če A    
            if (!nodes[l].done ) {//& nodes[l].name != previous) { 
                cerr << "curr " << nodes[current].name << " link " << nodes[l].name <<endl;
                countPaths(nodes,l,nodes[current].name,end,nPaths); 
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

    int nPaths = 0;
    int i = 0;
    for (Node n : tree.nodes) {
       if (n.name == "start") { countPaths(tree.nodes,i,"fake","end",nPaths); }
       i++;
    }


}
