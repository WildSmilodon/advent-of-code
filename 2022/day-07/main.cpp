
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cstring>

using namespace std;



size_t split(const std::string &txt, std::vector<std::string> &strs, char ch)
{
    size_t pos = txt.find( ch );
    size_t initialPos = 0;
    strs.clear();

    // Decompose statement
    while( pos != std::string::npos ) {
        strs.push_back( txt.substr( initialPos, pos - initialPos ) );
        initialPos = pos + 1;

        pos = txt.find( ch, initialPos );
    }

    // Add the last one
    strs.push_back( txt.substr( initialPos, std::min( pos, txt.size() ) - initialPos + 1 ) );

    return strs.size();
}


class File {
public:
    string name;
    int size;
};

class Folder {
public:
    string name;
    vector<File> files;
    int parent;
    vector<int> children;
    int totalSize;
};

int main()
{

    vector<Folder> tree;


    string line;
    ifstream myfile; 
    myfile.open("input.txt");

    getline (myfile,line); // skip $ cd /
    Folder f;
    f.name = "/";
    f.parent = -1;
    tree.push_back(f);
    int currentFolder = 0; // id of folder I am currently in.    

    while ( getline (myfile,line) ) {
       
        vector<string> s;
        split(line,s,' ');

        if (s[0] == "$") {
            if (s[1] == "cd") {
                if (s[2] == "..") {
                    currentFolder = tree[currentFolder].parent;
                } else {
                  //  cerr << " cd " << s[2] << endl;
                    for (int child : tree[currentFolder].children ) {                    
                        if (tree[child].name == s[2]) { currentFolder = child;}
                    }
                }
            } else { // ls
            }
        } else if (s[0] == "dir") {
            Folder f;
            f.name = s[1];
            f.parent = currentFolder;
            tree.push_back(f);
            tree[currentFolder].children.push_back(tree.size()-1);
        } else {
            File f;
            f.size = stoi(s[0]);
            f.name = s[1];
            tree[currentFolder].files.push_back(f);
        }

    }

    myfile.close();

    // find total size - do BFS from each node in tree
    vector<int> q;
    for (int me = 0; me < tree.size(); me++) {
        q.clear();
        q.push_back(me);
        int c = 0;

        int ts = 0;
        while ( c < q.size() ) {
            // add all children to the queue
            for (int child : tree[q[c]].children) {
                q.push_back(child);
            }
            // sum up all file sizes
            for (File f : tree[q[c]].files) {
                ts = ts + f.size;
            }
            c++;
        }
        tree[me].totalSize = ts;
    }

    int part1 = 0;
    for (Folder f : tree) {
        if ( f.totalSize <= 100000) { part1 += f.totalSize;}
    }
    cout << part1 << endl;

    
    int totSpace = 70000000;
    int unused = totSpace - tree[0].totalSize;
    int target = 30000000;
    int freeUp = target - unused;
    int part2 = 0;

    int maxD = 1000000000;
    for (Folder f : tree) {
        if ( f.totalSize >= freeUp &&  f.totalSize - freeUp < maxD ) { maxD =  - freeUp + f.totalSize; part2 = f.totalSize; }
    }
    cout << part2 << endl;




}






