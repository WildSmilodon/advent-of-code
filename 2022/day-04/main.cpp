
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

    int totalOverlap = 0;
    int totalOverlap2 = 0;

    while ( getline (myfile,line) ) {

        vector<string> s;
        split(line,s,',');

        vector<string> ss;
        split(s[0],ss,'-');
        int elf1left = stoi(ss[0]);
        int elf1right = stoi(ss[1]);

        split(s[1],ss,'-');
        int elf2left = stoi(ss[0]);
        int elf2right = stoi(ss[1]);

        bool overlap = false;

        if ( elf1left <= elf2left && elf1right >= elf2right ) { overlap = true; }
        if ( elf1left >= elf2left && elf1right <= elf2right ) { overlap = true; }

        if (overlap) { totalOverlap++; }

        overlap = false;

        if ( elf1left <= elf2left && elf2left <= elf1right ) { overlap = true; }
        if ( elf1left <= elf2right && elf2right <= elf1right ) { overlap = true; }


        if ( elf2left <= elf1left && elf1left <= elf2right ) { overlap = true; }
        if ( elf2left <= elf1right && elf1right <= elf2right ) { overlap = true; }

        if (overlap) { totalOverlap2++; }

    }

    myfile.close();

    cout << totalOverlap << endl;
    cout << totalOverlap2 << endl;


}






