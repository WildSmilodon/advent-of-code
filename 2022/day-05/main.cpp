
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



int main()
{

    string line;
    ifstream myfile; 
    myfile.open("input.txt");

    getline (myfile,line); int maxHeight = stoi(line);
    getline (myfile,line); int nStacks = stoi(line);


    vector<string> stacks[nStacks];

    for (int i = 0; i<maxHeight; i++) {
        getline (myfile,line);
        vector<string> s;
        split(line,s,' ');

        for (int j = 0; j<nStacks; j++) {
            if (s[j] != "-" ) {
                stacks[j].insert(stacks[j].begin(),s[j]);
                //stacks[j].push_back(s[j]);
            }
        }
    
    }

    while ( getline (myfile,line) ) {

        vector<string> s;
        split(line,s,' ');

        int n = stoi(s[1]);
        int from = stoi(s[3])-1;
        int to = stoi(s[5])-1;

// PART 1       
//        for (int i = 0; i<n; i++) {
//            stacks[to].push_back(stacks[from].back());
//            stacks[from].pop_back();
//        }


// PART 2
        vector<string> tmp;
        for (int i = 0; i<n; i++) {
            tmp.push_back(stacks[from].back());
            stacks[from].pop_back();
        }        
        for (int i = tmp.size()-1 ; i>-1 ; i-- ) {
            stacks[to].push_back(tmp[i]);
        }        
        tmp.clear();

    }

    myfile.close();

    string s  = "";
    for (int j = 0; j<nStacks; j++) {
        s = s + stacks[j].back();
    }

    cout << s << endl;



}






