
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


void addSignalStrength(int& ss, int cycle, int x) {
    if (cycle == 20 || cycle == 60 || cycle == 100 || cycle == 140 || cycle == 180 || cycle == 220 ) {
        ss = ss + cycle * x;
    }
}

int main()
{

    string line;
    ifstream myfile; 

    myfile.open("input.txt");

    int cycle = 0;
    int x = 1;
    int signalStrength = 0;
    int v = 0;

    while ( getline (myfile,line) ) {

        vector<string> s;
        split(line,s,' ');
        string cmd = s[0];
        if (cmd == "addx") { v = stoi(s[1]); }

        // During cycle
        cycle++;
        addSignalStrength(signalStrength,cycle,x);
        int currentPixel = (cycle-1) % 40;
        if (x-1 <= currentPixel && x+1 >= currentPixel) {cout << "#";} else {cout << " ";}
        if (cycle % 40 == 0) { cout << endl;}

        // Afer cycle
        if (cmd == "noop") {}
        if (cmd == "addx") {
                cycle++;
                addSignalStrength(signalStrength,cycle,x);
                int currentPixel = (cycle-1) % 40;
                if (x-1 <= currentPixel && x+1 >= currentPixel) {cout << "#";} else {cout << " ";}
                if (cycle % 40 == 0) { cout << endl;}
                x += v;
            }

    }

    myfile.close();

}






